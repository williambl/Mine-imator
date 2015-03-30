﻿#include "mineimator.h"

int main() {
	/*zip_fileinfo zfi;
	zipFile zf = zipOpen("myarch.zip", APPEND_STATUS_CREATE);
	int ret = zipOpenNewFileInZip(zf,
								  "myfile.txt",
								  &zfi,
								  NULL, 0,
								  NULL, 0,
								  "my comment for this interior file",
								  Z_DEFLATED,
								  Z_NO_COMPRESSION
								  );
	zipCloseFileInZip(zf);
	zipClose(zf, "my comment for exterior file");*/

	GLFWwindow* window;
	glfwSetErrorCallback(errorCallback);
	
	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "Mine-imator", NULL, NULL);
	windowMaximize(window);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);

	wstring_list formats;
	formats.push_back(L"PNG files (*.png)");
	formats.push_back(L"*.png");
	formats.push_back(L"JPG files (*.jpg)");
	formats.push_back(L"*.jpg;*.jpeg");
	formats.push_back(L"All files (*.*)");
	formats.push_back(L"*.*");

	wstring_list fn = dialogOpenFile(L"\"My Title\"", L"", formats, true);
	//wstring fn = dialogSaveFile(L"\"My Title\"", L"", formats);
	wcout << "fn = " << fn[0] << endl;

	Image myImage(fn[0]);
	cout << myImage.width << "x" << myImage.height << endl;
	
	while (!glfwWindowShouldClose(window)) {
		int width, height;

		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, 0, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		drawImage(&myImage, 0, 0);
		drawGradient(0, 0, width, height, colorMake(255, 50, 0), 0, 0, 1, 1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void errorCallback(int error, const char* description) {
	cout << "Error " << error << ": " << description << endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		std::cout << "Click!" << std::endl;
}

void windowMaximize(GLFWwindow* window) {
#ifdef _WIN32
	glfwMaximizeWindow(window);
#else
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(window, 25, 25);
	glfwSetWindowSize(window, mode->width - 50, mode->height - 100);
#endif
}