
#ifndef INC_DISPLAY1_H_
#define INC_DISPLAY1_H_

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "stm32f429i_discovery_lcd.h"

#define PI 3.141592653589

typedef enum{
  Orientation_Portrait = 0,
  Orientation_Landscape = 1
}Tft_Display_Mode_t;

typedef struct{
  uint16_t xStartPosition;
  uint16_t yStartPosition;
  uint16_t xEndPosition;
  uint16_t yEndPosition;
  uint32_t Pixel;
}Tft_Display_Setting_t;

typedef struct{
	int16_t X;
	int16_t Y;
}Coords, *vertex;

#define  RGB_COL_BLACK          0x0000
#define  RGB_COL_BLUE           0x001F
#define  RGB_COL_GREEN          0x07E0
#define  RGB_COL_RED            0xF800
#define  RGB_COL_WHITE          0xFFFF

#define  RGB_COL_CYAN           0x07FF
#define  RGB_COL_MAGENTA        0xF81F
#define  RGB_COL_YELLOW         0xFFE0

#define  RGB_COL_GREY           0xF7DE
//--------------------------------------------------------------
#define  ILI9341_X           	((uint16_t)240)
#define  ILI9341_Y           	((uint16_t)320)
#define  ILI9341_PIXEL  			ILI9341_X*ILI9341_Y

#define  ILI9341_INIT_PAUSE   200
#define  ILI9341_SPI_PAUSE    10

//--------------------------------------------------------------
#define  ILI9341_FRAME_BUFFER     SDRAM_START_ADR
#define  ILI9341_FRAME_OFFSET   	((uint32_t)(ILI9341_PIXEL*2))

//--------------------------------------------------------------
#define ILI9341_CS_PIN             GPIO_Pin_2
#define ILI9341_CS_GPIO_PORT       GPIOC
#define ILI9341_CS_GPIO_CLK        RCC_AHB1Periph_GPIOC

//--------------------------------------------------------------
#define ILI9341_WRX_PIN            GPIO_Pin_13
#define ILI9341_WRX_GPIO_PORT      GPIOD
#define ILI9341_WRX_GPIO_CLK       RCC_AHB1Periph_GPIOD

//--------------------------------------------------------------
#define ILI9341_SLEEP_OUT            0x11   // Sleep out register
#define ILI9341_GAMMA                0x26   // Gamma register
#define ILI9341_DISPLAY_OFF          0x28   // Display off register
#define ILI9341_DISPLAY_ON           0x29   // Display on register
#define ILI9341_COLUMN_ADDR          0x2A   // Column address register
#define ILI9341_PAGE_ADDR            0x2B   // Page address register
#define ILI9341_GRAM                 0x2C   // GRAM register
#define ILI9341_MAC                  0x36   // Memory Access Control register
#define ILI9341_PIXEL_FORMAT         0x3A   // Pixel Format register
#define ILI9341_WDB                  0x51   // Write Brightness Display register
#define ILI9341_WCD                  0x53   // Write Control Display register
#define ILI9341_RGB_INTERFACE        0xB0   // RGB Interface Signal Control
#define ILI9341_FRC                  0xB1   // Frame Rate Control register
#define ILI9341_BPC                  0xB5   // Blanking Porch Control register
#define ILI9341_DFC                  0xB6   // Display Function Control register
#define ILI9341_POWER1               0xC0   // Power Control 1 register
#define ILI9341_POWER2               0xC1   // Power Control 2 register
#define ILI9341_VCOM1                0xC5   // VCOM Control 1 register
#define ILI9341_VCOM2                0xC7   // VCOM Control 2 register
#define ILI9341_POWERA               0xCB   // Power control A register
#define ILI9341_POWERB               0xCF   // Power control B register
#define ILI9341_PGAMMA               0xE0   // Positive Gamma Correction register
#define ILI9341_NGAMMA               0xE1   // Negative Gamma Correction register
#define ILI9341_DTCA                 0xE8   // Driver timing control A
#define ILI9341_DTCB                 0xEA   // Driver timing control B
#define ILI9341_POWER_SEQ            0xED   // Power on sequence register
#define ILI9341_3GAMMA_EN            0xF2   // 3 Gamma enable register
#define ILI9341_INTERFACE            0xF6   // Interface control register
#define ILI9341_PRC                  0xF7   // Pump ratio control register

#define kSwapVariable(a,b) {int16_t t=a;a=b;b=t;}

void DrawPixel_WithCords(uint16_t Xpos, uint16_t Ypos);
void DrawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
void DrawClearRectangle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);
void DrawCircle(uint16_t x_Position, uint16_t y_Position, int radius, uint16_t color);
void FillRectangle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color);
void DrawPolygen(uint16_t x_middle, uint16_t y_middle, uint16_t x, uint16_t y, int amountOfSides);
void PolygenDrawing(uint16_t x_middle, uint16_t y_middle, uint16_t x, uint16_t y, int amountOfSides);


#endif /* INC_DISPLAY1_H_ */
