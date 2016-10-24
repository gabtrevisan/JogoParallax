#pragma once
#include "Image.h"
#include "GameObject.h"
#include <vector>
using namespace std;
class Layer
{
public:
	Layer(double rate);
	Layer(Image* image, double rate);
	Layer(Image * image, double rate, bool visibility);
	~Layer();
	void scroll(bool scroll);
	void insertGameObject(GameObject* go);
	Image * getImage();
	void removeGameObject(string name);
	void removeGameObject(GameObject *go);
	GameObject * getGameObject(string name);
	vector<GameObject*>* getGameObjects();
	int getRate();
	void setVisibility(bool visibility);
	bool isVisible();
private:
	Image* image;
	double rate;
	vector<GameObject*>* objects;
	bool visibility;
};

