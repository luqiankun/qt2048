#ifndef GAME_H
#define GAME_H
class Game
{
public:
    int Scroe = 0;//初始分数
    bool ADD = false;//是否添加棋子
    int BoardList[4][4] = {};
    Game();// 构造函数， 初始化一些参数
    bool AddBoard();//添加棋子
    void Up();//上下左右按键事件，都类似，以左按键为母版
    void Down();
    void Right();
    void Left();
    void Restart();//复位
    bool WIN();//判断是否赢了
    bool LOSE();//判断是否输了
};


#endif // GAME_H
