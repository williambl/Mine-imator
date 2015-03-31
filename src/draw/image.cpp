#include "../mineimator.h"

Image::Image(wstring filename) {
	void* data = SOIL_load_image(&filename[0], &width, &height, 0, SOIL_LOAD_RGBA);
	load(data);
	SOIL_free_image_data((unsigned char*)data);
}

Image::Image(void *data) {
	load(data);
}

void Image::load(void *data) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}