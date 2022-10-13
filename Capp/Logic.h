#pragma once
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#pragma region settings

int numberOfGuesses = 5;

int minVal = 0;
int maxVal = 10;

#pragma endregion settings


enum NumberPrefs
{
	Lower =0,
	Equal,
	Higher
};

enum SettingsTab
{
	SNumberOfGuesses =0,
	SMinValue,
	SMaxValue
};

int StartGame(bool* isEndOfGame);

void SimulateGame(bool* isEndOfGame, int numberToGuess);

int GenerateNumber();

bool CheckNumbers(enum NumberPrefs compare);

enum NumberPrefs CompareNumbers(int correctNumber, int guessedNumber);

bool NewGame();

void Settings();
bool OpenSettingsTab(enum SettingsTab tab);