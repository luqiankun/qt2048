#include "game.h"
#include <iomanip>
#include <conio.h>
#include <ctime>

Game::Game()
{

}
bool Game::LOSE()
{
    bool lose=true;//标志位
    //出现0，表示还未结束
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j <4; j++)
        {

            if (this->BoardList[i][j] == 0)
            {
                lose = false;
                return false;
            }
        }
    }
    //横竖相邻元素相等未结束
    for (size_t i = 0; i < 4 - 1; i++)
    {
        for (size_t j = 0; j < 4 - 1; j++)
        {
            if (this->BoardList[i][j]== this->BoardList[i][j+1]&& this->BoardList[i][j]!=0)
            {
                return false;
            }
            if (this->BoardList[j][i]== this->BoardList[j+1][i]&& this->BoardList[j][i]!=0)
            {
                lose = false;
                return false;
            }
        }
    }
    if (lose)
    {
        return true;
    }
    return false;
}

bool Game::WIN()
{
    for (size_t i = 0; i <4; i++)
    {
        for (int j = 0; j <4; ++j)
        {
            //出现2048，即为赢
            if (this->BoardList[i][j]==2048)
            {
                return true;
            }

        }
    }
    return false;
}
bool Game::AddBoard()
{
    int choice[] = { 4, 2, 4, 4, 2, 2, 2, 2 };//可以调节2和4出现的频率
    //srand(time(0));
    int temp = (rand() % int((sizeof(choice)/sizeof (choice[0]) - 0))) + 0;
    int p1 = rand() % 4;
    int p2 = rand() % 4;
    while (this->BoardList[p1][p2] != 0)//位置已有数字，重新选取
    {
        p1 = rand() % 4;
        p2 = rand() % 4;
    }
    this->BoardList[p1][p2] = choice[temp];
    this->ADD = false;
    return true;
}

void Game::Up()
{
    for (size_t i = 0; i <4; i++)
    {
        for (size_t t = 0; t <4; t++)
        {
            for (size_t j = 0; j <4 - 1; j++)
            {
                if (this->BoardList[j][i] == 0)
                {
                    if (this->BoardList[j + 1][i]!=0)
                    {
                        this->ADD = true;
                    }
                    auto temp = this->BoardList[j][i];
                    this->BoardList[j][i] = this->BoardList[j + 1][i];
                    this->BoardList[j + 1][i] = temp;
                }
            }
        }
        // 2、合并同类项
        for (size_t j = 0; j < 4 - 1; j++)
        {
            // 2 2 2 2 ->4 0 2 2 ->4 0 4 0
            // 2 2 2 0 -> 4 0 2 0
            if (this->BoardList[j][i] == this->BoardList[j + 1][i])
            {
                if (this->BoardList[j][i]!=0)
                {
                    this->ADD = true;
                }
                this->BoardList[j][i] = this->BoardList[j][i] * 2;
                this->Scroe = this->BoardList[j][i] + this->Scroe;
                this->BoardList[j + 1][i] = 0;
            }
        }
        //3、 再次移动0元素
        for (size_t t = 0; t < 4; t++)
        {
            for (size_t j = 0; j < 4 - 1; j++)
            {
                // 0 2 0 2 -> 2 2 0 0
                if (this->BoardList[j][i] == 0)
                {
                    auto temp = this->BoardList[j][i];
                    this->BoardList[j][i] = this->BoardList[j + 1][i];
                    this->BoardList[j + 1][i] = temp;
                }
            }
        }
    }
    if (this->LOSE() || this->WIN())
    {}
    else
    {
        if (this->ADD)
        {

            this->AddBoard();
            this->ADD = false;
        }
    }
}

void Game::Down()
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t t = 4; t>0; t--)
        {
            for (size_t j = 4 - 1; j >0; j--)
            {
                if (this->BoardList[j][i] == 0)
                {
                    if (this->BoardList[j - 1][i] != 0)
                    {
                        this->ADD = true;
                    }
                    auto temp = this->BoardList[j][i];
                    this->BoardList[j][i] = this->BoardList[j - 1][i];
                    this->BoardList[j - 1][i] = temp;
                }
            }
        }
        // 2、合并同类项
        for (size_t j =4 - 1; j>0; j--)
        {
            // 2 2 2 2 ->4 0 2 2 ->4 0 4 0
            // 2 2 2 0 -> 4 0 2 0
            if (this->BoardList[j][i] == this->BoardList[j - 1][i])
            {
                if (this->BoardList[j][i] != 0)
                {
                    this->ADD = true;
                }
                this->BoardList[j][i] = this->BoardList[j][i] * 2;
                this->Scroe = this->BoardList[j][i] + this->Scroe;
                this->BoardList[j - 1][i] = 0;
            }
        }
        //3、 再次移动0元素
        for (size_t t =4; t >0; t--)
        {
            for (size_t j =4 - 1; j >0; j--)
            {
                // 0 2 0 2 -> 2 2 0 0
                if (this->BoardList[j][i] == 0)
                {
                    auto temp = this->BoardList[j][i];
                    this->BoardList[j][i] = this->BoardList[j - 1][i];
                    this->BoardList[j - 1][i] = temp;
                }
            }
        }
    }
    if (this->LOSE() || this->WIN())
    {}
    else
    {
        if (this->ADD)
        {

            this->AddBoard();
            this->ADD = false;
        }
    }
}

