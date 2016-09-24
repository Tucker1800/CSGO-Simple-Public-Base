#pragma once
//simple draw class...
class cDraw
{
public:
	//defining font
	unsigned long DefaultFont;
	//creating fonts
	void Start();

	//functions
	//draw string
	void String(unsigned long font, int x, int y, Color color, const char* msg, ...);
};