#include "../Headers/data_classes.h"

 void  Vertex_3_2::getBindingDescription(VkVertexInputBindingDescription& bindingDescription)const
{
	 //The binding parameter specifies the index of the binding in the array of bindings
	 bindingDescription.binding = 0;
	 bindingDescription.stride = sizeof(Vertex_3_2);
	 bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
}
 void Vertex_3_2::getAttributeDescriptions(std::vector<VkVertexInputAttributeDescription>& attributeDescriptions)const
{
	 attributeDescriptions.resize(2);


	 (attributeDescriptions)[0].binding = 0;
	 (attributeDescriptions)[0].location = 0;
	 (attributeDescriptions)[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	 (attributeDescriptions)[0].offset = offsetof(Vertex_3_2::Vertex_struct, pos);

	 (attributeDescriptions)[1].binding = 0;
	 (attributeDescriptions)[1].location = 1;
	 (attributeDescriptions)[1].format = VK_FORMAT_R32G32_SFLOAT;
	 (attributeDescriptions)[1].offset = offsetof(Vertex_3_2::Vertex_struct, tex);
}