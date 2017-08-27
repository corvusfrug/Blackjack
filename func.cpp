#include "func.h"

const int MAX_PLAYERS=4;
vector<karta> koloda;
vector<player> players;
int col_player;
int col_kart;
int player_in_game;
player viner;
bool end_game_flag;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Для цвету

karta::karta(int x, mast_type y)
{
    nominal=x;
    mast=y;
};

karta::karta() {};

player::player()
{
    name="";
    score=0;
};

void karta::print_karta()
{
    if((mast==2)||(mast==3)) SetConsoleTextAttribute(hStdOut,4);
    if(nominal<11) cout << " " << nominal << " ";
    else
    {
        if(nominal==11) cout << " ВАЛЕТ ";
        if(nominal==12) cout << " ДАМА ";
        if(nominal==13) cout << " КОРОЛЬ ";
        if(nominal==14) cout << " ТУЗ ";
    };
    if(mast==0) cout << (char)6 << "  ";
    if(mast==1) cout << (char)5 << "  ";
    if(mast==2) cout << (char)3 << "  ";
    if(mast==3) cout << (char)4 << "  ";
    SetConsoleTextAttribute(hStdOut,7);
};

void input_koloda()
{
    end_game_flag=false;
    for(int i=2; i<15; i++)
        for(int j=0 ; j<4; j++)
        {

            koloda.push_back(karta(i,(mast_type)j));
        };
    col_kart=52;
};


void output_koloda()
{
    for(int i=0; i<koloda.size(); i++) koloda[i].print_karta();
};


void intro()
{
    //system("color F0");
    col_player=2;
    cout << "\n\n\n\n\n\n\n\n\t\tПриветствуем в игре \"21\" она же Блекджек\n";
    cout << "\t\t \"W\" - ЕЩЕ, \"S\" - ХВАТИТ, \"Q\" - ПАС\n";
    cout << "\t\tВведите количество игроков (по умолчанию 1) : ";
    cin >> col_player;
    if((col_player<1)||(col_player>MAX_PLAYERS))
    {
        if(col_player>MAX_PLAYERS)
            cout << "\n\n\t\tМноговато, значит сыграешь в одиночестве\n";
        else
            cout << "\n\n\t\tТак не бывает, сыграешь один(на)\n";
        col_player=1;
    };
    col_player++;
    player_in_game=col_player;
    input_player();
};


void input_player()
{
    players.push_back(player());
    players[0].name="Крупье";
    players[0].in_game=true;
    players[0].pas=false;
    for(int i=1; i<col_player; i++)
    {
        players.push_back(player());
        cout << "\t\tВведите имя " << i << "-го игрока: ";
        cin >> players[i].name;
        players[i].in_game=true;
        players[i].pas=false;
        cout << endl;
    };
    system("cls");
};


void mix_koloda()
{
    srand(time(NULL));
    karta temp;
    int n=51,y,i=0;
    while(n>0)
    {
        temp=koloda[i];
        y=rand()%(n--);
        koloda[i++]=koloda[y];
        koloda[y]=temp;
    }
};

karta choose_karta()
{
    int temp_num = rand()%(col_kart-1);
    karta temp_kart=koloda[temp_num];

    koloda[temp_num]=koloda[col_kart-1];
    koloda.pop_back();

    col_kart--;
    return temp_kart;

};


void deal()
{
    viner.score=0;
    for(int i=0; i<col_player; i++)
    {
        for(int j=0; j<2; j++)
        {
            players[i].nabor.push_back(choose_karta());
            if(players[i].nabor[j].nominal<11)
            {
                players[i].score+=players[i].nabor[j].nominal;
                if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
            }
            else
                switch(players[i].nabor[j].nominal)
                {
                case 11:
                    players[i].score+=2;
                    if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
                    break;
                case 12:
                    players[i].score+=3;
                    if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
                    break;
                case 13:
                    players[i].score+=4;
                    if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
                    break;
                case 14:
                    if(players[i].score+11>21)
                    {
                        players[i].score+=1;
                        if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
                    }
                    else
                    {
                        players[i].score+=11;
                        if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
                    };
                    break;
                };
        };
    };
};

void output_players()
{
    system("cls");
    for(int i=0; i<col_player; i++)
    {
        cout << "\n" << players[i].name << ":\n";
        for(int j=0; j<players[i].nabor.size(); j++)
        {
            players[i].nabor[j].print_karta();
            if((j<players[i].nabor.size()-1)) cout << "|";
        };

        if(players[i].score>21) cout << "\n ПЕРЕБОР!\n";
        else if(!players[i].in_game)
            if(players[i].pas) cout << "\n ПАС!\n";
            else if(players[i].score==21) cout << "\n ОЧКО!\n";
            else cout << "\n Набрал: " << players[i].score << " очков, ему ХВАТИТ!\n";
        else cout << "\n Набрал: " << players[i].score << " очков\n";

        cout << "______________________________\n";
    };
};

