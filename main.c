/*
 * main.c
 *
 *  Created on: Jan 23, 2017
 *      Author: Ahmed HAmdy
 */
#define PASSWORD_LENGTH 4
#define ASCII_OFFSET 0x30

#include "STD_TYPES.h"
#include "Macro.h"
#include "DIO.h"
#include "LCD.h"
#include "keypad.h"
#include "util/delay.h"

int main ()
{
	/* Initialization */
	u8 index,key;
	u8 welcome_message [] = "WELCOME";
	u8 password_message [] = "ENTER PASSWORD";
	u8 password_count = 0;
	u8 Entered_password [5];
	u8 Checked_password [5] = "1234";
	u8 wrong_message [] = "WRONG PASSWORD";
	u8 correct_message [] = "CORRECT PASSWORD";
	u8 end_message [] = "#SAFE_COMPLEX";

	/* LCD Module Intialize */
	for (index = 0;index < 8;index ++)
	{
		Dio_vidSetDirection(2,index,1);
	}
	for (index = 2;index < 5;index ++)
	{
		Dio_vidSetDirection(3,index,1);
	}
	LCD_vidInit();

	/* Keypad Module Intialize */
	for (index = 0;index < 4;index ++)
	{
		Dio_vidSetDirection(0,index,1);
		Dio_vidSetPinValue(0,index,1);
	}
	for (index = 0;index < 4;index ++)
	{
		Dio_vidSetDirection(1,index,0);
		Dio_vidSetPinValue(1,index,1);
	}

	/* LEDs Initialization */
	Dio_vidSetDirection(0,6,1);
	Dio_vidSetDirection(0,7,1);

	/* DC Motor and Buzzer Intialize */
	Dio_vidSetDirection(3,0,1);
	Dio_vidSetDirection(3,1,1);

	LCD_vidSendCommand(0b10000101);
	LCD_vidWriteString(welcome_message);
	_delay_ms(3000);
	LCD_vidSendCommand(0b00000001);
	LCD_vidSendCommand(0b10000001);
	LCD_vidWriteString(password_message);

	LCD_vidSendCommand(0b11000110);


	while (1)
	{
		while (password_count < 4)

		{
			key = KPD_u8GetKeyPressed();
			if (key != 0xFF)
			{
				Entered_password[password_count] = ((ASCII_OFFSET) + key);
				password_count ++;
				LCD_vidWriteCharacter('*');
			}
			else {}
			_delay_ms(700);
		}

		password_count = 0;

		if (((Entered_password [0] != Checked_password [0]) || (Entered_password [1] != Checked_password [1])
					|| (Entered_password [2] != Checked_password [2]) || (Entered_password [3] != Checked_password [3])))
				{
					Dio_vidSetPinValue(0, 6, 1);
					Dio_vidSetPinValue(3, 0, 1);
					LCD_vidSendCommand(0b00000001);
					LCD_vidSendCommand(0b10000001);
					LCD_vidWriteString(wrong_message);
					_delay_ms(10000);
					LCD_vidSendCommand(0b00000001);
					LCD_vidSendCommand(0b10000001);
					LCD_vidWriteString(password_message);
					Dio_vidSetPinValue(0, 6, 0);
					Dio_vidSetPinValue(3, 0, 0);

					LCD_vidSendCommand(0b11000110);
					while (password_count < 4)

							{
								key = KPD_u8GetKeyPressed();
								if (key != 0xFF)
								{
									Entered_password[password_count] = ((ASCII_OFFSET) + key);
									password_count ++;
									LCD_vidWriteCharacter('*');
								}
								else {}
								_delay_ms(700);
							}
				}
		else if ((Entered_password [0] == Checked_password [0]) && (Entered_password [1] == Checked_password [1])
			&& (Entered_password [2] == Checked_password [2]) && (Entered_password [3] == Checked_password [3]))
		{
			LCD_vidSendCommand(0b00000001);
			LCD_vidSendCommand(0b10000000);
			LCD_vidWriteString(correct_message);
			LCD_vidSendCommand(0b11000100);
			LCD_vidWriteString(welcome_message);
			Dio_vidSetPinValue(0, 7, 1);
			Dio_vidSetPinValue(3, 1, 1);
			_delay_ms(5000);
			Dio_vidSetPinValue(0, 7, 0);
			Dio_vidSetPinValue(3, 1, 0);
			LCD_vidSendCommand(0b00000001);
			LCD_vidSendCommand(0b10000001);
			LCD_vidWriteString(end_message);
			_delay_ms (5000);

		}


		}
	return 0;
	}



