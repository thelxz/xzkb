/*
 * keyboard.h
 *
 *  Created on: Apr 18, 2020
 *      Author: stor
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include <stdbool.h>
#include "main.h"

#define COLUMN0 GPIO_PIN_8
#define COLUMN1 GPIO_PIN_9
#define COLUMN2 GPIO_PIN_10
#define COLUMN3 GPIO_PIN_11
#define COLUMN4 GPIO_PIN_12
#define COLUMN5 GPIO_PIN_13
#define COLUMN6 GPIO_PIN_14
#define COLUMN7 GPIO_PIN_15

#define ROW0    GPIO_PIN_0
#define ROW1    GPIO_PIN_1
#define ROW2    GPIO_PIN_2
#define ROW3    GPIO_PIN_3
#define ROW4    GPIO_PIN_4
#define ROW5    GPIO_PIN_5
#define ROW6    GPIO_PIN_6
#define ROW7    GPIO_PIN_7

#define COLUMN(n) (COLUMN0 << (n))
#define ROW(n) (ROW0 << (n))

#define COLUMN_OFFSET	8
#define COLUMN_PIN 		(GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_9)
#define COLUMN_PORT		GPIOB
#define ROW_OFFSET     	0
#define ROW_PIN    		(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7)
#define ROW_PORT   		GPIOA

#define KB_COLUMN 		8
#define KB_ROW    		8
#define KB_LEVEL 	    2

#define STATE_PRESS 	0
#define KEYS_PRESS_MAX 	6

enum
{
 esc,      num1,         num2,           num3,       num4,       num5,       num6,       num7,
 num8,     num9,         num0,           charMin,    charPlus,   keyOr,      tab,        keyQ,
 keyW,     keyE,         keyR,           keyT,       keyY,       keyU,       keyI,       keyO,
 keyP,     LeftMBrace,   rightMBrace,    backspace,  lCtrl,      keyA,       keyS,       keyD,
 keyF,     keyG,         keyH,           keyJ,       keyK,       keyL,       keyColon,   keyQuot,
 KeyEnter, lShift,       keyZ,           keyX,       keyC,       keyV,       keyB,       keyN,
 keyM,     keyComma,     keyPoint,       keyQues,    rShift,     lCorner,      lFn,        lAlt,
 space,    rAlt,         rWin,           rCtrl,      rFn
};

typedef struct {
	uint8_t matrix[KB_COLUMN * KB_ROW];
	uint8_t keylist[KEYS_PRESS_MAX];
	uint8_t keycnt;
	uint8_t vaild;
} KeyState;

void ScanKeyState(KeyState * keystate);
void GenReport(KeyState * keystate, uint8_t * reportBuf);

#endif /* INC_KEYBOARD_H_ */
