#include <p18cxxx.h>


#define db7				PORTDbits.RD7
#define	db6				PORTDbits.RD6
#define db5				PORTDbits.RD5
#define	db4				PORTDbits.RD4

#define	enable    		PORTAbits.RA1 
#define	rs		   		PORTAbits.RA2   
   

#define trisDb7  		TRISDbits.TRISD7
#define trisDb6  		TRISDbits.TRISD6
#define trisDb5  		TRISDbits.TRISD5
#define trisDb4			TRISDbits.TRISD4

#define trisEnable 		TRISAbits.TRISA1   
#define trisRs  		TRISAbits.TRISA2

void pulsaEnable(void);
void ligaDisplay(void);
void inicializaLCD(void);
void escreveLCD(unsigned char dado);
void vLCD_EscreveHexa(unsigned char kucChar);
void lcd_escreveDecimal(int b);
void escreveStringLCD(char* mensagem);
void pocicionaLCD(char pocicao);
