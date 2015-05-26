#include <p18f4550.h>
#include <delays.h>
#include <lcd.h>


#pragma config WDT = OFF
//#pragma config OSC = HS
#pragma config LVP = OFF


void main()
{
	char palavraLCD[20]="A Temp eh:";
	int temp = 100;
	
	ADCON0=0b00000001;
  	ADCON2=0b10101011;

	ADCON1 = 0x0E;
	inicializaLCD();
	
	pocicionaLCD(0x80);
	escreveStringLCD(palavraLCD);
	

	
	while (1)
	{
		ADCON0bits.GO=1;
	    while (ADCON0bits.GO);   // Wait conversion done
	    temp = ADRESL;           // Get the 8 bit LSB result
	    temp += (ADRESH << 8); // Get the 2 bit MSB result
		pocicionaLCD(0x8B);
		lcd_escreveDecimal((temp*50000)/1024);

		//Delay1KTCYx(250);
	}
}	
