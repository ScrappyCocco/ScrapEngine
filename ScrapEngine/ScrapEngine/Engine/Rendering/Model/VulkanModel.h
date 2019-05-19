#pragma once

#include <vulkan/vulkan.hpp>
#include <string>
#include <vector>
#include <Engine/Rendering/Base/Vertex.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanModel
		{
		private:
			std::vector<ScrapEngine::Vertex> vertices_;
			std::vector<uint32_t> indices_;
		public:
			VulkanModel(const std::string& input_model_path);
			~VulkanModel() = default;

			const std::vector<ScrapEngine::Vertex>* get_vertices() const;
			const std::vector<uint32_t>* get_indices() const;
		};
	}
}
