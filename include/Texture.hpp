#include <string>

class Texture
{
public:
	Texture();
	Texture(std::string texturePath);

	unsigned int texture()const;
private:
	unsigned int m_Texture;

protected:

};