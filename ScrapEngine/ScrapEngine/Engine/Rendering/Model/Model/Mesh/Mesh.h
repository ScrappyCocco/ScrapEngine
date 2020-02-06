#pragma once

#include <Engine/Rendering/Base/Vertex.h>

namespace ScrapEngine
{
	namespace Render
	{
		class Mesh
		{
		private:
			std::vector<Vertex> vertices_;
			std::vector<uint32_t> indices_;
		public:
			Mesh(const std::vector<Vertex>& input_mesh_vertices,
			     const std::vector<uint32_t>& input_mesh_indices);
			~Mesh() = default;

			const std::vector<Vertex>* get_vertices() const;
			const std::vector<uint32_t>* get_indices() const;
		};
	}
}
