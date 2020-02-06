#pragma once

#include <unordered_map>
#include <memory>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanModel;
		class IndexBuffer;
		class VertexBuffer;
		class IndicesBufferContainer;
		class VertexBufferContainer;

		class VulkanModelBuffersPool
		{
		private:
			//Singleton static instance
			static VulkanModelBuffersPool* instance_;

			//The constructor is private because this class is a Singleton
			VulkanModelBuffersPool() = default;

			//The pool associate the model path with a shared_ptr vector of VertexBufferContainer* & IndicesBufferContainer*
			//This because for every model i can have N mesh, every mesh has a VertexBufferContainer and a IndicesBufferContainer
			std::unordered_map<std::string,
			                   std::shared_ptr<std::vector<
					                   std::pair<
						                   VertexBufferContainer*,
						                   IndicesBufferContainer*>
				                   >
			                   >
			> model_buffers_pool_;

			//It's necessary to keep also a vector of VertexBuffer* and IndexBuffer*
			//This because these are the concrete buffers i must clean when possible
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
