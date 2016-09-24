#pragma once

//isurface... Using color class to make life a bit easier i guess...
class ISurface
{
public:
	//setting font to use...
	void DrawSetTextFont(unsigned long HFont);
	//homework is to use the function which uses Color class.... very close by :)
	void DrawSetTextColor(int r, int g, int b, int a);
	//text pos
	void DrawSetTextPos(int x, int y);
	//text itself
	void DrawPrintText(const wchar_t* wszText, int length);
	//creating a new font
	unsigned long CreateCSFont(void);
	//font settings
	bool SetFontGlyphSet(unsigned long font, const char* szName, int tall, int weight, int blur, int scanlines, FontFlags_t flags);
};