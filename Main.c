
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

uint8_t resizeDataArray(uint8_t input[], uint8_t inputLength, uint8_t output[])
{
	uint8_t i=0;
	uint8_t fillData = 0x00;
	if(inputLength < CHAR_LENGTH)
	{
		uint8_t rightSize = (CHAR_LENGTH - inputLength)/2;
		//if array length is odd left side will have one element more than right
		uint8_t leftSize = rightSize + (CHAR_LENGTH - inputLength)%2;
		//fill right side
		for(i=0;i<rightSize;i++)
		{
			output[i] = fillData;
		}
		//add data in the middle
		for(i=rightSize;i<rightSize + inputLength;i++)
		{
			output[i] = input[i-rightSize];
		}
		//fill left side
		for(i=rightSize+inputLength;i<rightSize+inputLength+leftSize;i++)
		{
			output[i] = fillData;
		}
	}
}

int main(void)
{
    uint8_t const memoryData[CHAR_LENGTH] = {0xAA, 0x77};

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
			uint8_t output[CHAR_LENGTH];
			resizeDataArray(memoryData, 2, output);
			PORTB = output[j];
			clockRegisterState();
			PORTD |= OUT;
		}
    }

    return 0;
}
