/**
@author Gabriela de Campos Trevisan
*/

#include "Game.h"

Game::Game()
{
	this->gameLayers = new vector<Layer*>();
	this->points = 0;
	this->level = 1;
	this->animationRun = "fat-run";
	this->animationStop = "fat-stop";
	this->animationGameOver = "fat-game-over";
}


Game::~Game()
{
}

vector<Layer*>* Game::getGameLayers() {
	return this->gameLayers;
}

void Game::insertLayer(Layer *layer)
{
	this->gameLayers->push_back(layer);
}

GameObject* Game::getGameObject(string name) {
	for (int i = 0; i < this->gameLayers->size(); i++)
	{
		GameObject* go = gameLayers->at(i)->getGameObject(name);
		if (go != NULL) {
			return go;
		}			
	}
	return NULL;
}

void Game::updateAnim()
{	
	for (int i = 0; i < this->getGameLayers()->size(); i++)
	{
		for (int j = 0; j < this->getGameLayers()->at(i)->getGameObjects()->size(); j++) {
			GameObject *obj = this->getGameLayers()->at(i)->getGameObjects()->at(j);
			Animation * anim = obj->getSprite()->getActiveAnimation();
			if (obj->isAnimated()) {
				int nFrames = anim->getSequence().size();
				int curr = (obj->getCurrentFrame() + 1) % nFrames;
				obj->setCurrentFrame(curr);
			}
		}
	}
}

void Game::addGameObject(int indexLayer, GameObject* gameObject) {
	this->gameLayers->at(indexLayer)->insertGameObject(gameObject);
}

void Game::setPoints(int points)
{
	this->points = points;					
	if (this->getPoints() != 0 && this->getPoints() % 100 == 0) {
		this->setLevel(this->getLevel() + 1);
	}

	if (this->getPoints() >= 0 && this->getPoints() < 200) {
		this->animationRun = "fat-run";
		this->animationStop = "fat-stop";
		this->animationGameOver = "fat-game-over";
	}
	else if (this->getPoints() >= 200 && this->getPoints() < 600) {
		this->animationRun = "normal-run";
		this->animationStop = "normal-stop";
		this->animationGameOver = "normal-game-over";
	}
	else {
		this->animationRun = "skinny-run";
		this->animationStop = "skinny-stop";
		this->animationGameOver = "skinny-game-over";
	}
}

int Game::getPoints()
{
	return this->points;
}

void Game::setAnimationRun(string animation) {
	this->animationRun = animation;
}

string Game::getAnimationRun() {
	return this->animationRun;
}

void Game::setAnimationStop(string animation) {
	this->animationStop = animation;
}

string Game::getAnimationStop() {
	return this->animationStop;
}

void Game::setAnimationGameOver(string animation) {
	this->animationGameOver = animation;
}

string Game::getAnimationGameOver() {
	return this->animationGameOver;
}

void Game::setLevel(int level) {
	this->level = level;
}

int Game::getLevel() {
	return this->level;
}