//The goal of this driver is the simulate readings from an IMU234234
#include "imu_driver.h"
#include <cstdlib>
#include <ctime>

imuData readImu() {
	//create a imuData object
	//define it random numbers for the imu readings
	imuData data;

    data.ax = (rand() % 2000 - 1000) / 1000.0f;; // Random value between -10 and 10
    data.ay = (rand() % 2000 - 1000) / 1000.0f;
    data.az = 1.0f; // Simulating gravity
    data.gx = (rand() % 2000 - 1000) / 1000.0f;
    data.gy = (rand() % 2000 - 1000) / 1000.0f;
    data.gz = (rand() % 2000 - 1000) / 1000.0f;


    return data;
}

/*
| Variable | Randomized range | Meaning (physical)                                  |
| -------- | ---------------- | --------------------------------------------------- |
| `ax` | -1.0 → 1.0 g     | Forward/backward acceleration (tilt)                |
| `ay` | -1.0 → 1.0 g     | Left/right acceleration (tilt)                      |
| `az` | 1.0 g            | Up/down acceleration (gravity only, for simplicity) |
| `gx`  | -10 → 10 °/s     | Roll rate (tilting left/right)                      |
| `gy`  | -10 → 10 °/s     | Pitch rate (tilting forward/backward)               |
| `gz`  | -10 → 10 °/s     | Yaw rate (rotating clockwise/counterclockwise)      |
*/