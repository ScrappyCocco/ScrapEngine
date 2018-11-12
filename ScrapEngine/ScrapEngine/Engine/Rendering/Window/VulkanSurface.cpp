#include "VulkanSurface.h"
#include "../Base/StaticTypes.h"
//Init Static Members

const vk::SurfaceKHR* ScrapEngine::VulkanSurface::StaticSurfaceRef = nullptr;

//Class

ScrapEngine::VulkanSurface::VulkanSurface(ScrapEngine::GameWindow* windowRef) 
{
	createSurface(windowRef);
	StaticSurfaceRef = &surface;
}

ScrapEngine::VulkanSurface::~VulkanSurface()
{
	VukanInstance::StaticInstanceRef->destroySurfaceKHR(surface);
}

void ScrapEngine::VulkanSurface::createSurface(ScrapEngine::GameWindow* windowRef)
{
	surface = vk::SurfaceKHR();
	if (glfwCreateWindowSurface(*VukanInstance::StaticInstanceRef, windowRef->window, nullptr, reinterpret_cast<VkSurfaceKHR*>(&surface)) != VK_SUCCESS) {
		throw std::runtime_error("VulkanSurface: Failed to create window surface!");
	}
}

vk::SurfaceKHR* ScrapEngine::VulkanSurface::getSurface()
{
	return &surface;
}
