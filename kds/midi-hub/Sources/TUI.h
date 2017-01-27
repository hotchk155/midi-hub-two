
#ifndef SOURCES_TUI_H_
#define SOURCES_TUI_H_

namespace tui {

typedef struct
{
	char x;
	char y;
} POINT;

typedef struct
{
	POINT tl;
	POINT br;
} RECT;

class Bitmap
{
public:
	byte *data;
	byte height;
	byte width;
	byte scan_row;
	Bitmap() : data(nullptr), height(0), width(0) {}
	~Bitmap() {
		delete[] data;
		data = nullptr;
	}
	void alloc(int h, int w) {
		if(data) {
			delete[] data;
		}
		scan_row = 8 * (w/8 + 1);
		data = new byte[h*scan_row];
		memset(data,0,h*scan_row);
		height = h;
		width = w;
	}
};


class Tools
{
public:
	static void clear(COLED::Buf& buf);
	static void clear(COLED::Buf& buf, int x1, int y1, int x2, int y2, byte fill=0);
	static void v_line(COLED::Buf& buf, int x, int y1, int y2);
	static void h_line(COLED::Buf& buf, int x1, int y, int x2);
	static void box(COLED::Buf& buf, int x1, int y1, int x2, int y2);
	static void draw_text(COLED::Buf& buf, int x, int y, const char *text);
	static void render_text(Bitmap& bmp, const char *text);
	static void draw_bitmap(COLED::Buf& buf, int x, int y, Bitmap& bmp);
};

/*
class Thing
{
public:
	RECT bounds;
	virtual void paint(COLED::Buf& buf) = 0;

};

class Box : public Thing
{
public:
	enum {
		BORDER = 0x01
	}
	byte flags;


	Box(char x1, char y1, char x2, char y2, int f=0)  {
		flags = f;
		bounds.tl.x = x1;
		bounds.tl.y = y1;
		bounds.br.x = x2;
		bounds.br.y = y2;
	}

	void paint(COLED::Buf& buf)
	{
		Tools::clear(buf, bounds);
		if(flags & BORDER) {
			Tools::box(buf, bounds);
		}
	}

};


class Text : public Thing {
public:
	char *text;
	Text(char x1, char y1, char x2, char y2, char *t) : bounds(x1,y1,x2,y2,t) {}

}
*/
}; // namespace tui

#endif /* SOURCES_TUI_H_ */
