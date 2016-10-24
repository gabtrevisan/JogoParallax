/**
@author Gabriela de Campos Trevisan
*/

#include "GameObject.h"

GameObject::GameObject(string name)
{
	this->name = name;
	this->currentFrame = 0;
	this->animated = true;
	this->scale = 0;
	this->layer = 5;
}

GameObject::~GameObject()
{
}

int GameObject::getCurrentFrame() {
	return this->currentFrame;
}

void GameObject::setCurrentFrame(int frameNumber) {
	this->currentFrame = frameNumber;
}

int GameObject::getPosX() {
	return this->posX;
}

int GameObject::getPosY() {
	return this->posY;
}

void GameObject::setPosX(int x) {
	this->posX = x;
}

void GameObject::setPosY(int y) {
	this->posY = y;
}

void GameObject::setSprite(Sprite* sprite) {
	this->sprite = sprite;
}

Sprite* GameObject::getSprite() {
	return this->sprite;
}

Image* GameObject::getFrame() {
	Animation *a = this->sprite->getActiveAnimation();
	return a->getFrame(currentFrame % a->getSequence().size());
}

string GameObject::getName() {
	return this->name;
}

bool GameObject::isAnimated() {
	return this->animated;
}

void GameObject::setAnimated(bool animated) {
	this->animated = animated;
}

void GameObject::setScale(double scale) {
	this->scale = scale;
}

double GameObject::getScale() {
	return this->scale;
}

void GameObject::setLayer(int l) {
	this->layer = l;
}

int GameObject::getLayer()
{
	return this->layer;
}

