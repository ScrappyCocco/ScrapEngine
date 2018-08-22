#include "VulkanModel.h"
#include "../../Debug/DebugLog.h"
#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h>     // Post processing flags
#include <unordered_map>
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

ScrapEngine::VulkanModel::VulkanModel(std::string input_MODEL_PATH, std::string input_TEXTURE_PATH) 
	: MODEL_PATH(input_MODEL_PATH), TEXTURE_PATH(input_TEXTURE_PATH)
{
	DebugLog::printToConsoleLog("Loading 3D model...");

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
	std::cout << " NUM MESHES: " << scene->mNumMeshes << std::endl;
	std::cout << " NUM TEXTURES: " << scene->mNumTextures << std::endl;
	std::cout << " NUM MATERIALS: " << scene->mNumMaterials << std::endl;
	std::cout << " NUM FACES: " << scene->mMeshes[0]->mNumFaces << std::endl;
	for (unsigned int x = 0; x < scene->mMeshes[0]->mNumFaces; ++x) {

		const struct aiFace* face = &scene->mMeshes[0]->mFaces[x];

		for (unsigned int y = 0; y < face->mNumIndices; ++y) {
			Vertex vertex = {};

			int vertexIndex = face->mIndices[y];

			vertex.pos = {
				scene->mMeshes[0]->mVertices[vertexIndex].x,
				scene->mMeshes[0]->mVertices[vertexIndex].y,
				scene->mMeshes[0]->mVertices[vertexIndex].z
			};
			if (scene->mMeshes[0]->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
			{
				vertex.texCoord = {
					scene->mMeshes[0]->mTextureCoords[0][vertexIndex].x,
					1 - scene->mMeshes[0]->mTextureCoords[0][vertexIndex].y
				};
			}
			vertex.color = { 1.0f, 1.0f, 1.0f };
			/*if (scene->mMeshes[0]->mColors[0] != NULL){
				vertex.color = {
					scene->mMeshes[0]->mColors[0][vertexIndex].r,
					scene->mMeshes[0]->mColors[0][vertexIndex].g,
					scene->mMeshes[0]->mColors[0][vertexIndex].b
				};
			}else{
				vertex.color = { 1.0f, 1.0f, 1.0f };
			}*/
			vertices.push_back(vertex);
			indices.push_back(face->mNumIndices);
		}
		
	}

	/*tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, MODEL_PATH.c_str())) {
		throw std::runtime_error(err);
	}
	bool considerMaterials = true;
	if (attrib.texcoords.size() == 0) {
		considerMaterials = false;
		DebugLog::printToConsoleLog("Ignoring model materials");
	}
	
	std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};
			if(considerMaterials){
				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}
			else {
				
			}

			vertex.color = { 1.0f, 1.0f, 1.0f };

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}

			indices.push_back(uniqueVertices[vertex]);
		}
	}*/
	DebugLog::printToConsoleLog("Vertex and Index model info loaded");
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
