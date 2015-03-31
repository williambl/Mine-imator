#pragma once

class Image {
public:
	Image(wstring filename);
	Image(void *data);
	GLuint texture;
	int width, height;
private:
	void load(void *data);
};