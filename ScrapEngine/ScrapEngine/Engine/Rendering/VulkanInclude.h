#pragma once

#ifndef SCRAPENGINE_INCLUDE_VULKAN
#define SCRAPENGINE_INCLUDE_VULKAN

//---------------------------
// VULKAN HPP
// 
// TO KNOW MORE SEE:
// https://github.com/KhronosGroup/Vulkan-Headers
//---------------------------

//<Windows.h> header file includes macro definitions named max and min
//We don't want that
#define NOMINMAX

//Define the Vulkan platform
#if defined(_WIN64) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

//If you're porting the engine consider adding another define for the destination platform, it could be necessary

#include <vulkan/vulkan.hpp>

//---------------------------
// MEMORY ALLOCATOR (From GPUOpen)
// 
// TO EDIT THIS FILE SEE:
// https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/quick_start.html
//---------------------------

#include <vk_mem_alloc.h>

#endif
