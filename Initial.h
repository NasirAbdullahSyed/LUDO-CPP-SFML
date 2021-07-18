/*   This is Initial.h which is used for initialization of our game before start and here stays 		all code and information which is needed during the game also*/

#include <iostream>
#include <pthread.h>
#include <mutex>
#include "SFML/Graphics.hpp"
using namespace std;
float radius = 13.f; /// Radius of each Goti
bool cur_done=false;
int size = 4;                // Number of players
vector<int> players;         // Player vector to store selected players
Player *obj = new Player[4]; /// Object of all the players

// Co-ordinates Structure which is send to each thread function to check collision
struct Cords
{
    int x;            // Mouse x
    int y;            // Mouse y
    int player;       // Current player turn
    int goti_no;      // Player Selected Goti
    int check_player; // Player to currently check

    Cords()
    {
        x = 0;
        y = 0;
        player = 0;
        goti_no = 0;
    }

    Cords(int pl, int goti)
    {

        player = pl;
        goti_no = goti;
    }
};

pthread_t *player_threads = new pthread_t[4]; // Threads of each player for collision
pthread_mutex_t player_mutex;                 // Player Mutex

int endLine[4]; // Contains ending coordinates

//////  Player 1

sf::Color player1_col = sf::Color::Red;
int **player1_cord = new int *[4];
int *player1_home = new int[2];
int *player1_start = new int[2];

//////  Player 2
sf::Color player2_col = sf::Color::Blue;
int **player2_cord = new int *[4];
int *player2_home = new int[2];
int *player2_start = new int[2];

//////  Player 3
sf::Color player3_col = sf::Color::Green;
int **player3_cord = new int *[4];
int *player3_home = new int[2];
int *player3_start = new int[2];

//////  Player 4
sf::Color player4_col = sf::Color::Yellow;
int **player4_cord = new int *[4];
int *player4_home = new int[2];
int *player4_start = new int[2];

////  DICE

//1
sf::CircleShape r_1(10.f);

//2
sf::CircleShape r_2_1(10.f);
sf::CircleShape r_2_2(10.f);

//3
sf::CircleShape r_3_1(10.f);
sf::CircleShape r_3_2(10.f);
sf::CircleShape r_3_3(10.f);

//4
sf::CircleShape r_4_1(10.f);
sf::CircleShape r_4_2(10.f);
sf::CircleShape r_4_4(10.f);
sf::CircleShape r_4_3(10.f);

//5
sf::CircleShape r_5_1(10.f);
sf::CircleShape r_5_2(10.f);
sf::CircleShape r_5_3(10.f);
sf::CircleShape r_5_4(10.f);
sf::CircleShape r_5_5(10.f);

//6
sf::CircleShape r_6_1(10.f);
sf::CircleShape r_6_2(10.f);
sf::CircleShape r_6_3(10.f);
sf::CircleShape r_6_4(10.f);
sf::CircleShape r_6_5(10.f);
sf::CircleShape r_6_6(10.f);

