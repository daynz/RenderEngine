#include <string>

class Texture
{
public:
	Texture();
	Texture(std::string texturePath);

	unsigned int texture()const;

	std::string type()const;
	void type(std::string t);
	std::string path()const;
	void path(std::string p);
private:
	std::string m_Path;
	unsigned int m_Texture;
	std::string m_type;
protected:

};