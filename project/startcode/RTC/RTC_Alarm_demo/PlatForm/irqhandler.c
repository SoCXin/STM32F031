#include "irqhandler.h"
#include "lib_wdt.h"
#include "systick.h"
#include "lib_rtc.h"

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
    TimingDelay_Decrement();
}

/*********************************************************
函数名: void T16N3_IRQHandler(void)
描  述: T16N3定时中断函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N3_IRQHandler(void)
{
    if (T16Nx_GetFlagStatus(T16N3, T16Nx_IT_MAT0) != RESET)
    {
        T16Nx_ClearITPendingBit(T16N3, T16Nx_IT_MAT0);
        g_2ms_flag = 1;

        g_10ms_cnt++;

        if (g_10ms_cnt >= 5)
        {
            g_10ms_cnt = 0;
            g_10ms_flag = 1;
        }

        g_500ms_cnt++;

        if (g_500ms_cnt >= 250)
        {
            g_500ms_cnt = 0;
            g_500ms_flag = 1;
        }
    }

    return;
}

uint32_t SecondCount = 0;
uint32_t MinuteCount = 0;
uint32_t HourCount = 0;
uint32_t DayCount = 0;
uint32_t MonthCount = 0;
/*********************************************************
函数名: void RTC_IRQHandler(void)
描  述: 实时时钟中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void RTC_IRQHandler(void)
{
    if (RTC_GetFlagStatus(RTC_Interrupt_Source_DayALE) != RESET
            && RTC_GetITStatus(RTC_Interrupt_Source_DayALE) != RESET)   //多个中断源时，需同时判断IE和IF
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_DayALE);    //清中断标识
        g_day_flag = 1;
    }

    if (RTC_GetFlagStatus(RTC_Interrupt_Source_WeekALE) != RESET
            && RTC_GetITStatus(RTC_Interrupt_Source_WeekALE) != RESET)   //多个中断源时，需同时判断IE和IF
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_WeekALE);    //清中断标识
        g_week_flag = 1;
    }
}

