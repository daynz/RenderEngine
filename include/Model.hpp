#pragma once
#include <string>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.hpp"

class Model
{
public:
	Model(char* path, bool gamma = false);
	void Draw(Shader& shader);

private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);

	std::vector<Mesh> m_Meshes;
	std::string m_Directory;
	std::vector<Texture> m_Textures_Loaded;
	bool m_GammaCorrection;
};