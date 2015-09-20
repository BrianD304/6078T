/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
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
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {

	pinMode(dLIM_SW_7, OUTPUT);

}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */

void initialize() {
	delay(50);

	usartInit(LCD, 115200, SERIAL_8N1);

	lcdInit(LCD );
	lcdClear(LCD );
digitalWrite(7,LOW);

	delay(1000);

	lcdSetBacklight(LCD, true);
	lcdSetText(LCD, 1, "Robo-Plugs");
	lcdSetText(LCD, 2, "Team 6078T");
	delay(20);

	delay(1000);
imeReset(0);
	imeReset(1);
	imeReset(2);
	imeReset(3);
	bool exit = false;
	int mode = 1;

	while (!exit & isOnline(true)) {
		switch (mode) {
		case 1:
			lcdClear(LCD );
			lcdSetText(LCD, 1, "Red Skyrise");
			lcdSetText(LCD, 2, "<   Enter   >");
			delay(500);
			switch (waitForPress()) {
			case LCD_BTN_LEFT:
				//waitForRelease();
				mode = 4;
				//LCDButtons = 0;
				break;
			case LCD_BTN_RIGHT:
				//waitForRelease();
				mode = 2;
				//LCDButtons = 0;
				break;
			case LCD_BTN_CENTER:
				lcdClear(LCD );
				lcdSetText(LCD, 1, "Please Wait...");
				delay(1000);

				AutoMode = 1;
				exit = true;

				break;
			}
			break;
		case 2:
			lcdClear(LCD );
			lcdSetText(LCD, 1, "Blue Skyrise");
			lcdSetText(LCD, 2, "<   Enter   >");
			delay(500);
			switch (waitForPress()) {
			case LCD_BTN_LEFT:
				//waitForRelease();
				mode = 1;
				//LCDButtons = 0;
				break;
			case LCD_BTN_RIGHT:
				//waitForRelease();
				mode = 3;
				//LCDButtons = 0;
				break;
			case LCD_BTN_CENTER:
				lcdClear(LCD );
				lcdSetText(LCD, 1, "Please Wait...");
				delay(1000);
				AutoMode = 2;
				exit = true;

				break;
			}
			break;
		case 3:
			lcdClear(LCD );
			lcdSetText(LCD, 1, "Autonomous 3");
			lcdSetText(LCD, 2, "<   Enter   >");
			delay(500);
			switch (waitForPress()) {
			case LCD_BTN_LEFT:
				//waitForRelease();
				mode = 2;
				//LCDButtons = 0;
				break;
			case LCD_BTN_RIGHT:
				//waitForRelease();
				mode = 4;
				//LCDButtons = 0;
				break;
			case LCD_BTN_CENTER:
				lcdClear(LCD );
				lcdSetText(LCD, 1, "Please Wait...");
				delay(1000);
				AutoMode = 3;
				exit = true;
				break;
			}
			break;
		case 4:
			lcdClear(LCD );
			lcdSetText(LCD, 1, "Autonomous 4");
			lcdSetText(LCD, 2, "<   Enter   >");
			delay(500);
			waitForPress();
			switch (waitForPress()) {
			case LCD_BTN_LEFT:
				//waitForRelease();
				mode = 3;
				//LCDButtons = 0;
				break;
			case LCD_BTN_RIGHT:
				//waitForRelease();
				mode = 1;
				//LCDButtons = 0;
				break;
			case LCD_BTN_CENTER:
				lcdClear(LCD );
				lcdSetText(LCD, 1, "Please Wait...");
				delay(1000);
				exit = true;
				AutoMode = 4;
				break;
			}
			break;

		}
	}

}

int waitForPress() {
	int button = 0;

	while (button == 0) {

		if (lcdReadButtons(LCD ) == LCD_BTN_LEFT)
			button = LCD_BTN_LEFT;
		else if (lcdReadButtons(LCD ) == LCD_BTN_CENTER)
			button = LCD_BTN_CENTER;
		else if (lcdReadButtons(LCD ) == LCD_BTN_RIGHT)
			button = LCD_BTN_RIGHT;
		else
			button = 0;
		delay(20);
	}
	//delay(1000);

	return button;
}

