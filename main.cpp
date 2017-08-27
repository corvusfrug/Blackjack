#include "func.h"
//#include "func.cpp"

extern const int MAX_PLAYERS=4;
extern vector<karta> koloda;
extern vector<player> players;
extern int col_player;
extern int col_kart;
extern int player_in_game;
extern player viner;
extern bool end_game_flag;

int main(int argv, char* argc[])
{
    setlocale(LC_ALL, "Russian");
    intro();
    input_koloda();
    mix_koloda();
    deal();
    //output_players();
    end_game_flag=false;

    dealer_ii();
    int i;
    while(1)
    {
        output_players();
        i=1;
        while(i<col_player)
        {
            if(players[i].in_game)
            {
                output_players();
                cout << players[i].name << " ходит! ";
                moove(_getch(),i);
                Sleep(1000);
                if(end_game_flag) break;
                if(player_in_game<=0) break;
            } else i++;
        };
        if(end_game_flag) break;
        if(player_in_game<=0) break;
    };
    output_players();
    fin();
    //output_koloda();
    //system("pause");
    return 0;
};


