 /******************************************************************************
 *
 * Module: KEYPAD_Cfg
 *
 * File Name: KEYPAD_Cfg.c
 *
 * Description: Source file for the KEYPAD driver Configurations
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "GPIO.h"
#include "Keypad.h"

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
/*Initialization of the KEYPAD configuration structure*/
KEYPAD_strConfig_t KEYPAD_strConfig = {
	.KEYPAD_strROWS = {
		[ROW0] = {
			.KEYPAD_enumPORT = GPIO_PORTB,
			.KEYPAD_enumPin = KEYPAD_enumPin3,
		},
		[ROW1] = {
			.KEYPAD_enumPORT = GPIO_PORTB,
			.KEYPAD_enumPin = KEYPAD_enumPin4,
		},
		[ROW2] = {
			.KEYPAD_enumPORT = GPIO_PORTB,
			.KEYPAD_enumPin = KEYPAD_enumPin5,
		},
	},
	.KEYPAD_strCOLS = {
		[COL0] = {
			.KEYPAD_enumPORT = GPIO_PORTB,
			.KEYPAD_enumPin = KEYPAD_enumPin2,
		},
		[COL1] = {
			.KEYPAD_enumPORT = GPIO_PORTB,
			.KEYPAD_enumPin = KEYPAD_enumPin1,
		},
		[COL2] = {
			.KEYPAD_enumPORT = GPIO_PORTB,
			.KEYPAD_enumPin = KEYPAD_enumPin0,
		},
	},
	.KEYPAD_enumConnection = KEYPAD_enumPullUp,    /*Connection type (Pull-Up or Pull-Down)*/
	.KEYPAD_enumLogicType = KEYPAD_enumLogicLow   /*Logic type (High or Low when pressed)*/
};

/*Characters assigned to each key on the keypad*/
/*S = Start ,U = Up, P = Stop, L = Left, K = Ok, R = Right, E = Edit, M = Mode "Stopwatch, Display Date and Time"  */
char KEYPAD_Charchters[KEYPAD_NUMBER_OF_ROWS][KEYPAD_NUMBER_OF_COLS] =
{
	{'S','U','P'},
	{'L','K','R'},
	{'E','D','M'}
};


