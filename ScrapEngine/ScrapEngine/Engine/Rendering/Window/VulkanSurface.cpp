#include "VulkanSurface.h"

ScrapEngine::VulkanSurface::VulkanSurface(ScrapEngine::VukanInstance* input_instanceRef, ScrapEngine::GameWindow* windowRef) 
	: instanceRef(input_instanceRef->getVulkanInstance())
{
	createSurface(windowRef);
}

ScrapEngine::VulkanSurface::~VulkanSurface()
{
	vkDestroySurfaceKHR(instanceRef, surface, nullptr);
}

void ScrapEngine::VulkanSurface::createSurface(ScrapEngine::GameWindow* windowRef)
{
	if (glfwCreateWindowSurface(instanceRef, windowRef->getWindowRef(), nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

VkSurfaceKHR ScrapEngine::VulkanSurface::getSurface() const
{
	return surface;
}
