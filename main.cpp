// RTOS FCS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//FreeRTOS includes
#include "FreeRTOS.h"

#include "task.h"
#include "queue.h"
#include "timers.h"

//FCS includes
#include "imu_driver.h"
#include "imu_task.h"
#include "fusion_task.h"
#include <queues.h>


QueueHandle_t imuQueue;

int main()
{
	imuQueue = xQueueCreate(10, sizeof(imuData));
    //if (imuQueue == NULL) {
    //    printf("Failed to create queue!\n");
    //    while (1);
    //}

    xTaskCreate(imuTask, "imuTask", 1000, NULL, 4, NULL);
    xTaskCreate(fusionTask, "fusionTask", 1000, NULL, 4, NULL);
    
    

    printf("Free heap: %zu bytes\n", xPortGetFreeHeapSize());



    vTaskStartScheduler();

    for (;;);
}



//Extra functions needed to compile
void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName) {
    printf("Stack overflow in task %s\n", pcTaskName);
    for (;;);
}
void vAssertCalled(const char* file, int line) {
    printf("ASSERT CALLED! file: %s  line: %ld", file, line);
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
   implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
   used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t** ppxTimerTaskTCBBuffer,
    StackType_t** ppxTimerTaskStackBuffer,
    configSTACK_DEPTH_TYPE* puxTimerTaskStackSize)
{
    /* If the buffers to be provided to the Idle task are declared inside this
       function then they must be declared static - otherwise they will be allocated on
       the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
       state will be stored. */
    *ppxTimerTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxTimerTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
       Note that, as the array is necessarily of type StackType_t,
       configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *puxTimerTaskStackSize = configMINIMAL_STACK_SIZE;
}

/*-----------------------------------------------------------*/

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
   application must provide an implementation of vApplicationGetTimerTaskMemory()
   to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t** ppxTimerTaskTCBBuffer,
    StackType_t** ppxTimerTaskStackBuffer,
    configSTACK_DEPTH_TYPE* puxTimerTaskStackSize)
{
    /* If the buffers to be provided to the Timer task are declared inside this
       function then they must be declared static - otherwise they will be allocated on
       the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
       task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
       Note that, as the array is necessarily of type StackType_t,
      configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *puxTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
