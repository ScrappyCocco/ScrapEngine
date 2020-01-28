#include <Engine/Rendering/Model/Model/Mesh/Mesh.h>


ScrapEngine::Render::Mesh::Mesh(const std::vector<Vertex>& input_mesh_vertices,
                                const std::vector<uint32_t>& input_mesh_indices)
	: vertices_(input_mesh_vertices), indices_(input_mesh_indices)
{
}

const std::vector<ScrapEngine::Render::Vertex>* ScrapEngine::Render::Mesh::get_vertices() const
{
	return &vertices_;
}

const std::vector<uint32_t>* ScrapEngine::Render::Mesh::get_indices() const
{
	return &indices_;
}
