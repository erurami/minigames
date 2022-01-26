

namespace 4InARow
{

class Game
{

    public:

        explicit Game(int width, int height);
        ~Game();

        int GetBoardWidth(void);
        int GetBoardHeight(void);

        int PutCoin(int player, int column);

        int GetGameStatus(void);

        void Print(void);


    private:

}

};

