#ifndef E_IMGCHAR_H
#define E_IMGCHAR_H

#include <string>
#include <vector>

#include "../entity.h"

#define IMAGESTRINGDEFAULTXPOS	8
#define IMAGESTRINGDEFAULTYPOS	8

#define DEFAULTCHARWIDTH		8
#define DEFUALTCHARHEIGHT		8
#define DEFAULTLINEWIDTH		32

#define SPRITESHEETCHARWIDTH    8
#define SPRITESHEETCHARHEIGHT   8

#define FONTSET "fontsetW.png"

namespace
{
	class imageChar
	{
	public:
		//constructor  block
		imageChar();

		//loads character of char c with the image width and height x, y.
		imageChar(const char& c, const unsigned& x, const unsigned& y);
		
		//sets position where the character image will be drawn
		void setCharPos(const int& x, const int& y);

		//deallocates currently loaded character image.
		void deallocateChar();

		void setChar(const char& c, const unsigned& x, const unsigned& y);

	private:

		CRE_Entity* character = NULL;
	};
}

class imageString
{
public:
	//constructor block
	imageString();

	imageString(const std::string& s);

	void setStringPos(const unsigned& x, const unsigned& y);

	void setStringCharSize(const unsigned& x, const unsigned& y);

	void setLineWidth(const unsigned& lw);

	void loadString(const std::string& s);

	~imageString();

private:
	std::vector<imageChar> imgCharVector;

	std::string str;

	int xPos;
	int yPos;

	int charWidth;
	int charHeight;

	unsigned lineWidth;

	void clearImgCharVector();
};

#endif