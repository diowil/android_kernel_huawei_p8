
/*lint --e{537} */
#include <stdio.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_spinlock.h>

#include <bsp_om.h>
#include <bsp_memmap.h>
#include <bsp_hardtimer.h>
#include <bsp_hw_spinlock.h>

#include <product_config.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_HW_SPINLOCK

#define HW_SPINLOCK_MODEM_ID            (0x05U)
#define HW_SPINLOCK_MASTER_ID           (HW_SPINLOCK_MODEM_ID)
#define HW_SPINLOCK_MODEM_LOCK_CMD      ((HW_SPINLOCK_MASTER_ID << 1U) | 0x01U)
#define HW_SPINLOCK_MODEM_UNLOCK_CMD    (HW_SPINLOCK_MODEM_LOCK_CMD)
#define HW_SPINLOCK_MODEM_ID_MASK       (0x0F)

#define HW_SPINLOCK_LOCK_ADDR(group)    (HI_PCTRL_REGBASE_ADDR + (((group) / 4 + 1) * 0x400) + (((group) % 4) * 0x0C))
#define HW_SPINLOCK_UNLOCK_ADDR(group)  (HI_PCTRL_REGBASE_ADDR + (((group) / 4 + 1) * 0x404) + (((group) % 4) * 0x0C))
#define HW_SPINLOCK_STATUS_ADDR(group)  (HI_PCTRL_REGBASE_ADDR + (((group) / 4 + 1) * 0x408) + (((group) % 4) * 0x0C))

#define HW_SPINLOCK_NUM_A_GROUP         (8)
#define HW_SPINLOCK_NUM_GROUPS          (8)
#define HW_SPINLOCK_ID_MAX              (HW_SPINLOCK_NUM_A_GROUP * HW_SPINLOCK_NUM_GROUPS)


static struct spinlock g_hw_spinlock;

int hwspin_trylock(u32 id)
{
    int ret = 0;
    u32 group = 0;
    u32 lock_index = 0;
    u32 value = 0;

    unsigned long irq_flags;

    if (id >= HW_SPINLOCK_ID_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HW_SPINLOCK, "[lock]spinlock id error: %d\n", id);
        return -1;
    }

    spin_lock_irqsave(&g_hw_spinlock, irq_flags);

    group = id / HW_SPINLOCK_NUM_A_GROUP;
    lock_index = id % HW_SPINLOCK_NUM_A_GROUP;

    writel(HW_SPINLOCK_MODEM_LOCK_CMD << (lock_index * 4), HW_SPINLOCK_LOCK_ADDR(group));
    value = (readl(HW_SPINLOCK_STATUS_ADDR(group)) >> (lock_index * 4)) & HW_SPINLOCK_MODEM_ID_MASK;

    ret = (value == HW_SPINLOCK_MODEM_LOCK_CMD) ? 0 : -1;

    spin_unlock_irqrestore(&g_hw_spinlock, irq_flags);

    return ret;
}

int hwspin_unlock(u32 id)
{
    u32 group = 0;
    u32 lock_index = 0;

    unsigned long irq_flags;

    if (id >= HW_SPINLOCK_ID_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HW_SPINLOCK, "[lock]spinlock id error: %d\n", id);
        return -1;
    }

    spin_lock_irqsave(&g_hw_spinlock, irq_flags);

    group = id / HW_SPINLOCK_NUM_A_GROUP;
    lock_index = id % HW_SPINLOCK_NUM_A_GROUP;

    writel(HW_SPINLOCK_MODEM_UNLOCK_CMD << (lock_index * 4), HW_SPINLOCK_UNLOCK_ADDR(group));

    spin_unlock_irqrestore(&g_hw_spinlock, irq_flags);

    return 0;
}

int hwspin_lock_timeout(u32 id, int time_us)
{
    int ret = 0;

    if (id >= HW_SPINLOCK_ID_MAX)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HW_SPINLOCK, "[lock]spinlock id error: %d\n", id);
        return -1;
    }

    for (;;)
    {
        /* Try to take the hwspinlock */
        ret = hwspin_trylock(id);
        if (ret == 0 || time_us == 0)
            break;

        /*
         * The lock is already taken, let's check if the user wants
         * us to try again
         */
        if (time_us != HW_SPINLOCK_WAIT_FOREVER)
        {
            time_us--;
            udelay(1);
        }
    }

    return ret;
}

void hwspinlock_init(void)
{
    u32 id = 0;

    spin_lock_init(&g_hw_spinlock);

    for (id = 0; id < HW_SPINLOCK_ID_MAX; id++)
    {
        (void)hwspin_unlock(id);
    }
}

#else

int hwspin_trylock(u32 id)
{
    return 0;
}

int hwspin_unlock(u32 id)
{
    return 0;
}

int hwspin_lock_timeout(u32 id, int time_us)
{
    return 0;
}

void hwspinlock_init(void)
{
}

#endif

#ifdef __cplusplus
}
#endif


