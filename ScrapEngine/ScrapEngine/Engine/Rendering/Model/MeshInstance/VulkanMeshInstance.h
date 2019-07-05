#pragma once

#include <Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h>
#include <Engine/Rendering/Model/Model/VulkanModel.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Buffer/BufferContainer/VertexBufferContainer/VertexBufferContainer.h>
#include <Engine/Rendering/Buffer/BufferContainer/IndicesBufferContainer/IndicesBufferContainer.h>
#include <Engine/Rendering/Model/Material/SimpleMaterial/SimpleMaterial.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanMeshInstance
		{
		private:
			std::shared_ptr<VulkanModel> vulkan_render_model_ = nullptr;
			UniformBuffer* vulkan_render_uniform_buffer_ = nullptr;
			std::vector<BasicMaterial*> model_materials_;

			std::shared_ptr<std::vector<
				std::pair<
					VertexBufferContainer*,
					IndicesBufferContainer*>
			>> mesh_buffers_;

			Core::STransform object_location_;
			bool is_visible_ = true;
		public:
			VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                   const std::string& model_path, const std::vector<std::string>& textures_path,
			                   VulkanSwapChain* swap_chain);
			~VulkanMeshInstance();

			void set_mesh_location(const Core::SVector3& location);
			void set_mesh_rotation(const Core::SVector3& rotation);
			void set_mesh_scale(const Core::SVector3& scale);

			Core::SVector3 get_mesh_location() const;
			Core::SVector3 get_mesh_rotation() const;
			Core::SVector3 get_mesh_scale() const;

			bool get_is_visible() const;
			void set_is_visible(bool visible);

			void update_uniform_buffer(const uint32_t& current_image, Camera* render_camera) const;

			UniformBuffer* get_vulkan_render_uniform_buffer() const;
			const std::vector<BasicMaterial*>* get_mesh_materials() const;

			std::shared_ptr<std::vector<
				std::pair<
					VertexBufferContainer*,
					IndicesBufferContainer*>
			>> get_mesh_buffers() const;
		};
	}
}
