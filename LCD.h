/*
 * LCD.h
 *
 *  Created on: Jan 14, 2017
 *      Author: Ahmed HAmdy
 */

#ifndef LCD_H_
#define LCD_H_

void LCD_vidInit (void);						/*Initialize LCD */

void LCD_vidSendCommand (u8 command);			/*configuration and setup */

void LCD_vidWriteCharacter (u8 character);		/*write character on screen */

void LCD_vidWriteString (u8* string);			/* write string on screen*/



#endif /* LCD_H_ */
