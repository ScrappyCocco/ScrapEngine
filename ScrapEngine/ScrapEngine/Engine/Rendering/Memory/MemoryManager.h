#pragma once

#include <vulkan/vulkan.hpp>
#include <stdexcept>

namespace ScrapEngine {
	static uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties, vk::PhysicalDevice* physicalDevice) {
		vk::PhysicalDeviceMemoryProperties memProperties;
		physicalDevice->getMemoryProperties(&memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}
		//Try a simpler way
		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if (memProperties.memoryTypes[i].propertyFlags == properties) {
				return i;
			}
		}

		throw std::runtime_error("Memory Manager: Failed to find suitable memory type!");
	}
}