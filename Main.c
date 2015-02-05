
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Const.h"
#include "MemoryData.h"

uint16_t memoryPointer = 0;
uint8_t dataToDisplay[CHAR_LENGTH];
uint8_t memoryData[CHARS_NUMBER] = {0xFF, 0xFF, '\0', 0xFF, 0xFF, '\0', 0xFF};

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

void resizeDataArray(uint8_t input[], uint8_t inputLength, uint8_t output[])
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

void readDataFromMemory(uint8_t memory[], uint8_t output[])
{
	uint8_t i=0;
	uint8_t memoryData[CHAR_LENGTH];
	while(memory[memoryPointer] != '\0')
	{
		memoryData[i] = memory[memoryPointer];
		i++;
		memoryPointer++;
	}

	memoryPointer++;
	resizeDataArray(memoryData, i, output);
}

ISR(TIMER1_COMPA_vect)
{
	if(memoryPointer > CHARS_NUMBER)
	{
		memoryPointer = 0;
	}
	readDataFromMemory(memoryData, dataToDisplay);
}

void putOutRowData(uint8_t data)
{
	uint8_t i=0;
	uint8_t temp = 0;

	PORTB |= (_ROW_OUTPUT_ENABLE);


	_delay_us(10);
	PORTB  |= (_ROW_CLR);
	for(i=0;i<8;i++)
	{
		temp = data & 0x80;
		if(temp)
		{
			PORTB |= (1<<PB0);
		}
		else
		{
			PORTB &= ~(1<<PB0);
		}

		//PORTB |= (ROW_DATA);
		data = data << 1;

		PORTB |= (ROW_SERIAL_CLK);
		_delay_us(DELAY);
		PORTB &= ~(ROW_SERIAL_CLK);
		_delay_us(DELAY);
	}

	PORTB |= ROW_LATCH;
	_delay_us(DELAY);
	PORTB &= ~(ROW_LATCH);
	_delay_us(DELAY);
	PORTB &= ~(_ROW_OUTPUT_ENABLE);
}

int main(void)
{

    uint8_t j=0;
    memoryPointer = 0;

    setUpIO();
    initialiseTimer_1_B();
    //set global interrupt flag
    sei();

    while(1)
    {
    	PORTD &= ~(0x04);
		PORTD |= RST;
		PORTD &= ~(OUT);
		for(j=0;j<8;j++)
		{
			putOutRowData(0xAA);
			clockRegisterState();
			PORTD |= OUT;
		}
    }

    return 0;
}
