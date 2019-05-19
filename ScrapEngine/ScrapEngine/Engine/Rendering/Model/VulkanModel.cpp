#include "VulkanModel.h"
#include "../../Debug/DebugLog.h"
#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h>     // Post processing flags
#include <unordered_map>
#include <iostream>

ScrapEngine::Render::VulkanModel::VulkanModel(const std::string& input_model_path)
{
	Debug::DebugLog::print_to_console_log("Loading 3D model...");
	Debug::DebugLog::print_to_console_log("Loading assimp...");
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(input_model_path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene)
	{
		throw std::runtime_error(importer.GetErrorString());
	}

	const aiVector3D zero_3d(0.0f, 0.0f, 0.0f);
	Debug::DebugLog::print_to_console_log("Begin model loading...");
	Debug::DebugLog::print_to_console_log("Number of meshes to load:" + std::to_string(scene->mNumMeshes));
	for (unsigned int k = 0; k < scene->mNumMeshes; k++) {
		Debug::DebugLog::print_to_console_log("Mesh " + std::to_string(k) + " - Loading vertices...");
		for (unsigned int i = 0; i < scene->mMeshes[k]->mNumVertices; i++) {
			const aiVector3D* p_pos = &(scene->mMeshes[k]->mVertices[i]);
			const aiVector3D* p_normal = scene->mMeshes[k]->HasNormals() ? &(scene->mMeshes[k]->mNormals[i]) : &zero_3d;
			const aiVector3D* p_tex_coord = scene->mMeshes[k]->HasTextureCoords(0) ? &(scene->mMeshes[k]->mTextureCoords[0][i]) : &zero_3d;
			Vertex vertex = {};
			vertex.pos = { p_pos->x, p_pos->y, p_pos->z };
			vertex.texCoord = { p_tex_coord->x, 1 - p_tex_coord->y };
			vertex.color = { p_normal->x, p_normal->y, p_normal->z };
			vertices_.push_back(vertex);
		}
		Debug::DebugLog::print_to_console_log("Mesh " + std::to_string(k) + " - Loading indices...");
		for (unsigned int i = 0; i < scene->mMeshes[k]->mNumFaces; i++) {
			const aiFace& face = scene->mMeshes[k]->mFaces[i];
			assert(face.mNumIndices == 3);
			indices_.push_back(face.mIndices[0]);
			indices_.push_back(face.mIndices[1]);
			indices_.push_back(face.mIndices[2]);
		}
	}
	Debug::DebugLog::print_to_console_log("Vertex and Index model info loaded");
}

ScrapEngine::Render::VulkanModel::~VulkanModel()
{

}

const std::vector<ScrapEngine::Vertex>* ScrapEngine::Render::VulkanModel::get_vertices() const
{
	return &vertices_;
}

const std::vector<uint32_t>* ScrapEngine::Render::VulkanModel::get_indices() const
{
	return &indices_;
}
