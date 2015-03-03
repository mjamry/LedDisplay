
#ifndef CONS_H_
#define CONS_H_

#define DELAY_ROW 80
#define DELAY_COL 120
#define CHARS_NUMBER 8
#define CHAR_LENGTH 8
#define MATRIX_LENGTH 24
#define NUMBER_OF_GRAPHICS 7

uint8_t GRAPHICS[MATRIX_LENGTH*NUMBER_OF_GRAPHICS] = {
									//[1] space invaders 1
									0x80, 0x5C, 0xB6, 0x5F, 0x5F, 0xB6, 0x5C, 0x80,
									0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
									0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
									//[2] space invaders 2
									0x02, 0x02 ,0x02 ,0x02 ,0x02 ,0x02 ,0x02 ,0x02,
									0x98, 0x5C, 0xB6, 0x5F, 0x5F, 0xB6, 0x5C, 0x98,
									0x02, 0x02 ,0x02 ,0x02 ,0x02 ,0x02 ,0x02 ,0x02,
									//[3] space invaders 3
									0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
									0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
									0x38, 0x1D, 0x76, 0x9C, 0x9C, 0x76, 0x1D, 0x38,
									//[4] three smiles
									0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
									0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
									0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
									//[5] space invaders 4
									0x78, 0x3D, 0x76, 0xBC, 0xBC, 0x76, 0x3D, 0x78,
									0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
									0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
									//[6] hearts
									0x1C, 0x3E, 0x7E, 0xFC, 0xFC, 0x7E, 0x3E, 0x1C,
									0x1C, 0x3E, 0x7E, 0xFC, 0xFC, 0x7E, 0x3E, 0x1C,
									0x1C, 0x3E, 0x7E, 0xFC, 0xFC, 0x7E, 0x3E, 0x1C,
									//[7] be happy
									0x00, 0xFF, 0x88, 0x88, 0x88, 0x70, 0x00, 0x70,
									0xA8, 0xA8, 0xA8, 0x30, 0x00, 0x3C, 0x42, 0x91,
									0xAD, 0xAD, 0xA1, 0xAD, 0xAD, 0x91, 0x42, 0x3C,
									};

#define COL_PORT PORTD

#define CLK 0x20
#define OUT 0x10
#define RST 0x40

#define ROW_PORT PORTB

#define ROW_DATA 0x80
#define _ROW_OUTPUT_ENABLE 0x02
#define ROW_LATCH 0x20
#define ROW_SERIAL_CLK 0x40
#define _ROW_CLR 0x10

typedef int bool;
#define true 1
#define false 0

#endif /* CONS_H_ */
