#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Shader/Shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader& shader);

private:

	void Setup();
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	std::vector<Texture> _textures;
	unsigned int VAO, VBO, EBO;
};



#endif