/* ###################################################################
**     Filename    : main.c
**     Project     : oled
**     Processor   : MKE02Z64VLD4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-01-11, 19:23, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "I2CBus.h"
#include "AS1.h"
#include "AS2.h"
#include "AS3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <string.h>
#include <stdlib.h>

#include "OLED.h"
#include "TUI.h"


byte digit0[6][28] = {
{	0,	0,	0,	0,	0,	0,	224,	248,	248,	246,	207,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	191,	223,	239,	246,	248,	240	},
{	0,	0,	0,	0,	192,	252,	255,	255,	255,	255,	255,	7,	0,	0,	0,	0,	0,	0,	0,	128,	252,	255,	255,	255,	255,	255,	63,	3	},
{	0,	0,	0,	128,	135,	223,	15,	15,	7,	3,	1,	0,	0,	0,	0,	0,	0,	0,	0,	3,	7,	159,	63,	31,	15,	3,	0,	0	},
{	0,	248,	255,	255,	255,	255,	255,	60,	0,	0,	0,	0,	0,	0,	0,	0,	128,	252,	254,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
{	63,	255,	255,	127,	191,	223,	227,	224,	224,	224,	224,	224,	224,	224,	224,	224,	159,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
{	0,	0,	6,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	7,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit1[6][28] = {
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	128,	192,	224,	240,	248,	240	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	128,	252,	255,	255,	255,	255,	255,	63,	3	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	7,	159,	63,	31,	15,	3,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	128,	252,	254,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	31,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit2[6][28] = {
		{	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	15,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	191,	223,	239,	246,	248,	240	},
		{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	128,	252,	255,	255,	255,	255,	255,	63,	3	},
		{	0,	0,	0,	128,	128,	192,	96,	224,	240,	248,	248,	248,	248,	248,	248,	248,	248,	248,	248,	243,	103,	31,	63,	31,	15,	3,	0,	0	},
		{	0,	248,	255,	255,	255,	255,	255,	60,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
		{	63,	255,	255,	127,	191,	223,	227,	224,	224,	224,	224,	224,	224,	224,	224,	224,	128,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
		{	0,	0,	6,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	7,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit3[6][28] = {
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	15,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	191,	223,	239,	246,	248,	240	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	128,	252,	255,	255,	255,	255,	255,	63,	3	},
{	0,	0,	0,	0,	0,	0,	96,	224,	240,	248,	248,	248,	248,	248,	248,	248,	248,	248,	248,	243,	103,	159,	63,	31,	15,	3,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	129,	253,	255,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
{	0,	0,	0,	0,	128,	192,	224,	224,	224,	224,	224,	224,	224,	224,	224,	224,	159,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
{	0,	0,	6,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	7,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit4[6][28] = {
{	0,	0,	0,	0,	0,	0,	224,	248,	248,	240,	192,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	128,	192,	224,	240,	248,	240	},
{	0,	0,	0,	0,	192,	252,	255,	255,	255,	255,	255,	7,	0,	0,	0,	0,	0,	0,	0,	128,	252,	255,	255,	255,	255,	255,	63,	3	},
{	0,	0,	0,	0,	7,	31,	111,	239,	247,	251,	249,	248,	248,	248,	248,	248,	248,	248,	248,	243,	103,	159,	63,	31,	15,	3,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	129,	253,	255,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	31,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit5[6][28] = {
		{	0,	0,	0,	0,	0,	0,	224,	248,	248,	246,	207,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	31,	15,	6,	0,	0	},
		{	0,	0,	0,	0,	192,	252,	255,	255,	255,	255,	255,	7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
		{	0,	0,	0,	0,	7,	31,	111,	239,	247,	251,	249,	248,	248,	248,	248,	248,	248,	248,	248,	240,	96,	128,	0,	0,	0,	0,	0,	0	},
		{	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	129,	253,	255,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
		{	0,	0,	0,	0,	128,	192,	224,	224,	224,	224,	224,	224,	224,	224,	224,	224,	159,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
		{	0,	0,	6,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	7,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit6[6][28] = {
{	0,	0,	0,	0,	0,	0,	224,	248,	248,	246,	207,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	31,	15,	6,	0,	0	},
{	0,	0,	0,	0,	192,	252,	255,	255,	255,	255,	255,	7,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
{	0,	0,	0,	128,	135,	223,	111,	239,	247,	251,	249,	248,	248,	248,	248,	248,	248,	248,	248,	240,	96,	128,	0,	0,	0,	0,	0,	0	},
{	0,	248,	255,	255,	255,	255,	255,	60,	1,	1,	1,	1,	1,	1,	1,	1,	129,	253,	255,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
{	63,	255,	255,	127,	191,	223,	227,	224,	224,	224,	224,	224,	224,	224,	224,	224,	159,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
{	0,	0,	6,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	7,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit7[6][28] = {
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	15,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	191,	223,	239,	246,	248,	240	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	128,	252,	255,	255,	255,	255,	255,	63,	3	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	7,	159,	63,	31,	15,	3,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	128,	252,	254,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	31,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit8[6][28] = {
{	0,	0,	0,	0,	0,	0,	224,	248,	248,	246,	207,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	191,	223,	239,	246,	248,	240	},
{	0,	0,	0,	0,	192,	252,	255,	255,	255,	255,	255,	7,	0,	0,	0,	0,	0,	0,	0,	128,	252,	255,	255,	255,	255,	255,	63,	3	},
{	0,	0,	0,	128,	135,	223,	111,	239,	247,	251,	249,	248,	248,	248,	248,	248,	248,	248,	248,	243,	103,	159,	63,	31,	15,	3,	0,	0	},
{	0,	248,	255,	255,	255,	255,	255,	60,	1,	1,	1,	1,	1,	1,	1,	1,	129,	253,	255,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
{	63,	255,	255,	127,	191,	223,	227,	224,	224,	224,	224,	224,	224,	224,	224,	224,	159,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
{	0,	0,	6,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	7,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};


byte digit9[6][28] = {
{	0,	0,	0,	0,	0,	0,	224,	248,	248,	246,	207,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	63,	191,	223,	239,	246,	248,	240	},
{	0,	0,	0,	0,	192,	252,	255,	255,	255,	255,	255,	7,	0,	0,	0,	0,	0,	0,	0,	128,	252,	255,	255,	255,	255,	255,	63,	3	},
{	0,	0,	0,	0,	7,	31,	111,	239,	247,	251,	249,	248,	248,	248,	248,	248,	248,	248,	248,	243,	103,	159,	63,	31,	15,	3,	0,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	129,	253,	255,	254,	255,	255,	255,	126,	0,	0,	0,	0	},
{	0,	0,	0,	0,	128,	192,	224,	224,	224,	224,	224,	224,	224,	224,	224,	224,	159,	127,	255,	255,	255,	127,	15,	0,	0,	0,	0,	0	},
{	0,	0,	6,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	7,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0	}
};

/*


#define OLED_COLS					128	//128 Pixels
#define OLED_ROWS					64	//64  Pixels


// registers
#define OLED_COMMAND_MODE				0x80
#define OLED_DATA_MODE				0x40

// commands
#define OLED_CMD_DISPLAY_OFF			0xAE
#define OLED_CMD_DISPLAY_ON			0xAF
#define OLED_CMD_NORMAL_DISPLAY		0xA6
#define OLED_CMD_INVERSE_DISPLAY		0xA7
#define OLED_CMD_SET_BRIGHTNESS		0x81

#define OLED_RIGHT_SCROLL				0x26
#define OLED_LEFT_SCROLL				0x27
#define OLED_SET_VERTICAL_SCROLL_AREA 0xA3
#define OLED_VERTICAL_RIGHT_SCROLL	0x29
#define OLED_VERTICAL_LEFT_SCROLL		0x2A
#define OLED_CMD_ACTIVATE_SCROLL		0x2F
#define OLED_CMD_DEACTIVATE_SCROLL	0x2E

#define HORIZONTAL_ADDRESSING	0x00
#define PAGE_ADDRESSING			0x02

#define Scroll_Left				0x00
#define Scroll_Right			0x01
#define Scroll_Up				0x02
#define Scroll_Down				0x03

#define Scroll_2Frames			0x07
#define Scroll_3Frames			0x04
#define Scroll_4Frames			0x05
#define Scroll_5Frames			0x00
#define Scroll_25Frames			0x06
#define Scroll_64Frames			0x01
#define Scroll_128Frames		0x02
#define Scroll_256Frames		0x03

#define OLED_ADDR 0x3c
typedef unsigned char byte;
volatile byte I2CBlockComplete = 0;

*/


