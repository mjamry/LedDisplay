
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Const.h"
#include "MemoryData.h"

uint16_t memoryPointer = 0;
bool btnPressed = false;
uint8_t dataToDisplay[CHAR_LENGTH];

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

void initialiseInt_1()
{
	//enable INT1
	GIMSK |= (1<<INT1);
	//The falling edge of INT1 generates an interrupt request
	MCUCR |= (1<<ISC11) | (1<<ISC10);
	//enable pull up resistor
	PORTD |= (1<<PD3);
}

void setUpIO()
{
    DDRB = 0xFF;
    DDRD = 0xF7;
}

//clocks column clock
void clockRegisterState()
{
	PORTD |= CLK;
	_delay_us(DELAY_COL);
	PORTD &= ~(CLK);
	_delay_us(DELAY_COL);
}

//put data in the middle, and fill rest with empty space (LEDs turned off)
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

//reads data from the memory using pointer.
//pointer is incremented after reading data.
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

//timer interrupt handler
ISR(TIMER1_COMPA_vect)
{
	//at the moment does nothing
}

//external interrupt handler
ISR(INT1_vect)
{
	btnPressed = true;
}

void putOutRowData(uint8_t data)
{
	uint8_t i=0;
	uint8_t temp = 0;

	for(i=0;i<8;i++)
	{
		temp = data & 0x80;
		if(temp)
		{
			PORTB |= (1<<PB7);
		}
		else
		{
			PORTB &= ~(1<<PB7);
		}

		data = data << 1;

		PORTB &= ~(ROW_SERIAL_CLK);
		_delay_us(DELAY_ROW);
		PORTB |= (ROW_SERIAL_CLK);
	}

	PORTB &= ~(ROW_LATCH);
	_delay_us(DELAY_ROW);
	PORTB |= ROW_LATCH;
}

int main(void)
{
    uint8_t j=0;

    setUpIO();
    initialiseTimer_1_B();
    initialiseInt_1();
    //set global interrupt flag
    sei();

    while(1)
    {
		PORTD |= RST;
		//puts 0 to the output which will selects current column
		PORTD &= ~(OUT);
		//handle button pressed
		if(btnPressed)
		{
			memoryPointer++;
			if(memoryPointer == NUMBER_OF_GRAPHICS)
			{
				memoryPointer = 0;
			}

			btnPressed = false;
		}
		for(j=0;j<MATRIX_LENGTH;j++)
		{
			putOutRowData(GRAPHICS[memoryPointer*MATRIX_LENGTH+j]);
			clockRegisterState();
			PORTD |= OUT;
		}
    }

    return 0;
}
