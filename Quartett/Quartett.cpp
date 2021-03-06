#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <utility>

//Defining a globally used struct, so it won't be newly declared everytime 
//the "Game" function gets used
typedef struct Card
{
  char name[50];
  int fighting;
  double age;
  struct Card* pNext;
} StruCard;

//Defining the input parameters for the functions
int Game(int);
StruCard* AddCard(StruCard* pStart, StruCard* pNew);
StruCard* CreateCard(const char* bez, int par1, double par2);
void OutputList(StruCard* pStart);
StruCard** ShuffleCards(StruCard* pStart);
int Randomizer(int);
int LesserThan(StruCard*, StruCard*,short);
int GreaterThan(StruCard*, StruCard*, short);
int AI(StruCard*, StruCard*);
int DumbAI(StruCard*, StruCard*);
int PlayerMenuIG(StruCard*, StruCard*, short, bool);
int CardCounter(StruCard*);



//The "main" function will help us set what the game function does.
//Therefore we will declare a [bool] array which is given to the "Game" function.
//The "main" function is mostly used for menus which appear b4 the actual game.
int main()
{
  int menuinput;
  int menuinputdifficulty;
  printf("Hello Player!\nThis is the best \x22Star Wars Quartett\x22\n");
  printf("Are you playing for the first time?\nYes = [1], No = [2]\n");
  scanf_s("%d", &menuinput);
  if (menuinput == 1)
  {
    printf("The Rules of \x22Quartett\x22 are:\nYou get 5 cards from the deck at the start of the game.\n");
    printf("You play with one opponent, who also draws 5 cards at the start, therefore the deck contains 10 cards.\n");
    printf("You then take the card off of the top of your bunch, thats when the game begins.\n");
    printf("When it is your turn, you choose either one of your stats of the card and decide if you bet higher or lower.\n");
    printf("Then this stat gets compared to your opponents, if you bet right, you win the round and their card.\n");
    printf("These two cards go to the bottom of your bunch. Then your opponent gets to choose.\n");
    printf("The victor is decided by whom collets all the cards\n");
    system("pause");
    system("cls");
  }
  difficultyselection:
  system("cls");
  printf("Do you want to play HARD [1] or easy [2] difficulty? \n");
  scanf_s("%d", &menuinputdifficulty);
  if (menuinputdifficulty > 3 || menuinputdifficulty < 0)
  {
    goto difficultyselection;
  }
  int again = 1;
  while (again == 1)
  {
    again = Game(menuinputdifficulty);
    if (menuinputdifficulty == 1)
    {
      printf("Do you want to try easy difficulty?\n Yes = [1] No = [2]");
      scanf_s("%d", &menuinput);
      if (menuinput == 1)
      {
        menuinputdifficulty = 2;
      }
    }
    else
    {
      printf("Do you want to try HARD difficulty?\n Yes = [1] No = [2]");
      scanf_s("%d", &menuinput);
      if (menuinput == 1)
      {
        menuinputdifficulty = 1;
      }
    }
  }
  printf("\nThank you for playing!\n");
  system("Pause");
}

