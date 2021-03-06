/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  servSoftTimer.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.11.11;
历史版本:  无;
*********************************************************************************************/
#ifndef __SERV_SOFT_TIMER_H
#define __SERV_SOFT_TIMER_H



/******************************************包含文件*******************************************/
#include "comDatatype.h"
#include "comStruct.h"
#include "comEnum.h"
#include "comDebug.h"



/****************************************外部变量声明*****************************************/



/*******************************************宏定义********************************************/



/***************************************常数和类型声明****************************************/



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void servStimerInit(SoftTimerStruct *pSoftTimer, u16 interval, TimeOutFunc pTimerOutFunc);
void servStimerExamine(SoftTimerStruct * ptSoftTimer, void *timeOutPara);
void servStimerAdd(SoftTimerStruct *ptSoftTimer);
void servStimerDelete(SoftTimerStruct *ptSoftTimer);
void servStimerAllInit(void);
void servStimerManage(SoftTimerStateStruct softTimer);
void servSoftDelayMs(u32 delayMs);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/