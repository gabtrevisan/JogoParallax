#pragma once
class Rect {
public:
	int xup;
	int yup;
	int width;
	int height;
	Rect(int xup,int yup,int width,int height) {
		this->xup = xup;
		this->yup = yup;
		this->width = width;
		this->height = height;
	};
};

