
#ifndef CONS_H_
#define CONS_H_

#define DELAY_ROW 80
#define DELAY_COL 120
#define CHARS_NUMBER 8
#define CHAR_LENGTH 8
#define MATRIX_LENGTH 24
#define NUMBER_OF_GRAPHICS 4

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
