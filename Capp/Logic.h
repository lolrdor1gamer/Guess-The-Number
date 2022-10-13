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
extern struct Attempt Attempts;
#pragma endregion settings


enum GameState
{
	GSettings =0,
	GGame,
	GExit,
	GStats
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

struct Guessing
{
	int number;

	int attempt;
	int val;

	struct Guessing* next;
};


struct Attempt
{
	int number;

	int m_minVal;
	int m_maxVal;
	int m_NumberOfGuesses;

	struct Guessing* guessing;

	struct Attempt* next;
	struct Attempt* prev;
};


void CreateFirstAttempt();

struct Attempt* NewAttempt();


void NewGuessing(struct Attempt* Attempts, int attempt, char* res);



int StartGame();

void SimulateGame(int numberToGuess, int m_numberOfGuesses);

int GenerateNumber();

bool CheckNumbers(enum NumberPrefs compare);

enum NumberPrefs CompareNumbers(int correctNumber, int guessedNumber, struct Attempt* att);

enum GameState NewState();

void ParseMenu(enum GameState state);

void StartProgram();

void Settings();
bool OpenSettingsTab(enum SettingsTab* tab);
void ChangeTab(enum SettingsTab* tab, char direction);
void ChangeSettingsValue(enum SettingsTab* tab, int val);


void PrintGuesses(struct Attempt* att);
bool PrintAttempts(struct Attempt* att);
void ChangeAttempt(struct Attempt* att, char dir);
void ShowAttempts();