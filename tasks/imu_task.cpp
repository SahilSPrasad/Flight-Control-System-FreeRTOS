//C
#include <stdio.h>

//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//FCS
#include "imu_driver.h"


static QueueHandle_t imuQueue = xQueueCreate(10, sizeof(unsigned long));

void imuTask(void* pvParameters)
{
    (void)pvParameters;
    
    for (;;)
    {
        imuData data = readImu();
        printf("a: %f %f %f \n", data.ax, data.ay, data.az);
        printf("g: %f %f %f \n\n", data.gx, data.gy, data.gz);

        xQueueSend(imuQueue, (void*) &data, (TickType_t) 10);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
