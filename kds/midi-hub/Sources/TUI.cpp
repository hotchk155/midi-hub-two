/*
 * TUI.cpp
 *
 *  Created on: 26 Jan 2017
 *      Author: Jason
 */

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
#include "TUI.h"

#define CHAR_HEIGHT 16

static const byte char_set[][CHAR_HEIGHT] = {
			{60,126,195,195,195,195,255,255,195,195,195,195,195,195,0,0}, //A
			{252,254,195,195,195,195,254,254,195,195,195,195,254,252,0,0}, //B
			{126,255,195,192,192,192,192,192,192,192,192,195,255,126,0,0}, //C
			{252,254,195,195,195,195,195,195,195,195,195,195,255,254,0,0}, //D
			{255,255,192,192,192,192,254,254,192,192,192,192,255,255,0,0}, //E
			{255,255,192,192,192,192,254,254,192,192,192,192,192,192,0,0}, //F
			{124,254,195,192,192,192,207,207,195,195,195,195,255,126,0,0}, //G
			{195,195,195,195,195,195,255,255,195,195,195,195,195,195,0,0}, //H
			{255,255,24,24,24,24,24,24,24,24,24,24,255,255,0,0}, //I
			{3,3,3,3,3,3,3,3,3,3,3,195,255,126,0,0}, //J
			{195,198,204,216,240,224,192,192,224,240,216,204,198,195,0,0}, //K
			{192,192,192,192,192,192,192,192,192,192,192,192,255,255,0,0}, //L
			{195,231,255,219,219,219,219,195,195,195,195,195,195,195,0,0}, //M
			{195,195,195,195,227,243,219,207,199,195,195,195,195,195,0,0}, //N
			{126,255,195,195,195,195,195,195,195,195,195,195,255,126,0,0}, //O
			{252,254,195,195,195,195,254,254,192,192,192,192,192,192,0,0}, //P
			{126,255,195,195,195,195,195,195,195,203,207,199,255,127,0,0}, //Q
			{252,254,195,195,195,195,254,254,224,240,216,204,198,195,0,0}, //R
			{126,255,195,192,192,192,254,127,3,3,3,195,255,126,0,0}, //S
			{255,255,24,24,24,24,24,24,24,24,24,24,24,24,0,0}, //T
			{195,195,195,195,195,195,195,195,195,195,195,195,255,126,0,0}, //U
			{195,195,195,195,195,195,195,195,195,195,195,102,62,24,0,0}, //V
			{195,195,195,195,195,195,195,219,219,219,219,255,231,195,0,0}, //W
			{195,195,195,195,102,60,24,24,60,102,195,195,195,195,0,0}, //X
			{195,195,195,195,102,60,24,24,24,24,24,24,24,24,0,0}, //Y
			{255,255,3,3,6,12,24,48,96,192,192,192,255,255,0,0}, //Z

			{126,255,195,195,199,207,219,243,227,195,195,195,255,126,0,0}, //0
			{24,56,120,88,24,24,24,24,24,24,24,24,255,255,0,0}, //1
			{126,255,195,3,3,3,127,126,192,192,192,195,255,255,0,0}, //2
			{126,255,195,3,3,3,62,62,3,3,3,195,255,126,0,0}, //3
			{30,30,54,54,102,102,198,198,255,255,6,6,6,6,0,0}, //4
			{127,255,192,192,192,192,254,127,3,3,3,195,255,126,0,0}, //5
			{126,255,195,192,192,192,254,255,195,195,195,195,255,126,0,0}, //6
			{255,255,3,6,6,12,12,24,24,48,48,96,96,192,0,0}, //7
			{126,255,195,195,195,195,126,255,195,195,195,195,255,126,0,0}, //8
			{126,255,195,195,195,195,127,127,3,3,3,195,255,126,0,0} //9
};

