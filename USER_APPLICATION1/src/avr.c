// Michael J. Chen 37145431
// Ellen Liu 54186168

#include "avr.h"
#include "lcd.h"
#define DATETABLE[] = {31,28,31,30,31,30,31,31,30,31,30,31};

int Day, Month, Year, Hour, Minutes, Seconds; 

int main (void)
{
	//ini_avr();
	//start_led();
	//read_keyPad();
	LCD();

	// Insert application code here, after the board has been initialized.
	return 1;
}
void LCD(void)
{
	ini_lcd();
	put_str_lcd("hello!");
	wait_avr(2000);
	
	resetLCD();
	setDateTime();
	
	while(1)
	{
		wait_avr(1000);
		incrementTime();
		char buf[10];
		sprintf(buf, "%02i/%02i/%04i", Month, Day, Year);
		put_str_lcd(buf);
		buf[9];
		sprintf(buf, "%02i:%02i:%02i", Hour, Minutes, Seconds);
		put_str_lcd(buf);
	}

	
}
void resetLCD(void)
{
	clr_lcd();
	// print the first date line
	char buf[10];
	pos_lcd(0, 2);
	sprintf(buf, "%02s/%02s/%04s", "MM", "DD", "YYYY");
	put_str_lcd(buf);
	
	// print time line
	buf[9];
	pos_lcd(1, 2);
	sprintf(buf, "%02s:%02s:%02s", "HH", "MIN", "SS");
	put_str_lcd(buf);
}

void incrementTime(void)
{
	Seconds++;
	if(Seconds >= 60)
	{
		Seconds = 0;
		Minutes++;
		if(Minutes >= 60)
		{
			Minutes = 0;
			Hour++;
			if(Hour >= 24)
			{
				Hour = 0;
				Day++;
				if(!isValidDate(Day,Month,Year))
				{
					Day = 1;
					Month++;
					if(!isValidDate(Day,Month,Year))
					{
						Month = 1;
						Year++;
					}	
				}
			}
		}
	}
}
void setDateTime(void)
{
	// keep track of LCD pos
	int row, col;
	// number is the number entered
	int number;
	// counter to keep track of how many digits entered
	int counter = 0;
	// number to keep track of the number so far
	int userInput = 0;

	while(1)
	{
		pos_lcd(row, col);
		number = get_key();
		if(number > 0)
		{
			put_lcd(number);
			if(col > 13)
			{
				row++;
				col = 4;
			}
			else
				col++;
			counter++;
			if(counter%2 == 0 && counter != 6)
				userInput += number;
			else if(counter == 5)
				userInput = 1000*number;
			else if(counter == 6)
				userInput = 100*number;
			else 
				userInput = 10*number;
			
		}
		if(counter == 2)
			Month = userInput;
		else if(counter == 4)
			Day = userInput;
		else if(counter == 8)
			Year = userInput;
		else if(counter == 10)
			Hour = userInput;
		else if(counter == 12)
			Minutes = userInput;
		else if(counter == 14)
			Seconds = userInput;
		if(row >= 1 && col >= 12)
			break;
	} 
	if(!isValidDate(Day, Month, Year)
		resetLCD();
}
_Bool isValidDate(int day, int month, int year)
{
	if(day > DATETABLE[month-1])
	{
		if((year%4 == 0) && (month == 1) && (day == 29) && (year%100 != 0))
			return true;
		return false;
	}
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
		}
		else
			CLR_BIT(PORTB, 0);
	}
	

}
int get_key(void){	

	if(pressed(2,4))
		return 0;
	SET_BIT(PORTC, 2);
	// i is ROW! *******
	for(int i = 4; i < 8; i++)
	{
		for(int j = 1; j < 4; j++)
		{
			if(pressed(j,i))
				{
					int row = 4-(i-3);
					int col = 4-j;
					return row*3 + col;
				}
				SET_BIT(PORTC, j);
		}
	}
	return -1;
}

_Bool pressed(int col, int row)
{
	CLR_BIT(PORTC, col);
	_Bool buttonPressed = !GET_BIT(PINC, col) && !GET_BIT(PINC, row);
	
	return !GET_BIT(PINC, col) && !GET_BIT(PINC, row);
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
// for debugging
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
