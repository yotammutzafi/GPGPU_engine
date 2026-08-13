#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // Necessary for Vulkan depth range
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
int main()
{
    if (glfwInit()) {
        std::cout << "Initializing GLFW worked" << std::endl;
    }
    else
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
    }
    glm::mat4 m{ 1.0f };


    return 0;
}