/*
static const byte char_set[] = {

1,1,1,1,1,0,1,0, //!
5,5,0,0,0,0,0,0, //"
10,10,31,10,31,10,10,0, //#
2,7,4,7,1,7,2,0, //$
0,0,25,26,4,11,19,0, //%
0,4,10,4,11,10,5,0, //&
1,1,0,0,0,0,0,0, //'
1,2,2,2,2,2,2,1, //(
2,1,1,1,1,1,1,2, //)
0,5,2,7,2,5,0,0, //*
0,2,2,7,2,2,0,0, //+
0,0,0,0,0,1,1,2, //,
0,0,0,7,0,0,0,0, //-
0,0,0,0,0,0,1,0, //.
0,1,1,2,2,4,4,0, ///

6,9,11,13,9,9,6,0, //0
2,6,2,2,2,2,7,0, //1
6,9,1,6,8,8,15,0, //2
6,9,1,6,1,9,6,0, //3
1,3,5,9,15,1,1,0, //4
15,8,8,6,1,9,6,0, //5
6,9,8,14,9,9,6,0, //6
15,1,1,2,4,4,4,0, //7
6,9,9,6,9,9,6,0, //8
6,9,9,7,1,9,6,0, //9

0,0,0,1,0,1,0,0,//:
0,0,0,1,0,1,1,2, //;
0,1,2,4,2,1,0,0, //<
0,0,7,0,7,0,0,0, //=
0,4,2,1,2,4,0,0, //>
2,5,1,2,2,0,2,0, //?
14,17,17,23,21,23,16,15, //@

6,9,9,15,9,9,9,0, //A
14,9,9,14,9,9,14,0, //B
6,9,8,8,8,9,6,0, //C
14,9,9,9,9,9,14,0, //D
15,8,8,14,8,8,15,0, //E
15,8,8,14,8,8,8,0, //F
6,9,8,11,9,9,7,0, //G
9,9,9,15,9,9,9,0, //H
7,2,2,2,2,2,7,0, //I
15,1,1,1,1,9,6,0, //J
9,10,12,8,12,10,9,0, //K
8,8,8,8,8,8,15,0, //L
17,27,21,17,17,17,17,0, //M
9,9,13,11,9,9,9,0, //N
6,9,9,9,9,9,6,0, //O
14,9,9,14,8,8,8,0, //P
6,9,9,9,11,9,7,0, //Q
14,9,9,14,9,9,9,0, //R
6,9,8,6,1,9,6,0, //S
31,4,4,4,4,4,4,0, //T
9,9,9,9,9,9,6,0, //U
9,9,9,9,9,10,12,0, //V
17,17,17,17,21,27,17,0, //W
17,17,10,4,10,17,17,0, //X
17,17,10,4,4,4,4,0, //Y
31,1,2,4,8,16,31,0, //Z

3,2,2,2,2,2,2,3, //[
0,4,4,2,2,1,1,0, // backslash
3,1,1,1,1,1,1,3, //]
2,5,0,0,0,0,0,0, //^
0,0,0,0,0,0,0,7, //_

0b01111110,
0b10000001,
0b10100101,
0b10000001,
0b10100101,
0b10111101,
0b10000001,
0b01111110,

0,0,14,1,7,9,7,0, //a
8,8,14,9,9,9,14,0, //b
0,0,6,9,8,9,6,0, //c
1,1,7,9,9,9,7,0, //d
0,0,6,9,15,8,6,0, //e
3,4,4,6,4,4,4,0, //f
0,0,7,9,9,7,1,14, //g
8,8,14,9,9,9,9,0, //h
1,0,1,1,1,1,1,0, //i
1,0,1,1,1,1,1,2, //j
8,8,9,10,12,10,9,0, //k
2,2,2,2,2,2,1,0, //l
0,0,30,21,21,17,17,0, //m
0,0,14,9,9,9,9,0, //n
0,0,6,9,9,9,6,0, //o
0,0,14,9,9,14,8,8, //p
0,0,7,9,9,7,1,1, //q
0,0,14,9,8,8,8,0, //r
0,0,7,8,6,1,14,0, //s
2,2,3,2,2,2,1,0, //t
0,0,9,9,9,9,7,0, //u
0,0,9,9,9,10,12,0, //v
0,0,17,17,21,21,27,0, //w
0,0,17,10,4,10,17,0, //x
0,0,9,9,9,7,1,14, //y
0,0,31,2,4,8,31,0, //z


1,2,2,4,2,2,2,1, //{
1,1,1,1,1,1,1,1, //|
4,2,2,1,2,2,2,4, //}
5,10,0,0,0,0,0,0 //~

};
*/


