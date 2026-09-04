#include "../Headers/gpu_objects_container.h"
#include <stdexcept>

Gpu_objects_container::Descriptor_set_layout_container::Descriptor_set_layout_container(const Logical_device_data& device) :descriptor_set_layout_array{},
descriptor_set_layout0{ descriptor_set_layout_array[0]},
descriptor_set_layout1{ descriptor_set_layout_array[1] },
descriptor_set_layout2{ descriptor_set_layout_array[2] },
descriptor_set_layout3{ descriptor_set_layout_array[3] }
{
    VkDescriptorSetLayoutBinding uboLayoutBinding[3]{};
    VkDescriptorSetLayoutCreateInfo layoutInfo{};

   
   //basic

        uboLayoutBinding[0].binding = 0;
        uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        //the length of the array of bindings in binding 0(our binding), in this case its thats 1 (array length = 1 )
        uboLayoutBinding[0].descriptorCount = 1;
        uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;


        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = uboLayoutBinding;

        if (vkCreateDescriptorSetLayout(device.device, &layoutInfo, nullptr, &descriptor_set_layout0) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
//camera.vp,sunlight,6 light sources

        uboLayoutBinding[0].binding = 0;

        uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        //the length of the array of bindings in binding 0(our binding), in this case its thats 1 (array length = 1 )
        uboLayoutBinding[0].descriptorCount = 1;
        uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        uboLayoutBinding[0].pImmutableSamplers = nullptr;


        uboLayoutBinding[1].binding = 1;

        uboLayoutBinding[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        //the length of the array of bindings in binding 0(our binding), in this case its thats 1 (array length = 1 )
        uboLayoutBinding[1].descriptorCount = 1;
        uboLayoutBinding[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        uboLayoutBinding[1].pImmutableSamplers = nullptr;



        uboLayoutBinding[2].binding = 2;

        uboLayoutBinding[2].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        //the length of the array of bindings in binding 0(our binding), in this case its thats 1 (array length = 1 )
        uboLayoutBinding[2].descriptorCount = 6;//number of light sources
        uboLayoutBinding[2].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        uboLayoutBinding[2].pImmutableSamplers = nullptr;


        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 3;
        layoutInfo.pBindings = uboLayoutBinding;

        if (vkCreateDescriptorSetLayout(device.device, &layoutInfo, nullptr, &descriptor_set_layout1) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }

    //mvp,texture

        uboLayoutBinding[0].binding = 0;
        uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        //the length of the array of bindings in binding 0(our binding), in this case its thats 1 (array length = 1 )
        uboLayoutBinding[0].descriptorCount = 1;
        uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        uboLayoutBinding[1].binding = 1;
        uboLayoutBinding[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        //the length of the array of bindings in binding 0(our binding), in this case its thats 1 (array length = 1 )
        uboLayoutBinding[1].descriptorCount = 1;
        uboLayoutBinding[1].pImmutableSamplers = nullptr;
        uboLayoutBinding[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;



        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 2;
        layoutInfo.pBindings = uboLayoutBinding;

      
        if (vkCreateDescriptorSetLayout(device.device, &layoutInfo, nullptr, &descriptor_set_layout2) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    //compute_partical_system


        uboLayoutBinding[0].binding = 0;
        uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding[0].descriptorCount = 1;
        uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

        uboLayoutBinding[1].binding = 1;
        uboLayoutBinding[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        uboLayoutBinding[1].descriptorCount = 1;
        uboLayoutBinding[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

        uboLayoutBinding[2].binding = 2;
        uboLayoutBinding[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        uboLayoutBinding[2].descriptorCount = 1;
        uboLayoutBinding[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;



        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 3;
        layoutInfo.pBindings = uboLayoutBinding;

        if (vkCreateDescriptorSetLayout(device.device, &layoutInfo, nullptr, &descriptor_set_layout3) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }

}