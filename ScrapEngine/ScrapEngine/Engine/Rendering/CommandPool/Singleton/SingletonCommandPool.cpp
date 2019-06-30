#include <Engine/Rendering/CommandPool/Singleton/SingletonCommandPool.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

//Init static instance reference

ScrapEngine::Render::VulkanCommandPool* ScrapEngine::Render::SingletonCommandPool::instance_ = nullptr;

//Class

ScrapEngine::Render::VulkanCommandPool* ScrapEngine::Render::SingletonCommandPool::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SingletonCommandPool();
	}
	return instance_;
}
