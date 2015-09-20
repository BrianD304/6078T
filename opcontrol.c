
/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "definitions.h"
#define DEADZONE 30
int pl;
/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
int deadzone(int speed) {
	if (abs(speed) < DEADZONE) {
		return 0;
	} else {
		return speed;
	}
}

void operatorControl() {

	float v = powerLevelMain();
	float g = powerLevelBackup();
	int left = 0; // left drive train
	int right = 0; // right drive train
	int imeValue1; // current ime tick count
	int imeValue2;
	int x;
	int y;
	int z;
	int error = 0; // difference of target and imeValue
	int target = 0; // set ime tick count target

	int mode = 1; // mode 0 = IME control, mode 1 = manual control
	//imeReset(0);
	//imeReset(1);
	lcdPrint(LCD, 1, "Main: %.1f", v);
	lcdPrint(LCD, 2, "9v: %.1f", g);
	while (1) {

		/* -------------------- DRIVE CONTROL --------------------*/
		// Tank Drive
		int Drivetype = 2; // 1=tank drive mode, 2=mecanum drive

		if (Drivetype == 1) {

			left = joystickGetAnalog(1, 3); // 3 = left y-axis
			right = joystickGetAnalog(1, 2); // 2 = right y-axis
			motorSet(1, deadzone(left)); //motor port 1
			motorSet(10, deadzone(-right)); //motor port 10
			motorSet(2, deadzone(left));
			motorSet(3, deadzone(right));
		}

		if (Drivetype == 2) {
			x = joystickGetAnalog(1, 4);
			z = joystickGetAnalog(1, 1);
			y = joystickGetAnalog(1, 3);

			motorSet(1, deadzone(z + x - y));
			motorSet(2, deadzone(z - x - y));
			motorSet(3, deadzone(z + x + y));
			motorSet(10, deadzone(-z + x - y));
			delay(20);
		}

		/*==============>Pneumatics<==============*/

		if (joystickGetDigital(2, 8, JOY_RIGHT) == true) {
			digitalWrite(7, LOW); // reverse for user release

		}
		if ((joystickGetDigital(2, 8, JOY_LEFT) == true)) { // may change syntax
			delay(20);
			digitalWrite(7, HIGH);

		}
		if (joystickGetDigital(2, 6, JOY_UP) == true) { //go up mode manual
			mode = 1; // mode 1 = manual control
			//motorSet(L_LIFT_TOP, 127); //set to speed motor can understand
			motorSet(L_LIFT_BTM, 127);
			motorSet(R_LIFT_TOP, 127);
			motorSet(R_LIFT_BTM, 127);

			if ((digitalRead(dLIM_SW_5) == 0) && (digitalRead(dLIM_SW_6) == 0)
					&& (joystickGetDigital(1, 6, JOY_UP) == true)) { // vertical height limit switch

				//motorSet(L_LIFT_TOP, 0);
				motorSet(L_LIFT_BTM, 0);
				motorSet(R_LIFT_TOP, 0);
				motorSet(R_LIFT_BTM, 0);

			}
		} else if (joystickGetDigital(2, 6, JOY_DOWN) == true) { //go down mode manual
			mode = 1; // mode 1 = manual control
			//motorSet(L_LIFT_TOP, -90); //set to speed motor can understand
			motorSet(L_LIFT_BTM, -90);
			motorSet(R_LIFT_TOP, -90);
			motorSet(R_LIFT_BTM, -90);

			if ((digitalRead(dLIM_SW_3) == 0) && (digitalRead(dLIM_SW_4) == 0)
					&& (joystickGetDigital(1, 6, JOY_DOWN) == true)) {

				//motorSet(L_LIFT_TOP, 0);
				motorSet(L_LIFT_BTM, 0);
				motorSet(R_LIFT_TOP, 0);
				motorSet(R_LIFT_BTM, 0);

			}
		} else if (mode == 1) { //if mode manual but no button stop motor
			//motorSet(L_LIFT_TOP, 0); //set to speed motor can understand
			motorSet(L_LIFT_BTM, 0);
			motorSet(R_LIFT_TOP, 0);
			motorSet(R_LIFT_BTM, 0);

		}
		if (joystickGetDigital(2, 5, JOY_UP) == true) {
			motorSet(7, 100);
			motorSet(8, 100);

		} else if (joystickGetDigital(2, 5, JOY_DOWN) == true) {
			motorSet(7, -100);
			motorSet(8, -100);
		} else {
			motorSet(7, 0);
			motorSet(8, 0);

		}
		if (joystickGetDigital(2, 7, JOY_UP) == true) {
			motorSet(9, 127);
		} else if (joystickGetDigital(2, 7, JOY_DOWN) == true) {
			motorSet(9, -127);
		} else {
			motorSet(9, 0);
		}

		delay(20);
	}
}

