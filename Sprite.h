#pragma once
#include <string>
#include "Rect.h"
#include <vector>
#include "Animation.h"

using namespace std;

class Sprite
{
private:
	string id;
	Image *src;
	vector<Animation*> animations;
	Animation *activeAnimation;

public:
	Sprite();
	Sprite(Image *src);
	~Sprite();
	void insertAnimation(string name, vector<Rect> rects);
	void setActiveAnimation(string name);
	Animation* getActiveAnimation();
};

