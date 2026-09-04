#pragma once
#include <vulkan/vulkan.h>
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <vector>

class Vertex_buffer
{
public:
	virtual void  getBindingDescription(VkVertexInputBindingDescription& bindingDescription) const = 0;
	virtual void getAttributeDescriptions(std::vector<VkVertexInputAttributeDescription>& attributeDescriptions) const = 0;
private:

};
	class Vertex_3_2: public Vertex_buffer
	{
	public:
		struct Vertex_struct
		{
			glm::vec3 pos;
			glm::vec2 tex;
		};
		

		 void  getBindingDescription(VkVertexInputBindingDescription& bindingDescription)const override;
		 void getAttributeDescriptions(std::vector<VkVertexInputAttributeDescription>& attributeDescriptions)const override;
	};
	class Particle:public Vertex_buffer {
	public:
		struct Vertex_struct
		{
			alignas(16) glm::vec3 position;
			alignas(16) glm::vec3 velocity;
			alignas(16) glm::vec4 color;
		};
		

//		virtual void  getBindingDescription(VkVertexInputBindingDescription& bindingDescription)final;
//		virtual void getAttributeDescriptions(std::vector<VkVertexInputAttributeDescription>& attributeDescriptions)final;
	};
