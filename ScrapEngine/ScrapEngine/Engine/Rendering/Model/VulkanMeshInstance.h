#pragma once
#include <Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h>
#include <Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h>
#include <Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h>
#include <Engine/Rendering/Model/VulkanModel.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Utility/UsefulTypes.h>
#include <Engine/Rendering/Buffer/BufferContainer/VertexBufferContainer/VertexBufferContainer.h>
#include <Engine/Rendering/Buffer/BufferContainer/IndicesBufferContainer/IndicesBufferContainer.h>
#include <Engine/Rendering/Model/Material/BasicMaterial.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BasicMaterial;

		class VulkanMeshInstance
		{
		private:
			ScrapEngine::Render::VulkanModel* vulkan_render_model_ = nullptr;
			ScrapEngine::Render::UniformBuffer* vulkan_render_uniform_buffer_ = nullptr;
			std::vector<ScrapEngine::Render::BasicMaterial*> model_materials_;
			std::vector<VertexBuffer*> created_vertex_buffers_;
			std::vector<IndexBuffer*> created_index_buffers_;

			std::vector<std::pair<VertexBufferContainer*, IndicesBufferContainer*>> mesh_buffers_;

			ScrapEngine::Transform object_location_;
		public:
			VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                   const std::string& model_path, const std::vector<std::string>& textures_path,
			                   ScrapEngine::Render::VulkanDevice* render_device,
			                   ScrapEngine::Render::VulkanSwapChain* swap_chain);
			~VulkanMeshInstance();

			void set_mesh_location(const glm::vec3& location);
			void set_mesh_rotation(const glm::vec3& rotation);
			void set_mesh_scale(const glm::vec3& scale);

			glm::vec3 get_mesh_location() const;
			glm::vec3 get_mesh_rotation() const;
			glm::vec3 get_mesh_scale() const;

			void update_uniform_buffer(const uint32_t& current_image, ScrapEngine::Render::Camera* render_camera) const;

			ScrapEngine::Render::UniformBuffer* get_vulkan_render_uniform_buffer() const;
			const std::vector<ScrapEngine::Render::BasicMaterial*>* get_mesh_materials() const;
			const std::vector<std::pair<VertexBufferContainer*, IndicesBufferContainer*>>* get_mesh_buffers() const;
		};
	}
}
