/**
@author Gabriela de Campos Trevisan
*/

#include "Sprite.h"

Sprite::Sprite() 
{
}

Sprite::Sprite(Image *src)
{
	this->src = src;
}


Sprite::~Sprite()
{
}

void Sprite::insertAnimation(string name, vector<Rect> rects)
{
	Animation *ani = new Animation(name);
	for (int i = 0; i < rects.size(); i++)
	{
		Rect r = rects[i];
		Image *img = new Image(r.width, r.height);
		src->subimage(img, r.xup, r.yup, r.xup + r.width, r.yup + r.height);
		ani->addFrame(img);
	}
	this->animations.push_back(ani);
}

void Sprite::setActiveAnimation(string name)
{
	for (int i = 0; i < this->animations.size(); i++)
	{
		if (name == animations[i]->getName()) {
			activeAnimation = animations[i];
		}
	}
}

Animation* Sprite::getActiveAnimation()
{
	return this->activeAnimation;
}

