#include "FirstTriangle.h"
#include "FirstRectangle.h"
#include "practice/Practice1.h"
#include "practice/Practice2.h"
#include "practice/Practice3.h"

void processInput(GLFWwindow* window)
{
	//检查有没有按下esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	FirstTriangle firstTriangle;
	FirstRectangle firstRectangle;
	Practice1 practice1;
	Practice2 practice2;
	Practice3 practice3;

	return 0;
}