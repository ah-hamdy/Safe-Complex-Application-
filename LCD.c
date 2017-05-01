/*
 * LCD.c
 *
 *  Created on: Jan 14, 2017
 *      Author: Ahmed HAmdy
 */


#include "STD_TYPES.h"
#include "Macro.h"
#include "util/delay.h"
#include "DIO.h"
#include "LCD.h"

void LCD_vidInit (void)
{
	_delay_ms (100);
	LCD_vidSendCommand (0b00000001);		/*clear display*/
	LCD_vidSendCommand (0b00000010);			/*return home */
	LCD_vidSendCommand (0b00000110);		/*entry mode set*/
	LCD_vidSendCommand (0b00001100);		/*display ON/OFF*/
	LCD_vidSendCommand (0b00111000);		/*Function set*/

}

void LCD_vidSendCommand (u8 command)
{
	Dio_vidSetPinValue (3,2,0);		/*clear RS*/
	Dio_vidSetPinValue (3,3,0);		/*clear Read or write */
	Dio_vidSetPinValue (3,4,1);		/* set E high*/

	Dio_vidSetPortValue (2,command);	/*put command on bus*/
	_delay_ms (2);

	Dio_vidSetPinValue (3,4,0);		/* set E low*/
	_delay_ms (5);

	Dio_vidSetPinValue (3,4,1);		/* set E high*/
	_delay_ms (10);					/*wait for the next command */

}

void LCD_vidWriteCharacter (u8 character)
{
	Dio_vidSetPinValue (3,2,1);
	Dio_vidSetPinValue (3,3,0);
	Dio_vidSetPinValue (3,4,1);

	Dio_vidSetPortValue (2,character);
	_delay_ms (2);

	Dio_vidSetPinValue (3,4,0);		/* set E low*/
	_delay_ms (5);

	Dio_vidSetPinValue (3,4,1);		/* set E high*/
		_delay_ms (10);
}

void LCD_vidWriteString (u8* string)
{
	u8 index = 0;		/* msh zay el for ana h.use while */
	while (string [index] != '\0')
	{
		LCD_vidWriteCharacter(string [index]);
		index ++;
		_delay_ms (2);
	}


}
