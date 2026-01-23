struct imuData {
	float ax, ay, az; //accelerometer
	float gx, gy, gz; //gyroscope
	float mx, my, mz; //magnetometer

};

imuData readImu();

