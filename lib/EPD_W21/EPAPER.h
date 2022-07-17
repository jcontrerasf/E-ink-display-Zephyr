#ifndef __EPAPER_H
#define __EPAPER_H
//#include "stm32f10x.h"
//250*122///////////////////////////////////////


#include <device.h>
#include <zephyr/types.h>
#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <sys/printk.h>


/* The devicetree node identifier for the "led0" alias. */
#define RES DT_ALIAS(respin) //res
#define EPD_CS DT_ALIAS(cspin) //cs
#define EPD_DC DT_ALIAS(dcpin) //dc
#define EPD_BUSY DT_ALIAS(busypin) //busy
//#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec edp_res_pin  = GPIO_DT_SPEC_GET(RES, gpios);
static const struct gpio_dt_spec edp_cs_pin   = GPIO_DT_SPEC_GET(EPD_CS, gpios);
static const struct gpio_dt_spec edp_dc_pin   = GPIO_DT_SPEC_GET(EPD_DC, gpios);
static const struct gpio_dt_spec edp_busy_pin = GPIO_DT_SPEC_GET(EPD_BUSY, gpios);
//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

#define SPI_BUS DT_NODELABEL(spi1)

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES 25// =200/8
#define MAX_COLUMN_BYTES  200

#define ALLSCREEN_GRAGHBYTES	5000

///////////////////////////GPIO Settings//////////////////////////////////////////////////////

//#define EPD_W21_MOSI_0	GPIO_ResetBits(GPIOD, GPIO_Pin_10)
//#define EPD_W21_MOSI_1	GPIO_SetBits(GPIOD, GPIO_Pin_10)

//#define EPD_W21_CLK_0	GPIO_ResetBits(GPIOD, GPIO_Pin_9)
//#define EPD_W21_CLK_1	GPIO_SetBits(GPIOD, GPIO_Pin_9)

#define EPD_W21_CS_0	gpio_pin_set_dt(&edp_cs_pin, 0); //GPIO_ResetBits(GPIOD, GPIO_Pin_8)
#define EPD_W21_CS_1	gpio_pin_set_dt(&edp_cs_pin, 1); //GPIO_SetBits(GPIOD, GPIO_Pin_8)

#define EPD_W21_DC_0	gpio_pin_set_dt(&edp_dc_pin, 0); //GPIO_ResetBits(GPIOE, GPIO_Pin_15)
#define EPD_W21_DC_1	gpio_pin_set_dt(&edp_dc_pin, 1); //GPIO_SetBits(GPIOE, GPIO_Pin_15)

#define EPD_W21_RST_0	gpio_pin_set_dt(&edp_res_pin, 0); //GPIO_ResetBits(GPIOE, GPIO_Pin_14)
#define EPD_W21_RST_1	gpio_pin_set_dt(&edp_res_pin, 1); //GPIO_SetBits(GPIOE, GPIO_Pin_14)

#define EPD_W21_BUSY_LEVEL 0
#define isEPD_W21_BUSY gpio_pin_get_dt(&edp_busy_pin) //GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13) 


void driver_delay_xms(int32_t xms);			
void Epaper_READBUSY(void);
void Epaper_Spi_WriteByte(uint8_t TxData);
void Epaper_Write_Command(uint8_t cmd);
void Epaper_Write_Data(uint8_t data);

void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Update(void);

void EPD_Part_Init(void);//Local refresh initialization
void EPD_Part_Update(void); 

void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);
//Display 
void EPD_WhiteScreen_ALL(const unsigned char *datas);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);
void EPD_Dis_Part_myself(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
											   unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      );
#endif


