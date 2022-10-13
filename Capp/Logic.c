#include "Logic.h"


int numberOfGuesses = 5;

int minVal = 0;
int maxVal = 10;

bool isEndOfGame = false;
bool quitGame = false;

int StartGame(bool* isEndOfGame)
{
	isEndOfGame = false;
	return GenerateNumber();
}

void SimulateGame(bool* isEndOfGame, int numberToGuess, int m_numberOfGuesses)
{
	printf("Start of the game\nPlease enter your number\n");
	int u;
	int o;
	while (!*isEndOfGame)
	{
		scanf(" %i", &u);
		fflush(stdin);
		*isEndOfGame = CheckNumbers(CompareNumbers(numberToGuess, u));
		if(!*isEndOfGame)
		{
			m_numberOfGuesses--;
		}
		else
		{
			printf("End of the game\nYou won\n");
			printf("Enter anything to continue\n");
			scanf(" %i", &o);
			fflush(stdin);
			return;
		}
		if(m_numberOfGuesses == 0)
		{
			printf("End of the game\nYou lost\nThe number was %i\n", numberToGuess);
			printf("Enter anything to continue\n");
			scanf(" %i", &o);
			fflush(stdin);
			return;
		}
	}
}
bool CheckNumbers(enum NumberPrefs compare)
{
	switch (compare)
	{
	case Lower:
		printf("Your number lower than guessed\n");
		return false;
		break;
	case Equal:
		printf("Your number is equal with guessed\n");
		return true;
		break;
	case Higher:
		printf("Your number higher than guessed\n");
		return false;
		break;
	default:
		printf("code error\n");
		return true;
		break;
	}
}

enum GameState NewState()
{
	printf("What You want to do?\nP - play      E - exit		S - settings\n");
	char answer;
	scanf(" %c", &answer);
	fflush(stdin);
	
	answer = toupper(answer);
	switch (answer)
	{
	case 'P':
		return GGame;
		break;
	case 'S':
		return GSettings;
		break;
	case 'E':
		return GExit;
		break;
	default:
		break;
	}
}

void ParseMenu(enum GameState state)
{
	switch (state)
	{
	case GSettings:
		Settings();
		break;
	case GGame:
		SimulateGame(&isEndOfGame, StartGame(&isEndOfGame),numberOfGuesses);
		break;
	case GExit:
		quitGame = true;
		break;
	default:
		break;
	}
}

void Settings()
{
	enum SettingsTab tab = 0;
	bool isInMenu = true;
	do
	{
		printf("Settings menu:\n");
		isInMenu = OpenSettingsTab(&tab);

	} while (isInMenu);

}

bool OpenSettingsTab(enum SettingsTab* tab)
{
	char inp[5];
	switch (*tab)
	{
	case SNumberOfGuesses:
		printf("Number of guesses = %i\n", numberOfGuesses);
		break;
	case SMinValue:
		printf("Minimum value = %i\n", minVal);
		break;
	case SMaxValue:
		printf("Maximum value = %i\n", maxVal);
		break;
	default:
		break;
	}
	printf("Enter new number or switch tab\n print number or \'<\' \'>\' for changing menu\nExit from menu - E\n");
	scanf(" %s", inp);
	fflush(stdin);


	if (toupper(inp[0]) == 'E')
		return false;
	else if (inp[0] == '<' || inp[0] == '>')
		ChangeTab(tab, inp[0]);
	else
	{
		ChangeSettingsValue(tab, atoi(inp));
	}
	return true;
}

void ChangeTab(enum SettingsTab* tab, char direction)
{
	switch(direction)
	{
	case '<':
		if (*tab == 0)
			*tab = 2;
		else
			--*tab;
		break;
	case '>':
		if (*tab == 2)
			*tab = 0;
		else
			++*tab;
		break;
	default:
		break;
	}
}
void ChangeSettingsValue(enum SettingsTab* tab, int val)
{
	switch (*tab)
	{
	case SNumberOfGuesses:
		numberOfGuesses = val;
		break;
	case SMinValue:
		minVal = val;
		break;
	case SMaxValue:
		maxVal = val;
		break;
	default:
		break;
	}

}
enum NumberPrefs CompareNumbers(int correctNumber, int guessedNumber)
{
	if(guessedNumber> correctNumber)
	{
		return Higher;
	}
	else if(guessedNumber == correctNumber)
	{
		return Equal;
	}
	else if(guessedNumber < correctNumber)
	{
		return Lower;
	}
}
int GenerateNumber()
{
	int r = rand()+ minVal;
	return r % maxVal;
}
