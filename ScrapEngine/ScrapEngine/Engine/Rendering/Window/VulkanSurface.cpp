#include "VulkanSurface.h"
#include "../Base/StaticTypes.h"
//Init Static Members

const vk::SurfaceKHR* ScrapEngine::Render::VulkanSurface::StaticSurfaceRef = nullptr;

//Class

ScrapEngine::Render::VulkanSurface::VulkanSurface(ScrapEngine::Render::GameWindow* windowRef)
{
	createSurface(windowRef);
	StaticSurfaceRef = &surface;
}

ScrapEngine::Render::VulkanSurface::~VulkanSurface()
{
	VukanInstance::StaticInstanceRef->destroySurfaceKHR(surface);
}

void ScrapEngine::Render::VulkanSurface::createSurface(ScrapEngine::Render::GameWindow* windowRef)
{
	surface = vk::SurfaceKHR();
	if (glfwCreateWindowSurface(*VukanInstance::StaticInstanceRef, windowRef->window, nullptr, reinterpret_cast<VkSurfaceKHR*>(&surface)) != VK_SUCCESS) {
		throw std::runtime_error("VulkanSurface: Failed to create window surface!");
	}
}

vk::SurfaceKHR* ScrapEngine::Render::VulkanSurface::getSurface()
{
	return &surface;
}
