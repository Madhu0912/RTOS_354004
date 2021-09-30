/*Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

TaskHandle_t t1_handle;
TaskHandle_t t2_handle;
TaskHandle_t t3_handle;
TimerHandle_t timer_handle;

void *const timer_id;
void call_back(TimerHandle_t xTimer);
void task1(void *data)
{
    while(1)
    {
        printf("task t1 started \n");
        //*code implementation*/
        printf("task t1 completed.\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void task2(void *data)
{
    while(1)
    {
        printf("task t2 started \n");
        //*code implementation*/
        printf("task t2 completed.\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
void task3(void *data)
{
    timer_handle = xTimerCreate("timer",(10000 / portTICK_PERIOD_MS),pdFALSE,timer_id,call_back);
    xTimerStart(timer_handle, 1);
    while (1)
    {
        printf("task t3 started \n");
        //*code implementation*/
        printf("task t3 completed.\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
void call_back(TimerHandle_t xTimer)
{
    printf("\nIn Callback Function\n");
}

void app_main(void)
{
    xTaskCreate(task1, "task_t1", 2048, NULL, 5, &t1_handle);
    xTaskCreate(task2, "task_t1", 2048, NULL, 4, &t2_handle);
    xTaskCreate(task3, "task_t1", 2048, NULL, 3, &t3_handle);
}