//C
#include <stdio.h>

//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//FCS
#include "imu_task.h"
#include "imu_driver.h"



extern QueueHandle_t imuQueue;
void imuTask(void* pvParameters)
{
 
    for (;;)
    {
        imuData data = readImu();
        //printf("a: %f %f %f \n", data.ax, data.ay, data.az);
        //printf("g: %f %f %f \n\n", data.gx, data.gy, data.gz);
  
        
        if (xQueueSend(imuQueue, &data, (TickType_t)10) != pdPASS) {
			printf("IMU queue full!\n");
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