//The "Game" function is the function which will handle 
//generating the cards, defining whose turn it is, starting other 
//functions and handing cards back and forth to the winner of each round.
int Game(int difficulty)
{
  StruCard* pStartPlayer = NULL;
  StruCard* pStart = NULL;
  pStart = AddCard(pStart, CreateCard("Sheev Palpatine", 41, 63.6));
  pStart = AddCard(pStart, CreateCard("Anakin Skywalker", 39, 22.5));
  pStart = AddCard(pStart, CreateCard("Darth Vader", 42, 22.6));
  pStart = AddCard(pStart, CreateCard("Obi-Wan Kenobi", 35, 38.1));
  pStart = AddCard(pStart, CreateCard("Mace Windu", 43, 53.7));
  pStart = AddCard(pStart, CreateCard("Jar Jar Binks", 25, 33.3));
  pStart = AddCard(pStart, CreateCard("Yoda", 40, 877.0));
  pStart = AddCard(pStart, CreateCard("Darth Maul", 33, 35.3));
  pStart = AddCard(pStart, CreateCard("Chewbacca", 30, 181.9));
  pStart = AddCard(pStart, CreateCard("Count Dooku", 38, 83.2));
  StruCard** ListOfStarts = ShuffleCards(pStart);
  pStart = ListOfStarts[0];
  pStartPlayer = ListOfStarts[1];
  bool PlayerTurn = true;
  int Result = 0;
  while (pStartPlayer != NULL && pStart != NULL)
  {
    if (PlayerTurn == true)
    {
      Result = PlayerMenuIG(pStartPlayer, pStart, 0, PlayerTurn);
      PlayerTurn = false;
    }
    else if (PlayerTurn == false)
    {
      if (difficulty == 1)
      {
        Result = AI(pStart, pStartPlayer);
      }
      else
      {
        Result = DumbAI(pStart, pStartPlayer);
      }
      PlayerTurn = true;
    }
    if (Result == 0)
    {
      //First card of the computer gets added to player's list
      //and player's first card gets put to the end if its list.
      StruCard* pEnd = pStart;
      StruCard* pTmp = pStartPlayer;
      pStart = pStart->pNext;
      pStartPlayer = pStartPlayer->pNext;
      pEnd->pNext = pTmp;
      pTmp->pNext = NULL;
      pTmp = pEnd;
      pEnd = pStartPlayer;
      while (pEnd->pNext != NULL)
        pEnd = pEnd->pNext;
      pEnd->pNext = pTmp;

      printf("\nYou won the round!\n");
      system("pause");
      system("cls");
    }
    else if (Result == 1)
    {
      //First card of the player gets added to computer's list
      //and computer's first card gets put to the end if its list.
      StruCard* pEnd = pStartPlayer;
      StruCard* pTmp = pStart;
      pStart = pStart->pNext;
      pStartPlayer = pStartPlayer->pNext;
      pEnd->pNext = pTmp;
      pTmp->pNext = NULL;
      pTmp = pEnd;
      pEnd = pStart;
      while (pEnd->pNext != NULL)
        pEnd = pEnd->pNext;
      pEnd->pNext = pTmp;


      printf("\nYou lost this round...\n");
      system("pause");
      system("cls");
    }
  }
  if (pStart == NULL)
    printf("Congratulations, you win the Game!\n");

  else if (pStartPlayer == NULL)
    printf("You lose the Game\n.");


  printf("Do you want to play again? \nYes = [1] No = [2]\n");
  int again;
  scanf_s("%i", &again);
  if (again == 1)
  {
    return 1;
  }
  return 0;
}

//Adds the cards to the first list
StruCard* AddCard(StruCard* pStart, StruCard* pNew)
{
  pNew->pNext = NULL;
  if (pStart == NULL) { //empty list
    pStart = pNew;
  }
  else {
    StruCard* pLast = pStart;
    while (pLast->pNext != NULL) pLast = pLast->pNext;
    pLast->pNext = pNew;
  }
  return pStart;
}

//Creates the cards
StruCard* CreateCard(const char* name, int par1, double par2)
{
  StruCard* newCard = (StruCard*)malloc(sizeof(StruCard));
  strcpy_s(newCard->name, 50, name);
  newCard->fighting = par1;
  newCard->age = par2;
  return newCard;
}

//Outputs the list
void OutputList(StruCard* pStart)
{
  for (StruCard* pTmp = pStart; pTmp != NULL; pTmp = pTmp->pNext)
    printf("Name = %s\n", pTmp->name);
}

