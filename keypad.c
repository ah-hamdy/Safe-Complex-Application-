/*
 * keypad.c
 *
 *  Created on: Jan 13, 2017
 *      Author: Ahmed HAmdy
 */

#include "STD_TYPES.h"
#include "Macro.h"
#include "util/delay.h"
#include "DIO.h"
#include "keypad.h"

u8 KPD_u8GetKeyPressed (void)

{
	u8 column,row,value,key_pressed = 0xFF;		// dummy value no press key return this value
	u8 key [4][4] = {{1,4,7,0x0A},{2,5,8,0x0B},{3,6,9,0x0C},{0,0x0D,0x0E,0x0F}};



	for (column = 0; column < 4; column ++)
	{
		Dio_vidSetPinValue (0,column,0);

		for (row = 0; row < 4; row ++)
		{
			value = Dio_u8GetPinValue (1,row);
			if (value == 0) {
				key_pressed = key[column][row];
				while (Dio_u8GetPinValue(1, row) != 1)
					; /*Single Press*/
				_delay_ms(10); /*for debouncing */
			}
		}
		Dio_vidSetPinValue (0,column,1);
	}
	return key_pressed;
}
