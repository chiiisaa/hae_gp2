#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <unordered_map>

using namespace sf;
using namespace std;

class AssetManager
{
public:
	unordered_map<string, Texture> _textures;
	unordered_map<string, Font> _fonts;

	AssetManager()
	{

	}

	~AssetManager()
	{

	}

	void LoadTexture(string name, string fileName)
	{
		Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
		}
	}

	Texture& GetTexture(string name)
	{
		return this->_textures.at(name);
	}

	void LoadFont(string name, string fileName)
	{
		Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	Font& GetFont(string name)
	{
		return this->_fonts.at(name);
	}
};
