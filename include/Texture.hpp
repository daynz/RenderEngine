#include <string>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Texture
{
public:
	Texture();
	Texture(std::string texturePath);
	Texture(std::string path, const std::string& directory, bool gamma);

	unsigned int texture()const;

	std::string type()const;
	void type(std::string t);

	aiString path()const;
	void path(aiString p);

private:
	unsigned int m_Texture;
	std::string m_type;
	aiString m_Path;
protected:

};