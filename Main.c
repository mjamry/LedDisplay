
#include <avr/io.h>
#include <util/delay.h>
#define DELAY 100
#define CHAR_NUMBER 2
#define CHAR_LENGTH 8

#define CLK 0x40
#define OUT 0x20
#define RST 0x10

int main(void)
{
    uint8_t const charTab[CHAR_NUMBER][CHAR_LENGTH] = {{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
    													{0xF8, 0xF4, 0xF2, 0xF1, 0x8F, 0x4F, 0x2F, 0x1F}};
    uint8_t i=0, j=0;

    DDRB = 0xFF;
    DDRD = 0xFF;

    while(1)
    {

        for(i=0;i<CHAR_NUMBER;i++)
        {
        	PORTD |= RST;
			PORTD &= ~(OUT);
        	for(j=0;j<CHAR_LENGTH;j++)
        	{
        		PORTD |= CLK;
				PORTB = charTab[i][j];
				_delay_us(DELAY);
				PORTD &= ~(CLK);
				_delay_us(DELAY);
				PORTD |= OUT;
        	}

        }
    }

    return 0;
}
