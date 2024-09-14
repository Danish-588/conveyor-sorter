/*
 * variables.h
 *
 *  Created on: Sep 11, 2018
 *      Author: Varun
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

#define RED 0
#define BLUE 1
#define zone BLUE

//----------------------------------IMU----------------------------------//
volatile double angle_temp = 0, angle_deadreckon_point = 0, angle = 0;
//------For Error Correction---------//
volatile double req_angle = 0, error_angle = 0;
volatile bool angle_correct = 1;


//----------------------------------Distance Sensor----------------------------------//
volatile float dist1 = 0, dist2 = 0, dist3 = 0, dist4 = 0;
volatile int data_dist1 = 0, data_dist2 = 0, data_dist3 = 0, data_dist4 = 0;

//------For Error Correction---------//
volatile float req_sensor_x = 0, req_sensor_y = 0, req_sensor_angle = 0;
volatile float error_sensor_x = 0, error_sensor_y = 0, error_sensor_angle = 0;
volatile int error_sensor_x_dir = -1, error_sensor_y_dir = 1, error_sensor_angle_dir = 1;
volatile bool y_sensor_correct = 0, x_sensor_correct = 0;

//----------------------------------Velocity----------------------------------//
volatile float v1 = 0, v2 = 0, v3 = 0, v4 = 0;
volatile float vx = 0, vy = 0, w = 0, v_scaling_factor = 1, rpm1 = 0, rpm2 = 0, rpm3 = 0, rpm4 = 0;
volatile float bot_radius = 0.401, accs = 0.0075, deaccs = 0.01, accs_w = 0.015, deaccs_w = 0.015, omni_front_angle = 90;
volatile int drive = 1;
volatile bool holonomic = 1, rpm_control = 1;
volatile float vx_limit = 1.5, vy_limit = 1.5, w_limit = 3;

//----------------------------------XY----------------------------------//
volatile float x = 0, y = 0, x_scale = 0, y_scale = 0, x_final = 0, y_final = 0, x_deadreck = 0, y_deadreck = 0, x_photo = 0, y_photo = 0;

//------For Error Correction---------//
volatile float req_x = 0, req_y = 0, error_x = 0, error_y = 0;
volatile int error_x_dir = 1, error_y_dir = 1, error_angle_dir = 1;
volatile bool x_correct = 0, y_correct = 0;
volatile float x_xy_buffer = 0.01, y_xy_buffer = 0.01, x_sensor_buffer = 30, y_sensor_buffer = 30;

//----------------------------------Accs----------------------------------//
volatile float accs_ka_accs = 2.0;
volatile double accs_vy_limit = 0, accs_vx_limit = 0, accs_vy_limit_neg = 0, accs_vx_limit_neg = 0;
volatile bool accs_enable_x = 1, accs_enable_y = 1;

//----------------------------------Stall----------------------------------//
volatile int stall = 0;
volatile float stall_deaccs = 0.05, stall_w_deaccs = 0.1;

//----------------------------------Navigation----------------------------------//
volatile int navi_choice = 0, next_case = 0, direct_next = 0, angle_check = 0;

//----------------------------------Bezier----------------------------------//
volatile float t = 0.0, bezier_buff = 0.0;


//----------------------------------Navigation----------------------------------//
//enum navi_case{case1, case2};   //Replace with case names for the navigation cases

#endif /* VARIABLES_H_ */
