#include "../mineimator.h"

void drawImage(Image *image, int x, int y) {
	drawImage(image, x, y, colorMake(255, 255, 255), 1.0, 1.0, 1.0);
}

void drawImage(Image *image, int x, int y, int color, double alpha) {
	drawImage(image, x, y, color, alpha, 1.0, 1.0);
}

void drawImage(Image *image, int x, int y, int color, double alpha, double xScale, double yScale) {
	glBindTexture(GL_TEXTURE_2D, image->texture);
	glBegin(GL_QUADS);

	glColor4d(
		colorGetRed(color) / 255.0,
		colorGetGreen(color) / 255.0,
		colorGetBlue(color) / 255.0,
		alpha
	);

	glTexCoord2d(0, 0);
	glVertex2d(x, y);
	glTexCoord2d(1, 0);
	glVertex2d(x + image->width * xScale, y);
	glTexCoord2d(1, 1);
	glVertex2d(x + image->width * xScale, y + image->height * yScale);
	glTexCoord2d(0, 1);
	glVertex2d(x, y + image->height * yScale);

	glEnd();
}

void drawBox(int x, int y, int width, int height, bool fill, int color, double alpha) {
	if (fill)
		glBegin(GL_QUADS);
	else
		glBegin(GL_LINE_LOOP);

	glColor4d(
		colorGetRed(color) / 255.0,
		colorGetGreen(color) / 255.0,
		colorGetBlue(color) / 255.0,
		alpha
	);
		
	glVertex2d(x, y);
	glVertex2d(x + width, y);
	glVertex2d(x + width, y + height);
	glVertex2d(x, y + height);

	glEnd();
}

void drawGradient(int x, int y, int width, int height, int color, double alphaTopLeft, double alphaTopRight, double alphaBottomRight, double alphaBottomLeft) {
	double r, g, b;

	r = colorGetRed(color) / 255.0;
	g = colorGetGreen(color) / 255.0;
	b = colorGetBlue(color) / 255.0;

	glBegin(GL_QUADS);

	glColor4d(r, g, b, alphaTopLeft);
	glVertex2d(x, y);
	glColor4d(r, g, b, alphaTopRight);
	glVertex2d(x + width, y);
	glColor4d(r, g, b, alphaBottomRight);
	glVertex2d(x + width, y + height);
	glColor4d(r, g, b, alphaBottomLeft);
	glVertex2d(x, y + height);

	glEnd();
}

void drawLine(int x1, int y1, int x2, int y2, int color, double alpha) {
	glBegin(GL_LINES);

	glColor4d(
		colorGetRed(color) / 255.0,
		colorGetGreen(color) / 255.0,
		colorGetBlue(color) / 255.0,
		alpha
	);

	glVertex2d(x1, y1);
	glVertex2d(x2, y2);

	glEnd();
}