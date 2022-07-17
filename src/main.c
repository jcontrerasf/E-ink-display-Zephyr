#include <zephyr.h>
#include "epaper.h" 
#include "picture.h"

void gpio_init(){
    if (!device_is_ready(edp_cs_pin.port) && !device_is_ready(edp_dc_pin.port)) {
		printk("GPIO port initialization error\n");
		return;
	}
	int ret;
	ret = gpio_pin_configure_dt(&edp_cs_pin, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}
	ret = gpio_pin_configure_dt(&edp_dc_pin, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}
	ret = gpio_pin_configure_dt(&edp_res_pin, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}
	ret = gpio_pin_configure_dt(&edp_busy_pin, GPIO_INPUT | GPIO_PULL_UP);
	if (ret < 0) {
		return;
	}

	printk("GPIO pins initialized correctly\n");
    ret = gpio_pin_set_dt(&edp_res_pin, 0);
    printk("pin reset low: %d\n", ret);
}

void main(void)
{
	unsigned char fen_L,fen_H,miao_L,miao_H;
	gpio_init();
	
    while(1)
    {
	  //Full screen refresh
		EPD_HW_Init(); //Electronic paper initialization
	 	EPD_WhiteScreen_ALL(gImage_1); //Refresh the picture in full screen
        driver_delay_xms(3000);
		EPD_WhiteScreen_ALL(gImage_2); //Refresh the picture in full screen
        driver_delay_xms(3000);
		EPD_WhiteScreen_ALL(gImage_3); //Refresh the picture in full screen
        driver_delay_xms(3000);
		EPD_WhiteScreen_ALL(gImage_4); //Refresh the picture in full screen
        driver_delay_xms(3000);

//////////////////////Partial refresh digital presentation//////////////////////////////////////
        EPD_HW_Init(); //Electronic paper initialization	
	    EPD_SetRAMValue_BaseMap(gImage_logo);  //Partial refresh background color 
	    EPD_Dis_Part(0,32,gImage_num1,32,32); //x,y,DATA,Resolution 32*32
		EPD_Dis_Part(0,32,gImage_num2,32,32); //x,y,DATA,Resolution 32*32
		EPD_Dis_Part(0,32,gImage_num3,32,32); //x,y,DATA,Resolution 32*32
	    driver_delay_xms(1000);	
			//Clear screen
		EPD_HW_Init(); //Electronic paper initialization
		EPD_WhiteScreen_White(); //Show all white
	
//////////////////////Partial refresh time demo/////////////////////////////////////
        EPD_HW_Init(); //Electronic paper initialization	
	    EPD_SetRAMValue_BaseMap(gImage_basemap); //Partial refresh background color  		
		for(fen_H=0;fen_H<6;fen_H++)
		{
            for(fen_L=0;fen_L<10;fen_L++)
            {
                for(miao_H=0;miao_H<6;miao_H++) 	
                {
                    for(miao_L=0;miao_L<10;miao_L++)
                    {
                        EPD_Dis_Part_myself(64,40,Num[miao_L],         //x-A,y-A,DATA-A
                                                                64,72,Num[miao_H],         //x-B,y-B,DATA-B
                                                                64,112,gImage_numdot,       //x-C,y-C,DATA-C
                                                                64,154,Num[fen_L],         //x-D,y-D,DATA-D
                                                                64,186,Num[fen_H],32,64);	 //x-E,y-E,DATA-E,Resolution 32*64

                    if((fen_L==0)&&(miao_H==0)&&(miao_L==9))
                                            goto Clear;
                        
                    }
                }
            
            }
	    }
		
////////////////////////////////////////////////////////////////////////	
			//Clear screen
		Clear:
		EPD_HW_Init(); //Electronic paper initialization
		EPD_WhiteScreen_White(); //Show all white
		EPD_DeepSleep();  //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
		while(1);		

    }
///////////////////////////////////////////////////////////
}