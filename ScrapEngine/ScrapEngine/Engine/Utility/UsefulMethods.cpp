#include "UsefulMethods.h"

#include <stb_image.h>

GLFWimage ScrapEngine::UsefulMethods::loadIcon(const std::string & path_to_file)
{
	GLFWimage icon;
	icon.pixels = stbi_load(path_to_file.c_str(), &icon.width, &icon.height, 0, 4);

	if (!icon.pixels) {
		throw std::runtime_error("TextureImage: Failed to load texture image! (pixels not valid)");
	}

	return icon;
}