/////////////////////////////////////////////////////////////////////////
// Lookup the 8 raster rows for an ASCII character. Unknown characters
// are blanks. The function return the width of the character
static int lookup_char(char ch, byte *buf)
{
  int index;
  if(ch >= 'a' && ch <= 'z') {
	  index = ch - 'a';
  }
  else if(ch >= 'A' && ch <= 'Z') {
	  index = ch - 'A';
  }
  else if(ch >= '0' && ch <= '9') {
	  index = 26 + ch - '0';
  }
  else {
    memset(buf, 0, 8);
    return 3;
  }
	byte mask = 0;
	const byte *p = char_set[index];
	for(int i=0; i<CHAR_HEIGHT; ++i) {
	  buf[i] = p[i];
	  mask |= buf[i];
	}
	if(mask & 0x80) {  return 8; }
	if(mask & 0x40) {  return 7; }
	if(mask & 0x20) {  return 6; }
	if(mask & 0x10) {  return 5; }
	if(mask & 0x08) {  return 4; }
	if(mask & 0x04) {  return 3; }
	if(mask & 0x02) {  return 2; }
	if(mask & 0x01) {  return 1; }
	return 3;
}

// prepare a 128 bit mask in an array of 16 byte
// where bits (from..to) are set and all others reset.
// from, to are values in the range 0-127
static void make_mask(byte *mask, int x1, int x2) {
	memset(mask, 0, 16);

	// for each of the 16 bytes of the mask
	for(int n=0; n<16; ++n) {

		// get the extent of this byte as measured within the
		// 128 bits (0..127) of the scan row
		int from = n*8;
		int to = from + 7; // inclusive

		// is the word entirely within the target position range
		if(from >= x1 && to <= x2) {
			// OK the word is entirely within the bounds
			//  <----------------> (x1..x2)
			//       wwwwwwww      this word (from..to)
			// mask the complete word
			mask[n] = ~0;
		}
		// does the word extend from below end of bounds to inside bounds?
		else if(from < x1 && to >= x1 && to <= x2) {
			//       <----------------> (x1..x2)
			//  wwwwwwww      this word (from..to)
			// mask low bits of the word
			int c = to - x1;
			do {
				mask[n] <<= 1;
				mask[n] |= 0x01;
			} while(c-- > 0);
		}
		// does the word extend from within bounds to outside upper end
		else if(from >= x1 && from <= x2 && to > x2) {
			//
			//  <----------------> (x1..x2)
			//               wwwwwwww      this word (from..to)
			// mask high bits of the word
			int c = x2 - from;
			do {
				mask[n] >>= 1;
				mask[n] |= 0x80;
			} while(c-- > 0);
		}
		// does the word completely include the bounds?
		else if(from <= x1 && to >= x2) {
			//
			//        <----> (x1..x2)
			//     wwwwwwwwwwwww      this word (from..to)
			byte m = (byte)1<<(to-x2);
			int c = x2 - x1;
			do {
				mask[n] <<= 1;
				mask[n] |= m;
			} while(c-- > 0);
		}

	}
}

