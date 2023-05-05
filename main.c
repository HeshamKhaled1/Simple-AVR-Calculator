#include "MCAL/Dio/Dio.h"
#include "HAL/LCD/lcd.h"
#include "HAL/KEYPAD/KeyPad.h"
#include <util/delay.h>

u16 calculate(u8 a[], u8 b[], u8 n, u8 m, u8 op);

u8 KpValue = 255; // variable to store the pressed button for Keypad

u8 FristNum[4];  // Array to store the first number (Assuming the number of digits 4)
u8 SecondNum[4]; // Array to store the Second number (Assuming the number of digits 4)

int main()
{
	KP_init();
	LCD_Init(); // Initialize LCD;
	while (1)
	{
		/*   Loading to Start Calculator */
		LCD_Send_Command(_LCD_CLEAR);
		LCD_Send_String_Pos((u8 *)"Loading", 1 , 1);
		for (u8 counter = 0; counter < 3; counter++)
		{
			LCD_Send_Char_Pos('.', 1, counter + 8);
			_delay_ms(10);
		}
		_delay_ms(200);
		LCD_Send_Command(_LCD_CLEAR);
		LCD_Send_String_Pos((u8 *)"Welcome!", 1, 1);
		LCD_Send_String_Pos((u8 *)"Team 16", 2, 1);
		_delay_ms(2000);

		/*    loop for repeating the calculation    */
		while (1)
		{
			start:
			LCD_Send_Command(_LCD_CLEAR);

			/*    Getting The First Number    */
			u8 counter = 0;
			u8 operation = 0;
			while (1)
			{
				do
				{
					KpValue = KP_GetPressed();
					_delay_us(1);
				} while (KpValue == 255);
				if (KpValue == '+' || KpValue == '-' || KpValue == '/' || KpValue == 'x')
				{
					operation = KpValue;
					LCD_Send_Char_Pos(KpValue, 1, counter + 1);
					break;
				}
				if(KpValue == 'C'){
					goto start;
				}
				FristNum[counter] = KpValue;
				counter++;
				LCD_Send_Number_Pos(KpValue, 1, counter);
			}

			/*    Getting The Second Number    */
			u8 counter2 = counter + 1;
			u8 counter3 = 0;
			while (1)
			{
				do
				{
					KpValue = KP_GetPressed();
					_delay_us(1);
				} while (KpValue == 255);
				if (KpValue == '=')
				{
					LCD_Send_Char_Pos(KpValue, 1, counter2 + 1);
					break;
				}
				if(KpValue == 'C'){
					goto start;
				}
				SecondNum[counter3] = KpValue;
				counter2++;
				counter3++;
				LCD_Send_Number_Pos(KpValue, 1, counter2);
			}

			LCD_Send_Number_Pos(calculate(FristNum, SecondNum, counter, counter3, operation), 2, 1);
			_delay_ms(300);
			LCD_Send_Command(_LCD_CLEAR);
		}
	}
}

u16 calculate(u8 a[], u8 b[], u8 n, u8 m, u8 op)
{
	u16 num1 = a[0];
	u16 num2 = b[0];
	for (u8 counter = 1; counter < n; counter++)
	{
		num1 = num1 * 10 + a[counter];
	}
	for (u8 counter = 1; counter < m; counter++)
	{
		num2 = num2 * 10 + b[counter];
	}
	switch (op)
	{
		case '+':
		return (num1 + num2);
		break;
		case '-':
		return (num1 - num2);
		break;
		case 'x':
		return (num1 * num2);
		break;
		case '/':
		return (num1 / num2);
		break;
		default:
		return 0;
	}
}
