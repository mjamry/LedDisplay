
#include <avr/io.h>
#include <util/delay.h>
#define DELAY 100
#define CHAR_NUMBER 1
#define CHAR_LENGTH 8

#define CLK 0x40
#define OUT 0x20
#define RST 0x10

int main(void)
{
    uint8_t const chatTab[CHAR_NUMBER][CHAR_LENGTH] = {{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}};
    uint8_t i=0, j=0;

    DDRB = 0xFF;
    DDRD = 0xFF;

    while(1)
    {
    	PORTD |= RST;
    	PORTD |= OUT;

        for(i=0;i<CHAR_NUMBER;i++)
        {
        	for(j=0;j<CHAR_LENGTH;j++)
        	{
        		PORTD |= CLK;
				PORTB = chatTab[i][j];
				_delay_us(DELAY);
				PORTD &= ~(CLK);
				_delay_us(DELAY);
				PORTD &= ~(OUT);
        	}

        	PORTD &= ~(RST);
        }
    }

    return 0;
}