//////////////////////////////////////////////////////////////////////////////////////
//
// tui:Tools public implementation
//
//////////////////////////////////////////////////////////////////////////////////////
void tui::Tools::render_text(Bitmap& bmp, const char *text)
{
	bmp.alloc(CHAR_HEIGHT, 128);

	// this is the column position (0-127) at the start of the next character
	// from left to right
	int pos = 0;
	while(*text && pos < 128)
	{

	    // get the definition and width of the next character
	    byte char_bitmap[CHAR_HEIGHT];
	    int width = lookup_char(*text, char_bitmap);

	    // the shifted character bytes will be OR'd into the target
	    // buffer

	    // 0         1         2         3         4
	    // 01234567890123456789012345678901234567890123456789... pos
	    //        0       1       2       3       4       5..  dest_byte
	    // 765432107654321076543210765432107654321076543210..  dest_bit
        //             AAAAAAA
	    //             ^-pos (=12)

	    //              1         0
	    //         5432109876543210
	    //                  AAAAAAA (width = 7)
        //                  ^ aligned pos (=17)

	    // the byte column index to be addressed for this pixel
	    // column position
	    int dest_byte = pos / 8; //1

	    int aligned_pos = (dest_byte+2) * 8 - width;



	    // all characters are right justified in the 8 byte map, so they may
	    // need to be left shifted to align them with the target column position
	    // within the target bytes
	    int left_shift = aligned_pos - pos;



	    // now need to transfer the data for each of the 8 scan rows of the character
	    for(int row=0; row < CHAR_HEIGHT; ++row)
		{
	    	// get the shifted data in a 16 bit word
	    	uint16_t shifted_word = (((uint16_t)char_bitmap[row])<<left_shift);

	    	// OR the upper byte of the word into the first target byte
	    	int index = row*bmp.scan_row+dest_byte;
	    	bmp.data[index] |= (byte)(shifted_word >> 8);

	    	// OR the lower byte of the word into the second target byte
	        if(dest_byte < 15) {
	        	bmp.data[index+1] |= (byte)shifted_word;
	        }
		}
	    pos+=(width+2);
	    ++text;
	}
}

void tui::Tools::draw_bitmap(COLED::Buf& buf, int x, int y, Bitmap& bmp)
{
	// word out how many of the 16 target scan row bytes will be updated
	// by this bitmap
	int first_byte = x/8;
	int last_byte = (x+bmp.width-1)/8;
	int num_bytes = last_byte-first_byte+1;

	// each byte will be shifted to the left 8 places then back to the
	// right up to 7 places to align it with the required position
	int left_shift = 8-x%8;

	// loop to copy each row of the bitmap
	for(int row=0; row<bmp.height; ++row) {

		// store a pointer to the start of the source bitmap scan row
		byte *src = &bmp.data[row * bmp.scan_row];

		// store a pointer to the first destination byte on this row
		byte *dst = &buf.b[y + row][first_byte];

		// loop over the required number of bytes to copy the row of the bitmap
		byte carryover = 0;
		for(int j = 0; j<num_bytes; ++j) {

			uint16_t shifted = ((uint16_t)src[j])<<left_shift;
			dst[j] |= ((byte)(shifted >> 8) |carryover);
			carryover = (byte)shifted;
		}
	}

}

void tui::Tools::clear(COLED::Buf& buf)
{
	memset(buf.b,0,sizeof(buf.b));
}


void tui::Tools::clear(COLED::Buf& buf, int x1, int y1, int x2, int y2, byte fill)
{

	byte mask[16];
	make_mask(mask, x1 , x2);

	// now apply the mask
	for(int y=y1; y <= y2; ++y) {
		for(int b=0; b<8; ++b) {
			if(fill) {
				buf.b[y][b] |= mask[b];
			}
			else {
				buf.b[y][b] &= ~mask[b];
			}
		}
	}

}

void tui::Tools::v_line(COLED::Buf& buf, int x, int y1, int y2) {
	byte mask[16];
	make_mask(mask, x, x);
	for(int y=y1; y<=y2; ++y) {
		for(int b=0; b<8; ++b) {
			buf.b[y][b] |= mask[b];
		}
	}
}
void tui::Tools::h_line(COLED::Buf& buf, int x1, int y, int x2) {
	byte mask[16];
	make_mask(mask, x1, x2);
	for(int b=0; b<8; ++b) {
		buf.b[y][b] |= mask[b];
	}
}

void tui::Tools::box(COLED::Buf& buf, int x1, int y1, int x2, int y2) {
	h_line(buf, x1, y1, x2);
	h_line(buf, x1, y2, x2);
	v_line(buf, x1, y1, y2);
	v_line(buf, x2, y1, y2);
}

void tui::Tools::draw_text(COLED::Buf& buf, int x, int y, const char *text) {
	Bitmap bmp;
	render_text(bmp, text);
	draw_bitmap(buf, x, y, bmp);
}