static void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}

/*
/////////////////////////////////////////////////////////////////////
// SEND COMMAND
void oled_send_cmd(byte command){
	byte cmd[2] = {0x80, command};
	I2CBus_SelectSlaveDevice(I2CBus_DeviceData, LDD_I2C_ADDRTYPE_7BITS, OLED_ADDR);
	I2CBlockComplete = 0;
	I2CBus_MasterSendBlock(I2CBus_DeviceData, cmd, 2, LDD_I2C_SEND_STOP);
	while(!I2CBlockComplete);
}

#define MAX_BLOCK (8 * 128)
void oled_send_block(byte *data, int len){
	byte block[MAX_BLOCK + 1] = {0x40};
	memcpy(block + 1, data, len);
	I2CBus_SelectSlaveDevice(I2CBus_DeviceData, LDD_I2C_ADDRTYPE_7BITS, OLED_ADDR);
	I2CBlockComplete = 0;
	I2CBus_MasterSendBlock(I2CBus_DeviceData, block, len+1, LDD_I2C_SEND_STOP);
	while(!I2CBlockComplete);
}

void oled_at(byte x, byte y){
	// Y - 1 unit = 1 page (8 pixel rows)
	// X - 1 unit = 8 pixel columns

    oled_send_cmd(0x02 + (8*x & 0x0F)); 		//set column lower address
    oled_send_cmd(0x10 + ((8*x>>4)&0x0F)); 	//set column higher address
	oled_send_cmd(0xB0 + y); 					//set page address

}

/////////////////////////////////////////////////////////////////////
// CLEAR SCREEN
void oled_cls()	{
	byte block[128 + 1] = {0x40};
	memset(&block[1], 0, 128);
	for(byte page=0; page<8; page++) {
		oled_at(0, page);
		I2CBus_SelectSlaveDevice(I2CBus_DeviceData, LDD_I2C_ADDRTYPE_7BITS, OLED_ADDR);
		I2CBlockComplete = 0;
		I2CBus_MasterSendBlock(I2CBus_DeviceData, block, 129, LDD_I2C_SEND_STOP);
		while(!I2CBlockComplete);
	}
	oled_at(0, 0);
}
*/
COLED Oled;

