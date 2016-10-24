/**
@author Gabriela de Campos Trevisan
*/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "PTMReader.h"
#include "FpsManager.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Rect.h"
#include "Layer.h"
#include "Text.h"
#include "Config.h"

using namespace std;

const unsigned long MIN_DISTANCE_OBSTACLES = 30;
const int W = 1300;
const int H = 650;

Game *game;
Image* frameBuffer;
Text* text = new Text();
Image* points;
GameObject* character;
bool started = false;
bool layersAnimated = false;
unsigned long frameCount = 0;
unsigned long numberObstacles = 0;
double delta;

void loadLayers() {
	vector<Layer*>* l = allLayers();
	for (int i = 0; i < l->size(); i++) {
		game->insertLayer(l->at(i));
	}
}

void loadCharacter() {
	character = new GameObject("character");
	character->setPosX(50);
	character->setPosY(450);
	character->setSprite(characterSprite());
	character->setLayer(5);
	character->setScale(1);
	game->addGameObject(5, character);
}

void addObstacle(int layer) {
	GameObject* obs = new GameObject("obstacle");
	obs->id = numberObstacles++;
	obs->setPosX(W - 75);
	if (layer == 4) {
		obs->setPosY(500);
		obs->setScale(2);
	}
	if (layer == 5) {
		obs->setPosY(520);
		obs->setScale(1);
	}
	if (layer == 6) {
		obs->setPosY(530);
		obs->setScale(0);
	}
	obs->setSprite(obstacleSprite());
	obs->setLayer(layer);
	game->addGameObject(layer, obs);	
}

void insertObstacles() {
	if (layersAnimated) {
		frameCount++;
		if (MIN_DISTANCE_OBSTACLES < frameCount) {
			frameCount = 0;
			srand(time(NULL));
			int r = rand() % 10;
			if (r <= 5 + game->getLevel()) {
				int p1 = rand() % 3 + 4;
				addObstacle(p1);
				int r = rand() % 10;
				if (r <= 3 + game->getLevel()) {
					int p2 = rand() % 3 + 4;
					if (p1 != p2)
						addObstacle(p2);
				}
			}
		}
	}
	else { frameCount = 0; }
}

