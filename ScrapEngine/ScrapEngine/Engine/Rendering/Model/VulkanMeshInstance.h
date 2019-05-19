#pragma once
#include "../Texture/TextureImage.h"
#include "../Texture/TextureImageView.h"
#include "../Texture/TextureSampler.h"
#include "Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h"
#include "Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h"
#include "Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h"
#include "../Model/VulkanModel.h"
#include "Engine/Rendering/Buffer/CommandBuffer/VulkanCommandBuffer.h"
#include "../Descriptor/VulkanDescriptorPool.h"
#include "../Descriptor/VulkanDescriptorSet.h"
#include "../Device/VulkanDevice.h"
#include "../SwapChain/VulkanSwapChain.h"
#include "../../Utility/UsefulTypes.h"

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanMeshInstance
		{
		private:
			ScrapEngine::Render::VulkanGraphicsPipeline* vulkan_render_graphics_pipeline_ = nullptr;
			ScrapEngine::Render::TextureImage* vulkan_texture_image_ = nullptr;
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

			ScrapEngine::Transform object_location_;
		public:
			VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                   const std::string& model_path, const std::string& texture_path,
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
			void delete_graphics_pipeline();

			ScrapEngine::Render::UniformBuffer* get_vulkan_render_uniform_buffer() const;
			ScrapEngine::Render::VulkanGraphicsPipeline* get_vulkan_render_graphics_pipeline() const;
			ScrapEngine::Render::VulkanDescriptorSet* get_vulkan_render_descriptor_set() const;
			ScrapEngine::simple_buffer<ScrapEngine::Vertex>* get_vertex_buffer() const;
			ScrapEngine::simple_buffer<uint32_t>* get_index_buffer() const;
		};
	}
}