void test(byte digit[][28])	{
	for(byte row=0; row<6; row++) {
		Oled.at(0, row);
		Oled.send(digit[row],28);
	}
}

void display_digit(byte n, byte col)	{
	for(byte row=0; row<6; row++) {
		Oled.at(col, row);
		switch(n)
		{
		case 0: Oled.send(digit0[row],28); break;
		case 1: Oled.send(digit1[row],28); break;
		case 2: Oled.send(digit2[row],28); break;
		case 3: Oled.send(digit3[row],28); break;
		case 4: Oled.send(digit4[row],28); break;
		case 5: Oled.send(digit5[row],28); break;
		case 6: Oled.send(digit6[row],28); break;
		case 7: Oled.send(digit7[row],28); break;
		case 8: Oled.send(digit8[row],28); break;
		case 9: Oled.send(digit9[row],28); break;
		}
	}
}

void disp_number(int n)
{
	n %= 10000;
	display_digit(n/1000, 0);
	n %= 1000;
	display_digit(n/100, 84);
	n %= 100;
	display_digit(n/10, 56);
	n %= 10;
	display_digit(n, 28);
}
/*
void oled_init(){
	//oled_send_cmd(OLED_CMD_DISPLAY_OFF);
    //delay_ms(10);
	//oled_send_cmd(0x8D);
	//oled_send_cmd(0x14);
    //delay_ms(10);

delay(100000);

	oled_send_cmd(0xAE);
	oled_send_cmd(0xD5);
	oled_send_cmd(0x80);
	oled_send_cmd(0xA8);
	oled_send_cmd(0x3F);
	oled_send_cmd(0xD3);
	oled_send_cmd(0x00);
    oled_send_cmd(0x40);
	oled_send_cmd(0x8D);
	oled_send_cmd(0x14);
	//oled_send_cmd(0x20);
	//oled_send_cmd(0x00);
    oled_send_cmd(0xA1);
    oled_send_cmd(0xC8);
    oled_send_cmd(0xDA);
    oled_send_cmd(0x12);
	oled_send_cmd(0x81);
	oled_send_cmd(0xCF);
	oled_send_cmd(0xd9);
	oled_send_cmd(0xF1);
	oled_send_cmd(0xDB);
	oled_send_cmd(0x40);
	oled_send_cmd(0xA4);
	oled_send_cmd(0xA6);



	//oled_send_cmd(OLED_CMD_NORMAL_DISPLAY);
    //delay_ms(10);


	oled_send_cmd(0x20);
	oled_send_cmd(PAGE_ADDRESSING);
    //delay_ms(10);

	oled_send_cmd(0xAF);
    //delay_ms(10);
oled_cls();

int z = 0;
	for(;;) {
		int d = 0;//1000000;
		disp_number(z++);
//		int d = 0;
	}
	//oled_at(0,0);
}
*/

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  Oled.init();
  //Oled.cls();

  COLED::Buf b;
  tui::Tools::clear(b);
