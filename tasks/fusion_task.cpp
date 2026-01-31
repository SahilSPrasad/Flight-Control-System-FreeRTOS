
//C
#include <stdio.h>

//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//FCS
#include "fusion_task.h"
#include "imu_driver.h"
#include "madgwick_filter.h"



extern QueueHandle_t imuQueue;


void fusionTask(void* pvParameters) {
    imuData imu;
    Quaternion q = initQuat(); //[1, 0, 0, 0] current estimated orientation
    
    for (;;) {


        if (xQueueReceive(imuQueue, &imu, (TickType_t)10) == pdPASS) {
            taskENTER_CRITICAL();
            printf("Fusion got IMU: ax=%f ay=%f az=%f gx=%f gy=%f gz=%f\n",
                imu.ax, imu.ay, imu.az,
                imu.gx, imu.gy, imu.gz);
            taskEXIT_CRITICAL();
		}



        vTaskDelay(pdMS_TO_TICKS(10)); // 100 Hz
    }
}
