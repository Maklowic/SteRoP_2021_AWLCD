
#include "display1.h"

Tft_Display_Mode_t  Tft_Display_Mode;
Tft_Display_Setting_t TftDispSetting;

uint32_t ILI9341_CurrentFrameBuffer;
uint32_t ILI9341_CurrentLayer;
uint32_t ILI9341_CurrentOrientation;

static uint16_t SetGlobalYCursor;
static uint32_t SetGlobalCursor;

void DrawPixel_WithCords(uint16_t Xpos, uint16_t Ypos, uint32_t color)
{
	*(  uint16_t*)(SetGlobalCursor) = color;
	SetGlobalCursor = ILI9341_CurrentFrameBuffer + (2 * ((Ypos * ILI9341_X) + Xpos));
}

void DrawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color)
{
	 int steep = abs(y_end - y_start) > abs(x_end - x_start);
	 int dx = 0;
	 int dy = 0;
	 int err = 0;
	 int ystep = 0;

	 if (steep){
		kSwapVariable(x_start, y_start);
		kSwapVariable(x_end, y_end);
	 }
	 if(x_start > x_end){
		kSwapVariable(x_start, x_end);
		kSwapVariable(y_start, y_end);
	 }
	 dx = x_end - x_start;
	 dy = abs(y_end - y_start);
	 err = dx / 2;

	 if(y_start < y_end){
		 ystep = 1;
	 }
	 else{
		 ystep = -1;
	 }
	 for (; x_start <= x_end; x_start++)
	 {
		if (steep){
			DrawPixel_WithCords(y_start, x_start, color);
		}
		else{
			DrawPixel_WithCords(x_start, y_start, color);
		}
		err -= dy;
		if (err < 0){
		 y_start += ystep;
		 err += dx;
		}
	 }
}

void DrawClearRectangle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color)
{
	DrawLine(start_x, start_y, end_x, start_y, color);
	DrawLine(end_x, start_y, end_x, end_y, color);
	DrawLine(start_x, start_y, start_x, end_y, color);
	DrawLine(start_x, end_y, end_x, end_y, color);
}

void DrawCircle(uint16_t x_Position, uint16_t y_Position, int radius, uint16_t color)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	DrawPixel_WithCords(x_Position, y_Position + radius, color);
	DrawPixel_WithCords(x_Position, y_Position - radius, color);
	DrawPixel_WithCords(x_Position + radius, y_Position, color);
	DrawPixel_WithCords(x_Position - radius, y_Position, color);
	while (x < y){
		if (f >= 0){
			y--;
      ddF_y += 2;
      f += ddF_y;
		}
    x++;
    ddF_x += 2;
    f += ddF_x;
    DrawPixel_WithCords(x_Position + x, y_Position + y, color);
    DrawPixel_WithCords(x_Position - x, y_Position + y, color);
    DrawPixel_WithCords(x_Position + x, y_Position - y, color);
    DrawPixel_WithCords(x_Position - x ,y_Position - y, color);
    DrawPixel_WithCords(x_Position + y, y_Position + x, color);
    DrawPixel_WithCords(x_Position - y, y_Position + x, color);
    DrawPixel_WithCords(x_Position + y, y_Position - x, color);
    DrawPixel_WithCords(x_Position - y, y_Position - x , color);
  }
}

void FillRectangle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color)
{
    uint32_t xPosition;
    uint32_t yPosition;

    if(start_x > end_x){
        kSwapVariable(start_x, end_x);
    }
    if(start_y > end_y){
        kSwapVariable(start_y, end_y);
    }

    for(yPosition = start_y; yPosition <= end_y; yPosition++){
            for(xPosition = start_x; xPosition <= end_x; xPosition++){
                    *(uint32_t*)(ILI9341_CurrentFrameBuffer + ( 2 * (yPosition * ILI9341_X + xPosition)))
                = color;
        }
  }
}
 void DrawPolygen(vertex Vertex, uint16_t vertexCounter){
	 int16_t x = 0, y  = 0;
	 uint32_t color = 0x0000;
	 if(vertexCounter < 2){
		 return;
	 }
	 DrawLine(Vertex->X, Vertex->Y, (Vertex + vertexCounter - 1)->X, (Vertex + vertexCounter - 1)->Y, color);

	 while(--vertexCounter){
		 x = Vertex->X;
		 y = Vertex->Y;
		 Vertex++;
		 DrawLine(x, y, Vertex->X, Vertex->Y, color);
	 }
 }
 void DrawPolygen1(uint16_t x_middle, uint16_t y_middle, uint16_t x, uint16_t y, int amountOfSides){

	 uint16_t x_end, y_end;
	 uint16_t color = 0x0000;
	 double r = sqrt(pow((x - x_middle), 2) + pow((y - y_middle), 2));
	 double a = atan2(y - y_middle, x - x_middle);
	 for(int i = 1; i <= amountOfSides; i++){
		 x_end = x;
		 y_end = y;
		 a = a + PI * 2 / amountOfSides;
		 x = round((double)x_middle + (double)r * cos(a));
		 y = round((double)y_middle + (double)r * sin(a));
		 DrawLine(x, y, x_end, y_end, color);
	 }
 }

 void PolygenDrawing(uint16_t x_middle, uint16_t y_middle, uint16_t x, uint16_t y, int amountOfSides){

	 uint16_t x_end, y_end;
	 double r = sqrt(pow((x - x_middle), 2) + pow((y - y_middle), 2));
	 double a = atan2(y - y_middle, x - x_middle);
	 for(int i = 1; i <= amountOfSides; i++){
	 	x_end = x;
	 	y_end = y;
	 	a = a + PI * 2 / amountOfSides;
	 	x = round((double)x_middle + (double)r * cos(a));
	 	y = round((double)y_middle + (double)r * sin(a));
	 	BSP_LCD_DrawLine(x, y, x_end, y_end);
	 }
 }
