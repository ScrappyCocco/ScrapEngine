#include "VulkanSurface.h"

//Init Static Members

const vk::SurfaceKHR* ScrapEngine::VulkanSurface::StaticSurfaceRef = nullptr;

//Class

ScrapEngine::VulkanSurface::VulkanSurface(ScrapEngine::VukanInstance* input_instanceRef, ScrapEngine::GameWindow* windowRef) 
	: instanceRef(input_instanceRef->getVulkanInstance())
{
	createSurface(windowRef);
	StaticSurfaceRef = &surface;
}

ScrapEngine::VulkanSurface::~VulkanSurface()
{
	instanceRef->destroySurfaceKHR(surface);
}

void ScrapEngine::VulkanSurface::createSurface(ScrapEngine::GameWindow* windowRef)
{
	surface = vk::SurfaceKHR();
	if (glfwCreateWindowSurface(*instanceRef, windowRef->window, nullptr, reinterpret_cast<VkSurfaceKHR*>(&surface)) != VK_SUCCESS) {
		throw std::runtime_error("VulkanSurface: Failed to create window surface!");
	}
}

vk::SurfaceKHR* ScrapEngine::VulkanSurface::getSurface()
{
	return &surface;
}
