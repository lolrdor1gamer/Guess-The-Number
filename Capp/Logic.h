#pragma once
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#pragma region settings

extern int numberOfGuesses;

extern int minVal;
extern int maxVal;


extern bool isEndOfGame;
extern bool quitGame;
#pragma endregion settings


enum GameState
{
	GSettings =0,
	GGame,
	GExit
};

enum NumberPrefs
{
	Lower= 0,
	Equal,
	Higher
};

enum SettingsTab
{
	SNumberOfGuesses= 0,
	SMinValue= 1,
	SMaxValue= 2
};

int StartGame(bool* isEndOfGame);

void SimulateGame(bool* isEndOfGame, int numberToGuess, int m_numberOfGuesses);

int GenerateNumber();

bool CheckNumbers(enum NumberPrefs compare);

enum NumberPrefs CompareNumbers(int correctNumber, int guessedNumber);

enum GameState NewState();

void ParseMenu(enum GameState state);

void StartProgram();

void Settings();
bool OpenSettingsTab(enum SettingsTab* tab);
void ChangeTab(enum SettingsTab* tab, char direction);
void ChangeSettingsValue(enum SettingsTab* tab, int val);
