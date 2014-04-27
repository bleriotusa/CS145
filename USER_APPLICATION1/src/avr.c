// Michael J. Chen 37145431
// Ellen Liu 54186168

#include "avr.h"
#include "lcd.h"


int main (void)
{
	ini_avr();
	//start_led();
	read_keyPad();

	// Insert application code here, after the board has been initialized.
	return 1;
}
void LCD(void)
{
	ini_lcd();
	clr_lcd();
	put_lcd('!');
}
void
read_keyPad(void)
{
	SET_BIT(PORTC, 7);
	SET_BIT(PORTC, 6);
	SET_BIT(PORTC, 5);
	SET_BIT(PORTC, 4);
	SET_BIT(PORTC, 3);
	SET_BIT(PORTC, 2);
	SET_BIT(PORTC, 1);
	SET_BIT(PORTC, 0);
	
	for(;;)
	{
		if(get_key()>0)
		{
			blinkNTimes(get_key());
			//SET_BIT(PORTB, 0);
		}
		else
			CLR_BIT(PORTB, 0);
	}
	

}
int get_key(void){	
	// i is row
	for(int i = 4; i < 8; ++i)
	{
		for(int j = 0; j < 4; j++)
		{
			if(pressed(j,i))
				return (i*4) + j +1;
				//return 1;
		}
	}
	return 0;
}
void blinkNTimes(int n)
{	int msec = 500;
	SET_BIT(PORTB, 0);

	for(int i = 0; i < n; i++)
	{
		SET_BIT(PORTB, 0);
		wait_avr(msec);
		CLR_BIT(PORTB, 0);
		wait_avr(msec);
	}
		
}
_Bool pressed(int col, int row)
{
	//_Bool buttonPressed = 0;

	CLR_BIT(PORTC, col);
	//_Bool buttonPressed = !GET_BIT(PINC, col) && !GET_BIT(PINC, row);
	//SET_BIT(PORTC, col);
	return !GET_BIT(PINC, col) && !GET_BIT(PINC, row);

	//SET_BIT(PORTC, col);
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
	CLR_BIT(DDRC, 4);
	CLR_BIT(DDRC, 5);
	CLR_BIT(DDRC, 6);
	CLR_BIT(DDRC, 7);
	SET_BIT(DDRC, 0);
	SET_BIT(DDRC, 1);
	SET_BIT(DDRC, 2);
	SET_BIT(DDRC, 3);
	
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
