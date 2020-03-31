#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <vector>
class GameResources
{
private:
	struct SLoadedTexture
	{
		SLoadedTexture(std::string argTextureName) : texture(new sf::Texture), textureName(argTextureName) {};
		~SLoadedTexture() { delete texture; }
		std::string textureName;
		sf::Texture* texture;
	};

	struct SLoadedSoundBuffer
	{
		SLoadedSoundBuffer(std::string argSoundBufferName) : soundBuffer(new sf::SoundBuffer), soundBufferName(argSoundBufferName) {}
		~SLoadedSoundBuffer() { delete soundBuffer; }
		std::string soundBufferName;
		sf::SoundBuffer* soundBuffer;
	};



	std::vector<SLoadedTexture*> textures;
	std::vector<SLoadedSoundBuffer*> soundBuffers;


public:
	GameResources();
	~GameResources();

	// Game Mechanics
	sf::Texture* LoadTexture(std::string argTextureName);
	sf::SoundBuffer* LoadSoundBuffer(std::string argSoundBufferName);

	// Get Functions
	sf::Texture* GetTexture(unsigned int argTextureID);
	sf::SoundBuffer* GetSoundBuffer(unsigned int argBufferID);
};