void initialize()
{

    // Setting Player numbers in vectors according to size
    players.resize(size);
    players[0] = 0;
    players[1] = 1;
    players[2] = 2;
    players[3] = 3;

    ///End Lines

    endLine[0] = 441; // y
    endLine[1] = 442; // x
    endLine[2] = 311; // x
    endLine[3] = 308; // y

    ////home
    player1_home[0] = 215;
    player1_home[1] = 503;

    player2_home[0] = 500;
    player2_home[1] = 501;

    player3_home[0] = 216;
    player3_home[1] = 219;

    player4_home[0] = 506;
    player4_home[1] = 220;

    /////  start point
    player1_start[0] = 320;
    player1_start[1] = 618;

    player2_start[0] = 619;
    player2_start[1] = 404;

    player3_start[0] = 108;
    player3_start[1] = 323;

    player4_start[0] = 405;
    player4_start[1] = 105;

    for (int i = 0; i < 4; i++)
    {
        player1_cord[i] = new int[2];
        player2_cord[i] = new int[2];
        player3_cord[i] = new int[2];
        player4_cord[i] = new int[2];
    }

    //// Player 1  ////
    player1_cord[0][0] = 172;
    player1_cord[0][1] = 551;

    player1_cord[1][0] = 262;
    player1_cord[1][1] = 551;

    player1_cord[2][0] = 172;
    player1_cord[2][1] = 461;

    player1_cord[3][0] = 262;
    player1_cord[3][1] = 461;

    //// Player 2  ////
    player2_cord[0][0] = 460;
    player2_cord[0][1] = 551;

    player2_cord[1][0] = 550;
    player2_cord[1][1] = 551;

    player2_cord[2][0] = 460;
    player2_cord[2][1] = 461;

    player2_cord[3][0] = 550;
    player2_cord[3][1] = 461;

    //// Player 3  ////
    player3_cord[0][0] = 172;
    player3_cord[0][1] = 268;

    player3_cord[1][0] = 262;
    player3_cord[1][1] = 268;

    player3_cord[2][0] = 172;
    player3_cord[2][1] = 180;

    player3_cord[3][0] = 262;
    player3_cord[3][1] = 180;

    //// Player 4  ////
    player4_cord[0][0] = 460;
    player4_cord[0][1] = 268;

    player4_cord[1][0] = 550;
    player4_cord[1][1] = 268;

    player4_cord[2][0] = 460;
    player4_cord[2][1] = 180;

    player4_cord[3][0] = 550;
    player4_cord[3][1] = 180;

    /////  DICE
    r_1.setFillColor(sf::Color::White);
    r_1.setPosition(632, 92);

    r_2_1.setFillColor(sf::Color::White);
    r_2_1.setPosition(612, 92);
    r_2_2.setFillColor(sf::Color::White);
    r_2_2.setPosition(652, 92);

    r_3_1.setFillColor(sf::Color::White);
    r_3_1.setPosition(612, 108);

    r_3_2.setFillColor(sf::Color::White);
    r_3_2.setPosition(652, 108);

    r_3_3.setFillColor(sf::Color::White);
    r_3_3.setPosition(632, 72);

    r_4_1.setFillColor(sf::Color::White);
    r_4_1.setPosition(612, 112);
    r_4_2.setFillColor(sf::Color::White);
    r_4_2.setPosition(652, 112);
    r_4_3.setFillColor(sf::Color::White);
    r_4_3.setPosition(612, 72);
    r_4_4.setFillColor(sf::Color::White);
    r_4_4.setPosition(652, 72);

    r_5_1.setFillColor(sf::Color::White);
    r_5_1.setPosition(612, 112);
    r_5_2.setFillColor(sf::Color::White);
    r_5_2.setPosition(652, 112);
    r_5_3.setFillColor(sf::Color::White);
    r_5_3.setPosition(612, 72);
    r_5_4.setFillColor(sf::Color::White);
    r_5_4.setPosition(652, 72);
    r_5_5.setFillColor(sf::Color::White);
    r_5_5.setPosition(632, 92);

    r_6_1.setFillColor(sf::Color::White);
    r_6_1.setPosition(612, 120);
    r_6_2.setFillColor(sf::Color::White);
    r_6_2.setPosition(652, 120);
    r_6_3.setFillColor(sf::Color::White);
    r_6_3.setPosition(612, 60);
    r_6_4.setFillColor(sf::Color::White);
    r_6_4.setPosition(652, 60);
    r_6_5.setFillColor(sf::Color::White);
    r_6_5.setPosition(612, 88);
    r_6_6.setFillColor(sf::Color::White);
    r_6_6.setPosition(652, 88);

    obj[0].init(1, player1_col, player1_cord, radius, player1_home);
    obj[1].init(2, player2_col, player2_cord, radius, player2_home);
    obj[2].init(3, player3_col, player3_cord, radius, player3_home);
    obj[3].init(4, player4_col, player4_cord, radius, player4_home);
}

// Function to return HomeCoordinates of the respective Player
int *returnHome(int i)
{
    if (i == 0)
    {
        return player1_start;
    }

    if (i == 1)
    {
        return player2_start;
    }

    if (i == 2)
    {
        return player3_start;
    }

    if (i == 3)
    {
        return player4_start;
    }
    return nullptr;
}

// if move is true then moves the goti else if it is false then it only tells if the goti is on way to home or not
bool goingHome(bool move, int player_no, int &curx, int &cury, int movement = 1)
{

    if ((curx >= 357 && curx <= 393) && (cury >= 440 && cury <= 691) && player_no == 0)
    {
        if (move == true)
        {
            if (player_no == 0 && obj[player_no].score > 0)
            {
                cury -= (42 * movement);
            }
            else
            {
                curx -= 42;
            }
        }
        return true;
    }

    if ((curx >= 441 && curx <= 692) && (cury >= 358 && cury <= 393) && player_no == 1)
    {
        // cout<<"x is = "<<curx<<",  y is = "<<cury<<endl;
        if (move == true)
        {
            if (player_no == 1 && obj[player_no].score > 0)
            {
                curx -= (42 * movement);
            }
            else
            {
                cury += 42;
            }
        }
        return true;
    }

    if ((curx >= 58 && curx <= 311) && (cury >= 357 && cury <= 396) && player_no == 2)
    {
        if (move == true)
        {
            if (player_no == 2 && obj[player_no].score > 0)
            {
                curx += (42 * movement);
            }
            else
            {
                cury -= 42;
            }
        }
        return true;
    }

    if ((curx >= 358 && curx <= 395) && (cury >= 58 && cury <= 307) && player_no == 3)
    {
        if (move == true)
        {
            if (player_no == 3 && obj[player_no].score > 0)
            {
                cury += (42 * movement);
            }
            else
            {
                curx += 42;
            }
        }
        return true;
    }
    return false;
}

