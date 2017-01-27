/*
 * OLED.cpp

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

#include "OLED.h"


#define OLED_COLS					128	//128 Pixels
#define OLED_ROWS					64	//64  Pixels

extern volatile byte I2CBlockComplete;

typedef unsigned char byte;
#define MAX_BLOCK (8 * 128)


void COLED::init() {
	cmd(0xAE);//disp off
	cmd(0xD5);//osc freq
	cmd(0x80);
	cmd(0xA8);//mux ratio
	cmd(0x3F);
	cmd(0xD3);//disp offset
	cmd(0x00);
	cmd(0x40);//disp start line
	cmd(0x8D);//charge pump
	cmd(0x14);
	cmd(0xA1);//segment remap
	cmd(0xC8);//com scan direction
	cmd(0xDA);//com pin config
	cmd(0x12);
	cmd(0x81);//contrast
	cmd(0xCF);
	cmd(0xd9);//pre charge period
	cmd(0xF1);
	cmd(0xDB);//vcomh deselect level
	cmd(0x40);
	cmd(0xA4);
	cmd(0xA6);//normal display
	//oled_send_cmd(OLED_CMD_NORMAL_DISPLAY);
	//delay_ms(10);
	cmd(0x20);
	cmd(PAGE_ADDRESSING);
	//delay_ms(10);
	cmd(0xAF); // display on
}
void COLED::cmd(byte command) {
	byte cmd[2] = {0x80, command};
	I2CBus_SelectSlaveDevice(I2CBus_DeviceData, LDD_I2C_ADDRTYPE_7BITS, COLED::I2C_ADDR);
	I2CBlockComplete = 0;
	I2CBus_MasterSendBlock(I2CBus_DeviceData, cmd, 2, LDD_I2C_SEND_STOP);
	while(!I2CBlockComplete);
}
void COLED::send(byte *data, int len){
	byte block[MAX_BLOCK + 1] = {0x40};
	memcpy(block + 1, data, len);
	I2CBus_SelectSlaveDevice(I2CBus_DeviceData, LDD_I2C_ADDRTYPE_7BITS, COLED::I2C_ADDR);
	I2CBlockComplete = 0;
	I2CBus_MasterSendBlock(I2CBus_DeviceData, block, len+1, LDD_I2C_SEND_STOP);
	while(!I2CBlockComplete);
}
void COLED::at(byte x, byte y){
	// Y - 1 unit = 1 page (8 pixel rows)
	// X - 1 unit = 8 pixel columns

	cmd(0x02 + (8*x & 0x0F)); 		//set column lower address
	cmd(0x10 + ((8*x>>4)&0x0F)); 	//set column higher address
	cmd(0xB0 + y); 					//set page address

}
/*
void COLED::cls()	{
	byte block[128 + 1] = {0x40};
	memset(&block[1], 0, 128);
	for(byte page=0; page<8; page++) {
		at(0, page);
		I2CBus_SelectSlaveDevice(I2CBus_DeviceData, LDD_I2C_ADDRTYPE_7BITS, COLED::I2C_ADDR);
		I2CBlockComplete = 0;
		I2CBus_MasterSendBlock(I2CBus_DeviceData, block, 129, LDD_I2C_SEND_STOP);
		while(!I2CBlockComplete);
	}
	at(0, 0);
}
*/
/////////////////////////////////////////////////////////////////////////////////////
//
//
//
/////////////////////////////////////////////////////////////////////////////////////
//void COLED::zero(Buf& buf) {
//	memset(&buf, 0, sizeof(Buf));
//}

/////////////////////////////////////////////////////////////////////////////////////
//
//
//
/////////////////////////////////////////////////////////////////////////////////////
void COLED::set(Buf& buf)
{

	// variable to track the row where data is coming
	// from in the source buffer
	int src_row = 0;

	// target block is made up of 8 pages of 128 bytes
	for(int page=0; page<8; ++page) {

		byte block[128 + 1] = {0x40};
		byte *dest  = block + 1;

		// This is the bit value corresponding to the row. We'll be addressing
		// this bit in each of the 128 bytes for this page
		byte dest_bit = 0x01;
		while(dest_bit) {

			// back to the first byte location of the page, ready to address
			// the next bit
			int dest_index = -2; // shift left 2 .. odd offset on oled TODO

			// there are 16 source bytes per row
			for(int src_byte = 0; src_byte < 16; ++src_byte)	{

				// fetch the appropriate byte
				byte b = buf.b[src_row][src_byte];

				// scan over bits of this byte
				uint32_t mask = 0x80;
				while(mask)
				{
					if(b & mask) {
						dest[(dest_index+128) & 0x7F] |= dest_bit; // taking into account shift left 2
					}
					mask >>= 1;
					++dest_index;
				}
			}

			// now setting the next bit
			dest_bit <<= 1;

			// next row
			++src_row;
		}

		at(0, page);
		I2CBus_SelectSlaveDevice(I2CBus_DeviceData, LDD_I2C_ADDRTYPE_7BITS, COLED::I2C_ADDR);
		I2CBlockComplete = 0;
		I2CBus_MasterSendBlock(I2CBus_DeviceData, block, 129, LDD_I2C_SEND_STOP);
		while(!I2CBlockComplete);

	}
}


