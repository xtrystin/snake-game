#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

const int height = 20;
const int width = 40;
int SnakeX = width / 2 - 1;
int SnakeY = height / 2 - 1;
int FruitX;
int FruitY;
bool FruitEaten = true;
int SnakeSize = 1;
int TailX[100];      
int TailY[100];   
bool DrawTail = false;
bool gameOver = false;
int score = 0;

void Draw()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
          
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                {
                    cout << "*";
                }
                // SNAKE HEAD
                else if (x == SnakeX && y == SnakeY)
                {
                    cout << "O";
                }
                // FRUIT
                else if (x == FruitX && y == FruitY)
                {
                    cout << "F";
                }
                else
                {
                    for (int i = 1; i < SnakeSize; i++)
                    {
                        if (x == TailX[i] && y == TailY[i])
                        {
                            cout << "o";
                            DrawTail = true;
                        }
                    }
                    if ( DrawTail == false)
                    {
                        cout << " ";
                    }
                    DrawTail = false;
                }
            
        }
        cout << endl;
        
    }


}

void Movement()
{

    //TAIL MOV
    int prevX, prevY, prev2X, prev2Y;
     prevX = TailX[0];
     prevY = TailY[0];
    TailX[0]= SnakeX;
    TailY[0] = SnakeY;
   
    for (int i = 0; i < SnakeSize; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }


    if (GetAsyncKeyState(VK_UP))
    {
        SnakeY--;
        
    }
    else if (GetAsyncKeyState(VK_DOWN))
    {
        SnakeY++;
       
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        SnakeX++;
        
    }
    else if (GetAsyncKeyState(VK_LEFT))
    {
        SnakeX--;
        
    }
   
    
    // FRUIT EATEN
    if (SnakeX == FruitX && SnakeY == FruitY)
    {
        FruitEaten = true;
        SnakeSize++;
        score++;
    }
  
}
void Fruit()
{
    
    // GENERATE NEW FRUIT           // CHECK sometimes is not drown!
    if (FruitEaten == true)
    {
        FruitX = rand() % (width - 1) + 1;
        FruitY = rand() % (height - 1) + 1;
        FruitEaten = false;
      //  cout << FruitX << " " << FruitY << endl;
    }
     

}

void Logic()
{
    //HIT WALL
    if (SnakeX == 0 || SnakeX == width - 1 || SnakeY == 0 || SnakeY == height - 1)
    {
        gameOver = true;
    }

    // HIT YOURSELF   
    for (int i = 1; i < SnakeSize; i++)
    {
        if (SnakeX == TailX[1] && SnakeY == TailY[1])
        {
            gameOver == true;
        }
    }
}

int main()
{
    bool first = true;
    srand(time(NULL));

    TailX[0] = SnakeX;
    TailY[0] = SnakeY;

    while (!gameOver)
    {

        if (first == true)
        {
            Fruit();
            Draw();
            first = false;
        }
        // if clicked
        if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT))
        {
            system("cls");
            Movement();
            Fruit();
            Logic();
            Draw();
            Sleep(10);
        }
        
   }
    if (gameOver)
    {
        system("cls");
        cout << "GAME OVER" <<endl;
        cout << "Your score: " << score;
    }
    

    
       
       
    
   


    getchar();
    return 0;
}

