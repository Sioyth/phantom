#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Mesh.h"

namespace Phantom
{
	class Model
	{
		public:
			Model(std::string path);
			void Draw(Shader& shader);
		private:

			std::string _dir;
			std::vector<Mesh> _meshes;
			std::vector<Texture> _loadedTextures;

			void Load(std::string path);
			void ProcessNode(aiNode* node, const aiScene* scene);
			Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
			unsigned int TextureFromFile(const char* path, const std::string& directory);
			std::vector<Texture> LoadTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}
#endif

