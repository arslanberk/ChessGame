// utils.h
#ifndef utils_h
#define utils_h

namespace GraphUtils
{
	// Declaration of arrays that define the colors:
	extern float diffWhite[];
	extern float ambiWhite[];
	extern float specWhite[];

	extern float diffBlue[];
	extern float ambiBlue[];
	extern float specBlue[];

	extern float diffBlack[];
	extern float ambiBlack[];
	extern float specBlack[];

	extern float diffRed[];
	extern float ambiRed[];
	extern float specRed[];

	extern float diffYellow[];
	extern float ambiYellow[];
	extern float specYellow[];

	extern float diffGreen[];
	extern float ambiGreen[];
	extern float specGreen[];

	extern float diffOrange[];
	extern float ambiOrange[];
	extern float specOrange[];

	extern float diffLightBlue[];
	extern float ambiLightBlue[];
	extern float specLightBlue[];

	extern float diffViolet[];
	extern float ambiViolet[];
	extern float specViolet[];

	const float shininess = 64;

	// Drawing parallesquare
	void parallesquare(float length, float width, float height);
	// Displays the text string in a specified position using specified font
	void drawString(void *font, const char* text, float x, float y);
}

#endif