#include <imgui.h>
#include <Engine/Rendering/Gui/VulkanImGui.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <Engine/Rendering/Buffer/StagingBuffer/ImageStagingBuffer/ImageStagingBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/GuiDescriptorPool/GuiDescriptorPool.h>

ScrapEngine::Render::VulkanImGui::VulkanImGui()
{
	ImGui::CreateContext();

	vertex_buffer_ = new GenericBuffer();
	index_buffer_ = new GenericBuffer();
}

ScrapEngine::Render::VulkanImGui::~VulkanImGui()
{
	ImGui::DestroyContext();
	// Release all Vulkan resources required for rendering imGui
	vk::Device* device = VulkanDevice::get_instance()->get_logical_device();

	//Clear buffers
	delete vertex_buffer_;
	delete index_buffer_;
	//Clear other resources
	device->destroyImage(front_image_);
	delete front_view_;
	device->freeMemory(font_memory_);
	delete sampler_;
	delete pipeline_;
	delete descriptor_pool_;
	delete descriptor_set_;
}

void ScrapEngine::Render::VulkanImGui::init(const float width, const float height)
{
	// Dimensions
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(width, height);
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
}

void ScrapEngine::Render::VulkanImGui::init_resources(VulkanSwapChain* swap_chain, BaseRenderPass* render_pass)
{
	ImGuiIO& io = ImGui::GetIO();

	// Create font texture
	unsigned char* font_data;
	int tex_width, tex_height;
	io.Fonts->GetTexDataAsRGBA32(&font_data, &tex_width, &tex_height);
	const vk::DeviceSize upload_size = tex_width * tex_height * 4 * sizeof(char);

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
	vk::ImageSubresourceLayers image_subresource_layer;
	image_subresource_layer.setAspectMask(vk::ImageAspectFlagBits::eColor);
	image_subresource_layer.setLayerCount(1);
	buffer_copy_region.setImageSubresource(image_subresource_layer);
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
	descriptor_pool_ = new GuiDescriptorPool(swap_chain->get_swap_chain_images_vector());
	// Descriptor set
	descriptor_set_ = new GuiDescriptorSet();
	descriptor_set_->create_descriptor_sets(descriptor_pool_->get_descriptor_pool(),
	                                        swap_chain->get_swap_chain_images_vector(),
	                                        sampler_->get_texture_sampler(), front_view_->get_texture_image_view());

	//Create pipeline
	pipeline_ = new GuiVulkanGraphicsPipeline("../assets/shader/compiled_shaders/ui.vert.spv",
	                                          "../assets/shader/compiled_shaders/ui.frag.spv",
	                                          &swap_chain->get_swap_chain_extent(),
	                                          descriptor_set_->get_descriptor_set_layout(), sizeof(PushConstBlock),
	                                          render_pass);

	//Empty frame initialization
	generate_empty_gui_frame();
}

void ScrapEngine::Render::VulkanImGui::update_buffers()
{
	ImDrawData* im_draw_data = ImGui::GetDrawData();

	const vk::DeviceSize vertex_buffer_size = im_draw_data->TotalVtxCount * sizeof(ImDrawVert);
	const vk::DeviceSize index_buffer_size = im_draw_data->TotalIdxCount * sizeof(ImDrawIdx);

	if (vertex_buffer_size == 0 || index_buffer_size == 0)
	{
		return;
	}

	// Vertex buffer
	if ((vertex_buffer_->get_buffer() == nullptr) || (vertex_count_ != im_draw_data->TotalVtxCount))
	{
		vertex_buffer_->unmap();
		vertex_buffer_->destroy();
		//Create it
		vk::BufferCreateInfo vertex_buffer_info;
		vertex_buffer_info.setUsage(vk::BufferUsageFlagBits::eVertexBuffer);
		vertex_buffer_info.setSize(vertex_buffer_size);
		vertex_buffer_->create_buffer(vertex_buffer_info);
		//Update data
		vertex_count_ = im_draw_data->TotalVtxCount;
		vertex_buffer_->map();
	}

	// Index buffer
	if ((index_buffer_->get_buffer() == nullptr) || (index_count_ < im_draw_data->TotalIdxCount))
	{
		index_buffer_->unmap();
		index_buffer_->destroy();
		vk::BufferCreateInfo index_buffer_info;
		index_buffer_info.setUsage(vk::BufferUsageFlagBits::eIndexBuffer);
		index_buffer_info.setSize(index_buffer_size);
		index_buffer_->create_buffer(index_buffer_info);
		index_count_ = im_draw_data->TotalIdxCount;
		index_buffer_->map();
	}

	// Upload data
	ImDrawVert* vtx_dst = reinterpret_cast<ImDrawVert*>(vertex_buffer_->get_mapped_memory());
	ImDrawIdx* idx_dst = reinterpret_cast<ImDrawIdx*>(index_buffer_->get_mapped_memory());

	for (int n = 0; n < im_draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = im_draw_data->CmdLists[n];
		memcpy(vtx_dst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
		memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
		vtx_dst += cmd_list->VtxBuffer.Size;
		idx_dst += cmd_list->IdxBuffer.Size;
	}

	// Flush to make writes visible to GPU
	vertex_buffer_->flush();
	index_buffer_->flush();
}

void ScrapEngine::Render::VulkanImGui::generate_empty_gui_frame() const
{
	pre_gui_frame();
	post_gui_frame();
}

void ScrapEngine::Render::VulkanImGui::generate_loading_gui_frame() const
{
	pre_gui_frame();
	loading_ui();
	post_gui_frame();
}

void ScrapEngine::Render::VulkanImGui::pre_gui_frame() const
{
	//prepare the ongui() event generating a new gui event
	ImGui::NewFrame();
}

void ScrapEngine::Render::VulkanImGui::post_gui_frame() const
{
	//Render to generate draw buffers
	ImGui::Render();
}

void ScrapEngine::Render::VulkanImGui::loading_ui() const
{
	ImGui::SetNextWindowPosCenter(ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

	if (ImGui::Begin("Loading UI Overlay", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::Text("ScrapEngine - Loading...");

		ImGui::End();
	}
}

ScrapEngine::Render::GuiDescriptorSet* ScrapEngine::Render::VulkanImGui::get_descriptor_set() const
{
	return descriptor_set_;
}

ScrapEngine::Render::GuiVulkanGraphicsPipeline* ScrapEngine::Render::VulkanImGui::get_pipeline() const
{
	return pipeline_;
}

ScrapEngine::Render::GenericBuffer* ScrapEngine::Render::VulkanImGui::get_vertex_buffer() const
{
	return vertex_buffer_;
}

ScrapEngine::Render::GenericBuffer* ScrapEngine::Render::VulkanImGui::get_index_buffer() const
{
	return index_buffer_;
}

ScrapEngine::Render::VulkanImGui::PushConstBlock* ScrapEngine::Render::VulkanImGui::get_push_const_block()
{
	return &push_const_block_;
}
