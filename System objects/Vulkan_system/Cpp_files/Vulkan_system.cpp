#include "../../Global_Variables/Constants_and_function/Headers/Constants_and_function.h"
#include "../Headers/Vulkan_system.h"
#include <iostream>

#pragma region Physical_device_data
Physical_device_data::Physical_device_data(VkInstance instance,VkPhysicalDevice physical_device, int index):
    instance{ instance }, physical_device{ physical_device }, index{index}
{
    vkGetPhysicalDeviceProperties(physical_device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(physical_device, &deviceFeatures);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queueFamilyCount, nullptr);
    queue_familys_properties.resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queueFamilyCount, queue_familys_properties.data());
}
void Physical_device_data::printing_physical_device()const
{
    std::cout << "Device name:" << deviceProperties.deviceName << std::endl;
    std::cout << "Queue familys:" << std::endl;
    for (unsigned int j = 0; j < queueFamilyCount; j++)
    {
        std::cout << "Queue family ID:" << j << std::endl;
        std::cout << "Queue family queue count is: " << queue_familys_properties[j].queueCount << std::endl;

        std::cout << "Queue family capabilities:" << std::endl;

        if (queue_familys_properties[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            std::cout << "VK_QUEUE_GRAPHICS_BIT" << std::endl;
        if (queue_familys_properties[j].queueFlags & VK_QUEUE_COMPUTE_BIT)
            std::cout << "VK_QUEUE_COMPUTE_BIT" << std::endl;
        if (queue_familys_properties[j].queueFlags & VK_QUEUE_TRANSFER_BIT)
            std::cout << "VK_QUEUE_TRANSFER_BIT" << std::endl;
        if (queue_familys_properties[j].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
            std::cout << "VK_QUEUE_SPARSE_BINDING_BIT" << std::endl;
        if (queue_familys_properties[j].queueFlags & VK_QUEUE_PROTECTED_BIT)
            std::cout << "VK_QUEUE_PROTECTED_BIT" << std::endl;
        if (queue_familys_properties[j].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
            std::cout << "VK_QUEUE_VIDEO_DECODE_BIT_KHR" << std::endl;
        if (queue_familys_properties[j].queueFlags & VK_QUEUE_OPTICAL_FLOW_BIT_NV)
            std::cout << "VK_QUEUE_OPTICAL_FLOW_BIT_NV  " << std::endl;
    }
}


#pragma endregion

#pragma region Logical_device_data
Logical_device_data::Logical_device_data(const Physical_device_data* Physical_device_data, const int device_index,const std::vector<const char*>& deviceExtensions, const std::vector<const char*>& validationLayers, Queue_creation_option option):physical_device_data{ Physical_device_data },
device_index{ device_index }, createInfo{}, deviceExtensions{ deviceExtensions }, validationLayers{ validationLayers }
{
    Queue_creation(option);
    //fill deviceFeaturess
    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;
    printing_device_supported_extensions();
    Create_logical_device(deviceFeatures);
}
void Logical_device_data::printing_device_supported_extensions()
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physical_device(), nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physical_device(), nullptr, &extensionCount, availableExtensions.data());
    std::cout << '\t' << "device extensions needed are:\n";

    for (int i = 0; i < deviceExtensions.size(); i++)
    {
        bool available = false;
        std::cout << '\t' << deviceExtensions[i];
        for (unsigned int j = 0; j < extensionCount; j++)
        {
            if (strcmp(availableExtensions[j].extensionName, deviceExtensions[i]) == 0)
            {
                available = true;
                break;
            }
        }
        if (available)
            std::cout << " available" << '\n';
        else
            std::cout << " not available" << '\n';

    }
}
void Logical_device_data::Queue_creation(Logical_device_data::Queue_creation_option option)
{
    switch (option)
    {
    case Logical_device_data::Queue_creation_option::option_1:
        Queue_creation_option_1();
        break;
    default:
        std::cout << "ERROR: Logical_device_data::Queue_creation: Invalid option" << std::endl;
        std::cout << "ERROR: Logical_device_data::Queue_creation: Invalid option" << std::endl;
        std::cout << "ERROR: Logical_device_data::Queue_creation: Invalid option" << std::endl;
        break;

    }

}
void Logical_device_data::Queue_creation_option_1()
{
    std::vector <float*> queue_priorities;
    int queue_count = 2;
    //initializing queue_priorities
    queue_priorities.resize(queue_count);
    for (size_t i = 0; i < queue_priorities.size(); i++)
    {
        queue_priorities[i] = new float{ 1.0 };
    }
    //initializing queueCreateInfos
    queueCreateInfos.resize(queue_count);
    for (size_t i = 0; i < queueCreateInfos.size(); i++)
    {
        queueCreateInfos[i].pQueuePriorities = queue_priorities[i];
        queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    }
    //graphics queueFamily(this has VK_QUEUE_COMPUTE_BIT too)
    queueCreateInfos[0].queueFamilyIndex = 0;//the QueueFamilieIndex
    queueCreateInfos[0].queueCount = 1;
    //COMPUTE queueFamily (VK_QUEUE_COMPUTE_BIT VK_QUEUE_TRANSFER_BIT)
    queueCreateInfos[1].queueFamilyIndex = 2;//the QueueFamilieIndex
    queueCreateInfos[1].queueCount = 1;
}

void Logical_device_data::Create_logical_device( VkPhysicalDeviceFeatures& deviceFeatures)
{
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = 0; //ever since vulkan 1.0.0 createInfo.enabledLayerCount needs to be zero = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames;//ever since vulkan 1.0.0 createInfo.enabledLayerCount needs to be zero= validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    VkPhysicalDeviceTimelineSemaphoreFeatures timelineSemaphoreFeatures = {};
    timelineSemaphoreFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
    timelineSemaphoreFeatures.timelineSemaphore = VK_TRUE; // זה החלק החשוב!
    timelineSemaphoreFeatures.pNext = nullptr;
    createInfo.pNext = &timelineSemaphoreFeatures;


    if (vkCreateDevice(physical_device(), &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
}



VkInstance Logical_device_data::instace() const
{
    return physical_device_data->instance;
}


VkPhysicalDevice Logical_device_data::physical_device()const
{
    return physical_device_data->physical_device;
}
int Logical_device_data::physical_device_index()const
{
    return physical_device_data->index;
}

#pragma endregion

#pragma region Family_queue_data
Family_queue_data::Family_queue_data(const Logical_device_data* logical_device_data, const int family_queue_physical_index, const int family_queue_device_index):logical_device_data{ logical_device_data },
family_queue_physical_index{ family_queue_physical_index }
, family_queue_device_index{ family_queue_device_index }
{
}
VkInstance Family_queue_data::instace() const
{
    return physical_device_data()->instance;
}
VkPhysicalDevice Family_queue_data::physical_device()const
{
    return logical_device_data->physical_device();
}
const Physical_device_data* Family_queue_data::physical_device_data()const
{
    return logical_device_data->physical_device_data;
}

int Family_queue_data::physical_device_index()const
{
    return logical_device_data->physical_device_index();
}

VkDevice Family_queue_data::device()const
{
    return logical_device_data->device;
}

int Family_queue_data::device_index()const
{
    return logical_device_data->device_index;
}



#pragma endregion

#pragma region Queue
Queue::Queue(Family_queue_data* family_queue_data, int queue_index):
    family_queue_data{ family_queue_data }, queue_index{ queue_index }
{
    vkGetDeviceQueue(this->device(), family_queue_data->family_queue_physical_index
        ,this->queue_index,&queue);
}
VkInstance Queue::instace()const
{
    return family_queue_data->instace();
}
const Physical_device_data* Queue::physical_device_data()const
{
    return family_queue_data->physical_device_data();
}
int Queue::physical_device_index()const
{
    return family_queue_data->physical_device_index();
}

VkPhysicalDevice Queue::Physical_device() const
{
    return family_queue_data->physical_device();
}

const Logical_device_data* Queue::logical_device_data() const
{
    return family_queue_data->logical_device_data;
}

VkDevice Queue::device() const
{
    return family_queue_data->device();
}
int Queue::device_index() const
{
    return family_queue_data->device_index();
}
int Queue::family_queue_physical_index() const
{
    return family_queue_data->family_queue_physical_index;
}
int Queue::family_queue_device_index()const
{
    return family_queue_data->family_queue_device_index;
}
#pragma endregion

#pragma region Commandpool
Commandpool::Commandpool(const Family_queue_data* family_queue_data, VkCommandPoolCreateFlags build_flag) :family_queue_data{ family_queue_data }
{
    if (family_queue_data == nullptr)
    {
        std::cout << "ERROR: famalyqueue_structure_data == nullptr" << std::endl;
        std::cout << "ERROR: famalyqueue_structure_data == nullptr" << std::endl;
        std::cout << "ERROR: famalyqueue_structure_data == nullptr" << std::endl;
    }
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = build_flag;
    poolInfo.queueFamilyIndex = family_queue_physical_index();

    if (vkCreateCommandPool(
        device(),
        &poolInfo, nullptr, &commandpool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }

}

VkInstance Commandpool::instace()const
{
    return family_queue_data->instace();
}

const Physical_device_data* Commandpool::physical_device_data()const
{
    return family_queue_data->physical_device_data();
}
int Commandpool::physical_device_index()const
{
    return family_queue_data->physical_device_index();
}
VkPhysicalDevice Commandpool::Physical_device()const
{
    return family_queue_data->physical_device();
}
const Logical_device_data* Commandpool::logical_device_data()const
{
    return family_queue_data->logical_device_data;
}
VkDevice Commandpool::device()const
{
    return family_queue_data->device();
}
int Commandpool::device_index()const
{
    return family_queue_data->device_index();
}
int Commandpool::family_queue_physical_index()const
{
    return family_queue_data->family_queue_physical_index;
}
int Commandpool::family_queue_device_index()const
{
    return family_queue_data->family_queue_device_index;
}


#pragma endregion

#pragma region Commandbuffer
Commandbuffer::Commandbuffer(const Commandpool* commandpool_input/*, flag*/) :
    commandpool_obj{ commandpool_input }
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandpool_input->commandpool;
    //allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    //COMMANDBUFFER_LEVEL_OPTION(&allocInfo, flag);
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(device(), &allocInfo, &commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

VkInstance Commandbuffer::instace()const
{
    return commandpool_obj->instace();
}
const Physical_device_data* Commandbuffer::physical_device_data()const
{
    return commandpool_obj->physical_device_data();
}
int Commandbuffer::physical_device_index()const
{
    return commandpool_obj->physical_device_index();
}
VkPhysicalDevice Commandbuffer::Physical_device()const
{
    return commandpool_obj->Physical_device();
}
const Logical_device_data* Commandbuffer::logical_device_data()const
{
    return commandpool_obj->logical_device_data();
}
VkDevice Commandbuffer::device()const
{
    return commandpool_obj->device();
}
int Commandbuffer::device_index()const
{
    return commandpool_obj->device_index();
}
int Commandbuffer::family_queue_physical_index()const
{
    return commandpool_obj->family_queue_physical_index();
}
int Commandbuffer::family_queue_device_index()const
{
    return commandpool_obj->family_queue_device_index();
}
VkCommandPool Commandbuffer::commandpool()const
{
    return commandpool_obj->commandpool;
}


#pragma endregion

#pragma region Family_queue
Family_queue::Family_queue(Logical_device_data* logical_device_data, const int family_queue_physical_index, const int family_queue_device_index, int number_of_queues) :family_queue_data{ logical_device_data ,family_queue_physical_index ,family_queue_device_index }
{
    Create_queues(number_of_queues);
}
void Family_queue::Create_queues(int number_of_queues)
{
    for (int i = 0; i < number_of_queues; i++)
    {
        queues.push_back(new Queue{&family_queue_data ,i });
    }
}
#pragma endregion

#pragma region Logical_device



Logical_device::Logical_device(const Physical_device_data* Physical_device_data, const int device_index, const std::vector<const char*> deviceExtensions, const std::vector<const char*> validationLayers,Logical_device_data::Queue_creation_option option):
    logical_device_data{ Physical_device_data ,device_index ,deviceExtensions,validationLayers,option }
{
    Create_familyqueues();
}
void Logical_device::Create_familyqueues()
{
    family_queues.reserve(logical_device_data.queueCreateInfos.size());
    for (int i = 0; i <logical_device_data.queueCreateInfos.size(); i++)
    {
        family_queues.push_back(new Family_queue(&logical_device_data, logical_device_data.queueCreateInfos[i].queueFamilyIndex, i, logical_device_data.queueCreateInfos[i].queueCount));
    }

}

#pragma endregion

#pragma region Physical_device
Physical_device::Physical_device(VkInstance instance, VkPhysicalDevice physical_device, int index) :physical_device_data { instance,physical_device,index }
{
}
Logical_device* Physical_device::Create_logical_device(const std::vector<const char*> deviceExtensions, const std::vector<const char*> validationLayers, Logical_device_data::Queue_creation_option option)
{
    Logical_device* ptr = new Logical_device(&physical_device_data, logical_devices.size(), deviceExtensions, validationLayers, option);
    logical_devices.push_back(ptr);

    return ptr;
}
#pragma endregion


