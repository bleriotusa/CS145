// Michael J. Chen 37145431
// Ellen Liu 54186168

#include "avr.h"
#include "lcd.h"


int main (void)
{
	ini_avr();
	//start_led();
	//read_keyPad();
	ini_lcd();
	put_str_lcd("hello world!");
	
	// Insert application code here, after the board has been initialized.
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
		get_key();

	}
	

}
int get_key(void){

	if(pressed(0,4))
	{
		SET_BIT(PORTB, 0);
		SET_BIT(PORTC, 0);
		SET_BIT(PORTC, 4);
	
	}
	else if(pressed(2,5))
	{
		SET_BIT(PORTB, 0);
		SET_BIT(PORTC, 3);
		SET_BIT(PORTC, 7);
	}
	else
	{
		CLR_BIT(PORTB,0);
	}
	// i = column
	//for(int i = 4; i < 8; i++)
		//for(int j = 0; j < 4; j++)
		//{
			//if(pressed(i,j))
			////return (j*4) + i +1;
			//SET_BIT(PORTB,0);
			//else
			//CLR_BIT(PORTB,0);
		//}
	return 0;
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
