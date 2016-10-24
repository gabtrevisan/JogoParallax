#pragma once
#include "Sprite.h"
class GameObject
{
public:
	GameObject(string name);
	~GameObject();
	int getCurrentFrame();
	void setCurrentFrame(int frameNumber);
	int getPosX();
	int getPosY();
	void setPosX(int x);
	void setPosY(int y);
	void setSprite(Sprite* anim);
	Sprite* getSprite();
	Image* getFrame();
	string getName();
	bool isAnimated();
	void setAnimated(bool animated);
	void setScale(double scale);
	double getScale();
	void setLayer(int layer);
	int getLayer();
	long id;
private:
	int currentFrame;
	int posX;
	int posY;
	Sprite* sprite;
	string name;
	bool animated;
	double scale;
	int layer;
};

