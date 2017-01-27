
#define OLED_COLS					128	//128 Pixels
#define OLED_ROWS					64	//64  Pixels

extern volatile byte I2CBlockComplete;

typedef unsigned char byte;
#define MAX_BLOCK (8 * 128)


class COLED
{
public:
	enum {
		MAX_ROWS = 64,
		MAX_COLS = 128,
		BYTES_PER_SCAN_ROW = 16
	};

	// Structure used to pass in a new screenful
	// of data for display. The data is laid out
	// for convenient access as sequential rows
	// of horizontal bytes (MSB to left) and needs
	// to be translated to correct format to be send
	// to the display hardware
	typedef struct
	{
		byte b[MAX_ROWS][BYTES_PER_SCAN_ROW];
	} Buf;

	enum {
	// registers
		COMMAND	= 0x80,
		DATA	= 0x40,

	// commands
		DISPLAY_OFF = 0xAE,
		DISPLAY_ON = 0xAF,
		NORMAL_DISPLAY = 0xA6,
		INVERSE_DISPLAY = 0xA7,
		SET_BRIGHTNESS = 0x81,

		RIGHT_SCROLL = 0x26,
		LEFT_SCROLL = 0x27,
		SET_VERTICAL_SCROLL_AREA = 0xA3,
		VERTICAL_RIGHT_SCROLL = 0x29,
		VERTICAL_LEFT_SCROLL = 0x2A,
		ACTIVATE_SCROLL = 0x2F,
		DEACTIVATE_SCROLL = 0x2E,

		HORIZONTAL_ADDRESSING = 0x00,
		PAGE_ADDRESSING = 0x02,

		I2C_ADDR = 0x3c
	};
	void init();
	void cmd(byte command);
	void send(byte *data, int len);
	void at(byte x, byte y);
	//void cls();
	//void zero(Buf& buf);
	void set(Buf& buf);
};
