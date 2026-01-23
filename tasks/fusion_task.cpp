//void fusion_task(void *pvParameters) {
//    imu_data_t imuSample;
//    while(1) {
//        // Wait for new IMU data
//        if(xQueueReceive(imuQueue, &imuSample, portMAX_DELAY) == pdPASS) {
//
//            // Call your filter: Madgwick or Kalman
//            madgwick_update(imuSample.gx, imuSample.gy, imuSample.gz,
//                            imuSample.ax, imuSample.ay, imuSample.az,
//                            imuSample.mx, imuSample.my, imuSample.mz);
//
//            // Store result in shared struct for control task
//            xSemaphoreTake(fusedDataMutex, portMAX_DELAY);
//            fusedData.roll  = madgwick_roll;
//            fusedData.pitch = madgwick_pitch;
//            fusedData.yaw   = madgwick_yaw;
//            xSemaphoreGive(fusedDataMutex);
//        }
//    }
//}
