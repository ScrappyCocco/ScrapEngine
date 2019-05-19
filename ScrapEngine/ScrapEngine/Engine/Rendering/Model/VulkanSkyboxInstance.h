#pragma once
#include <Engine/Rendering/Texture/SkyboxTexture.h>
#include <Engine/Rendering/Texture/TextureImageView.h>
#include <Engine/Rendering/Texture/TextureSampler.h>
#include <Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h>
#include <Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h>
#include <Engine/Rendering/Model/VulkanModel.h>
#include <Engine/Rendering/Descriptor/VulkanDescriptorPool.h>
#include <Engine/Rendering/Descriptor/VulkanDescriptorSet.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Utility/UsefulTypes.h>

namespace ScrapEngine
{
	namespace Render
	{
		class SkyboxTexture;

		class VulkanSkyboxInstance
		{
		private:
			ScrapEngine::Render::VulkanGraphicsPipeline* vulkan_render_graphics_pipeline_ = nullptr;
			ScrapEngine::Render::SkyboxTexture* skybox_texture_ = nullptr;
			ScrapEngine::Render::TextureImageView* vulkan_texture_image_view_ = nullptr;
			ScrapEngine::Render::TextureSampler* vulkan_texture_sampler_ = nullptr;
			ScrapEngine::Render::VulkanModel* vulkan_render_model_ = nullptr;
			ScrapEngine::Render::VertexBuffer* vulkan_render_vertex_buffer_ = nullptr;
			ScrapEngine::Render::IndexBuffer* vulkan_render_index_buffer_ = nullptr;
			ScrapEngine::Render::UniformBuffer* vulkan_render_uniform_buffer_ = nullptr;
			ScrapEngine::Render::VulkanDescriptorPool* vulkan_render_descriptor_pool_ = nullptr;
			ScrapEngine::Render::VulkanDescriptorSet* vulkan_render_descriptor_set_ = nullptr;

			simple_buffer<Vertex>* vertexbuffer_ = nullptr;
			simple_buffer<uint32_t>* indexbuffer_ = nullptr;
			ScrapEngine::Transform skybox_transform_;
		public:
			VulkanSkyboxInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     const std::string& model_path, const std::array<std::string, 6>& texture_path,
			                     ScrapEngine::Render::VulkanDevice* render_device,
			                     ScrapEngine::Render::VulkanSwapChain* swap_chain);
			~VulkanSkyboxInstance();

			void update_uniform_buffer(const uint32_t& current_image, ScrapEngine::Render::Camera* render_camera) const;
			void delete_graphics_pipeline() const;

			int get_cubemap_size() const;
			void set_cubemap_size(unsigned int new_size);

			ScrapEngine::Render::UniformBuffer* get_vulkan_render_uniform_buffer() const;
			ScrapEngine::Render::VulkanGraphicsPipeline* get_vulkan_render_graphics_pipeline() const;
			ScrapEngine::Render::VulkanDescriptorSet* get_vulkan_render_descriptor_set() const;
			ScrapEngine::simple_buffer<ScrapEngine::Vertex>* get_vertex_buffer() const;
			ScrapEngine::simple_buffer<uint32_t>* get_index_buffer() const;
		};
	}
}
