#include <Engine/Rendering/Window/VulkanSurface.h>
#include <Engine/Debug/DebugLog.h>

//Init static instance reference

ScrapEngine::Render::VulkanSurface* ScrapEngine::Render::VulkanSurface::instance_ = nullptr;

//Class

void ScrapEngine::Render::VulkanSurface::init(GameWindow* window_ref)
{
	create_surface(window_ref);
}

ScrapEngine::Render::VulkanSurface::~VulkanSurface()
{
	VukanInstance::get_instance()->get_vulkan_instance()->destroySurfaceKHR(surface_);
}

ScrapEngine::Render::VulkanSurface* ScrapEngine::Render::VulkanSurface::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanSurface();
	}
	return instance_;
}

void ScrapEngine::Render::VulkanSurface::create_surface(GameWindow* window_ref)
{
	surface_ = vk::SurfaceKHR();
	if (glfwCreateWindowSurface(*VukanInstance::get_instance(), window_ref->window_, nullptr,
	                            reinterpret_cast<VkSurfaceKHR*>(&surface_)) != VK_SUCCESS)
	{
		Debug::DebugLog::fatal_error(vk::Result(-13), "VulkanSurface: Failed to create window surface!");
	}
}

vk::SurfaceKHR* ScrapEngine::Render::VulkanSurface::get_surface()
{
	return &surface_;
}
