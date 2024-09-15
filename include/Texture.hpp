#include <string>

class Texture
{
public:
	Texture();
	Texture(std::string texturePath);

	unsigned int texture()const;
	std::string type()const;
private:
	unsigned int m_Texture;
	std::string m_type;
protected:

};