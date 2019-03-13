#include "VulkanModel.h"
#include "../../Debug/DebugLog.h"
#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h>     // Post processing flags
#include <unordered_map>
#include <iostream>

ScrapEngine::VulkanModel::VulkanModel(const std::string& input_MODEL_PATH)
{
	Debug::DebugLog::print_to_console_log("Loading 3D model...");
	Debug::DebugLog::print_to_console_log("Loading assimp...");
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(input_MODEL_PATH,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene)
	{
		throw std::runtime_error(importer.GetErrorString());
	}

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	Debug::DebugLog::print_to_console_log("Begin model loading...");
	Debug::DebugLog::print_to_console_log("Number of meshes to load:" + std::to_string(scene->mNumMeshes));
	for (unsigned int k = 0; k < scene->mNumMeshes; k++) {
		Debug::DebugLog::print_to_console_log("Mesh " + std::to_string(k) + " - Loading vertices...");
		for (unsigned int i = 0; i < scene->mMeshes[k]->mNumVertices; i++) {
			const aiVector3D* pPos = &(scene->mMeshes[k]->mVertices[i]);
			const aiVector3D* pNormal = scene->mMeshes[k]->HasNormals() ? &(scene->mMeshes[k]->mNormals[i]) : &Zero3D;
			const aiVector3D* pTexCoord = scene->mMeshes[k]->HasTextureCoords(0) ? &(scene->mMeshes[k]->mTextureCoords[0][i]) : &Zero3D;
			Vertex vertex = {};
			vertex.pos = { pPos->x, pPos->y, pPos->z };
			vertex.texCoord = { pTexCoord->x, 1 - pTexCoord->y };
			vertex.color = { pNormal->x, pNormal->y, pNormal->z };
			vertices.push_back(vertex);
		}
		Debug::DebugLog::print_to_console_log("Mesh " + std::to_string(k) + " - Loading indices...");
		for (unsigned int i = 0; i < scene->mMeshes[k]->mNumFaces; i++) {
			const aiFace& Face = scene->mMeshes[k]->mFaces[i];
			assert(Face.mNumIndices == 3);
			indices.push_back(Face.mIndices[0]);
			indices.push_back(Face.mIndices[1]);
			indices.push_back(Face.mIndices[2]);
		}
	}
	Debug::DebugLog::print_to_console_log("Vertex and Index model info loaded");
}

ScrapEngine::VulkanModel::~VulkanModel()
{

}

const std::vector<ScrapEngine::Vertex>* ScrapEngine::VulkanModel::getVertices()
{
	return &vertices;
}

const std::vector<uint32_t>* ScrapEngine::VulkanModel::getIndices()
{
	return &indices;
}
