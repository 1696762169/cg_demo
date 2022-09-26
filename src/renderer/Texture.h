#pragma once
#include<memory>
#include<iostream>
#include<stb/stb_image.h>

//std::string pathToTexName(std::string file_path);

class Texture {
public:
	Texture();
	~Texture();
public:
	static std::shared_ptr<Texture> loadFromFile(const std::string& file_path);

public:
	int width, height;
	std::string type; // shader �ж�Ӧ���� (diffuse, metallic, height, ..) 
	std::string name; // Ψһid��path
	unsigned int id;
};
