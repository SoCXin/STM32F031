#include "irqhandler.h"
#include "lib_wdt.h"
#include "lib_timer.h"

void NMI_IRQHandler(void)
{

}

void HardFault_IRQHandler(void)
{
    while (1);
}

void SVC_IRQHandler(void)
{

}

void PendSV_IRQHandler(void)
{

}

void SysTick_IRQHandler(void)
{

}

extern unsigned int Period;
extern unsigned int dutytab[6];
extern unsigned int dutyindex;
extern unsigned int dutyNext;

/*********************************************************
函数名: void T16N0_IRQHandler(void)
描  述: T16N0中断处理函数 1000us
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N0_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N0, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N0, T16Nx_IT_MAT0);

        if (dutyindex < 5)
            dutyindex++;
        else
            dutyindex = 0;

        T16Nx_SetMAT1(T16N0, dutytab[dutyindex]);

        if (dutytab[dutyindex] == 0)
            T16Nx_SetMAT1(T16N0, Period);

        if (dutyindex == 5)
            dutyNext = 0;
        else
            dutyNext = dutyindex + 1;

        if (dutytab[dutyNext] == 0)
            T16Nx_MAT0Out0Config(T16N0, T16Nx_Out_Low); //CNT0匹配到MAT1端口输出低
        else
            T16Nx_MAT0Out0Config(T16N0, T16Nx_Out_High); //CNT0匹配到MAT0端口输出高
    }
}
