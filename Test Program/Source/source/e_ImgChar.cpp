#include "e_ImgChar.h"

#include "../entityHandler.h"
#include "../texture.h"
#include "../file.h"

namespace
{
	imageChar::imageChar()
	{
		deallocateChar();
	}

	imageChar::imageChar(const char& c, const unsigned& x, const unsigned& y)
	{
		setChar(c, x, y);
	}

	void imageChar::setCharPos(const int& x, const int& y)
	{
		if (character != NULL)
		{
			(character)->setPosition(x, y, 0);
		}
	}

	void imageChar::deallocateChar()
	{
		if (character != NULL)
			deleteEntity((character)->getEntityID());
	}

	void imageChar::setChar(const char& c, const unsigned& x, const unsigned& y)
	{
		if (character == NULL)
		{
			character = allocateEntityPtr(TEXT);
		}

		//break if ascii char is from extended ascii
		if (c > 127)
		{
			character->setAlpha(0);
			return;
		}

		CRE_TextureData imgCharData =
		{
			FONTSET,
			{0, 0, x, y},
			0,
			0,
			255
		};

		//location on the char sprite sheet to draw from
		unsigned charSheetY = c / 16;
		unsigned charSheetX = c % 16;

		//determine where to draw from on the char sprite sheet
		imgCharData.source.x = charSheetX * SPRITESHEETCHARWIDTH;
		imgCharData.source.y = charSheetY * SPRITESHEETCHARHEIGHT;

		//load image data
		character->setTexture(imgCharData);
		character->setRenderingFlag(RENDERINGFLAG_STATIC_FOREGROUND);
		character->setPosition(IMAGESTRINGDEFAULTXPOS, IMAGESTRINGDEFAULTYPOS, 0);
	}
}


imageString::imageString()
{
	xPos		= IMAGESTRINGDEFAULTXPOS;
	yPos		= IMAGESTRINGDEFAULTYPOS;
	charWidth	= DEFAULTCHARWIDTH;
	charHeight	= DEFUALTCHARHEIGHT;
	lineWidth	= DEFAULTLINEWIDTH;
}

imageString::imageString(const std::string& s)
{
	xPos		= IMAGESTRINGDEFAULTXPOS;
	yPos		= IMAGESTRINGDEFAULTYPOS;
	charWidth	= DEFAULTCHARWIDTH;
	charHeight	= DEFUALTCHARHEIGHT;
	lineWidth	= DEFAULTLINEWIDTH;

	loadString(s);
}

void imageString::clearImgCharVector()
{
	for (int i = 0; i < imgCharVector.size(); i++)
	{
		imgCharVector[i].deallocateChar();
	}

	imgCharVector.clear();
}

void imageString::setStringPos(const unsigned& x, const unsigned& y)
{
	xPos = x;
	yPos = y;
	
	if (!str.empty())
	{
		loadString(str);
	}
}

void imageString::setStringCharSize(const unsigned& x, const unsigned& y)
{
	charWidth  = x;
	charHeight = y;

	if (!str.empty())
	{
		loadString(str);
	}
}

void imageString::setLineWidth(const unsigned& lw)
{
	lineWidth = lw;

	if (!str.empty())
	{
		loadString(str);
	}
}

imageString::~imageString()
{
	clearImgCharVector();
}

void imageString::loadString(const std::string& s)
{
	str = s;

	if (imgCharVector.size() < str.size())
	{
		imgCharVector.resize(str.size());
	}

	unsigned lineNumber = 0;
	unsigned linePos = 0;

	for (int i = 0; i < imgCharVector.size(); i++)
	{
		if (i < str.size())
		{
			imgCharVector[i].setChar(str[i], charWidth, charHeight);
			imgCharVector[i].setCharPos(IMAGESTRINGDEFAULTXPOS + linePos++ * charWidth,
				IMAGESTRINGDEFAULTYPOS + lineNumber * charHeight);

			if ((str[i] == '\n' && true) || linePos == lineWidth)
			{
				lineNumber++;
				linePos = 0;
			}
		}
		else
		{
			imgCharVector[i].setChar('\0', charWidth, charHeight);
			imgCharVector[i].setCharPos(IMAGESTRINGDEFAULTXPOS + linePos++ * charWidth,
				IMAGESTRINGDEFAULTYPOS + lineNumber * charHeight);
		}
		
	}
}