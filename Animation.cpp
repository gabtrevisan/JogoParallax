/**
@author Gabriela de Campos Trevisan
*/

#include "Animation.h"

Animation::Animation(string name)
{
	this->name = name;
}


Animation::~Animation()
{
}

string Animation::getName() {
	return this->name;
}

vector<Image*> Animation::getSequence() {
	return this->sequence;
}

void Animation::addFrame(Image *frame)
{
	this->sequence.push_back(frame);
}

Image* Animation::getFrame(int index) {
	return this->sequence[index];
}



