/*
 * IME.c
 *
 *  Created on: Nov 4, 2014
 *      Author: Brian Duffy
 */
#include "main.h"
#include "definitions.h"

void imeResetDrive() {
	imeReset(0);
	imeReset(1);
	imeReset(2);
	imeReset(3);

}

void liftset(int liftcounts) { // may need to reset imes after execution of this function
	int ticks;
	int lifterror;
	imeGet(2, &ticks);
	lifterror = (ticks - liftcounts) / 2;
	if (lifterror > 127) {
		motorSet(L_LIFT_TOP, 127);
		motorSet(L_LIFT_BTM, 127);
		motorSet(R_LIFT_BTM, 127);
		motorSet(R_LIFT_TOP, 127);
	} else if (lifterror < -127) {
		motorSet(L_LIFT_TOP, -127);
		motorSet(L_LIFT_BTM, -127);
		motorSet(R_LIFT_BTM, -127);
		motorSet(R_LIFT_TOP, -127);
	} else {
		motorSet(L_LIFT_TOP, lifterror);
		motorSet(L_LIFT_BTM, lifterror);
		motorSet(R_LIFT_BTM, lifterror);
		motorSet(R_LIFT_TOP, lifterror);
	}
}