/*
  for(int i=0; i<64; i+=2) {
	  b.d[i][0] = (uint32_t)0xAAAAAAAA;
	  b.d[i][1] = (uint32_t)0xAAAAAAAA;
	  b.d[i][2] = (uint32_t)0xAAAAAAAA;
	  b.d[i][3] = (uint32_t)0xAAAAAAAA;

	  b.d[i+1][0] = (uint32_t)0x55555555;
	  b.d[i+1][1] = (uint32_t)0x55555555;
	  b.d[i+1][2] = (uint32_t)0x55555555;
	  b.d[i+1][3] = (uint32_t)0x55555555;
  }*/

/*
  b.d[0][0] = (uint32_t)0b11111111;
  b.d[1][0] = (uint32_t)0b10000001;
  b.d[2][0] = (uint32_t)0b10000011;
  b.d[3][0] = (uint32_t)0b10000111;
  b.d[4][0] = (uint32_t)0b10001111;
  b.d[5][0] = (uint32_t)0b10011111;
  b.d[6][0] = (uint32_t)0b10111111;
  b.d[7][0] = (uint32_t)0b11111111;

  b.d[8][1] = (uint32_t)0b11111111;
  b.d[9][1] = (uint32_t)0b10000001;
  b.d[10][1] = (uint32_t)0b10000011;
  b.d[11][1] = (uint32_t)0b10000111;
  b.d[12][1] = (uint32_t)0b10001111;
  b.d[13][1] = (uint32_t)0b10011111;
  b.d[14][1] = (uint32_t)0b10111111;
  b.d[15][1] = (uint32_t)0b11111111;

  b.d[16][2] = (uint32_t)0b11111111;
  b.d[17][2] = (uint32_t)0b10000001;
  b.d[18][2] = (uint32_t)0b10000011;
  b.d[19][2] = (uint32_t)0b10000111;
  b.d[20][2] = (uint32_t)0b10001111;
  b.d[21][2] = (uint32_t)0b10011111;
  b.d[22][2] = (uint32_t)0b10111111;
  b.d[23][2] = (uint32_t)0b11111111;

  b.d[24][3] = (uint32_t)0b11111111;
  b.d[25][3] = (uint32_t)0b10000001;
  b.d[26][3] = (uint32_t)0b10000011;
  b.d[27][3] = (uint32_t)0b10000111;
  b.d[28][3] = (uint32_t)0b10001111;
  b.d[29][3] = (uint32_t)0b10011111;
  b.d[30][3] = (uint32_t)0b10111111;
  b.d[31][3] = (uint32_t)0b11111111;

  b.d[32][0] = (uint32_t)0b11111111;
  b.d[33][0] = (uint32_t)0b10000001;
  b.d[34][0] = (uint32_t)0b10000011;
  b.d[35][0] = (uint32_t)0b10000111;
  b.d[36][0] = (uint32_t)0b10001111;
  b.d[37][0] = (uint32_t)0b10011111;
  b.d[38][0] = (uint32_t)0b10111111;
  b.d[39][0] = (uint32_t)0b11111111;

  b.d[40][1] = (uint32_t)0b11111111;
  b.d[41][1] = (uint32_t)0b10000001;
  b.d[42][1] = (uint32_t)0b10000011;
  b.d[43][1] = (uint32_t)0b10000111;
  b.d[44][1] = (uint32_t)0b10001111;
  b.d[45][1] = (uint32_t)0b10011111;
  b.d[46][1] = (uint32_t)0b10111111;
  b.d[47][1] = (uint32_t)0b11111111;

  b.d[48][2] = (uint32_t)0b11111111;
  b.d[49][2] = (uint32_t)0b10000001;
  b.d[50][2] = (uint32_t)0b10000011;
  b.d[51][2] = (uint32_t)0b10000111;
  b.d[52][2] = (uint32_t)0b10001111;
  b.d[53][2] = (uint32_t)0b10011111;
  b.d[54][2] = (uint32_t)0b10111111;
  b.d[55][2] = (uint32_t)0b11111111;

  b.d[56][3] = (uint32_t)0b11111111;
  b.d[57][3] = (uint32_t)0b10000001;
  b.d[58][3] = (uint32_t)0b10000011;
  b.d[59][3] = (uint32_t)0b10000111;
  b.d[60][3] = (uint32_t)0b10001111;
  b.d[61][3] = (uint32_t)0b10011111;
  b.d[62][3] = (uint32_t)0b10111111;
  b.d[63][3] = (uint32_t)0b11111111;
*/
  /*
  while(1)
  {
	int x1 = rand()%128;
	int x2 = rand()%128;
	int y1 = rand()%64;
	int y2 = rand()%64;
	if(x1 > x2) {int t = x1; x1=x2; x2=t;}
	if(y1 > y2) {int t = y1; y1=y2; y2=t;}
  tui::Tools::clear(b,x1,y1,x2,y2);
  tui::Tools::box(b,x1,y1,x2,y2);;

  Oled.set(b);
  //delay(100000);
  }*/


/*
uint16_t d[] = {
  0,
  195,
  231,
  255,
  219,
  219,
  219,
  219,
  195,
  195,
  195,
  195,
  195,
  195,
  195,
  0
};

for(int j=0; j<16; ++j)
{
	  b.d[j][0] = d[j];
}
*/

  //tui::Tools::text(b,0,0,"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
  tui::Tools::draw_text(b,0,0,"0123456789");
  tui::Tools::draw_text(b,10,10,"0123456789");
  Oled.set(b);
  /* Write your code here */
  /* For example: for(;;) { } */
  //disp_number(0);
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
