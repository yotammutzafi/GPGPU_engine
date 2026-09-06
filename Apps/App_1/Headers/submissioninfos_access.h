#pragma once
#include <mutex>
#include "../../System objects/Vulkan_system/Headers/Vulkan_resources_decleration.h"



class App;
class submissioninfos_access
{
	friend class App;
private:
	mutable std::mutex mutex;
	mutable std::vector<const VkSubmitInfo*> submitinfos;
public:
	const Queue& queue;

	submissioninfos_access(const Queue& queue);

	void Add_submitinfos(const std::vector<const VkSubmitInfo*>& submitinfos_input)const;


	submissioninfos_access(submissioninfos_access&& other) noexcept;
};