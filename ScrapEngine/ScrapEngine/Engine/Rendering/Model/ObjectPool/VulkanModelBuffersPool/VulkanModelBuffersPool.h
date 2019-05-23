#pragma once
#include <unordered_map>
#include <Engine/Rendering/Buffer/BufferContainer/VertexBufferContainer/VertexBufferContainer.h>
#include <Engine/Rendering/Buffer/BufferContainer/IndicesBufferContainer/IndicesBufferContainer.h>
#include <Engine/Rendering/Model/Model/VulkanModel.h>
#include <Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h>
#include <Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanModelBuffersPool
		{
		private:
			//Singleton static instance
			static VulkanModelBuffersPool* instance_;

			//The constructor is private because this class is a Singleton
			VulkanModelBuffersPool() = default;

			std::unordered_map<std::string,
			                   std::shared_ptr<std::vector<
					                   std::pair<
						                   VertexBufferContainer*,
						                   IndicesBufferContainer*>
				                   >
			                   >
			> model_buffers_pool_;

			std::unordered_map<std::string, std::vector<std::pair<VertexBuffer*, IndexBuffer*>>> concrete_buffers_;
		public:
			//Singleton static function to get or create a class instance
			static VulkanModelBuffersPool* get_instance();

			std::shared_ptr<std::vector<
					std::pair<
						VertexBufferContainer*,
						IndicesBufferContainer*>
				>
			> get_model_buffers(const std::string& model_path, const std::shared_ptr<VulkanModel>& model_ref);

			~VulkanModelBuffersPool();

			void clear_memory();
		};
	}
}
