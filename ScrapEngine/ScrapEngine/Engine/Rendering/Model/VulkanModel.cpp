#include "VulkanModel.h"
#include "../../Debug/DebugLog.h"
#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h>     // Post processing flags
#include <unordered_map>
#include <iostream>

ScrapEngine::VulkanModel::VulkanModel(std::string input_MODEL_PATH) 
	: MODEL_PATH(input_MODEL_PATH)
{
	DebugLog::printToConsoleLog("Loading 3D model...");
	DebugLog::printToConsoleLog("Loading assimp...");
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(MODEL_PATH,
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
	DebugLog::printToConsoleLog("Loading vertices...");
	for (unsigned int i = 0; i < scene->mMeshes[0]->mNumVertices; i++) {
		const aiVector3D* pPos = &(scene->mMeshes[0]->mVertices[i]);
		const aiVector3D* pNormal = scene->mMeshes[0]->HasNormals() ? &(scene->mMeshes[0]->mNormals[i]) : &Zero3D;
		const aiVector3D* pTexCoord = scene->mMeshes[0]->HasTextureCoords(0) ? &(scene->mMeshes[0]->mTextureCoords[0][i]) : &Zero3D;
		Vertex vertex = {};
		vertex.pos = { pPos->x, pPos->y, pPos->z };
		vertex.texCoord = { pTexCoord->x, 1 - pTexCoord->y };
		vertex.color = { pNormal->x, pNormal->y, pNormal->z};
		vertices.push_back(vertex);
	}
	DebugLog::printToConsoleLog("Loading indices...");
	for (unsigned int i = 0; i < scene->mMeshes[0]->mNumFaces; i++) {
		const aiFace& Face = scene->mMeshes[0]->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}
	DebugLog::printToConsoleLog("Vertex and Index model info loaded");
}

ScrapEngine::VulkanModel::~VulkanModel()
{

}

void ScrapEngine::VulkanModel::SimpleTranslate(glm::vec3 input_vector)
{
	for (std::vector<ScrapEngine::Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
		(*it).pos = { (*it).pos.x + input_vector.x, (*it).pos.y + input_vector.y, (*it).pos.z + input_vector.z};
	}
}

const std::vector<ScrapEngine::Vertex>* ScrapEngine::VulkanModel::getVertices()
{
	return &vertices;
}

const std::vector<uint32_t>* ScrapEngine::VulkanModel::getIndices()
{
	return &indices;
}
