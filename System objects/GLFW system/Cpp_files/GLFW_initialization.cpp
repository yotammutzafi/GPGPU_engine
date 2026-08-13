#include "../Headers/GLFW_initialization.h"
#include <iostream>

GLFW_Core_system::GLFW_Core_system()
{
	GLFW_initialization();
}

void GLFW_Core_system::GLFW_initialization()
{
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

}


GLFW_Core_system::~GLFW_Core_system()
{
	glfwTerminate();
}