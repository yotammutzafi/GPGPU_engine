#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // Necessary for Vulkan depth range
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "../../Global_Variables/Vulkan_GLFW_global_variable/Headers/Vulkan_resources_decleration.h"
#include "Graphics_and_gpu_objects/Graphics_and_gpu_objects_container/Headers/gpu_objects_container.h"
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
    Gpu_objects_container container{ vulkan_resources.logical_device->logical_device_data };

    return 0;
}