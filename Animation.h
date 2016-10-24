#pragma once
#include <string>
#include <vector>
#include "Image.h"
using namespace std;
class Animation
{
public:
	Animation(string name);
	~Animation();
	string getName();
	vector<Image*> getSequence();
	void addFrame(Image *frame);
	Image* getFrame(int index);
private:
	string name;
	vector<Image*> sequence;
};

