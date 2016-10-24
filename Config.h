#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Sprite.h"
#include "Rect.h"
#include "PTMReader.h"
#include "Layer.h"

PTMReader* ptm2 = new PTMReader();

Sprite* characterSprite() {
	Sprite *sprite = new Sprite(ptm2->read("character.ptm"));
	vector<Rect> rects;

	// SKINNY
	rects.push_back(Rect(28, 1, 34, 124));
	sprite->insertAnimation("skinny-stop", rects);

	rects.clear();
	rects.push_back(Rect(28, 127, 52, 124));
	rects.push_back(Rect(155, 127, 52, 124));
	rects.push_back(Rect(281, 127, 52, 124));
	rects.push_back(Rect(411, 127, 52, 124));
	rects.push_back(Rect(535, 127, 52, 124));
	rects.push_back(Rect(654, 127, 52, 124));
	sprite->insertAnimation("skinny-run", rects);

	rects.clear();
	rects.push_back(Rect(459, 768, 124, 106));
	sprite->insertAnimation("skinny-game-over", rects);

	// NORMAL
	rects.clear();
	rects.push_back(Rect(15, 255, 48, 124));
	sprite->insertAnimation("normal-stop", rects);

	rects.clear();
	rects.push_back(Rect(14, 380, 58, 124));
	rects.push_back(Rect(144, 380, 58, 124));
	rects.push_back(Rect(269, 380, 58, 124));
	rects.push_back(Rect(397, 380, 58, 124));
	rects.push_back(Rect(521, 380, 58, 124));
	rects.push_back(Rect(647, 380, 58, 124));
	sprite->insertAnimation("normal-run", rects);

	rects.clear();
	rects.push_back(Rect(226, 764, 124, 108));
	sprite->insertAnimation("normal-game-over", rects);

	// FAT
	rects.clear();
	rects.push_back(Rect(1, 511, 75, 124));
	sprite->insertAnimation("fat-stop", rects);

	rects.clear();
	rects.push_back(Rect(6, 644, 75, 124));
	rects.push_back(Rect(138, 644, 75, 124));
	rects.push_back(Rect(264, 644, 75, 124));
	rects.push_back(Rect(394, 644, 75, 124));
	rects.push_back(Rect(518, 644, 75, 124));
	rects.push_back(Rect(640, 644, 75, 124));
	sprite->insertAnimation("fat-run", rects);

	rects.clear();
	rects.push_back(Rect(8, 766, 119, 108));
	sprite->insertAnimation("fat-game-over", rects);

	sprite->setActiveAnimation("fat-stop");

	return sprite;
}

Sprite* obstacleSprite() {
	Rect r[] = { 
		Rect(2, 2, 53, 53), // hamburger
		Rect(57, 2, 43, 52), // french fries
		Rect(159, 7, 28, 46)  // coke
	};

	Sprite *sprite = new Sprite(ptm2->read("food.ptm"));
	vector<Rect> rects;
	rects.clear();
	rects.push_back(r[rand() % 3]);
	sprite->insertAnimation("food", rects);
	sprite->setActiveAnimation("food");
	return sprite;
}

vector<Layer*>* allLayers() {
	vector<Layer*>* l = new vector<Layer*>();
	l->push_back(new Layer(ptm2->read("sky.ptm"), 0)); // [0] Sky
	l->push_back(new Layer(ptm2->read("clouds.ptm"), 1)); // [1] Clouds
	l->push_back(new Layer(ptm2->read("mountains1.ptm"), 4)); // [2] Mountains 1
	l->push_back(new Layer(ptm2->read("mountains2.ptm"), 6)); // [3] Mountains 2
	l->push_back(new Layer(ptm2->read("floor.ptm"), 8)); // [4] Floor 1
	l->push_back(new Layer(8)); // [5] Floor 2
	l->push_back(new Layer(8)); // [6] Floor 3	
	l->push_back(new Layer(ptm2->read("start.ptm"), 0, true)); // [7] Start	
	l->push_back(new Layer(ptm2->read("game-over.ptm"), 0, false)); // [8] Game Over	
	return l;
}