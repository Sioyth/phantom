#include "Mesh.h"
#include <iostream>
namespace Phantom
{
	Mesh::Mesh()
	{
		Plane();
	}
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
		_vertices = vertices;
		_indices = indices;
		_textures = textures;
		Setup();
	}

	void Mesh::Draw(Shader& shader)
	{
		if (_textures.size() > 0)
		{
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			for (unsigned int i = 0; i < _textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
				// retrieve texture number (the N in diffuse_textureN)
				std::string number;
				std::string name = _textures[i].type;
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "texture_specular")
					number = std::to_string(specularNr++);

				shader.SendUniformData(("_material." + name + number).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, _textures[i].id);
			}
			glActiveTexture(GL_TEXTURE0);
		}

		//draw mesh
		glBindVertexArray(VAO);
		if (_indices.size() > 0)
			glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
		glBindVertexArray(0);

		//always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::Setup()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
		
		if (_indices.size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
		}

		// Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		// TextCoord
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

		glBindVertexArray(0);
	}
	void Mesh::Plane()
	{
		//unsigned int n = 1;
		////unsigned int n = 1;

		//float dz = 1.0f / n;
		//float dx = 1.0f / n;

		//for (int x = 0; x <= n; x++)
		//{
		//	for (int z = 0; z <= n; z++)
		//	{
		//		Vertex vertex;
		//		// * 2.0f - 1.0f, to pass from the space [0,1] to opengl NDC [-1, 1];
		//		vertex.position = glm::vec3(dz * z * 2.0f - 1.0f, dx * x * 2.0f - 1.0f, 0.0f);
		//		vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		//		//vertex.texCoord = glm::vec2(1.0f - x * dx, dz * z);

		//		std::cout << "X: " << vertex.position.x << " ";
		//		std::cout << "Z: " << vertex.position.z <<std::endl;

		//		_vertices.push_back(vertex);
		//	}
		//}
		
		std::vector<glm::vec3> vertices = { 
										glm::vec3(-1.0f, 0.0f,  1.0f),
										glm::vec3( 1.0f, 0.0f,  1.0f),
										glm::vec3( 1.0f, 0.0f, -1.0f),
										glm::vec3(-1.0f, 0.0f, -1.0f) };

		for (int i = 0; i < vertices.size(); i++)
		{
			Vertex vertex;
			vertex.position = vertices[i];
			vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			_vertices.push_back(vertex);
		}

		_indices = { 0, 1, 3, 3, 1, 2 };
		_textures = std::vector<Texture>();

		Setup();
	}
}
