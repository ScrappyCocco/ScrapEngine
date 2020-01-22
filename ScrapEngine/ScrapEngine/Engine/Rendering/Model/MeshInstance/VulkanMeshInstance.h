#pragma once

#include <Engine/Rendering/Buffer/UniformBuffer/StandardUniformBuffer/StandardUniformBuffer.h>
#include <Engine/Rendering/Model/Model/VulkanModel.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Buffer/BufferContainer/VertexBufferContainer/VertexBufferContainer.h>
#include <Engine/Rendering/Buffer/BufferContainer/IndicesBufferContainer/IndicesBufferContainer.h>
#include <Engine/Rendering/Model/Material/SimpleMaterial/SimpleMaterial.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>
#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardShadowmapping;

		class VulkanMeshInstance
		{
		private:
			std::shared_ptr<VulkanModel> vulkan_render_model_ = nullptr;
			StandardUniformBuffer* vulkan_render_uniform_buffer_ = nullptr;
			std::vector<BasicMaterial*> model_materials_;

			std::shared_ptr<std::vector<
				std::pair<
					VertexBufferContainer*,
					IndicesBufferContainer*>
			>> mesh_buffers_;

			Core::STransform object_location_;
			bool is_visible_ = true;

			//If this is true, the transform matrices not will be updated
			//The other flag says if i already updated the uniform buffer once
			bool is_static_ = false;
			bool transform_dirty_ = true;

			//Set that the mesh will be deleted as soon as possible
			//During command buffer re-creation
			//This is necessary because the mesh can't be deleted during command buffer creation
			bool pending_deletion_ = false;

			//I also need a deletion counter, to know how many command buffers read this mesh
			//When i'm sure no command buffer contain it this mesh can be deleted
			uint16_t deletion_counter_ = 0;

			//Shadowmapping stuff to draw mesh shadows
			ShadowmappingUniformBuffer* shadowmapping_uniform_buffer_ = nullptr;
			ShadowmappingDescriptorSet* shadowmapping_descriptor_set_ = nullptr;
			StandardDescriptorPool* shadowmapping_descriptor_pool_ = nullptr;
			void write_depth_descriptor(StandardShadowmapping* shadowmapping);
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

			bool get_is_static() const;
			void set_is_static(bool is_static);

			bool get_is_visible() const;
			void set_is_visible(bool visible);

			void set_for_deletion();
			bool get_pending_deletion() const;
			void increase_deletion_counter();
			uint16_t get_deletion_counter() const;

			void init_shadowmapping_resources(StandardShadowmapping* shadowmapping);

			void update_uniform_buffer(const uint32_t& current_image, Camera* render_camera,
			                           const glm::vec3& light_pos);
			void update_shadowmap_uniform_buffer(const uint32_t& current_image, StandardShadowmapping* shadowmap_info) const;

			StandardUniformBuffer* get_vulkan_render_uniform_buffer() const;
			const std::vector<BasicMaterial*>* get_mesh_materials() const;
			ShadowmappingUniformBuffer* get_shadowmapping_uniform_buffer() const;
			ShadowmappingDescriptorSet* get_shadowmapping_descriptor_set() const;

			std::shared_ptr<std::vector<
				std::pair<
					VertexBufferContainer*,
					IndicesBufferContainer*>
			>> get_mesh_buffers() const;
		};
	}
}
