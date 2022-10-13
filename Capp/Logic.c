#include "Logic.h"


int numberOfGuesses = 5;

int minVal = 0;
int maxVal = 10;

bool isEndOfGame = false;
bool quitGame = false;

char username[30];
struct Attempt Attempts;

struct Guessing m_g;

struct Attempt* NewAttempt()
{
	struct Attempt m_att;
	m_att.m_minVal = minVal;
	m_att.m_maxVal = maxVal;
	m_att.m_NumberOfGuesses = numberOfGuesses;

	m_g.number = 0;
	m_att.guessing = &m_g;

	struct Attempt* att = malloc(sizeof(struct Attempt));

	att = &Attempts;

	do
	{
		if (att->next = att)
			break;
		att = att->next;

	} while (true);

	if(att->number == 0)
	{
		m_att.number = 1;
		m_att.next = &Attempts;
		m_att.prev = &Attempts;

		Attempts = m_att;

		return &Attempts;
	}
	m_att.number = att->number+1;
	m_att.prev = att;
	m_att.next = &m_att;
	struct Attempt* atts = &m_att;
	att->next = atts;
	return atts;
}

void CreateFirstAttempt()
{
	Attempts.number = 0;
	Attempts.m_minVal = minVal;
	Attempts.m_maxVal = maxVal;
	Attempts.m_NumberOfGuesses = numberOfGuesses;
	struct Guessing m_g;
	m_g.number = 0;
	Attempts.guessing = &m_g;
	Attempts.prev = &Attempts;
	Attempts.next = &Attempts;
}


void NewGuessing(struct Attempt* attempts, int res, int attempt)
{
	struct Guessing* m_guess = malloc(sizeof(struct Guessing));
	m_guess->val = res;
	m_guess->attempt = attempt;

	struct Guessing* guess = attempts->guessing;

	if (guess->number == 0)
	{
		m_guess->number = 1;
		m_guess->next = NULL;
		attempts->guessing = m_guess;
		return;
	}

	do
	{
		if (guess->next == NULL)
			break;
		guess = guess->next;
	} while (true);

	m_guess->number = guess->number + 1;
	m_guess->next = NULL;
	guess->next = m_guess;
}

int StartGame()
{
	isEndOfGame = false;
	return GenerateNumber();
}

void SimulateGame( int numberToGuess, int m_numberOfGuesses)
{
	struct Attempt* att = malloc(sizeof(struct Attempt));
	att = NewAttempt();
	printf("Start of the game\nThere is a secret number between %i and %i\nPlease enter your number\n", minVal, maxVal);
	int u;
	int o;
	while (!isEndOfGame)
	{
		scanf(" %i", &u);
		fflush(stdin);
		isEndOfGame = CheckNumbers(CompareNumbers(numberToGuess, u, att));
		if(!isEndOfGame)
		{
			m_numberOfGuesses--;
		}
		else
		{
			printf("End of the game\nYou won, %s\n", username);
			printf("Enter anything to continue\n");
			scanf(" %i", &o);
			fflush(stdin);
			return;
		}
		if(m_numberOfGuesses == 0)
		{
			printf("End of the game\nYou lost, %s\nThe number was %i\n", username, numberToGuess);
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
	printf("%s, what You want to do?\nG - play      E - exit		P - preferences			S - stats\n", username);
	char answer;
	scanf(" %c", &answer);
	fflush(stdin);
	
	answer = toupper(answer);
	switch (answer)
	{
	case 'G':
		return GGame;
		break;
	case 'P':
		return GSettings;
		break;
	case 'E':
		return GExit;
		break;
	case 'S':
		return GStats;
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
		SimulateGame(StartGame(),numberOfGuesses);
		break;
	case GExit:
		quitGame = true;
		break;
	case GStats:
		ShowAttempts();
	default:
		break;
	}
}

void StartProgram()
{
	printf("Welcome to the guessing game!\nThe object of the game is to guess the secret number.\nYou get %i chances for that.\nTo address you personally, I would like to know your name.\nWhat is your name?\n", numberOfGuesses);
	scanf(" %s", &username);
	fflush(stdin);
	printf("Great %s, let's get started.\n", username);
	CreateFirstAttempt();
	do
	{
		ParseMenu(NewState());
		system("cls");
	} while (!quitGame);

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

void PrintGuesses(struct Attempt* att)
{
	struct Guessing* m_guess = att->guessing;
	printf("Number\tCorrect\tUser input\n");
	while(m_guess != NULL)
	{
		printf("%i\t%i\t%i\n", m_guess->number, m_guess->attempt, m_guess->attempt);
		if (m_guess->next == NULL)
			break;
		m_guess = m_guess->next;
	}
	printf("Enter anything to return\n");
	char o;
	scanf(" %c", &o);
	fflush(stdin);
}

bool PrintAttempts(struct Attempt* att)
{
	printf("Number: %i\nMinimal value: %i\nMaximum value: %i\nGuesses limit: %i\n", att->number, att->m_minVal, att->m_maxVal, att->m_NumberOfGuesses);
	printf("S - show history, \'<\' \'>\' for another attempt\nExit from menu - E\n");
	char inp;
	scanf(" %c", &inp);
	fflush(stdin);
	if (toupper(inp) == 'S')
		PrintGuesses(att);
	else if (toupper(inp) == 'E')
		return false;
	else
		ChangeAttempt(att, inp);
	return true;
}

void ChangeAttempt(struct Attempt* att, char dir)
{
	switch (dir)
	{
	case '<':
		*att = *att->prev;
		break;
	case'>' :
		*att = *att->next;
		break;
	default:
		break;
	}
}

void ShowAttempts()
{
	bool isInMenu = true;
	struct Attempt* att = &Attempts;
	do
	{
		printf("Attempts menu:\n");
		isInMenu = PrintAttempts(att);

	} while (isInMenu);
}

enum NumberPrefs CompareNumbers(int correctNumber, int guessedNumber, struct Attempt* att)
{
	NewGuessing(att, correctNumber, guessedNumber);
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
