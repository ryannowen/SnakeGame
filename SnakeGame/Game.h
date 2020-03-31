#pragma once

#include "SFML/Graphics.hpp"
#include "GameResources.h"

class SpawnManager;

class Game
{
public:
	enum class EGameState
	{
		MainMenu,
		InGame,
		HighScoreSubmittion,
		HighScoreTable,
		PauseMenu,
		Quit
	};

	enum class EDifficulty
	{
		Hard = 1,
		Medium,
		Easy
	};

	struct SHighScore
	{
		std::string name;
		unsigned int score;
	};

private:
	int waterLevel;
	float waterMaxTime;
	float waterRemainingTime;
	float pausedTime;
	unsigned short scale;
	unsigned short numOfAISnakes;
	unsigned short numOfPlayerSnakes;

	std::string winningSnakeName;
	unsigned int winningSnakeScore;

	SpawnManager* gameSpawnManager;
	GameResources* gameResourceHolder;

	EDifficulty gameDifficulty;
	EGameState gameState;

	unsigned short maxHighscores;
	std::vector<SHighScore> highScores;

	sf::Clock gameTime;
	sf::Vector2f ScreenDimensions = sf::Vector2f(1600, 900);
	sf::Font gameFont;

	// Game Mechanics
	void CheckSnakeCollisions();
	void CheckCollectablesWithWaterHeight();
	bool CheckGameWinner();

	void CheckIsHighScore(const unsigned int& argScore);
	void SaveHighScores();
	void LoadHighScores();

	void AddHighScore();

	void ResetGame();

	void SpawnUI();
	void HandleKeyboardPressedInput(const sf::Keyboard::Key& argKey);
	void HandleMouseInput(sf::RenderWindow& window);
	void LowerWater();
	void DrawWindow(sf::RenderWindow& window);

	// Get Functions
	float GetWaterFallRate() const;

public:
	Game(const unsigned short argScale = 30, const float argWaterMaxTime = 90.0f, const Game::EDifficulty argDifficulty = Game::EDifficulty::Medium);
	~Game();

	// Game Mechanics
	void Play(const unsigned short argNumOfAI = 3, const unsigned short argNumOfPlayers = 1);
	void SetGameState(Game::EGameState argNewState);
	void QuitGame();

	void SubmitHighScore();

	// Get Functions
	int GetNumberOfAI() const;
	int GetNumberOfPlayers() const;
	std::string GetWinningSnakeName() const;
	int GetWinningSnakeScore() const;
	int GetWaterLevel() const;
	float GetWaterRemainingTime() const;
	sf::Vector2f GetScreenDimensions() const;
	unsigned short GetScale() const;
	SpawnManager* GetGameSpawnManager() const;
	GameResources* GetGameResources() const;
	Game::EDifficulty GetGameDifficulty() const;
	Game::EGameState GetGameState() const;
	sf::Font* GetGameFont() const;
	std::vector<Game::SHighScore> GetHighScores() const;
};

