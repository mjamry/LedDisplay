
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Const.h"
#include "MemoryData.h"

uint8_t INDEX = 0;

ISR(TIMER1_COMPA_vect)
{
	PORTD |= 0x04;
	INDEX++;
	if(INDEX >= ROWS_NUMBER)
	{
		INDEX = 0;
	}
	//_delay_ms(100);
}

void initialiseTimer_1_B()
{
    //set CTC mode
    TCCR1B |= (1<<WGM12);
    //set prescaler to 64
    TCCR1B |= ((1<<CS11) | (1<<CS10));
    //set interrupt flag
    TIMSK |= (1<<OCIE1A);
    //set counter value
    OCR1A = 0x04F0;
}

void setUpIO()
{
    DDRB = 0xFF;
    DDRD = 0xFF;
}

void clockRegisterState()
{
	PORTD |= CLK;
	_delay_us(DELAY);
	PORTD &= ~(CLK);
	_delay_us(DELAY);
}

int main(void)
{
    uint8_t const charTab[ROWS_NUMBER][CHAR_LENGTH] = {
    		{0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    		{0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    		{0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00},
    		{0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00},
    		{0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00},
    		{0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00},
    		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00},
    		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}
    };

    uint8_t j=0;

    setUpIO();
    initialiseTimer_1_B();
    //set global interrupt flag
    sei();

    while(1)
    {
    	PORTD &= ~(0x04);
		PORTD |= RST;
		PORTD &= ~(OUT);
		for(j=0;j<CHAR_LENGTH;j++)
		{
			PORTB = charTab[INDEX][j];
			clockRegisterState();
			PORTD |= OUT;
		}
    }

    return 0;
}
