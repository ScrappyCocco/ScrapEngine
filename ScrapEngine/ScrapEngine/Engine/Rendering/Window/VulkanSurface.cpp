#include "VulkanSurface.h"

ScrapEngine::VulkanSurface::VulkanSurface(ScrapEngine::VukanInstance* input_instanceRef, ScrapEngine::GameWindow* windowRef) 
	: instanceRef(input_instanceRef->getVulkanInstance())
{
	createSurface(windowRef);
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
