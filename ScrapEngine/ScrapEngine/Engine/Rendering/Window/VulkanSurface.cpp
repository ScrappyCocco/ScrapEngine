#include "VulkanSurface.h"
#include "../Base/StaticTypes.h"
//Init Static Members

const vk::SurfaceKHR* ScrapEngine::Render::VulkanSurface::static_surface_ref = nullptr;

//Class

ScrapEngine::Render::VulkanSurface::VulkanSurface(ScrapEngine::Render::GameWindow* window_ref)
{
	create_surface(window_ref);
	static_surface_ref = &surface_;
}

ScrapEngine::Render::VulkanSurface::~VulkanSurface()
{
	VukanInstance::static_instance_ref->destroySurfaceKHR(surface_);
}

void ScrapEngine::Render::VulkanSurface::create_surface(ScrapEngine::Render::GameWindow* window_ref)
{
	surface_ = vk::SurfaceKHR();
	if (glfwCreateWindowSurface(*VukanInstance::static_instance_ref, window_ref->window_, nullptr,
	                            reinterpret_cast<VkSurfaceKHR*>(&surface_)) != VK_SUCCESS)
	{
		throw std::runtime_error("VulkanSurface: Failed to create window surface!");
	}
}

vk::SurfaceKHR* ScrapEngine::Render::VulkanSurface::get_surface()
{
	return &surface_;
}
