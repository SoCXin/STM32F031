/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  timer.h
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/28
*描  述:  Timer模块程序头文件
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "timer.h"

/*********************************************************
函数名: void T16N3Init(void)
描  述: T16N3定时器初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N3Init(void)
{
    T16Nx_BaseInitStruType x;

    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;                     //内部时钟PCLK
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_TC0;                      //定时器计数器模式
    x.T16Nx_PREMAT = 2;
    x.T16Nx_SYNC = Disable;
    T16Nx_BaseInit(T16N3, &x);                          //初始化定时器T16N3

    T16Nx_MAT0ITConfig(T16N3, T16Nx_Clr_Int);           //MAT0匹配设置
    T16Nx_SetCNT0(T16N3, 0);                            //设置T16N3初始值为0
    T16Nx_SetMAT0(T16N3, SystemCoreClock / 1000);       //设置T16N3MAT0值
    T16Nx_ITConfig(T16N3, T16Nx_IT_MAT0, Enable);       //使能T16N3匹配0中断
    NVIC_Init(NVIC_T16N3_IRQn, NVIC_Priority_1, Enable); //中断设置
    T16Nx_Enable(T16N3);

    return;
}

