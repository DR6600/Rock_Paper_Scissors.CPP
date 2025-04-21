#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enGameChoice {Stone = 1, Paper = 2, Scissors = 3};

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice = Stone;
	enGameChoice ComputerChoice = Stone;
	enWinner Winner = Draw;
	string WinnerName = "";
};

struct stGameResults
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner = Draw;
	string WinnerName = "";
};

short RandomNumber(short From, short To)
{
	return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

short ReadNumber(short From, short To, string Message)
{
	short Number = 0;

	do
	{
		cout << Message;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');

			cout << "That is not a Number, Enter a Number ";
			cin >> Number;
		}
	} while (Number < From || Number > To);

	return Number;

}

enGameChoice GetPlayerChoice()
{
	return (enGameChoice)ReadNumber(1, 3, "\nPlease choose between 1\\stone, 2\\Paper, 3\\Scissors\n");
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice)
		return enWinner::Draw;

	else if ((RoundInfo.ComputerChoice - RoundInfo.PlayerChoice == 1 || RoundInfo.ComputerChoice - RoundInfo.PlayerChoice == -2))
		return enWinner::Computer;

	else return enWinner::Player;
}

enWinner WhoWonTheGame(stGameResults &GameResults)
{
	if (GameResults.ComputerWinTimes > GameResults.PlayerWinTimes)
		return (enWinner)Computer;

	else if (GameResults.ComputerWinTimes < GameResults.PlayerWinTimes)
		return (enWinner)Player;

	else return (enWinner)Draw;
}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
	return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "The Player", "The Computer", "No Winner (Draw)" };
	return arrWinnerName[Winner - 1];
}

void FillRoundInfo(stRoundInfo &RoundInfo)
{
	RoundInfo.RoundNumber++;
	RoundInfo.PlayerChoice   = GetPlayerChoice();
	RoundInfo.ComputerChoice = GetComputerChoice();
	RoundInfo.Winner         = WhoWonTheRound(RoundInfo);
	RoundInfo.WinnerName     = WinnerName(RoundInfo.Winner);
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case Player:
		system("color 2F");
		break;
	case Computer:
		system("color 4F");
		break;
	default:
		system("color 6F");
		break;
	}
}

void PrintRoundInfo(stRoundInfo &RoundInfo)
{
	cout << "\n-------------------------------------'n";
	cout << "\nRound             : " << RoundInfo.RoundNumber;
	cout << "\nPlayer Choice is  : " << ChoiceName(RoundInfo.PlayerChoice);
	cout << "\nComputer Choice is: " << ChoiceName(RoundInfo.ComputerChoice);
	cout << "\nThe Winner is     : " << RoundInfo.WinnerName;
	cout << "\n-------------------------------------'n";
	SetWinnerScreenColor(RoundInfo.Winner);
}

void PrintGameResults(stGameResults &GameResults)
{
	cout << "\n---------------------------------------------";
	cout << "\nFinal Results     :";
	cout << "\nTotal Rounds are  : "    << GameResults.GameRounds;
	cout << "\nPlayer won times  : "       << GameResults.PlayerWinTimes;
	cout << "\nComputer won times: "     << GameResults.ComputerWinTimes;
	cout << "\nDraw times        : "           << GameResults.DrawTimes;
	cout << "\nThe Winner is     : "       << GameResults.WinnerName;
	cout << "\n---------------------------------------------\n";
}

void PlayGame()
{
	stRoundInfo RoundInfo;
	stGameResults GameResults;
	short Rounds = ReadNumber(1, 10, "How many rounds do you want to play ? (1 - 10) \n");

	for (short X = 1; X <= Rounds; X++)
	{
		FillRoundInfo(RoundInfo);
		PrintRoundInfo(RoundInfo);

		GameResults.GameRounds = X;

		if (RoundInfo.Winner == Player)
			GameResults.PlayerWinTimes++;

		else if (RoundInfo.Winner == Computer)
			GameResults.ComputerWinTimes++;

		else GameResults.DrawTimes++;

	}

	GameResults.GameWinner = WhoWonTheGame(GameResults);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	SetWinnerScreenColor(GameResults.GameWinner);


	PrintGameResults(GameResults);
}

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();

		PlayGame();

		cout << "\nDo you want to play again? (Y/N):";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();
	system("pause>0");
}