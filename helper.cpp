#include "helper.h"
Tile::Tile(int x, int y , int sx, int sy, bool isCollidable)
{
	this->x = x;
	this->y = y;
	this->sx = sx;
	this->sy = sy;
	this->isCollidable = isCollidable;
}
ScrollingField::ScrollingField(int x, int y , int w, int h, int offsetX, int offsetY )
{
	this->x = x;
	this->y = y;
	this->h = h;
	this->w = w;
    this->offsetX = offsetX;
	this->offsetY = offsetY;
}
