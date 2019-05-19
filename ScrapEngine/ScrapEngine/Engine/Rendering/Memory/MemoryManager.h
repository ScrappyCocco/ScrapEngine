#pragma once

#include <vulkan/vulkan.hpp>
#include <stdexcept>
#include <Engine/Rendering/Base/StaticTypes.h>

namespace ScrapEngine
{
	namespace Render
	{
		static uint32_t find_memory_type(const uint32_t& type_filter, const vk::MemoryPropertyFlags& properties)
		{
			vk::PhysicalDeviceMemoryProperties mem_properties;
			VulkanDevice::static_physical_device_ref->getMemoryProperties(&mem_properties);

			for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
			{
				if ((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties
				)
				{
					return i;
				}
			}
			//Try a simpler way
			for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
			{
				if (mem_properties.memoryTypes[i].propertyFlags == properties)
				{
					return i;
				}
			}

			throw std::runtime_error("Memory Manager: Failed to find suitable memory type!");
		}
	}
}
