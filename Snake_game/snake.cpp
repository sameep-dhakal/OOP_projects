#include <iostream>
#include <conio.h>
#include <windows.h>

#define max_length 50

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void set_vector(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

char accept_char(char op)
{
    if (op == 'w' || op == 'W' || op == 'a' || op == 'A' || op == 'd' || op == 'D' || op == 's' || op == 'S')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
class cons_vector
{
    int x;
    int y;

public:
    cons_vector()
    {
        x = y = rand() % 30;
    }
    cons_vector(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void SetPoint(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void MoveUp()
    {
        y--;
    }
    void MoveDown()
    {
        y++;
    }
    void MoveRight()
    {
        x++;
    }
    void MoveLeft()
    {
        x--;
    }
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }
    void fig_snake()
    {
        set_vector(x, y);
        cout << "*";
    }
    void fig_fruit()
    {
        set_vector(x, y);
        cout << "@";
    }
    void Copy_position(cons_vector *p)
    {
        p->x = x;
        p->y = y;
    }
};

class Snake
{
    cons_vector *cell[max_length];
    int size;
    cons_vector fruit;

public:
    Snake()
    {
        size = 1;
        cell[0] = new cons_vector(rand() % 50, rand() % 25);
        for (int i = 1; i < max_length; i++)
        {
            cell[i] = NULL; // Making cell of array null except cell 0.
        }
        fruit.SetPoint(rand() % 50, rand() % 25);
    }
    void Grow()
    {
        if (size < max_length)
        {
            cell[size++] = new cons_vector(0, 0);
        }
    }
    void TurnUp()
    {
        cell[0]->MoveUp();
    }
    void TurnDown()
    {
        cell[0]->MoveDown();
    }
    void TurnRight()
    {
        cell[0]->MoveRight();
    }
    void TurnLeft()
    {
        cell[0]->MoveLeft();
    }
    int check_hit()
    {
        for (int i = 1; i < size; i++)
        {
            if (cell[i]->get_x() == cell[0]->get_x() && cell[i]->get_y() == cell[0]->get_y())
            {
                return 0;
            }
        }
        return 1;
    }

    void move()
    {
        for (int i = size - 1; i > 0; i--)
        {
            cell[i - 1]->Copy_position(cell[i]);
        }

        if (fruit.get_x() == cell[0]->get_x() && fruit.get_y() == cell[0]->get_y())
        {
            Grow();
            fruit.SetPoint(rand() % 50, rand() % 25);
        }

        for (int i = 0; i < size; i++)
            cell[i]->fig_snake();
        fruit.fig_fruit();

        Sleep(100);
    }
    int get_size()
    {
        return size;
    }
};

int main()
{
    Snake snake;
    int z;
    char op = 'w';

    cout << "Welcome to Snake Game" << endl;
    cout << "Controls" << endl;
    cout << "w -> Up" << endl;
    cout << "s -> Down" << endl;
    cout << "a -> Left" << endl;
    cout << "d -> Right" << endl;
    cout << "Stay within the console" << endl;
    cout << "Press any key to continue";
    getch();
    do
    {

        system("cls");
        if (kbhit())
        {
            op = getch();
        }

        switch (op)
        {
        case 'w':
        case 'W':
            snake.TurnUp();
            break;
        case 's':
        case 'S':
            snake.TurnDown();
            break;
        case 'a':
        case 'A':
            snake.TurnLeft();
            break;
        case 'd':
        case 'D':
            snake.TurnRight();
            break;
        }
        z = snake.check_hit();
        snake.move();

    } while (accept_char(op) == 1 && z == 1);
    system("cls");
    cout << "Score =" << snake.get_size() - 1;
    return 0;
}