#include <p18cxxx.h>
#include "lcd.h"
#include <delays.h>

void pulsaEnable()
{
	Delay1KTCYx(25);
	enable=1;
	Delay1KTCYx(250);
	enable=0;
	Delay1KTCYx(250);	// pulsa enable para leitura dos dados na porta
}

void ligaDisplay()
{	
	db7=0;
	db6=0;
	db5=0;
	db4=0;
	pulsaEnable();
	db7=1;
	db6=1;
	db5=0;
	db4=0;			// - 08 / 0F
	pulsaEnable();	//liga display
}
	


	

void inicializaLCD()	// de acordo com a sequencia do datasheet do controlador
{
	Delay1KTCYx(250); // - 50 ms
	
	
	Delay1KTCYx(250);
	trisEnable=0;
	trisRs=0;
	trisDb7=0;
	trisDb6=0;
	trisDb5=0;
	trisDb4=0;

	

	rs=0;
	db7=0;
	db6=0;
	db5=1;
	db4=1;
	enable=0;
	pulsaEnable();	// passo 1 - 3
	pulsaEnable();	// passo 1
	pulsaEnable();	// passo 2
//					// 3 vezes início

	Delay1KTCYx(250);
	db7=0;
	db6=0;				
	db5=1;
	db4=0;			// - 2
	pulsaEnable();	//passo 4 - 2 linhas

	db7=0;
	db6=0;				
	db5=1;
	db4=0;			// -2
	pulsaEnable();
	db7=1;
	db6=0;
	db5=0;
	db4=0;			// - 28
	pulsaEnable();	//passo 5 - 4 bits 2 linhas 5x7
	
	db7=0;
	db6=0;
	db5=0;
	db4=0;
	pulsaEnable();
	db7=1;
	db6=0;
	db5=0;
	db4=0;			// - 0C
	pulsaEnable();	//passo 6 - display off, cursor underline off e sem blink

	db7=0;
	db6=0;
	db5=0;
	db4=0;
	pulsaEnable();
	db7=0;
	db6=0;
	db5=0;
	db4=1;			// - 01	
	pulsaEnable();	//passo 7 - limpa display

	db7=0;
	db6=0;
	db5=0;
	db4=0;
	pulsaEnable();	
	db7=0;
	db6=1;
	db5=1;
	db4=0;			// - 06
	pulsaEnable();	// passo 8 - modo entrada caracter - incrementa e sem deslocamento
	
	ligaDisplay();

}	
	


void escreveLCD(unsigned char dado)
{
	
	db7 = (unsigned int)((dado & 0x80)>>7);	//ACERTA DADO
    db6 = (unsigned int)((dado & 0x40)>>6);	//NO BARRAMENTO
    db5 = (unsigned int)((dado & 0x20)>>5);
    db4 = (unsigned int)((dado & 0x10)>>4);

	pulsaEnable();

    db7 = (unsigned int)((dado & 0x08)>>3);	//ACERTA DADO
    db6 = (unsigned int)((dado & 0x04)>>2);	//NO BARRAMENTO
    db5 = (unsigned int)((dado & 0x02)>>1);
    db4 = (unsigned int)(dado & 0x01);

   pulsaEnable();

	
	Delay1KTCYx(250);	
}


void vLCD_EscreveHexa(unsigned char kucChar){
	unsigned char c;
	c = kucChar >> 4;
	if (c <= 9) {
		escreveLCD(c + 0x30);
	}
	else {
		escreveLCD(c + 0x37);
	}
	c = kucChar & 0x0F;
	if (c <= 9) {
		escreveLCD(c + 0x30);
	}
	else {
		escreveLCD(c + 0x37);
	}
}

void lcd_escreveDecimal(int b)
{
   char i,k,escreverZeros=0;
   int j=10000;
   if (!b) escreveLCD('0');
   for (k=0;k<5;k++)
   {
      i=0;
      while (b >= j)
      {
         b = b - j;
         i++;
      }
   	if (i) escreverZeros = 1;
      if (escreverZeros) escreveLCD(i+'0');
      j = j/10;
   }
}

void escreveStringLCD(char* mensagem)
{
   for (;*mensagem != '\0';mensagem++) escreveLCD(*mensagem);
}



void pocicionaLCD(char pocicao)
{
	rs=0;
	escreveLCD(pocicao);
	rs=1;
}
