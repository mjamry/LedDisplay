
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DELAY 100
#define CHAR_NUMBER 2
#define CHAR_LENGTH 8

#define CLK 0x40
#define OUT 0x20
#define RST 0x10

uint8_t INDEX = 0;

ISR(TIMER1_COMPA_vect)
{
	PORTD |= 0x04;
	if(INDEX == 0)
		INDEX = 1;
	else
		INDEX = 0;
	//_delay_ms(100);
}


int main(void)
{
    uint8_t const charTab[CHAR_NUMBER][CHAR_LENGTH] = {{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
    													{0xF8, 0xF4, 0xF2, 0xF1, 0x8F, 0x4F, 0x2F, 0x1F}};
    uint8_t i=0, j=0;

    DDRB = 0xFF;
    DDRD = 0xFF;

    //set CTC mode
    TCCR1B |= (1<<WGM12);
    //set prescaler to 1024
    TCCR1B |= ((1<<CS12) | (1<<CS10));
    //set interupt flag
    TIMSK |= (1<<OCIE1A);
    //set counter value
    OCR1A = 0x00FF;
    //set global interrupt flag
    sei();


    while(1)
    {
    	PORTD &= ~(0x04);
        for(i=0;i<CHAR_NUMBER;i++)
        {
        	PORTD |= RST;
			PORTD &= ~(OUT);
        	for(j=0;j<CHAR_LENGTH;j++)
        	{
        		PORTD |= CLK;
				PORTB = charTab[INDEX][j];
				_delay_us(DELAY);
				PORTD &= ~(CLK);
				_delay_us(DELAY);
				PORTD |= OUT;
        	}

        }
    }

    return 0;
}
