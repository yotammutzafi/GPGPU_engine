#pragma once
#include <mutex>
#include "../../System objects/Vulkan_system/Headers/Vulkan_resources_decleration.h"



class App;
class Submissioninfos_access
{
	friend class App;
private:
	mutable std::mutex mutex;
	mutable std::vector<const VkSubmitInfo*> submitinfos;
public:
	const Queue& queue;

	Submissioninfos_access(const Queue& queue);

	void Add_submitinfos(const std::vector<const VkSubmitInfo*>& submitinfos_input)const;


	Submissioninfos_access(Submissioninfos_access&& other) noexcept;
};