//Shuffles the cards and gives 5 to the player and 5 to the computer
StruCard** ShuffleCards(StruCard* pStart)
{
  StruCard* pSelection = pStart;
  StruCard* pStartPlayer = NULL;
  StruCard* pSelectionPlayer = NULL;
  StruCard* pSavePlayer = NULL;
  int RandomizerVar = 0;

  //Attach the last element of the list to the first
  while (pSelection->pNext != NULL)
  {
    pSelection = pSelection->pNext;
  }
  pSelection->pNext = pStart;

  //Pick out 5 cards
  for (int index = 0; index < 5; index++)
  {
    RandomizerVar = Randomizer(10);
    if (RandomizerVar == 0)
      RandomizerVar = 10;
    for (int inindex = 0; inindex < RandomizerVar; inindex++)
    {
      pSelection = pSelection->pNext;
    }
    //Random Card picked.
    if (pSelection->pNext == pStart)
    {
      pStart = pSelection;
    }
    //first iteration
    if (index == 0)
    {
      pStartPlayer = pSelection->pNext;
      pSelection->pNext = pStartPlayer->pNext;
    }
    //second iteration
    else if (index == 1)
    {
      pStartPlayer->pNext = pSelection->pNext;
      pSelectionPlayer = pStartPlayer->pNext;
      pSelection->pNext = pSelectionPlayer->pNext;
    }
    //third to fifth iteration
    else
    {
      pSelectionPlayer->pNext = pSelection->pNext;
      pSavePlayer = pSelectionPlayer->pNext;
      pSelection->pNext = pSavePlayer->pNext;
      pSelectionPlayer = pSavePlayer;
    }
  }
  while (pSelection->pNext != pStart)
  {
    pSelection = pSelection->pNext;
  }
  pSelection->pNext = NULL;
  pSelectionPlayer->pNext = NULL;

  system("pause");

  //return both starts of the list with a pointer array
  StruCard* Saves[2];
  Saves[0] = pStart;
  Saves[1] = pStartPlayer;
  StruCard** Returnpointer = Saves;
  return Returnpointer;
}

int Randomizer(int range) 
{
  srand(time(NULL));
  return (rand() % range);
}

//Player chose greater than
int GreaterThan(StruCard* LP, StruCard* CP, short stat)
{
  if (stat == 0)
  {
    if (LP->fighting > CP->fighting)
    {
      return 0;
    }
    else
      return 1;

  }
  if (stat == 1)
  {
    if (LP->age > CP->age)
    {
      return 0;
    }
    else
      return 1;
  }
  else
    return 99;
}

//Player chose lesser than
int LesserThan(StruCard* LP, StruCard* CP, short stat)
{
  if (stat == 0)
  {
    if (LP->fighting < CP->fighting)
    {
      return 0;
    }
    else
      return 1;

  }
  if (stat == 1)
  {
    if (LP->age < CP->age)
    {
      return 0;
    }
    else
      return 1;
  }
  else
    return 99;
}

//The Coputer choses the stat to play randomly
//if he choses the fighting stat it looks if its higher or 
//lower than 40 and then choses to play higher or lower.
//The age threshold is at 50 Years.
int AI(StruCard* AICard, StruCard* PlayerCard)
{
  int returncode = 0;
  int StatChooser = Randomizer(2);
  int counter = CardCounter(PlayerCard);
  printf("\nThe computer takes it's turn.");
  printf("\nHere's your Card");
  printf("\n\nName = \t\t%s", PlayerCard->name);
  printf("\n\n");
  printf("Age =\t\t%.1lf \t[1]", PlayerCard->age);
  printf("\nFighting =\t%d \t[2]\n\n", PlayerCard->fighting);
  printf("\nYou:%d", counter);
  printf("\nAI:%d\n", (10 - counter));
  Sleep(2500);

  if (StatChooser == 0)
  {
    if (AICard->fighting <= 40)
    {
      returncode = LesserThan(PlayerCard, AICard, StatChooser);
      printf("\nThe Computer bets lower on fighting!\n\n");
    }
    else
    {
      returncode = GreaterThan(PlayerCard, AICard, StatChooser);
      printf("\nThe Computer bets higher on fighting!\n\n");
    }
  }
  else
  {
    if (AICard->age <= 50)
    {
      returncode = LesserThan(PlayerCard, AICard, StatChooser);
      printf("\nThe Computer bets lower on age!\n\n");
    }
    else
    {
      returncode = GreaterThan(PlayerCard, AICard, StatChooser);
      printf("\nThe Computer bets higher on age!\n\n");
    }
  }
  return returncode;
}

