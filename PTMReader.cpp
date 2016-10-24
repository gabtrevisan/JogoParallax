/**
@author Gabriela de Campos Trevisan
*/
#include "PTMReader.h"
PTMReader::PTMReader()
{
}

PTMReader::~PTMReader()
{
}

Image* PTMReader::read(char *filename)
{
	Image* img = NULL;
	int width, height, i = 0, j = 0, k = 0, l = 0, x = 0, y = 0;
	string line;
	string buf;

	ifstream ptm(filename);
	if (ptm.is_open()) 
	{
		while (getline(ptm, line))
		{
			if (line.at(0) != '#') {
				if(i == 0) {}
				else if (i == 1) {							
					vector<string> sep = split(line, ' ');
					width = stoi(sep[0]);
					height = stoi(sep[1]);
					img = new Image(width, height);					
				}
				else if(i == 2) {}
				else {	
					char* rgb = new char[5];
					memset(rgb, 0, 5);
					for (j = 0; j < line.length(); j++) {
						if (line.at(j) != ' ') {
							buf.push_back(line.at(j));
							k++;
						}
						else {
							rgb[l] = stoi(buf);
							buf.clear();
							k = 0;
							l++;
							if (l == 4) {
								l = 0;
								img->setPixel(rgb, x, y);
								x++;
								if (x == width) {
									x = 0;
									y++;
								}
							}								
						}
					}
				}
				i++;
			}
		}
		ptm.close();
	}
	return img;
}

vector<string> PTMReader::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}