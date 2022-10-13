#include "Logic.h"


int StartGame(bool* isEndOfGame)
{
	isEndOfGame = false;
	return GenerateNumber();
}

void SimulateGame(bool* isEndOfGame, int numberToGuess)
{
	printf("Start of the game\nPlease enter your number\n");
	int u;
	while (!*isEndOfGame)
	{
		scanf("%i", &u);
		fflush(stdin);
		*isEndOfGame = CheckNumbers(CompareNumbers(numberToGuess, u));
		if(!*isEndOfGame)
		{
			numberOfGuesses--;
		}
		else
		{
			printf("End of the game\nYou won\n");
			return;
		}
		if(numberOfGuesses == 0)
		{
			printf("End of the game\nYou lost\n");
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

bool NewGame()
{
	printf("Do You want to try again?\nY - yes      N-no\n");
	char answer;
	scanf(" %c", &answer);
	fflush(stdin);
	answer = toupper(answer);
	return (answer == 'Y' ? false : true);
}

void Settings()
{
	enum SettingsTab tab = 0;
	bool isInMenu = true;
	do
	{
		printf("Settings menu:\n");

	} while (isInMenu);

}

bool OpenSettingsTab(enum SettingsTab tab)
{
	char inp[5];
	switch (tab)
	{
	case SNumberOfGuesses:
		printf("Number of guesses = %i\n", numberOfGuesses);
		break;
	case SMinValue:
		break;
	case SMaxValue:
		break;
	default:
		break;
	}
	printf("Enter new number or switch tab\n print number or \'<\' \'>\' for changing menu\nExit from menu - E");
	scanf("%s", inp);
	fflush(stdin);
	printf("%i\n", inp);

	if (toupper(inp[0]) == 'E')
		return false;
	return true;
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
