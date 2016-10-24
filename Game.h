#pragma once
#include "GameObject.h"
#include "Layer.h"
#include <vector>
class Game
{
public:
	Game();
	~Game();
	vector<Layer*>* getGameLayers();
	void insertLayer(Layer* layer);
	GameObject* getGameObject(string name);
	void updateAnim();
	void addGameObject(int indexLayer, GameObject * gameObject);
	void setPoints(int points);
	int getPoints();
	void setAnimationRun(string animation);
	string getAnimationRun();
	void setAnimationStop(string animation);
	string getAnimationStop();
	void setAnimationGameOver(string animation);
	string getAnimationGameOver();
	void setLevel(int level);
	int getLevel();
private:
	vector<Layer*> *gameLayers;
	int points;
	string animationRun;
	string animationStop;
	string animationGameOver;
	int level;
};

