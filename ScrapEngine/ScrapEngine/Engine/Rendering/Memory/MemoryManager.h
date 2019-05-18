#pragma once

#include <vulkan/vulkan.hpp>
#include <stdexcept>
#include "../Base/StaticTypes.h"

namespace ScrapEngine {
	namespace Render {
		static uint32_t findMemoryType(const uint32_t& typeFilter, vk::MemoryPropertyFlags properties) {
			vk::PhysicalDeviceMemoryProperties memProperties;
			VulkanDevice::StaticPhysicalDeviceRef->getMemoryProperties(&memProperties);

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
}