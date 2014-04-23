// Michael J. Chen 37145431
// Ellen Liu 54186168

#include "avr.h"



int main (void)
{
	ini_avr();
	//start_led();
	read_keyPad();
	
	// Insert application code here, after the board has been initialized.
}
void
read_keyPad(void)
{
	CLR_BIT(PORTC, 7);
	CLR_BIT(PORTC, 6);
	CLR_BIT(PORTC, 5);
	CLR_BIT(PORTC, 4);
	SET_BIT(PORTC, 3);
	SET_BIT(PORTC, 2);
	SET_BIT(PORTC, 1);
	SET_BIT(PORTC, 0);
	
	for(;;)
	{
		for(int i = 0; i < 8; i++)
		{
			if(GET_BIT(PINC, i)){
				CLR_BIT(PORTB, 0);
				
			}
			else{
				
				SET_BIT(PORTB, 0);
			}
		}
		
	}
}
void 
start_led(void)
{
	int msec = 500;
	SET_BIT(PORTB, 0);

	for(;;)
	{
		
		if(GET_BIT(PINB,1)){
			CLR_BIT(PORTB, 0);

		}
		else{
			SET_BIT(PORTB, 0);
			wait_avr(msec);
			CLR_BIT(PORTB, 0);
			wait_avr(msec);
		}
	}

}
void
ini_avr(void)
{
	// init LED
	SET_BIT(DDRB, 0);
	CLR_BIT(DDRB, 1);
	
	// init keypad
	SET_BIT(DDRC, 7);
	SET_BIT(DDRC, 6);
	SET_BIT(DDRC, 5);
	SET_BIT(DDRC, 4);
	CLR_BIT(DDRC, 3);
	CLR_BIT(DDRC, 2);
	CLR_BIT(DDRC, 1);
	CLR_BIT(DDRC, 0);
	
}

void
wait_avr(unsigned short msec)
{
  TCCR0 = 3;
  while (msec--) {
    TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
    SET_BIT(TIFR, TOV0);
    while (!GET_BIT(TIFR, TOV0));
  }
  TCCR0 = 0;
}