// Calculate the number of boxes which it takes a goti to reach home
int boxes_to_home(int player_no, int goti)
{

    int tempx = obj[player_no].playerGoti[goti][0];
    int tempy = obj[player_no].playerGoti[goti][1];
    int count = 0;

    if (player_no == 0)
    {
        while (tempy >= endLine[player_no])
        {
            count += 1;
            tempy -= 42;
        }
        return count;
    }

    if (player_no == 1)
    {
        while (tempx >= endLine[player_no])
        {
            count += 1;
            tempx -= 42;
        }
        return count;
    }

    if (player_no == 2)
    {
        while (tempx <= endLine[player_no])
        {
            count += 1;
            tempx += 42;
        }
        return count;
    }

    if (player_no == 3)
    {
        while (tempy <= endLine[player_no])
        {
            count += 1;
            tempy += 42;
        }
        return count;
    }
    return count;
}

// Check if Goti is at home or not
bool checkHome(int player_no, int goti, int curx = 0, int cury = 0)
{
    int tempx = obj[player_no].playerGoti[goti][0];
    int tempy = obj[player_no].playerGoti[goti][1];
    if (goti == -1)
    {
        tempx = curx;
        tempy = cury;
    }
    else
    {
        tempx = obj[player_no].playerGoti[goti][0];
        tempy = obj[player_no].playerGoti[goti][1];
    }
    int count = 0;

    if (player_no == 0)
    {
        if ((tempx >= 357 && tempx <= 394) && tempy <= 440)
        {
            return true;
        }
    }

    if (player_no == 1)
    {
        if ((tempy >= 357 && tempy <= 395) && tempx <= 441)
        {
            return true;
        }
    }

    if (player_no == 2)
    {
        if (tempy >= 357 && tempy <= 394 && tempx >= 311)
        {
            return true;
        }
    }

    if (player_no == 3)
    {
        if ((tempx >= 357 && tempx <= 394) && tempy >= 307)
        {
            return true;
        }
    }
    return false;
}

// Function to move goti by size 42
void move_goti(int player_no, int &curx, int &cury)
{

    if ((curx >= 398 && curx <= 432) && (cury >= 271 && cury <= 306))
    {
        curx = 446;
        cury = 323;
    }
    else if ((curx >= 442 && curx <= 477) && (cury >= 399 && cury <= 433))
    {
        curx = 402;
        cury = 444;
    }
    else if ((curx >= 316 && curx <= 351) && (cury >= 440 && cury <= 475))
    {
        curx = 280;
        cury = 403;
    }
    else if ((curx >= 275 && curx <= 308) && (cury >= 319 && cury <= 354))
    {
        curx = 323;
        cury = 276;
    }
    else if ((curx >= 60 && curx <= 648) && (cury >= 319 && cury <= 354))
    {
        curx += 42;
    }
    else if ((curx >= 101 && curx <= 691) && (cury >= 400 && cury <= 433))
    {
        curx -= 42;
    }
    else if ((curx >= 317 && curx <= 352) && (cury >= 99 && cury <= 668))
    {
        cury -= 42;
    }
    else if ((curx >= 398 && curx <= 432) && (cury >= 57 && cury <= 647))
    {
        cury += 42;
    }
    else if ((curx >= 653 && curx <= 688) && (cury >= 317 && cury <= 394))
    {
        cury += 42;
    }
    else if ((curx >= 58 && curx <= 96) && (cury >= 358 && cury <= 434))
    {
        cury -= 42;
    }
    else if ((curx >= 317 && curx <= 393) && (cury >= 58 && cury <= 92))
    {
        curx += 42;
    }
    else if ((curx >= 357 && curx <= 433) && (cury >= 652 && cury <= 690))
    {
        curx -= 42;
    }
    else
    {
        //cout << "cur x is = " << curx << ", cur y is = " << cury << endl;
    }
}

