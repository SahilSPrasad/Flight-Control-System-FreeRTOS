#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H


struct imuData {
	float ax, ay, az; //accelerometer
	float gx, gy, gz; //gyroscope
	float mx, my, mz; //magnetometer

};

imuData readImu();

#endif // IMU_DRIVER_H