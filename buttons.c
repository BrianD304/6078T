/*
 * buttons.c
 *
 *  Created on: Aug 17, 2014
 *      Author: Brian Duffy
 */

#include "main.h"
#include "definitions.h"
int LCDButtons = 0;

void waitForRelease() {
	while (LCDButtons != 0) {
	}
	delay(20);
}
void autoselect() {
	int count = 0;
	lcdClear(LCD );
	while (LCDButtons != LCD_BTN_CENTER) {
		switch (count) {
		case 0:
			lcdSetText(LCD, 1, "Autonomous 1");
			lcdSetText(LCD, 2, "<   Enter   >");
			waitForPress();
			if (LCDButtons == LCD_BTN_LEFT) {
				waitForRelease();
				count = 3;
				LCDButtons = 0;
			} else if (LCDButtons == LCD_BTN_RIGHT) {
				waitForRelease();
				count++;
				LCDButtons = 0;
			}
			break;
		case 1:
			lcdSetText(LCD, 1, "Autonomous 2");
			lcdSetText(LCD, 2, "<   Enter   >");
			waitForPress();
			if (LCDButtons == LCD_BTN_LEFT) {
				waitForRelease();
				count--;
				LCDButtons = 0;
			} else if (LCDButtons == LCD_BTN_RIGHT) {
				waitForRelease();
				count++;
				LCDButtons = 0;
			}
			break;
		case 2:
			lcdSetText(LCD, 1, "Autonomous 3");
			lcdSetText(LCD, 2, "<   Enter   >");
			waitForPress();
			if (LCDButtons == LCD_BTN_LEFT) {
				waitForRelease();
				count--;
				LCDButtons = 0;
			} else if (LCDButtons == LCD_BTN_RIGHT) {
				waitForRelease();
				count++;
				LCDButtons = 0;
			}
			break;
		case 3:
			lcdSetText(LCD, 1, "Autonomous 4");
			lcdSetText(LCD, 2, "<   Enter   >");
			waitForPress();
			if (LCDButtons == LCD_BTN_LEFT) {
				waitForRelease();
				count--;
				LCDButtons = 0;
			} else if (LCDButtons == LCD_BTN_RIGHT) {
				waitForRelease();
				count = 0;
				LCDButtons = 0;
			}
			break;
		default:
			count = 0;
			LCDButtons = 0;
			break;
		}
	}
}
