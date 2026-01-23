#include <cstdlib>
#include <imu_driver.h>

struct Quaternion {
	float q0;
	float q1;
	float q2;
	float q3;
};

Quaternion initQuat();
Quaternion getWquat(float gx, float gy, float gz);
void printQuat(Quaternion quat);
Quaternion calculateQdot(Quaternion current, Quaternion w_quat);
void computeMadgwick(imuData imu);

//q: where you're currently oriented
//w_quat: how fast you're rotating right now, (gyroscope - angular velocity)
//q⊗ω_quat: how that rotation changes your current orientation
//
//step 1
//take the gyroscope data from the imu and create the w quaternion
// 
// step 2
//once we get the w quarternion we use the initial quaternion and 
//use the angular velocity formula to compute quaternion kinematics q̇ - time derivate of the quaternion
// q̇ = current orientation quaternion

//step 3 gradient decent step?

