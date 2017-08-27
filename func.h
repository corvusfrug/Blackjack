#ifndef FUNCtt_H
#define FUNCtt_H

#include <iostream>
#include <clocale>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::srand;
using std::time;
using std::rand;

enum mast_type {piki=0, kresti,cherva,bubna};

struct karta
{
        int nominal;
        mast_type mast;
        karta(int,mast_type);
        karta();
        void print_karta();
};
struct player
{
        string name;
        int score;
        bool in_game;
        bool pas;
        vector<karta> nabor;
        player();
};

void intro();
void input_player();
void input_koloda();
void mix_koloda();
void output_koloda(); //test
karta choose_karta();
void deal();
void output_players();
void moove(int,int);
void player_add_kart(int);
void fin();
void dealer_ii();

#endif
