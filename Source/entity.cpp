#include "entity.h"

entity::entity()
{
	posX = 0;
	posY = 0;
	posZ = 0;
}

void entity::setTexture(const std::string& path, SDL_Rect source, SDL_Rect dest, const int& xOffset, const int& yOffset)
{
	if (!rectIsUndefined(source) && !rectIsUndefined(dest))
	{
		//UNDEFINED_RECT passed for source and dest
		dest.x = dest.x - xOffset;
		dest.y = dest.y - yOffset;
		eTexture.loadTexture(path, source, dest);
	}
	else if (rectIsUndefined(source) && !rectIsUndefined(dest))
	{
		eTexture.loadTexture(path, eTexture.getSourceRect(), dest);
	}
	else if (!rectIsUndefined(source) && rectIsUndefined(dest))
	{
		eTexture.loadTexture(path, source, eTexture.getDestRect());
	}
	else
	{
		eTexture.loadTexture(path, eTexture.getSourceRect(), eTexture.getDestRect());
	}
}

bool entity::rectIsUndefined(SDL_Rect rect)
{
	return (rect.x < 0)||(rect.y < 0)||(rect.w < 0)||(rect.h < 0);
}

void entity::setTexture(const texture& text)
{
	eTexture = text;
}

texture* entity::getTexture()
{
	texture tempTexture = eTexture;
	SDL_Rect tempRect = tempTexture.getDestRect();


	return &eTexture;
}


void entity::setPosition(int x, int y, int z)
{
	SDL_Rect temp = eTexture.getDestRect();

	if (x != NULL)
	{
		temp.x += (x - posX);
		posX = x;
	}
		
	
	if (y != NULL)
	{
		temp.y += (y - posY);
		posY = y;
	}
		
	if(z != NULL)
		posZ = z;

	eTexture.setRect(eTexture.getSourceRect(), temp);
}


void entity::getPosition(int pos[3])
{
	pos[0] = posX;
	pos[1] = posY;
	pos[2] = posZ;
}

void entity::setTextureDest(SDL_Rect* dest)
{
	eTexture.setRect(eTexture.getSourceRect(), *dest);
}