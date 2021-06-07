
#ifndef INC_DOUBLE_BUFF_H_
#define INC_DOUBLE_BUFF_H_

#pragma once

#include "stm32f429i_discovery_lcd.h"

static int swap = 0;


#define LCD_WIDTH BSP_LCD_GetXSize()
#define LCD_LENGTH BSP_LCD_GetYSize()


void DBuff_init();
void DBuff_swap_buff();

#endif /* INC_DOUBLE_BUFF_H_ */
