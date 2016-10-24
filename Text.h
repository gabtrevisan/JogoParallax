#pragma once
#include "Image.h"
#include "PTMReader.h"
class Text
{
private:
	PTMReader ptm;
	Image* font;
public:
	Text();
	~Text();
	Image* textToImage(string text);
};