void Game::Left()
{
    for (size_t j= 0; j <4; j++)
    {
        //1、先移动每行0元素（出现0就交换）,最多交换size(this->BoardList)次
        for (size_t t = 0; t <4; t++)
        {
            for (size_t i = 0; i <4 - 1; i++)
            {
                // 0 2 0 2 ->2 0 2 0
                if (this->BoardList[j][i] == 0)
                {
                    // 发生了移动，添加棋子标志位置真
                    if (this->BoardList[j][i + 1]!=0)
                    {
                        this->ADD = true;
                    }
                    auto temp = this->BoardList[j][i];
                    this->BoardList[j][i] = this->BoardList[j][i + 1];
                    this->BoardList[j][i + 1] = temp;
                }
            }
        }
        // 2、合并同类项
        for (size_t i = 0; i <4 - 1; i++)
        {
            // 2 2 2 2 ->4 0 2 2 ->4 0 4 0
            // 2 2 2 0 -> 4 0 2 0
            if (this->BoardList[j][i]== this->BoardList[j][i+1])
            {
                // 发生了合并，添加棋子标志位置真
                if (this->BoardList[j][i]!=0)
                {
                    this->ADD = true;
                }
                this->BoardList[j][i] = this->BoardList[j][i] * 2;
                this->Scroe = this->BoardList[j][i] + this->Scroe;
                this->BoardList[j][i + 1] = 0;
            }
        }
        //3、 再次移动0元素 4 0 2 0 -> 4 2 0 0
        for (size_t t = 0; t < 4; t++)
        {
            for (size_t i = 0; i <4 - 1; i++)
            {
                // 0 2 0 2 -> 2 2 0 0
                if (this->BoardList[j][i] == 0)
                {
                    auto temp = this->BoardList[j][i];
                    this->BoardList[j][i] = this->BoardList[j][i + 1];
                    this->BoardList[j][i + 1] = temp;
                }
            }
        }
    }
    //赢了或者输了就不再添加
    if (this->LOSE()||this->WIN())
    {}
    else
    {
        if (this->ADD)
        {

            this->AddBoard();
            this->ADD = false;
        }
    }
}

void Game::Right()
{
    for (size_t j = 0; j < 4; j++)
    {
        //1、先移动每行0元素
        for (size_t t = 4; t >0;t--)
        {
            for (size_t i =4 - 1; i>0; i--)
            {
                if (this->BoardList[j][i] == 0)
                {
                    if (this->BoardList[j][i - 1]!=0)
                    {
                        this->ADD = true;
                    }
                    auto temp = this->BoardList[j][i];
                    this->BoardList[j][i] = this->BoardList[j][i - 1];
                    this->BoardList[j][i - 1] = temp;
                }
            }
        }
        // 2、合并同类项
        for (size_t i =4 - 1; i >0; i--)
        {
            if (this->BoardList[j][i] == this->BoardList[j][i - 1])
            {
                if (this->BoardList[j][i] != 0)
                {
                    this->ADD = true;
                }
                this->BoardList[j][i] = this->BoardList[j][i] * 2;
                this->Scroe = this->BoardList[j][i] + this->Scroe;
                this->BoardList[j][i - 1] = 0;
            }
        }
        //3、 再次移动0元素
        for (size_t t =4; t > 0; t--)
        {
            for (size_t i = 4 - 1; i > 0; i--)
            {
                // 0 2 0 2 -> 2 2 0 0
                if (this->BoardList[j][i] == 0)
                {
                    auto temp = this->BoardList[j][i];
                    this->BoardList[j][i] = this->BoardList[j][i - 1];
                    this->BoardList[j][i - 1] = temp;
                }
            }
        }
    }
    //赢了或者输了就不再添加
    if (this->LOSE() || this->WIN())
    {}
    else
    {
        if (this->ADD)
        {

            this->AddBoard();
            this->ADD = false;
        }
    }
}

void Game::Restart()
{
    this->Scroe = 0;//初始分数
    this->ADD = false;//是否添加棋子
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            this->BoardList[i][j] =0;
        }
    }
    this->AddBoard();
    this->AddBoard();
}
