#pragma once

class Image {
public:
	Image(wstring filename);
	Image(void *data);
	GLuint texture;
	int width, height;
};