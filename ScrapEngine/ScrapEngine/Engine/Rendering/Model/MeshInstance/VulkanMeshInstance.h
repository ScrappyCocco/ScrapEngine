#pragma once

#include <Engine/Rendering/Model/Model/VulkanModel.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

namespace ScrapEngine
{
	namespace Render
	{
		class Camera;
		class VulkanSwapChain;
		class StandardDescriptorPool;
		class ShadowmappingDescriptorSet;
		class ShadowmappingUniformBuffer;
		class StandardUniformBuffer;
		class IndicesBufferContainer;
		class VertexBufferContainer;
		class BasicMaterial;
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

			//Value that set if the mesh is currently visible
			bool is_visible_ = true;

			//Value that set if the mesh should be considered for shadow rendering
			bool cast_shadows_ = true;

			//If this is true, the transform matrices not will be updated
			//The other flag says if i already updated the uniform buffer once
			bool is_static_ = false;
			bool transform_dirty_ = true;

			//Value to set if the mesh should be hidden when out of view or not
			//Remember that a mesh with this value set to false will be always drawn
			bool frustum_check_ = true;
			//Value to know if the mesh is in the current view-frustum
			bool is_in_current_frustum_ = true;
			bool sun_shadow_is_in_current_frustum_ = true;
			//This is the sphere radius multiplier that will be used to check if a mesh is in the camera frustum
			//Shadow frustum check double this value to avoid (possibly) to remove objects that still have the shadow visible
			//There are better ways to check this, this is a way to keep it simple & basic
			//If necessary increase this value using the set() method
			float frustum_sphere_radius_multiplier_ = 20.f;

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
			void directional_light_frustum_check(Camera* render_camera);
		public:
			VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                   const std::string& model_path, const std::vector<std::string>& textures_path,
			                   VulkanSwapChain* swap_chain);
			~VulkanMeshInstance();

			//-------------------------------------
			//USER FEATURES
			//-------------------------------------
			
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

			bool get_cast_shadows() const;
			void set_cast_shadows(bool cast);

			bool get_frustum_check() const;
			void set_frustum_check(bool should_check);

			float get_frustum_check_radius() const;
			void set_frustum_check_radius(float radius);

			//-------------------------------------
			//ENGINE UTILS
			//-------------------------------------
			
			void set_for_deletion();
			bool get_pending_deletion() const;
			void increase_deletion_counter();
			uint16_t get_deletion_counter() const;

			void view_frustum_check(Camera* render_camera);
			bool get_is_in_current_frustum() const;
			bool get_sun_shadow_is_in_current_frustum() const;

			void init_shadowmapping_resources(StandardShadowmapping* shadowmapping);

			void update_uniform_buffer(uint32_t current_image, Camera* render_camera,
			                           const glm::vec3& light_pos);
			void update_shadowmap_uniform_buffer(uint32_t current_image, StandardShadowmapping* shadowmap_info) const;

			const std::vector<BasicMaterial*>* get_mesh_materials() const;
			ShadowmappingDescriptorSet* get_shadowmapping_descriptor_set() const;

			std::shared_ptr<std::vector<
				std::pair<
					VertexBufferContainer*,
					IndicesBufferContainer*>
			>> get_mesh_buffers() const;
		};
	}
}