bool detectColisions() {
	for (int i = 0; i < game->getGameLayers()->size(); i++)
	{		
		for (int j = 0; j < game->getGameLayers()->at(i)->getGameObjects()->size(); j++)
		{
			GameObject* gobj = game->getGameLayers()->at(i)->getGameObjects()->at(j);
			if (gobj->getName() != "character") {
				if (character->getLayer() == gobj->getLayer()) {
					if (abs(character->getPosX() - gobj->getPosX()) < 65) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void plotGameObject(GameObject* gobj) {
	Image* charTemp = new Image(gobj->getFrame()->getWidth(), gobj->getFrame()->getHeight());	
	charTemp->clear();
	int w = gobj->getFrame()->getWidth() + gobj->getScale() * (gobj->getFrame()->getWidth() * 0.2);
	int h = gobj->getFrame()->getHeight() + gobj->getScale() * (gobj->getFrame()->getHeight() * 0.2);
	gobj->getFrame()->resizePixels(charTemp, w, h);
	frameBuffer->plot(charTemp, gobj->getPosX(), gobj->getPosY());
	delete charTemp;
}

void updateScene() {
	if (layersAnimated) {
		for (int i = 0; i < game->getGameLayers()->size(); i++)
			game->getGameLayers()->at(i)->scroll(true);
	}

	insertObstacles();

	for (int i = 0; i < 5; i++) {
		frameBuffer->plot(game->getGameLayers()->at(i)->getImage(), 0, 0);
	}

	for (int i = 4; i < game->getGameLayers()->size() ; i++)
	{
		for (int j = 0; j < game->getGameLayers()->at(i)->getGameObjects()->size(); j++) {	
		
			bool removed = false;
			GameObject* gobj = game->getGameLayers()->at(i)->getGameObjects()->at(j);
			if (gobj->getName() == "obstacle") {
				if (gobj->getPosX() <= 0) {
					game->getGameLayers()->at(i)->removeGameObject(gobj);
					removed = true;
					game->setPoints(game->getPoints() + 10);
				}
			}
			if (gobj->getName() != "character")
				plotGameObject(gobj);

			if (!removed && gobj->getName() != "character") {
				if (character->getSprite()->getActiveAnimation()->getName() != game->getAnimationStop() && character->getSprite()->getActiveAnimation()->getName() != game->getAnimationGameOver())
					gobj->setPosX(gobj->getPosX() - game->getGameLayers()->at(gobj->getLayer())->getRate());
			}			
			
			if (detectColisions()) {
				layersAnimated = false;
				character->getSprite()->setActiveAnimation(game->getAnimationGameOver());
				game->getGameLayers()->at(8)->setVisibility(true);
			}

			// Game Over Layer
			if(game->getGameLayers()->at(8)->isVisible())
				frameBuffer->plot(game->getGameLayers()->at(8)->getImage(), 0, 0);
		}
		if(character->getLayer() == i)
			plotGameObject(character);
		//Start Layer
		if (game->getGameLayers()->at(7)->isVisible())
			frameBuffer->plot(game->getGameLayers()->at(7)->getImage(), 0, 0);
	}
}

void resetGame() {
	game->setPoints(0);
	for (int i = 0; i < game->getGameLayers()->size(); i++) {		
		game->getGameLayers()->at(i)->getGameObjects()->clear();
	}
	character->getSprite()->setActiveAnimation(game->getAnimationRun());
	character->setScale(1);
	character->setLayer(5);
	game->getGameLayers()->at(5)->insertGameObject(character);
	layersAnimated = true;
	game->getGameLayers()->at(8)->setVisibility(false);
	game->setLevel(1);
}

int validCharacterLayerIndex(int index) {
	if (index < 4)
		return 4;
	if (index > 6)
		return 6;
	return index;
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (character->getSprite()->getActiveAnimation()->getName() == game->getAnimationGameOver()) {
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
			resetGame();
		}
	}
	else if (character->getSprite()->getActiveAnimation()->getName() == game->getAnimationStop() && !started) {
		started = true;
		layersAnimated = true;
		character->getSprite()->setActiveAnimation(game->getAnimationRun());
		game->getGameLayers()->at(7)->setVisibility(false);
	} else {
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
			layersAnimated = true;
			character->getSprite()->setActiveAnimation(game->getAnimationRun());
		}

		if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
			layersAnimated = true;
			character->getSprite()->setActiveAnimation(game->getAnimationRun());
			if (character->getScale() < 2)
				character->setScale(character->getScale() + 1);
			character->setLayer(validCharacterLayerIndex(character->getLayer() - 1));

		}

		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
			layersAnimated = true;
			character->getSprite()->setActiveAnimation(game->getAnimationRun());
			if (character->getScale() > 0)
				character->setScale(character->getScale() - 1);
			character->setLayer(validCharacterLayerIndex(character->getLayer() + 1));
		}

		if (key == GLFW_KEY_P && action == GLFW_PRESS) {
			layersAnimated = false;
			character->getSprite()->setActiveAnimation(game->getAnimationStop());
		}
	}
}

void display() {
	updateScene();
	game->updateAnim();
	points = text->textToImage("POINTS " + to_string(game->getPoints()));
	frameBuffer->plot(points, 930, 10);
	glDrawPixels(frameBuffer->getWidth(), frameBuffer->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, frameBuffer->getPixels());
	delete points;
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	display();
	glFlush();
}

void init() {
	glOrtho(0.0, W, H, 0.0, 0.0, 1.0);
	glRasterPos2f(0, 0);
	glPixelZoom(1.0f, -1.0f);

	game = new Game();
	frameBuffer = new Image(W, H);
	loadLayers();
	loadCharacter();
}


int CALLBACK WinMain(
	__in  HINSTANCE hInstance,
	__in  HINSTANCE hPrevInstance,
	__in  LPSTR lpCmdLine,
	__in  int nCmdShow
	) {
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(W, H, "Parallax Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyboard);

	init();

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		FpsManager fpsManager(20+game->getLevel());
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
		delta = fpsManager.enforceFPS();
	}

	glfwTerminate();
	return 0;
}