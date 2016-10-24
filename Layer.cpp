/**
@author Gabriela de Campos Trevisan
*/

#include "Layer.h"

Layer::Layer(double rate)
{
	this->image = new Image(0,0);
	this->rate = rate;
	this->objects = new vector<GameObject*>();
	this->visibility = true;
}

Layer::Layer(Image* image, double rate)
{
	this->image = image;
	this->rate = rate;
	this->objects = new vector<GameObject*>();
	this->visibility = true;
}


Layer::Layer(Image* image, double rate, bool visibility)
{
	this->image = image;
	this->rate = rate;
	this->objects = new vector<GameObject*>();
	this->visibility = visibility;
}

Layer::~Layer()
{
}

void Layer::scroll(bool scroll) {
	if (scroll) 
		image->rollImage(rate);
	else 
		image->rollImage(0);
}

void Layer::insertGameObject(GameObject* go) {
	this->objects->push_back(go);
}

Image* Layer::getImage() {
	return this->image;
}

void Layer::removeGameObject(string name) {
	for (int i = 0; i < this->objects->size(); i++)
	{
		if (this->objects->at(i)->getName() == name) {	
			delete this->objects->at(i);
			this->objects->erase(objects->begin() + i);
		}			
	}
}

void Layer::removeGameObject(GameObject *go) {
	for (int i = 0; i < this->objects->size(); i++)
	{
		if (this->objects->at(i)->id == go->id) {
			delete this->objects->at(i);
			this->objects->erase(objects->begin() + i);
		}
	}
}

GameObject* Layer::getGameObject(string name) {
	for (int i = 0; i < this->objects->size(); i++)
	{
		if (this->objects->at(i)->getName() == name) {
			return this->objects->at(i);
		}
	}
	return NULL;
}

vector<GameObject*>* Layer::getGameObjects()
{
	return objects;
}

int Layer::getRate() {
	return this->rate;
}

void Layer::setVisibility(bool visibility)
{
	this->visibility = visibility;
}

bool Layer::isVisible()
{
	return this->visibility;
}
