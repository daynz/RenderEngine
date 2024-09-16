#pragma once
#include <vector>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Texture.hpp"
#include "Shader.hpp"

const unsigned int MAX_BONE_INFLUENCE = 4;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>vertices, std::vector<unsigned int>indices, std::vector<Texture>textures);
	void Draw(Shader& shader);

	unsigned int VAO()const;
	std::vector<Vertex> vertices()const;
	std::vector<unsigned int> indices()const;
	std::vector<Texture> textures()const;

private:
	unsigned int m_VAO;
	unsigned int VBO;
	unsigned int EBO;

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;

	void setupMesh();

protected:

};