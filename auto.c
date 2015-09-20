/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
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

char AutoMode;

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

int getimedrive() {

	int counts;
	int sum = 0;
	int avgime;
	imeGet(0, &counts);
	sum += abs(counts);
	imeGet(1, &counts);
	sum += abs(counts);
	imeGet(2, &counts);
	sum += abs(counts);
	imeGet(3, &counts);
	sum += abs(counts);

	avgime = sum / 4;
	return avgime;
}

void drive(int direction, int target) {

	while (direction == 0) { // forward
		int currentcounts = getimedrive();
		int error = target - currentcounts / 2;
		if (error > 127) {
			motorSet(1, 127);
			motorSet(2, 127);
			motorSet(3, 127);
			motorSet(10, 127);
		} else if (error < -127) {
			motorSet(1, -127);
			motorSet(2, -127);
			motorSet(3, -127);
			motorSet(10, -127);
		} else {
			motorSet(1, error);
			motorSet(2, error);
			motorSet(3, error);
			motorSet(10, -error);
		}
		if (abs(error) <= 12) {

			imeResetDrive();

			break;
		}
		delay(20);
	}
	while (direction == 1) { // backward
		int currentcounts = getimedrive();
		int error = target - currentcounts / 2;
		if (error > 127) {
			motorSet(1, 127);
			motorSet(2, 127);
			motorSet(3, 127);
			motorSet(10, 127);
		} else if (error < -127) {
			motorSet(1, -127);
			motorSet(2, -127);
			motorSet(3, -127);
			motorSet(10, -127);
		} else {
			motorSet(1, -error);
			motorSet(2, -error);
			motorSet(3, -error);
			motorSet(10, error);
		}
		if (abs(error) <= 15) {

			imeResetDrive();

			break;
		}
		delay(20);
	}
	while (direction == 2) { // strafe left
		int currentcounts = getimedrive();
		int error = target - currentcounts / 2;
		if (error > 127) {
			motorSet(1, 127);
			motorSet(2, 127);
			motorSet(3, 127);
			motorSet(10, 127);
		} else if (error < -127) {
			motorSet(1, -127);
			motorSet(2, -127);
			motorSet(3, -127);
			motorSet(10, -127);
		} else {
			motorSet(1, error);
			motorSet(2, error);
			motorSet(3, error);
			motorSet(10, error);
		}
		if (abs(error) <= 15) {

			imeResetDrive();

			break;
		}
		delay(20);
	}
	while (direction == 3) { // strafe right
		int currentcounts = getimedrive();
		int error = target - currentcounts / 2;
		if (error > 127) {
			motorSet(1, 127);
			motorSet(2, 127);
			motorSet(3, 127);
			motorSet(10, 127);
		} else if (error < -127) {
			motorSet(1, -127);
			motorSet(2, -127);
			motorSet(3, -127);
			motorSet(10, -127);
		} else {
			motorSet(1, -error);
			motorSet(2, -error);
			motorSet(3, -error);
			motorSet(10, -error);
		}
		if (abs(error) <= 15) {

			imeResetDrive();

			break;
		}
		delay(20);
	}
	while (direction == 4) { // rotate left
		int currentcounts = getimedrive();
		int error = target - currentcounts / 2;
		if (error > 127) {
			motorSet(1, 127);
			motorSet(2, 127);
			motorSet(3, 127);
			motorSet(10, 127);
		} else if (error < -127) {
			motorSet(1, -127);
			motorSet(2, -127);
			motorSet(3, -127);
			motorSet(10, -127);
		} else {
			motorSet(1, -error);
			motorSet(2, error);
			motorSet(3, -error);
			motorSet(10, -error);
		}
		if (abs(error) <= 15) {

			imeResetDrive();

			break;
		}
		delay(20);
	}
	while (direction == 5) { // rotate right
		int currentcounts = getimedrive();
		int error = target - currentcounts / 2;
		if (error > 127) {
			motorSet(1, 127);
			motorSet(2, 127);
			motorSet(3, 127);
			motorSet(10, 127);
		} else if (error < -127) {
			motorSet(1, -127);
			motorSet(2, -127);
			motorSet(3, -127);
			motorSet(10, -127);
		} else {
			motorSet(1, error);
			motorSet(2, -error);
			motorSet(3, error);
			motorSet(10, error);
		}
		if (abs(error) <= 15) {

			imeResetDrive();

			break;
		}
		delay(20);
	}

	delay(20);

}

void autonomous() {

	switch (AutoMode) {
	case 1:
		lcdClear(LCD );
		lcdSetText(LCD, 1, "Red Skyrise");
		lcdSetText(LCD, 2, "Running...");
		motorSet(7, 100);
		motorSet(8, 100);
		delay(1200);
		motorSet(7, 0);
		motorSet(8, 0);
		motorSet(1, -127);
		motorSet(2, -127);
		motorSet(3, 127);
		motorSet(10, -127);
		delay(1250);
		motorSet(1, 0);
		motorSet(2, 0);
		motorSet(3, 0);
		motorSet(10, 0);

		break;
	case 2:
		lcdClear(LCD );
		lcdSetText(LCD, 1, "Blue Skyrise");
		lcdSetText(LCD, 2, "Running...");
		motorSet(7, 100);
		motorSet(8, 100);
		delay(1200);
		motorSet(7, 0);
		motorSet(8, 0);
		motorSet(1, 127);
		motorSet(2, 127);
		motorSet(3, -127);
		motorSet(10, 127);
		delay(1250);
		motorSet(1, 0);
		motorSet(2, 0);
		motorSet(3, 0);
		motorSet(10, 0);

		break;
	case 3:
		lcdClear(LCD );
		lcdSetText(LCD, 1, "Autonomous 3");
		lcdSetText(LCD, 2, "Running...");
		imeResetDrive();
		//change the ime values
		drive(3, 300);

		drive(0, 100);
		//grab
		//arm movement
		drive(3, 100);
		delay(100);
		drive(1, 100);
		delay(100);
		drive(4, 100);
		delay(100);
		drive(0, 100);
		//arm movement
		//release
		break;
	case 4:
		lcdClear(LCD );
		lcdSetText(LCD, 1, "Autonomous 4");
		lcdSetText(LCD, 2, "Running...");
		imeResetDrive();
		drive(2, 300);
		delay(100);
		drive(0, 100);
		//arm movement
		//grab
		//arm movement
		drive(2, 100);
		delay(100);
		drive(1, 100);
		delay(100);
		drive(5, 100);
		delay(100);
		drive(0, 100);
		//arm movement
		//release

		break;

	}
}

