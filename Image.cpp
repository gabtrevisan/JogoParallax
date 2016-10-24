/**
@author Gabriela de Campos Trevisan
*/

#include "Image.h"
Image::Image(int w, int h)
{
	width = w;
	height = h;
	pixels = new int[width*height];
}

Image::~Image()
{
	delete pixels;
}

Image* Image::clone(Image *dst) {
	for (int i = 0; i < this->height; i++)
	{
		dst->setPixelsLine(this->getPixelsLine(0, i), width, 0, i);
	}
	return dst;
}

void Image::setPixel(char *rgb, int x, int y) {
	int pix = rgb[0] << 24 | (rgb[1] & 0xFF) << 16 | (rgb[2] & 0xFF) << 8 | (rgb[3] & 0xFF);
	pixels[x + y*width] = pix;
}

void Image::setPixel(int r, int g, int b, int x, int y) {
	int pix = 0xFF << 24 | (r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF);
	pixels[x + y*width] = pix;
}

void Image::setPixel(int a, int r, int g, int b, int x, int y) {
	int pix = (a & 0xFF) << 24 | (r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF);
	pixels[x + y*width] = pix;
}

void Image::setPixelsLine(int *rgb, int size, int x, int y) {
	int* pixelpointer = pixels;
	pixelpointer += x + y * width;
	memcpy(pixelpointer, rgb, size * sizeof(int));		
}

void Image::rollImage(int shift)
{
	//Copia as colunas que irão para o final da imagem
	Image *copy = new Image(shift, height);
	this->subimage(copy, 0, 0, shift, height);
	//Desloca o restante da imagem para esquerda
	for (int i = 0; i < height; i++)
	{
		this->setPixelsLine(getPixelsLine(shift, i), width-shift, 0, i);
		this->setPixelsLine(copy->getPixelsLine(0, i), shift, width-shift, i);
	}
	delete copy;
}

void Image::clear() {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			this->setPixel(0, 255, 255, 255, j, i);
		}
	}
}

int Image::getPixel(int x, int y) {
	return pixels[x + y*getWidth()];
}

int *Image::getPixels() {
	return pixels;
}

int *Image::getPixelsLine(int x, int y) {
	int* pixelspointer = pixels;
	pixelspointer += x + y * width;
	return pixelspointer;
}

void Image::plot(Image *foreground, int startx, int starty) {
	int a, r, g, b;
	for (int y = 0; y < foreground->getHeight(); y++) 
	{
		for (int x = 0; x < foreground->getWidth(); x++) 
		{
			a = foreground->getPixel(x, y) >> 24 & 0xFF;
			r = foreground->getPixel(x, y) >> 16 & 0xff;
			g = foreground->getPixel(x, y) >> 8 & 0xff;
			b = foreground->getPixel(x, y) & 0xff;

			int pixelBg = this->getPixel(x, y);
			int ab = pixelBg >> 24 & 0xFF;
			int rb = pixelBg >> 16 & 0xff;
			int gb = pixelBg >> 8 & 0xff;
			int bb = pixelBg & 0xff;
			
			/* Se o pixel atual da imagem de parâmetro é opaco (canal alfa do pixel é 255), então 
			 * apenas substituir pixels da imagem pelo pixel da imagem de parâmetro.*/
			if (a > 0) {
				r = rb*(1 - a / 255) + r*a / 255;
				g = gb*(1 - a / 255) + g*a / 255;
				b = bb*(1 - a / 255) + b*a / 255;
				setPixel(a, r, g, b, x + startx, y+ starty);
			} 
		}
	}
}

void Image::subimage(Image *dest, int startx, int starty, int endx, int endy) {
	int y1 = 0;
	for (int y = starty; y < endy; y++)
	{
		dest->setPixelsLine(this->getPixelsLine(startx, y), endx - startx, 0, y1);
		y1++;
	}
}

void Image::resizePixels(Image *pixels, int w2, int h2) {	
	int w1 = this->getWidth();
	int h1 = this->getHeight();	
	double x_ratio = w1 / (double)w2;
	double y_ratio = h1 / (double)h2;
	double px, py;

	for (int i = 0; i<h1; i++) {
		for (int j = 0; j<w1; j++) {
			px = floor(j*x_ratio);
			py = floor(i*y_ratio);
			int a = this->getPixel(j, i) >> 24 & 0xFF;
			int r = this->getPixel(j, i) >> 16 & 0xff;
			int g = this->getPixel(j, i) >> 8 & 0xff;
			int b = this->getPixel(j, i) & 0xff;
			pixels->setPixel(a, r, g, b, (int)px, (int)py);			
		}
	}
}
