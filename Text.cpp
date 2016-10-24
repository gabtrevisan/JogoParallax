/**
@author Gabriela de Campos Trevisan
*/
#include "Text.h"
Text::Text()
{
	font = ptm.read("font.ptm");
}

Text::~Text()
{
}

Image* Text::textToImage(string text) {
	Image* image = new Image(text.length() * 32, 32);
	int x, y, x1 = 0;
	for (int i = 0; i < text.length(); i++) {
		x1 = i * 32;
		x = ((text[i] % 32) * 32);
		y = (int)(text[i] / 16) * 32;
		
		for (int j = 0; j < 32; j++)
		{			
			image->setPixelsLine(font->getPixelsLine(x, y+j), 32, x1, j);
		}
	}
	return image;
}
