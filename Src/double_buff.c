#include <stdlib.h>
#include "double_buff.h"


void DBuff_init() {
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);   //Wlaczenie pierwszej warstw
	BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER);   //Wlaczenie drugiej warstwy
	BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, DISABLE);
	BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, ENABLE);
	BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
}

void DBuff_swap_buff(void) {
  // VSYNC
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));

	    if (swap == 0) {
	        swap= 1;
	        BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, ENABLE);
	        BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, DISABLE);
	        BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
	    } else {
	        swap= 0;
	        BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, ENABLE);
	        BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, DISABLE);
	        BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
	    }
}