void moove(int comand,int i)
{

    if(comand==27)
    {
        end_game_flag=true;
        return;
    }; // Escape

    switch(comand)
    {

    case 230:
        player_add_kart(i);
        if(players[i].in_game) cout << " " << players[i].name << " берет еще карту" << endl;
        break;
    case 119:
        player_add_kart(i);
        if(players[i].in_game) cout << " " << players[i].name << " берет еще карту" << endl;
        break;
    case 87:
        player_add_kart(i);
        if(players[i].in_game) cout << " " << players[i].name << " берет еще карту" << endl;
        break;
    case 150:
        player_add_kart(i);
        if(players[i].in_game) cout << " " << players[i].name << " берет еще карту" << endl;
        break;


    case 235:
        players[i].in_game=false;
        player_in_game--;
        if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
        cout << " " << players[i].name << " считает, что этого хватит" << endl;
        break;
    case 115:
        players[i].in_game=false;
        player_in_game--;
        if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
        cout << " " << players[i].name << " считает, что этого хватит" << endl;
        break;
    case 83:
        players[i].in_game=false;
        player_in_game--;
        if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
        cout << " " << players[i].name << " считает, что этого хватит" << endl;
        break;
    case 155:
        players[i].in_game=false;
        player_in_game--;
        if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
        cout << " " << players[i].name << " считает, что этого хватит" << endl;
        break;

    case 169:
        if((players[i].name==viner.name)&&(players[i].score==viner.score))
        {
            viner.score=-1;
            viner.name=="";
        };
        players[i].in_game=false;
        players[i].pas=true;
        //players[i].score=0;
        player_in_game--;
        cout << " " << players[i].name << " пасует" << endl;
        break;
    case 137:
        if((players[i].name==viner.name)&&(players[i].score==viner.score))
        {
            viner.score=-1;
            viner.name=="";
        };
        players[i].in_game=false;
        players[i].pas=true;
        //players[i].score=0;
        player_in_game--;
        cout << " " << players[i].name << " пасует" << endl;
        break;
    case 113:
        if((players[i].name==viner.name)&&(players[i].score==viner.score))
        {
            viner.score=-1;
            viner.name=="";
        };
        players[i].in_game=false;
        players[i].pas=true;
        //players[i].score=0;
        player_in_game--;
        cout << " " << players[i].name << " пасует" << endl;
        break;
    case 81:
        if((players[i].name==viner.name)&&(players[i].score==viner.score))
        {
            viner.score=-1;
            viner.name=="";
        };
        players[i].in_game=false;
        players[i].pas=true;
        //players[i].score=0;
        player_in_game--;
        cout << " " << players[i].name << " пасует" << endl;
        break;

    default:
        cout << " ERROR!" << endl;
        break;
    };
};


void player_add_kart(int i)
{
    players[i].nabor.push_back(choose_karta());
    if(players[i].nabor[players[i].nabor.size()-1].nominal<11)
    {
        players[i].score+=players[i].nabor[players[i].nabor.size()-1].nominal;
        if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
    }
    else
        switch(players[i].nabor[players[i].nabor.size()-1].nominal)
        {
        case 11:
            players[i].score+=2;
            if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
            break;
        case 12:
            players[i].score+=3;
            if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
            break;
        case 13:
            players[i].score+=4;
            if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
            break;
        case 14:
            if(players[i].score+11>21)
            {
                players[i].score+=1;
                if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
            }
            else
            {
                players[i].score+=11;
                if((players[i].score>viner.score)&&(players[i].score<=21)) viner=players[i];
            };
            break;
        };
    if(players[i].score>21)
    {
        cout << " " << players[i].name << " берет еще карту" << endl;
        cout << "У " << players[i].name << " перебор\n";
        players[i].in_game=false;
        player_in_game--;
        players[i].pas=true;
        //players[i].score=0;
        if((players[i].name==viner.name))
        {
            viner.score=-1;
            viner.name=="";
        };
    };
    if(players[i].score==21)
    {
        cout << " " << players[i].name << " берет еще карту" << endl;
        cout << "У " << players[i].name << " ОЧКО\n";
        players[i].in_game=false;
        end_game_flag=true;
        viner=players[i];
    };
};


void fin()
{
    if(viner.score!=-1)
    {
        cout << "Победил игрок: " << viner.name;
        if(viner.score==21) cout << " первым набрав Блекджек! Поздравляем!!!\n";
        else cout << " набравшим наибольшее количество очков ( " << viner.score << " очков )\n";
    }
    else cout << "Победитель отсутствует!\n";
    cout << "НЕ ИГРАЙТЕ В АЗАРТНЫЕ ИГРЫ!";

};


void dealer_ii()
{
    bool flag=false;
    output_players();
    cout << " Ход " << players[0].name << ":\n";
    //Sleep(1000);
    while(1)
    {
        Sleep(1000);
        if(flag) break;
        output_players();
        //Sleep(1000);
        if(players[0].score<8)
        {
            cout << " " << players[0].name << " думает...\n";
            Sleep(3000);
            moove(230,0);
            Sleep(1000);
        }
        else if(players[0].score<14)
        {
            cout << " " << players[0].name << " думает...\n";
            Sleep(4000);
            moove(230,0);
            Sleep(1000);
        }
        else if(players[0].score<16)
        {
            cout << " " << players[0].name << " колеблется...\n";
            Sleep(6000);
            int delema = rand()%2;
            if(delema==1)
            {
                moove(230,0);
                Sleep(1000);
            }
            else
            {
                Sleep(2000);
                moove(235,0);
                flag=true;
                Sleep(2000);
            };
        }
        else
        {
            cout << " " << players[0].name << " думает...\n";
            Sleep(2000);
            moove(235,0);
            flag=true;
        };
    };

};
