#include<glad/glad.h>
#include"Texture.h"
#define STB_IMAGE_IMPLEMENTATION

Texture::Texture() {
	width = height = 0;
	//type = ""; 
	name = ""; 
	id = 0;
}

Texture::~Texture() {
	if (id) {
		glDeleteTextures(1, &id);
	}
}
//std::string pathToTexName(std::string file_path) {
//	std::string name; 
//	int index = file_path.find_last_of("/");
//	std::string dir = file_path.substr(0, index);
//	index = dir.find_last_of("/");
//	name = dir.substr(index+1,dir.length()-index-1)+"_" + tex->type;  // name 用于统一区分
//	return name; 
//}


std::shared_ptr<Texture> Texture::loadFromFile(const std::string& file_path) {
	std::shared_ptr<Texture> tex = std::make_shared<Texture>(); 

	//int index = file_path.find_last_of("/");
	//tex->type = file_path.substr(index + 1, file_path.length() - index - 1 - 4); // 删去 .png
	//tex->type = "";
	tex->name = file_path;
	
	// type is for shaders 

	int nrChannels; 
	glGenTextures(1, &tex->id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load((file_path).c_str(), &tex->width, &tex->height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1) {
			format = GL_RED;
		}
		else if (nrChannels == 4) {
			format = GL_RGBA;
		}
		else if (nrChannels == 3) {
			format = GL_RGB;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, tex->width, tex->height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
	}
	else
	{
		std::cout << "Failed to load " <<file_path << std::endl;
	}
	stbi_image_free(data);

	//tex->type = file_path; 

	return tex; 
}

//std::shared_ptr<Texture> Texture::setType(const std::string& type) {
	//this->type = type;
	//return shared_from_this();
//}

std::shared_ptr<Texture> Texture::genTexture(unsigned int DataType,unsigned int channelType,int width, int height) {
	if (id)
		glDeleteTextures(1, &id);
	this->width = width;
	this->height = height;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	unsigned int dType; 
	if (DataType == GL_RGBA32F)
		dType = GL_FLOAT;
	else if (DataType == GL_RGBA)
		dType = GL_UNSIGNED_BYTE;
	else if (DataType == GL_DEPTH_COMPONENT)
		dType = GL_FLOAT;
	glTexImage2D(GL_TEXTURE_2D, 0, DataType, width, height, 0, channelType,
		dType, NULL);
	return shared_from_this();
}

std::shared_ptr<Texture> Texture::genCubeMap(GLenum format, int width,int height) {
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	for (int i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format,
			width, height, 0, format, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return shared_from_this();
}