// Thread function to check collission
void *check(void *args)
{
    pthread_mutex_lock(&player_mutex);
    int goti = -1;
    Cords *obj1 = (Cords *)args;
    // cout<<"Selected player -> "<<obj1->player<<endl;
    for (int j = 0; j < 4; j++)
    {
        obj1->check_player = j;

        if (j != obj1->player)
        {
            // cout<<"Checking in player -> "<<obj1->check_player<<endl;
            for (int i = 0; i < 4; i++)
            {
                //cout<<"Goti number is = "<<i<<endl;

                //cout<<"Player Goti x = "<<obj[obj1->player].playerGoti[obj1->goti_no][0]<<" , y = "<<obj[obj1->player].playerGoti[obj1->goti_no][1]<<endl;;
                //cout<<"Checking player Goti x = "<<obj[obj1->check_player].playerGoti[i][0]<<" , y = "<<obj[obj1->check_player].playerGoti[i][1]<<endl;;
                int tempx = obj[obj1->check_player].playerGoti[i][0];
                int tempy = obj[obj1->check_player].playerGoti[i][1];
                int userx = obj[obj1->player].playerGoti[obj1->goti_no][0];
                int usery = obj[obj1->player].playerGoti[obj1->goti_no][1];
                goti = i;

                if ((tempx >= userx - 20 && tempx <= userx + 20) && (tempy >= usery - 20 && tempy <= usery + 20))
                {
                    obj[obj1->player].score += 1;
                    //cout<<"-------------------------------------------------------------"<<endl;
                    if (obj1->check_player == 0)
                    {
                        obj[obj1->check_player].incGoti_home();
                        obj[obj1->check_player].gotis_home[goti] = true;

                        obj[obj1->check_player].setPosition(goti, player1_cord[goti][0], player1_cord[goti][1]);
                    }
                    else if (obj1->check_player == 1)
                    {

                        obj[obj1->check_player].incGoti_home();
                        obj[obj1->check_player].gotis_home[goti] = true;
                        obj[obj1->check_player].setPosition(goti, player2_cord[goti][0], player2_cord[goti][1]);
                    }
                    else if (obj1->check_player == 2)
                    {

                        obj[obj1->check_player].incGoti_home();
                        obj[obj1->check_player].gotis_home[goti] = true;
                        obj[obj1->check_player].setPosition(goti, player3_cord[goti][0], player3_cord[goti][1]);
                    }
                    else if (obj1->check_player == 3)
                    {

                        obj[obj1->check_player].incGoti_home();
                        obj[obj1->check_player].gotis_home[goti] = true;
                        obj[obj1->check_player].setPosition(goti, player4_cord[goti][0], player4_cord[goti][1]);
                    }
                }

                //cout<<endl;
            }
        }
    }
    pthread_mutex_unlock(&player_mutex);
    pthread_exit(NULL);
}

// Check collssion function which calls 3 threads to check collission.
void check_collision(int player_no, int goti)
{
    pthread_mutex_init(&player_mutex, NULL);
    Cords obj1(player_no, goti);
    for (int i = 0; i < 4; i++)
    {
        if (i != player_no)
        {
            pthread_create(&player_threads[i], NULL, &check, &obj1);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (i != player_no)
        {
            pthread_join(player_threads[i], NULL);
        }
    }
}

// Return if the goti is at save point or not
bool getSavePoint(int x, int y)
{

    if ((x >= 146 && x <= 180) && (y >= 400 && y <= 436))
    {
        return true;
    }

    if ((x >= 100 && x <= 140) && (y >= 319 && y <= 355))
    {
        return true;
    }

    if ((x >= 316 && x <= 354) && (y >= 143 && y <= 179))
    {
        return true;
    }

    if ((x >= 369 && x <= 434) && (y >= 99 && y <= 139))
    {
        return true;
    }

    if ((x >= 570 && x <= 608) && (y >= 321 && y <= 351))
    {
        return true;
    }

    if ((x >= 614 && x <= 653) && (y >= 400 && y <= 436))
    {
        return true;
    }

    if ((x >= 397 && x <= 434) && (y >= 570 && y <= 606))
    {
        return true;
    }

    if ((x >= 316 && x <= 355) && (y >= 612 && y <= 650))
    {
        return true;
    }

    return false;
}

// Return true if goti can go home with respective dice number or not.
bool canGoHome(int movement, int pturn, int goti_no)
{
    int tempx = obj[pturn].playerGoti[goti_no][0];
    int tempy = obj[pturn].playerGoti[goti_no][1];
    bool found = false;
    for (int i = 0; i < movement; i++)
    {

        move_goti(pturn, tempx, tempy);
        if (goingHome(false, pturn, tempx, tempy) == true)
        {
            goingHome(true, pturn, tempx, tempy);
            found = true;
        }
    }

    if (found == true)
    {
        return true;
    }

    return false;
}
