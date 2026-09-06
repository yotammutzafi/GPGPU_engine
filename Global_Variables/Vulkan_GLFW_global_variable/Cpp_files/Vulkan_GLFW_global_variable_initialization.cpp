#include "../../System objects/GLFW system/Headers/GLFW_obj_initialization.h"
#include "../../System objects/Vulkan_system/Headers/Vulkan_resources_initialization.h"
#include "../../Graphics_and_gpu_objects/Graphics_and_gpu_objects_container/Headers/gpu_objects_container.h"
extern const Gpu_objects_container gpu_objects_container{ vulkan_resources.logical_device->logical_device_data };