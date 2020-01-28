#include <Engine/Utility/UsefulMethods.h>
#include <stb_image.h>
#include <Engine/Debug/DebugLog.h>

GLFWimage ScrapEngine::Utility::UsefulMethods::load_icon(const std::string& path_to_file)
{
	GLFWimage icon;
	icon.pixels = stbi_load(path_to_file.c_str(), &icon.width, &icon.height, nullptr, 4);

	if (!icon.pixels)
	{
		Debug::DebugLog::fatal_error(vk::Result(-13), "TextureImage: Failed to load texture image! (pixels not valid) - " + path_to_file);
	}

	return icon;
}
