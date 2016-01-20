/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bsp_mailbox.h
  �� �� ��   : ����
  ��    ��   : ��ׯ�� 59026
  ��������   : 2012��12��17��
  ����޸�   :
  ��������   : mailbox ������ϵͳ�ڲ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��17��
    ��    ��   : ��ׯ�� 59026
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __BSP_MAILBOX_H__
#define __BSP_MAILBOX_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "drv_mailbox.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*����Զ�̵��÷�����*/
#define IFC_GEN_CALL0(id, name)       _IFC_GEN_CALLx(0, id, name)
#define IFC_GEN_CALL1(id, name, ...)  _IFC_GEN_CALLx(1, id, name, __VA_ARGS__)
#define IFC_GEN_CALL2(id, name, ...)  _IFC_GEN_CALLx(2, id, name, __VA_ARGS__)
#define IFC_GEN_CALL3(id, name, ...)  _IFC_GEN_CALLx(3, id, name, __VA_ARGS__)
#define IFC_GEN_CALL4(id, name, ...)  _IFC_GEN_CALLx(4, id, name, __VA_ARGS__)
#define IFC_GEN_CALL5(id, name, ...)  _IFC_GEN_CALLx(5, id, name, __VA_ARGS__)
#define IFC_GEN_CALL6(id, name, ...)  _IFC_GEN_CALLx(6, id, name, __VA_ARGS__)

/*���ɴ�����������Զ�̵���ִ�к���*/
/*ע��ִ�к���name�������з���ֵ��(������void�ͣ�������벻��)*/
#define IFC_GEN_EXEC0(name)      __IFC_GEN_EXECx(0, name)
#define IFC_GEN_EXEC1(name, ...) __IFC_GEN_EXECx(1, name, __VA_ARGS__)
#define IFC_GEN_EXEC2(name, ...) __IFC_GEN_EXECx(2, name, __VA_ARGS__)
#define IFC_GEN_EXEC3(name, ...) __IFC_GEN_EXECx(3, name, __VA_ARGS__)
#define IFC_GEN_EXEC4(name, ...) __IFC_GEN_EXECx(4, name, __VA_ARGS__)
#define IFC_GEN_EXEC5(name, ...) __IFC_GEN_EXECx(5, name, __VA_ARGS__)
#define IFC_GEN_EXEC6(name, ...) __IFC_GEN_EXECx(6, name, __VA_ARGS__)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


/*****************************************************************************
  7 UNION����
*****************************************************************************/

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

/*ע��Զ�̵���ִ�к���*/
#define mailbox_ifc_register(id, name) mailbox_ifc_register_exec(id ,IFC_GEN_EXEC_NAME(name))

#define IFC_REG_EXEC(id, name) mailbox_ifc_register(id, name)
unsigned int mailbox_init(void);



unsigned int mailbox_send_msg(
                unsigned int            mailcode,
                void                    *data,
                unsigned int            length);


unsigned int  mailbox_reg_msg_cb(
                unsigned int             mailcode,
                mb_msg_cb                 func,
                void                     *data);


unsigned int mailbox_read_msg_data(
                void                   *MailHandle,
                 char                 *pData,
                unsigned int          *pSize);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of bsp_mailbox.h */
