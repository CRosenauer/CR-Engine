#include "entity.h"

entity::entity()
{
	posX = 0;
	posY = 0;
	posZ = 0;
}

entity::entity(SDL_Renderer*& rend)
{
	posX = 0;
	posY = 0;
	posZ = 0;

	renderer = rend;

	eTexture.setRenderer(renderer);
}

void entity::setTexture(const std::string& path, SDL_Rect* source, SDL_Rect* dest)
{
	if (source == NULL)
	{
		source = eTexture.getSourceRect();
	}

	if (dest == NULL)
	{
		dest = eTexture.getDestRect();
	}

	eTexture.loadTexture(path, source, dest);
}

void entity::setTexture(const texture& text)
{
	eTexture = text;
	eTexture.setRenderer(renderer);
}

texture entity::getTexture()
{
	return eTexture;
}


void entity::setPosition(int x, int y, int z)
{
	SDL_Rect* temp = eTexture.getDestRect();

	
	

	if (x != NULL)
	{
		temp->x += (x - posX);
		posX = x;
	}
		
	
	if (y != NULL)
	{
		temp->y += (y - posY);
		posY = y;
	}
		
	if(z != NULL)
		posZ = z;
}


void entity::getPosition(int pos[3])
{
	pos[0] = posX;
	pos[1] = posY;
	pos[2] = posZ;
}

void entity::setTextureDest(SDL_Rect* dest)
{
	eTexture.setRect(eTexture.getSourceRect(), dest);
}