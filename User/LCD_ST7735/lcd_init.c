#include "lcd_init.h"
#include "pbdata.h"
#include "spi.h"


uint8_t SendBuffer[256];

void LCD_GPIO_Init(void) {
#if SPI_HARDWARE_SOFTWARE == 1
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, LCD_CS_Pin | LCD_SCL_Pin | LCD_SDA_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, LCD_RES_Pin | LCD_DC_Pin | LCD_BLK_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : PAPin PAPin PAPin */
    GPIO_InitStruct.Pin = LCD_CS_Pin | LCD_SCL_Pin | LCD_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PBPin PBPin PBPin */
    GPIO_InitStruct.Pin = LCD_RES_Pin | LCD_DC_Pin | LCD_BLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#else
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, LCD_CS_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, LCD_RES_Pin | LCD_DC_Pin | LCD_BLK_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : PAPin PAPin PAPin */
    GPIO_InitStruct.Pin = LCD_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PBPin PBPin PBPin */
    GPIO_InitStruct.Pin = LCD_RES_Pin | LCD_DC_Pin | LCD_BLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
}

void LCD_spi_init(void) {
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) {
#if SPI_HARDWARE_SOFTWARE == 1
    u8 i;
    LCD_CS_Clr();
    for (i = 0; i < 8; i++) {
        LCD_SCLK_Clr();
        if (dat & 0x80) {
            LCD_MOSI_Set();
        } else {
            LCD_MOSI_Clr();
        }
        LCD_SCLK_Set();
        dat <<= 1;
    }
    LCD_CS_Set();
#else
    LCD_CS_Clr();
    HAL_SPI_Transmit(&hspi1, &dat, 1, HAL_MAX_DELAY);
    LCD_CS_Set();
#endif
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat) {
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat) {
    LCD_Writ_Bus(dat >> 8);
    LCD_Writ_Bus(dat);
}

void LCD_WR_DATA_DMA(u8 *dat, u32 len) {
    LCD_CS_Clr();
    HAL_SPI_Transmit_DMA(&hspi1, dat, len);
    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
    LCD_CS_Set();
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat) {
    LCD_DC_Clr(); //写命令
    LCD_Writ_Bus(dat);
    LCD_DC_Set(); //写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2) {
    if (USE_HORIZONTAL == 0) {
        LCD_WR_REG(0x2a); //列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); //行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); //储存器写
    } else if (USE_HORIZONTAL == 1) {
        LCD_WR_REG(0x2a); //列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); //行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); //储存器写
    } else if (USE_HORIZONTAL == 2) {
        LCD_WR_REG(0x2a); //列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); //行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); //储存器写
    } else {
        LCD_WR_REG(0x2a); //列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); //行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); //储存器写
    }
}

void LCD_Init(void) {
    LCD_GPIO_Init(); //初始化GPIO
    LCD_spi_init();
    LCD_RES_Clr(); //复位
    delay_ms(100);
    LCD_RES_Set();
    delay_ms(100);

    LCD_BLK_Set(); //打开背光
    delay_ms(100);

    LCD_WR_REG(0x11); //Sleep out
    delay_ms(120); //Delay 120ms

    //------------------------------------ST7735S Frame rate-------------------------------------------------//
    LCD_WR_REG(0xB1); //Frame rate 80Hz
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x35);
    LCD_WR_DATA8(0x36);
    LCD_WR_REG(0xB2); //Frame rate 80Hz
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x35);
    LCD_WR_DATA8(0x36);
    LCD_WR_REG(0xB3); //Frame rate 80Hz
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x35);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x35);
    LCD_WR_DATA8(0x36);
    //------------------------------------End ST7735S Frame rate-------------------------------------------//
    LCD_WR_REG(0xB4); //Dot inversion
    LCD_WR_DATA8(0x03);
    //------------------------------------ST7735S Power Sequence-----------------------------------------//
    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0xA2);
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x84);
    LCD_WR_REG(0xC1);
    LCD_WR_DATA8(0xC5);
    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x00);
    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x8D);
    LCD_WR_DATA8(0x2A);
    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x8D);
    LCD_WR_DATA8(0xEE);
    //---------------------------------End ST7735S Power Sequence---------------------------------------//
    LCD_WR_REG(0xC5); //VCOM
    LCD_WR_DATA8(0x0a);
    LCD_WR_REG(0x36);
    if (USE_HORIZONTAL == 0)LCD_WR_DATA8(0x08);
    else if (USE_HORIZONTAL == 1)LCD_WR_DATA8(0xC8);
    else if (USE_HORIZONTAL == 2)LCD_WR_DATA8(0x78);
    else LCD_WR_DATA8(0xA8);
    //------------------------------------ST7735S Gamma Sequence-----------------------------------------//
    LCD_WR_REG(0XE0);
    LCD_WR_DATA8(0x12);
    LCD_WR_DATA8(0x1C);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x25);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x27);
    LCD_WR_DATA8(0x2F);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x10);
    LCD_WR_REG(0XE1);
    LCD_WR_DATA8(0x12);
    LCD_WR_DATA8(0x1C);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x2D);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x23);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x2F);
    LCD_WR_DATA8(0x3B);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x10);
    //------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
    LCD_WR_REG(0x3A); //65k mode
    LCD_WR_DATA8(0x05);
    LCD_WR_REG(0x29); //Display on
} 







