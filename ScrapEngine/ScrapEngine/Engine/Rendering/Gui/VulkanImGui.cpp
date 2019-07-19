#include <imgui.h>
#include <Engine/Rendering/Gui/VulkanImGui.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>


ScrapEngine::Render::VulkanImGui::VulkanImGui()
{
	ImGui::CreateContext();
}

void ScrapEngine::Render::VulkanImGui::init(const float width, const float height)
{
	// Color scheme
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.6f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
	style.Colors[ImGuiCol_Header] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	// Dimensions
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(width, height);
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
}

void ScrapEngine::Render::VulkanImGui::init_resources(VulkanRenderPass* render_pass, VkQueue copy_queue,
                                                      VulkanSwapChain* swap_chain)
{
	ImGuiIO& io = ImGui::GetIO();

	// Create font texture
	unsigned char* font_data;
	int tex_width, tex_height;
	io.Fonts->GetTexDataAsRGBA32(&font_data, &tex_width, &tex_height);
	vk::DeviceSize upload_size = tex_width * tex_height * 4 * sizeof(char);

	// Create target image for copy
	BaseTexture::create_image(tex_width, tex_height, vk::Format::eR8G8B8A8Unorm, vk::ImageTiling::eOptimal,
	                          vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferDst,
	                          vk::MemoryPropertyFlagBits::eDeviceLocal,
	                          front_image_, font_memory_, 1, vk::SampleCountFlagBits::e1);

	// Image view
	front_view_ = new TextureImageView(&front_image_, 1);

	// Prepare for transfer
	BaseTexture::transition_image_layout(&front_image_, vk::Format::eR8G8B8A8Unorm, vk::ImageLayout::eUndefined,
	                                     vk::ImageLayout::eTransferDstOptimal, 1);
	//Prepare buffer
	ImageStagingBuffer* staginf_buffer_ref = new ImageStagingBuffer(upload_size, font_data);
	//Set copy region data
	vk::BufferImageCopy buffer_copy_region;
	buffer_copy_region.setImageSubresource(vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 1, 1, 1));
	buffer_copy_region.setImageExtent(vk::Extent3D(tex_width, tex_height, 1));
	//Copy
	ImageStagingBuffer::copy_buffer_to_image(staginf_buffer_ref->get_staging_buffer(), &front_image_, tex_width,
	                                         tex_height, &buffer_copy_region, 1,
	                                         vk::ImageLayout::eTransferDstOptimal);
	delete staginf_buffer_ref;
	staginf_buffer_ref = nullptr;
	// Prepare for shader read
	BaseTexture::transition_image_layout(&front_image_, vk::Format::eR8G8B8A8Unorm,
	                                     vk::ImageLayout::eTransferDstOptimal,
	                                     vk::ImageLayout::eShaderReadOnlyOptimal, 1);
	// Font texture Sampler
	sampler_ = new TextureSampler(1, vk::Filter::eLinear, vk::Filter::eLinear, vk::SamplerMipmapMode::eLinear,
	                              vk::SamplerAddressMode::eClampToEdge, vk::SamplerAddressMode::eClampToEdge,
	                              vk::SamplerAddressMode::eClampToEdge, false, vk::CompareOp::eNever, false, 16,
	                              vk::BorderColor::eFloatOpaqueWhite);

	// Descriptor pool
	descriptor_pool_ = new VulkanDescriptorPool(swap_chain->get_swap_chain_images_vector());
	// Descriptor set
	descriptor_set_ = new GuiDescriptorSet();
	descriptor_set_->create_descriptor_sets(descriptor_pool_->get_descriptor_pool(),
	                                        swap_chain->get_swap_chain_images_vector(),
	                                        sampler_->get_texture_sampler(), front_view_->get_texture_image_view());


}
