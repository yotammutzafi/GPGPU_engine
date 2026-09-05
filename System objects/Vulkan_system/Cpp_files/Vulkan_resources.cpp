#include "../Headers/Vulkan_resources.h"
#include "../Headers/Vulkan_system.h"
#include <iostream>
#include <GLFW/glfw3.h>
const extern bool enableValidationLayers;

Vulkan_resources::Vulkan_resources()
{
    CreateInstance();
    Printextension();
    Create_physical_devices_and_resources();
    printing_physical_devices();
    create_resources();

}

void Vulkan_resources::CreateInstance()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    appInfo.apiVersion = VK_API_VERSION_1_2;



    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    VkValidationFeatureEnableEXT enabledFeatures[] = {
VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT
    };

    VkValidationFeaturesEXT features = {};
    features.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
    features.enabledValidationFeatureCount = 1;
    features.pEnabledValidationFeatures = enabledFeatures;


    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = &features; // <--- This links the features to the instance


    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    /*this function must has glfwInit() to be called before using otherways it will return null
    */


    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    if (glfwExtensions == nullptr)
    {
        std::cout << "EEROR: GLFW is not enable" << std::endl;
        std::cout << "EEROR: GLFW is not enable" << std::endl;
        std::cout << "EEROR: GLFW is not enable" << std::endl;
    }

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME); // Mandatory for pNext to work!
    }


    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}
void Vulkan_resources::Printextension()
{
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties>extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    std::cout << "available extensions:\n";

    for (const auto& extension : extensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }
}
void Vulkan_resources::Create_physical_devices_and_resources()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> temp_physical_devices_array;
    temp_physical_devices_array.resize(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, temp_physical_devices_array.data());
    physical_devices.resize(deviceCount);
    for (int i = 0; i < deviceCount; i++)
    {
        physical_devices[i] =
            new Physical_device{ instance,temp_physical_devices_array[i],i };
    }
}

void Vulkan_resources::printing_physical_devices()
{
    for (auto p: physical_devices)
    {
        p->physical_device_data.printing_physical_device();
    }
}

void Vulkan_resources::create_resources()
{
    physical_device = physical_devices[0];
    logical_device = physical_device->Create_logical_device( deviceExtensions,validationLayers, Logical_device_data::Queue_creation_option::option_1);

    graphics_family_queue = logical_device->family_queues[0];
    compute_family_queue = logical_device->family_queues[1];
    graphics_queue = graphics_family_queue->queues[0];
    compute_queue = compute_family_queue->queues[0];
}

Vulkan_resources::~Vulkan_resources()
{
    std::cout << "ERROR: there is no destractor for Vulkan_resources" << std::endl;
    std::cout << "ERROR: there is no destractor for Vulkan_resources" << std::endl;
    std::cout << "ERROR: there is no destractor for Vulkan_resources" << std::endl;
}