//AI for easy mode
int DumbAI(StruCard* AICard, StruCard* PlayerCard)
{
  int returncode = 0;
  int DumbChooser = Randomizer(4);
  int counter = CardCounter(PlayerCard);
  printf("\nThe computer takes it's turn.");
  printf("\nHere's your Card");
  printf("\n\nName = \t\t%s", PlayerCard->name);
  printf("\n\n");
  printf("Age =\t\t%.1lf \t[1]", PlayerCard->age);
  printf("\nFighting =\t%d \t[2]\n\n", PlayerCard->fighting);
  printf("\nYou:%d", counter);
  printf("\nAI:%d\n", (10 - counter));
  Sleep(2500);

  switch (DumbChooser)
  {
    case 0:
      printf("\nThe Computer bets lower on fighting!\n\n");
      break;
    case 1:
      printf("\nThe Computer bets higher on fighting!\n\n");
      break;
    case 2:
      printf("\nThe Computer bets lower on age!\n\n");
      break;
    case 3:
      printf("\nThe Computer bets higher on age!\n\n");
      break;
    default:
      system("cls");
      printf("You have found a bug in easy mode, please consult the devs with the code 'x569v0'");
      Sleep(100000);
      break;
  }
  if (DumbChooser == 0)
  {
    returncode = 1;
  }
  else
    returncode = 0;

  //ignore all that tbh its gonna be overwritten, it should give the illusion of playing
  return returncode;
}

//This is the function that communicates with the player and takes their input.
//It also starts the comparison if it is the player's turn.
int PlayerMenuIG(StruCard* PlayerCard, StruCard* AICard, short AIHoL, bool turn)
{
    int choiceHL = 0;
    int choiceST = 0;
    int counter = CardCounter(PlayerCard);
    system("cls");
    printf("\nITS YOUR TURN.");
    printf("\nHere's your Card");
    printf("\n\nName = \t\t%s", PlayerCard->name);
    printf("\n\n");
    printf("Age =\t\t%.1lf \t[1]", PlayerCard->age);
    printf("\nFighting =\t%d \t[2]", PlayerCard->fighting);
    printf("\n\nYou:%d", counter);
    printf("\nAI:%d", (10 - counter));
    printf("\n\nWhich stat do you want to bet on? \n");
    wronginputST:
    scanf_s("%d", &choiceST);
    if (choiceST > 2 || choiceST < 1)
    {
      printf("please input [1] or [2] ");
      goto wronginputST;
    }
    printf("\nAre you betting higher [1] or lower [2] ?\n");
    wronginputHL:
    scanf_s("%d", &choiceHL);
    if (choiceHL > 2 || choiceHL <= 0)
    {
      printf("please input [1] or [2] ");
      goto wronginputHL;
    }
    switch (choiceST)
    {
      case 1:
      {
        if (choiceHL == 1)
        {
          return GreaterThan(PlayerCard, AICard, 1);
        }
        else
        {
          return LesserThan(PlayerCard, AICard, 1);
        }
        break;
      }
      case 2:
      {
        if (choiceHL == 1)
        {
          return GreaterThan(PlayerCard, AICard, 0);
        }
        else
        {
          return LesserThan(PlayerCard, AICard, 0);
        }
        break;
      }
      default:
      {
        printf("Please consult the developers, thank you!");
        system("pause");
        return 102;
      }
    }
  }

//counts how many cards the player has n order for the user to know
int CardCounter(StruCard* PlayerCards)
{
  int counter = 1;
  while (PlayerCards->pNext != NULL)
  {
    PlayerCards = PlayerCards->pNext;
    counter++;
  }
  return counter;
}