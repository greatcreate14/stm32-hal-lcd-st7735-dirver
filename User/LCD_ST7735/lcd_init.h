#ifndef _LCD_INIT_H
#define _LCD_INIT_H

#include "stm32f1xx_hal.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define USE_HORIZONTAL 1 //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#define SPI_HARDWARE_SOFTWARE 0 //0:hardware SPI 1:software SPI
#define HARDWARE_SPI_DMA 1  //0:Unable 1:Enable

#define LCD_W 128
#define LCD_H 160

#define LCD_CS_Pin GPIO_PIN_4
#define LCD_CS_GPIO_Port GPIOA
#define LCD_SCL_Pin GPIO_PIN_5
#define LCD_SCL_GPIO_Port GPIOA
#define LCD_SDA_Pin GPIO_PIN_7
#define LCD_SDA_GPIO_Port GPIOA
#define LCD_RES_Pin GPIO_PIN_0
#define LCD_RES_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOB
#define LCD_BLK_Pin GPIO_PIN_10
#define LCD_BLK_GPIO_Port GPIOB

//-----------------LCD端口定义---------------- 

#define LCD_SCLK_Clr() do{HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, GPIO_PIN_RESET);}while(0)//SCL=SCLK
#define LCD_SCLK_Set() do{HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, GPIO_PIN_SET);}while(0)

#define LCD_MOSI_Clr() do{HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_RESET);}while(0)//SDA=MOSI
#define LCD_MOSI_Set() do{HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, GPIO_PIN_SET);}while(0)

#define LCD_RES_Clr()  do{HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET);}while(0)//RES
#define LCD_RES_Set()  do{HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET);}while(0)

#define LCD_DC_Clr()   do{HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);}while(0)//DC
#define LCD_DC_Set()   do{HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);}while(0)

#define LCD_CS_Clr()   do{HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);}while(0)//CS
#define LCD_CS_Set()   do{HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);}while(0)

#define LCD_BLK_Clr()  do{HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_RESET);}while(0)//BLK
#define LCD_BLK_Set()  do{HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_SET);}while(0)

extern uint8_t SendBuffer[256];

void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//SPI
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_DATA_DMA(u8 *dat, u32 len);//dma写入数据
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




