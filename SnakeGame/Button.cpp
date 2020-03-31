#include "Button.h"

#include <iostream>
#include "GameResources.h"

Button::Button(const Game* argGame, const Game::EGameState argButtonShowState, const sf::Vector2f argScreenPosition, const sf::Vector2f argButtonSize, const std::string argLabelText, const unsigned int argLabelSize, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture, const std::string argHoverSoundBufferName, const std::string argPressedSoundBufferName)
	: buttonShowState(argButtonShowState)
{
	// Loads Textures and Sounds
	LoadButtonTextures(argGame, argNormalTexture, argHoveredTexture, argPressedTexture);
	LoadSoundBuffers(argGame, argHoverSoundBufferName, argPressedSoundBufferName);

	// Updates button position and size
	button.SetScreenPosition(argScreenPosition);
	button.Resize(argButtonSize);

	// Updates buttonLabel with new Values
	buttonLabel.setFont(*argGame->GetGameFont());
	ChangeLabelText(argLabelSize, argLabelText, argFillColour, argOutlineSize, argOutlineColour);
	buttonLabel.setPosition(sf::Vector2f((argScreenPosition.x + button.GetRectangleSize().x / 2) - buttonLabel.getLocalBounds().width / 2, (argScreenPosition.y + button.GetRectangleSize().y / 2) - buttonLabel.getLocalBounds().height / 2));
}


Button::~Button()
{
}

// Checks if the button is hovered by the mouse, if it is and the state isn't already hovered then it will change to the hover state, play the sound and do the hover mechanics.
// if it isnt hovered but is in the state of hovered then it will stop being hovered and do the end hovered mechanics  
void Button::MouseHoverCheck(Game* argGame, sf::RenderWindow& window)
{
	if (buttonState != EState::Pressed)
	{
		if (button.GetGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			if (!(buttonState == EState::Hover))
			{
				buttonState = EState::Hover;
				PlayHoveredSound(false);
				OnBeginHover(argGame);
			}
		} 
		else
		{
			if (buttonState == EState::Hover)
			{
				buttonState = EState::Normal;
				OnEndHover(argGame);
			}
		}
	}
}

// Loads the buffer and plays the pressed button sound, if a sound isn't loaded outputs an error
void Button::PlayPressedSound(const bool argLoop)
{
	if (pressedSoundBuffer != nullptr)
	{
		pressedSound.setBuffer(*pressedSoundBuffer);
		pressedSound.setVolume(15.0f);
		pressedSound.setLoop(argLoop);
		pressedSound.play();
	} else
		std::cerr << "ERROR: Trying to play button pressed sound when it isn't loaded" << std::endl;

}

// Loads the buffer and plays the hovered button sound, if a sound isn't loaded outputs an error
void Button::PlayHoveredSound(const bool argLoop)
{
	if (hoverSoundBuffer != nullptr)
	{
		hoverSound.setBuffer(*hoverSoundBuffer);
		hoverSound.setVolume(15.0f);
		hoverSound.setLoop(argLoop);
		hoverSound.play();
	} else
		std::cerr << "ERROR: Trying to play button hovered sound when it isn't loaded" << std::endl;
}

// Checks if the Pressed sound is being played, if it is stops the sound
void Button::EndPressedSound()
{
	if (pressedSound.getStatus() == sf::SoundSource::Status::Playing)
		pressedSound.stop();
}

// Checks if the Hovered sound is being played, if it is stops the sound
void Button::EndHoveredSound()
{
	if (hoverSound.getStatus() == sf::SoundSource::Status::Playing)
		hoverSound.stop();
}

// Loads the textures for each state of the button, from the GameResources and saves them for later use  
void Button::LoadButtonTextures(const Game* argGame, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture)
{
	if (!(argNormalTexture == ""))
	{
		buttonNormalTexture = argGame->GetGameResources()->LoadTexture(argNormalTexture);
	}
	else
		std::cout << "WARNING: No button normal texture inputed" << std::endl;


	if (!(argHoveredTexture == ""))
	{
		buttonHoveredTexture = argGame->GetGameResources()->LoadTexture(argHoveredTexture);
	}
	else
		std::cout << "WARNING: No button hovered texture inputed" << std::endl;


	if (!(argPressedTexture == ""))
	{
		buttonPressedTexture = argGame->GetGameResources()->LoadTexture(argPressedTexture);
	}
	else
		std::cout << "WARNING: No button pressed texture inputed" << std::endl;
}

// Loads the sound for each state of the button, from the GameResources and saves them for later use  
void Button::LoadSoundBuffers(const Game* argGame, const std::string argHoverSoundBufferName, const std::string argPressedSoundBufferName)
{
	if (!(argHoverSoundBufferName == ""))
	{
		hoverSoundBuffer = argGame->GetGameResources()->LoadSoundBuffer(argHoverSoundBufferName);
	}
	else
		std::cout << "WARNING: No button hover sound inputed" << std::endl;


	if (!(argPressedSoundBufferName == ""))
	{
		pressedSoundBuffer = argGame->GetGameResources()->LoadSoundBuffer(argPressedSoundBufferName);
	}
	else
		std::cout << "WARNING: No button pressed sound inputed" << std::endl;
}

// Updates the button rectangle size increasing the click area
void Button::ChangeButtonSize(const sf::Vector2f argNewSize)
{
	button.Resize(argNewSize);
}

// Sets the button Label data to new values to match the button
void Button::ChangeLabelText(const unsigned int argNewSize, const std::string argNewText, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour)
{
	buttonLabel.setCharacterSize(argNewSize);
	buttonLabel.setString(argNewText);
	buttonLabel.setFillColor(argFillColour);
	buttonLabel.setOutlineThickness(argOutlineSize);
	buttonLabel.setOutlineColor(argOutlineColour);
}

// Changes the button label text size independantly because it is usually used quite often
void Button::ChangeLabelSize(const unsigned int argNewLabelSize)
{
	buttonLabel.setCharacterSize(argNewLabelSize);
}

// Checks if the button is hovered by the mouse, if it is and the state is being pressed then it will change to the pressed state, play the sound and do the begin pressed mechanics.
// if it isnt being pressed then set it back to normal, and do end press mechanics
// if the buttonn isnt hovered change it to normal
bool Button::CheckIfMouseClicked(Game* argGame, sf::RenderWindow& window, const bool argIsPressed)
{
	if (button.GetGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		if (argIsPressed)
		{
			buttonState = EState::Pressed;
			PlayPressedSound(false);
			OnBeginClick(argGame);
			return true;
		}
		else
		{
			buttonState = EState::Normal;
			OnEndClick(argGame);
			return true;
		}
	}
	else if (!argIsPressed)
	{
		buttonState = EState::Normal;
	}

	return false;
}

// Changes Texture depending on current state, then draws the button and then the label(So the label is on top)
void Button::Draw(Game* argGame, sf::RenderWindow& window)
{
	MouseHoverCheck(argGame, window);

	switch (buttonState)
	{
	default:
	case Button::EState::Normal:
		currentTexture = buttonNormalTexture;
		break;
	case Button::EState::Hover:
		currentTexture = buttonHoveredTexture;
		break;
	case Button::EState::Pressed:
		currentTexture = buttonPressedTexture;
		break;
	}

	button.SetTexture(currentTexture);


	button.Draw(window);
	window.draw(buttonLabel);
}

//
// Get Functions
//

Game::EGameState Button::GetShowState()
{
	return buttonShowState;
}