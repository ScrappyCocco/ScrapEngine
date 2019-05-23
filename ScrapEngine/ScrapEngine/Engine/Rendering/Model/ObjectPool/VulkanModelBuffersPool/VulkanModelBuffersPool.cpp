#include <Engine/Rendering/Model/ObjectPool/VulkanModelBuffersPool/VulkanModelBuffersPool.h>
#include <memory>
#include <Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h>

//Init static instance reference

ScrapEngine::Render::VulkanModelBuffersPool* ScrapEngine::Render::VulkanModelBuffersPool::instance_ = nullptr;

ScrapEngine::Render::VulkanModelBuffersPool* ScrapEngine::Render::VulkanModelBuffersPool::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanModelBuffersPool();
	}
	return instance_;
}

std::shared_ptr<std::vector<
	std::pair<
		ScrapEngine::Render::VertexBufferContainer*,
		ScrapEngine::Render::IndicesBufferContainer*>
>> ScrapEngine::Render::VulkanModelBuffersPool::get_model_buffers(
	const std::string& model_path,
	const std::shared_ptr<VulkanModel>& model_ref
)
{
	if (model_buffers_pool_.find(model_path) == model_buffers_pool_.end())
	{
		// Model not found, create the shared vector
		std::shared_ptr<std::vector<
				std::pair<
					VertexBufferContainer*,
					IndicesBufferContainer*>
			>
		> mesh_buffers = std::make_shared<std::vector<
				std::pair<
					VertexBufferContainer*,
					IndicesBufferContainer*>
			>
		>();

		std::vector<std::pair<VertexBuffer*, IndexBuffer*>> concrete_mesh_buffers;
		//LOADING MODEL BUFFERS
		for (auto mesh : (*model_ref->get_meshes()))
		{
			//LOADING MODEL BUFFERS
			std::pair<VertexBuffer*, IndexBuffer*> concrete_buffer_pair;
			std::pair<VertexBufferContainer*, IndicesBufferContainer*> buffer_pair;
			concrete_buffer_pair.first = new VertexBuffer(mesh->get_vertices());
			buffer_pair.first = new VertexBufferContainer(
				concrete_buffer_pair.first->get_vertex_buffer(),
				mesh->get_vertices());
			Debug::DebugLog::print_to_console_log("[VulkanModelBuffersPool] VertexBuffer created");

			concrete_buffer_pair.second = new IndexBuffer(mesh->get_indices());
			buffer_pair.second = new IndicesBufferContainer(
				concrete_buffer_pair.second->get_index_buffer(),
				mesh->get_indices());
			Debug::DebugLog::print_to_console_log("[VulkanModelBuffersPool] IndexBuffer created");

			concrete_mesh_buffers.push_back(concrete_buffer_pair);
			mesh_buffers->push_back(buffer_pair);
		}
		concrete_buffers_[model_path] = concrete_mesh_buffers;
		model_buffers_pool_[model_path] = mesh_buffers;
	}
	return model_buffers_pool_[model_path];
}

ScrapEngine::Render::VulkanModelBuffersPool::~VulkanModelBuffersPool()
{
	clear_memory();
}

void ScrapEngine::Render::VulkanModelBuffersPool::clear_memory()
{
	std::vector<std::string> model_to_erase;
	for (const auto& model : model_buffers_pool_)
	{
		if (model.second.use_count() == 1)
		{
			model_to_erase.push_back(model.first);
		}
	}
	for (const auto& model_key : model_to_erase)
	{
		Debug::DebugLog::print_to_console_log("[VulkanModelBuffersPool] Removing " 
			+ model_key + " buffers from pool memory");
		for(const auto& model_pair : concrete_buffers_[model_key])
		{
			delete model_pair.first;
			delete model_pair.second;
		}
		model_buffers_pool_[model_key]->clear();
		model_buffers_pool_[model_key] = nullptr;
		model_buffers_pool_.erase(model_key);
	}
}
