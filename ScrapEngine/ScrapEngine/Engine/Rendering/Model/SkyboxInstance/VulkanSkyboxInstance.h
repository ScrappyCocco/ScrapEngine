#pragma once

#include <Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h>
#include <Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h>
#include <Engine/Rendering/Model/Model/VulkanModel.h>
#include <Engine/Rendering/Descriptor/VulkanDescriptorSet.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Utility/UsefulTypes.h>
#include <Engine/Rendering/Buffer/BufferContainer/VertexBufferContainer/VertexBufferContainer.h>
#include <Engine/Rendering/Buffer/BufferContainer/IndicesBufferContainer/IndicesBufferContainer.h>
#include <Engine/Rendering/Model/Material/SkyboxMaterial/SkyboxMaterial.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanSkyboxInstance
		{
		private:
			ScrapEngine::Render::VulkanModel* vulkan_render_model_ = nullptr;
			ScrapEngine::Render::UniformBuffer* vulkan_render_uniform_buffer_ = nullptr;
			ScrapEngine::Render::SkyboxMaterial* skybox_material_ = nullptr;

			VertexBuffer* created_vertex_buffer_;
			IndexBuffer* created_index_buffer_;

			std::pair<VertexBufferContainer*, IndicesBufferContainer*> mesh_buffers_;
			ScrapEngine::Transform skybox_transform_;
		public:
			VulkanSkyboxInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     const std::string& model_path, const std::array<std::string, 6>& texture_path,
			                     ScrapEngine::Render::VulkanDevice* render_device,
			                     ScrapEngine::Render::VulkanSwapChain* swap_chain);
			~VulkanSkyboxInstance();

			void update_uniform_buffer(const uint32_t& current_image, ScrapEngine::Render::Camera* render_camera) const;

			int get_cubemap_size() const;
			void set_cubemap_size(unsigned int new_size);

			ScrapEngine::Render::UniformBuffer* get_vulkan_render_uniform_buffer() const;
			ScrapEngine::Render::BasicMaterial* get_skybox_material() const;
			const std::pair<VertexBufferContainer*, IndicesBufferContainer*>* get_mesh_buffers() const;
		};
	}
}
