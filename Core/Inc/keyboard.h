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

#define COLUMN0 GPIO_PIN_0
#define COLUMN1 GPIO_PIN_1
#define COLUMN2 GPIO_PIN_2
#define COLUMN3 GPIO_PIN_3
#define COLUMN4 GPIO_PIN_4
#define COLUMN5 GPIO_PIN_5
#define COLUMN6 GPIO_PIN_6
#define COLUMN7 GPIO_PIN_7

#define ROW0    GPIO_PIN_8
#define ROW1    GPIO_PIN_9
#define ROW2    GPIO_PIN_10
#define ROW3    GPIO_PIN_11
#define ROW4    GPIO_PIN_12
#define ROW5    GPIO_PIN_13
#define ROW6    GPIO_PIN_14
#define ROW7    GPIO_PIN_15

#define COLUMN(n) (COLUMN0 << (n))
#define ROW(n) (ROW0 << (n))

#define COLUMN_OFFSET	0
#define COLUMN_PIN 		(COLUMN0|COLUMN1|COLUMN2|COLUMN3|COLUMN4|COLUMN5|COLUMN6|COLUMN7)
#define COLUMN_PORT		GPIOA
#define ROW_OFFSET     	8
#define ROW_PIN    		(ROW0|ROW1|ROW2|ROW3|ROW4|ROW5|ROW6|ROW7)
#define ROW_PORT   		GPIOB

#define KB_COLUMN 		8
#define KB_ROW    		8
#define KB_LEVEL 	    2

#define STATE_PRESS 	0
#define KEYS_PRESS_MAX 	6

#define KEY_LEVEL_INVAILD -1
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
	int8_t keylevel[KEYS_PRESS_MAX];
	uint8_t keycnt;
	uint8_t keylastlist[KEYS_PRESS_MAX];
	int8_t keylastlevel[KEYS_PRESS_MAX];
	uint8_t keylastcnt;
	uint8_t vaild;
} KeyState;

void ScanKeyState(KeyState * keystate);
void GenReport(KeyState * keystate, uint8_t * reportBuf);

#endif /* INC_KEYBOARD_H_ */
