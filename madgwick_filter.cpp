#include "madgwick_filter.h"
#include <cstdio>

Quaternion initQuat() {
	Quaternion init;
	init.q0 = 1;
	init.q1 = 0;
	init.q2 = 0;
	init.q3 = 0;
	return init;
}

//quat omega (0, gx, gy, gz)
Quaternion getWquat(float gx, float gy, float gz) {
	//q dot = w , gx, gy, gz
	Quaternion wQuat;

	wQuat.q0 = 0;
	wQuat.q1 = gx; //wx
	wQuat.q2 = gy; //wy
	wQuat.q3 = gz; //wz

	return wQuat;
}

void printQuat(Quaternion quat) {
	printf("q0: %f q1: %f q2: %f q3: %f", quat.q0, quat.q1, quat.q2, quat.q3);
}

//q⊗ω_quat
Quaternion calculateQdot(Quaternion current, Quaternion w_quat) {
	Quaternion qDot;

	qDot.q0 = -0.5 * (current.q1 * w_quat.q1 + current.q2 * w_quat.q2 + current.q3 * w_quat.q3);
	qDot.q1 =  0.5 * (current.q0 * w_quat.q1 + current.q2 * w_quat.q3 - current.q3 * w_quat.q2);
	qDot.q2 =  0.5 * (current.q0 * w_quat.q2 - current.q1 * w_quat.q3 + current.q3 * w_quat.q1);
	qDot.q3 =  0.5 * (current.q0 * w_quat.q1 + current.q2 * w_quat.q2 - current.q3 * w_quat.q3);

	return qDot;
}

//imuData given from the fusion_task once it's called by the RTOS
void computeMadgwick(imuData imu) {
	Quaternion q = initQuat(); //[1, 0, 0, 0]
	Quaternion w_quat = getWquat(imu.gx, imu.gz, imu.gy);

	Quaternion qDot = calculateQdot(q, w_quat);




}

