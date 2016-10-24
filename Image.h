#pragma once
#include <windows.h>
#include <string.h>
#include <math.h>
class Image
{
private:
	int *pixels;
	int width, height;

public:
	Image(int w, int h);
	~Image();

	Image * clone(Image * dst);

	void setPixel(char *rgb, int x, int y);
	void setPixel(int r, int g, int b, int x, int y);
	void setPixel(int a, int r, int g, int b, int x, int y);
	void setPixelsLine(int *rgb, int size, int x, int y);
	void rollImage(int shift);
	void clear();
	int getPixel(int x, int y);
	int *getPixelsLine(int x, int y);
	int *getPixels();
	void plot(Image *foreground, int startx, int starty);
	void subimage(Image *dest, int startx, int starty, int endx, int endy);
	void resizePixels(Image * pixels, int w2, int h2);
	int getWidth() { return width; }
	int getHeight() { return height; }
};

