#include "GameResources.h"

#include <iostream>

GameResources::GameResources()
{
}

// Deletes all loaded resources
GameResources::~GameResources()
{
	for (SLoadedTexture* sTexture : textures)
	{
		delete sTexture;
	}

	for (SLoadedSoundBuffer* sSoundBuffer : soundBuffers)
	{
		delete sSoundBuffer;
	}
}

// Loads a texture from the /Textures/ Folder with the inputted name, will return the a already loaded texture if the name is the same
sf::Texture* GameResources::LoadTexture(std::string argTextureName)
{
	// Checks if asset is already loaded, returns it if it is
	for (SLoadedTexture* sTexture : textures) 
	{
		if (sTexture->textureName == argTextureName)
		{
			return sTexture->texture;
		}
	}

	// Creates new texture and loads it then stores the pointer
	SLoadedTexture* sTexture = new SLoadedTexture(argTextureName);

	if(!(*sTexture->texture).loadFromFile("Textures/" + argTextureName))
		std::cerr << "ERROR: Couldn't load texture " << argTextureName << std::endl;


	textures.push_back(sTexture);

	return sTexture->texture;
}

// Loads a sound from the /Sounds/ Folder with the inputted name, will return the a already loaded sound if the name is the same
sf::SoundBuffer* GameResources::LoadSoundBuffer(std::string argSoundBufferName)
{
	// Checks if asset is already loaded, returns it if it is
	for (SLoadedSoundBuffer* sSoundBuffer : soundBuffers)
	{
		if (sSoundBuffer->soundBufferName == argSoundBufferName)
		{
			return sSoundBuffer->soundBuffer;
		}
	}

	// Creates new soundBuffer and loads it and then stores the pointer
	SLoadedSoundBuffer* sSoundBuffer = new SLoadedSoundBuffer(argSoundBufferName);
	if (!(*sSoundBuffer->soundBuffer).loadFromFile("Sounds/" + argSoundBufferName))
		std::cerr << "ERROR: Couldn't load sound buffer " << argSoundBufferName << std::endl;

	soundBuffers.push_back(sSoundBuffer);

	return sSoundBuffer->soundBuffer;
}

//
// Get Functions
//

sf::Texture* GameResources::GetTexture(unsigned int argTextureID)
{
	return textures[argTextureID]->texture;
}

sf::SoundBuffer* GameResources::GetSoundBuffer(unsigned int argBufferID)
{
	return soundBuffers[argBufferID]->soundBuffer;
}
