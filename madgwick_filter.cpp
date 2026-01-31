#include "madgwick_filter.h"
#include <cstdio>
#include <cmath>

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

void normalizeQuat(Quaternion& q) {
	float norm = std::sqrt(q.q0 * q.q0 + q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3);
	q.q0 /= norm;
	q.q1 /= norm;
	q.q2 /= norm;
	q.q3 /= norm;
}

void quatToEuler(const Quaternion& q, float& roll, float& pitch, float& yaw) {
    // roll (x-axis rotation)
    roll = atan2(2.0f * (q.q0 * q.q1 + q.q2 * q.q3), 1.0f - 2.0f * (q.q1 * q.q1 + q.q2 * q.q2));
    // pitch (y-axis rotation)
    pitch = asin(2.0f * (q.q0 * q.q2 - q.q3 * q.q1));
    // yaw (z-axis rotation)
    yaw = atan2(2.0f * (q.q0 * q.q3 + q.q1 * q.q2), 1.0f - 2.0f * (q.q2 * q.q2 + q.q3 * q.q3));
}



//imuData given from the fusion_task once it's called by the RTOS
void computeMadgwick(imuData imu, Quaternion &q) {
	Quaternion w_quat = getWquat(imu.gx, imu.gy, imu.gz);

	Quaternion qDot = calculateQdot(q, w_quat);

    // 3. Accelerometer correction
   // normalize accelerometer
    float normAcc = std::sqrt(imu.ax * imu.ax + imu.ay * imu.ay + imu.az * imu.az);

    //if (normAcc == 0) return; // avoid division by zero
    float ax = imu.ax / normAcc;
    float ay = imu.ay / normAcc;
    float az = imu.az / normAcc;

    // Gradient descent algorithm corrective step
    float f1 = 2 * (q.q1 * q.q3 - q.q0 * q.q2) - ax;
    float f2 = 2 * (q.q0 * q.q1 + q.q2 * q.q3) - ay;
    float f3 = 2 * (0.5 - q.q1 * q.q1 - q.q2 * q.q2) - az;

    float J_11or24 = 2 * q.q2;
    float J_12or23 = 2 * q.q3;
    float J_13or22 = 2 * q.q0;
    float J_14or21 = 2 * q.q1;
    float J_32 = 2 * J_14or21;
    float J_33 = 2 * J_11or24;

    // Compute gradient (simplified)
    Quaternion grad;
    grad.q0 = J_14or21 * f2 - J_12or23 * f1;
    grad.q1 = J_13or22 * f1 + J_11or24 * f3 - J_14or21 * f2;
    grad.q2 = J_13or22 * f2 - J_32 * f3 - J_11or24 * f1;
    grad.q3 = J_12or23 * f2 + J_33 * f3;

    // normalize gradient
    float normGrad = std::sqrt(grad.q0 * grad.q0 + grad.q1 * grad.q1 + grad.q2 * grad.q2 + grad.q3 * grad.q3);
    grad.q0 /= normGrad;
    grad.q1 /= normGrad;
    grad.q2 /= normGrad;
    grad.q3 /= normGrad;

    // 4. Apply correction
    qDot.q0 -= beta * grad.q0;
    qDot.q1 -= beta * grad.q1;
    qDot.q2 -= beta * grad.q2;
    qDot.q3 -= beta * grad.q3;

    // 5. Integrate to get new quaternion
    q.q0 += qDot.q0 * dt;
    q.q1 += qDot.q1 * dt;
    q.q2 += qDot.q2 * dt;
    q.q3 += qDot.q3 * dt;

    // 6. Normalize
    normalizeQuat(q);
    printf("qDot: %f %f %f %f\n", qDot.q0, qDot.q1, qDot.q2, qDot.q3);
}

