#include <iostream>
#include <pthread.h>
#include <mutex> 
#include <semaphore.h> 
#include <vector>
#include <random>
#include <time.h>
#include <cstdlib>
#include "player.h"
#include "Initial.h"
#include <SFML/Graphics.hpp>
using namespace std;

sf::RenderWindow window(sf::VideoMode(1060,750), "LUDO");  // variable for game window
sf::Sprite backimg; // Backimg variable
sf::Sprite menus;   // variable to store menu page
pthread_t *threads=new pthread_t[4];// Player threads
pthread_mutex_t DiceMutex;  // Dice mutex
pthread_mutex_t BoardMutex; //Mutex for board
vector<int> Winners; // Vecotr for Winners
vector<int> dice_store;// Vector to store dice values
pthread_t master; // Master thread
int dice_roll; // integer to store current generated Dice Value
bool turn=false; // If player goti moving or not
int movement=0; // stores the value which user has selected.


// Thread Functin which master thread creates and in argument sends the player turn.
void *drawBoard(void* args){
   // pthread_detach(pthread_self());
pthread_mutex_lock(&BoardMutex);  // Lock so that no other player can access
int *prime = (int *)args;  // Store the argument
int pturn=*prime;
obj[pturn].setTurn(true); // Set player turn to true
turn=false;
int count=0; // Count to store number of sixes a player has
movement=0;
while(1){
    while (window.isOpen())
    {
            
                        sf::Event event; // Variable for event
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed) // If the user closes the window
                            {  
                                window.close();
                                exit(0);
                                pthread_exit(NULL);
                                
                            }
                            
                            if(event.type == sf::Event::MouseButtonPressed)  // Mouse Functio if player clicks mouse
                            {
                                sf::Vector2i position = sf::Mouse::getPosition(window); // returns the mouse c and y
                            
                            // The following 3 If statements check which dice value the user has selected.
                                if((position.x>=776 && position.x<=826)   &&   (position.y>=554 && position.y<=603) && dice_store.size()>0 && obj[pturn].goti_home<4){
                                        movement=dice_store[0];
                                }

                                if((position.x>=831 && position.x<=880)   &&   (position.y>=554 && position.y<=603) && dice_store.size()>1 && obj[pturn].goti_home<4){
                                        movement=dice_store[1];
                                }

                                if((position.x>=885 && position.x<=935)   &&   (position.y>=554 && position.y<=603) && dice_store.size()>2 && obj[pturn].goti_home<4){
                                        movement=dice_store[2];
                                }

                                // The following if determines if a user has clicled the dice or not
                                if((position.x>=590 && position.x<=700) && (position.y>=50 && position.y<=155))
                                {
                                    pthread_mutex_lock (&DiceMutex);  // Dice Lock itself
                                    
                                    if(turn==false){
                                        dice_roll = rand() % 6 + 1;  // Dice value from 1 to 6 generated
                                        dice_store.push_back(dice_roll);// Stored in dice vector
                                    
                                        if(dice_roll==6){   // If the dice is 6 then user again has to click on dice
                                            turn=false;
                                            count+=1;
                                            if(count==3){  // check whether the user has got 3 sixes or not, if yes then board mutex and dice mutex are unlocked and thread cancels itself.
                                                dice_store.clear();
                                                for(int i=0;i<4;i++){
                                                    obj[i].setTurn(false);
                                                }
                                                
                                                pthread_mutex_unlock(&DiceMutex);
                                                pthread_mutex_unlock (&BoardMutex);
                                                pthread_cancel(pthread_self());
                                                cur_done=true;
                                                pthread_exit(NULL);
                                            }
                                            // This else checks if the player has 4 gotis at home and if he hasnt got 6 then next player
                                        }else if(obj[pturn].goti_home==4 && std::find(dice_store.begin(), dice_store.end(), 6) == dice_store.end()){
                                            dice_store.clear();
                                            for(int i=0;i<4;i++){
                                                    obj[i].setTurn(false);
                                                }
                                            pthread_mutex_unlock(&DiceMutex);
                                            pthread_mutex_unlock (&BoardMutex);
                                            pthread_cancel(pthread_self());
                                            cur_done=true;
                                            pthread_exit(NULL);
                                        }
                                        
                                        else{
                                            // none of above are true then the current player does his turn
                                            turn=true;
                                        }
                                    }
                                    pthread_mutex_unlock(&DiceMutex);//    Dice mutex is unlocked                           
                                
                                    
                                }
                                    // The user selects which dice number to role, when selects goti and that goti moves, checks collision and whether it is going home or not
                                if(turn==true){ 
                                    int goti_no=-1;
                                    if(obj[pturn].checkGoti(position.x,position.y,goti_no) == true){ // Whether correct gti selected or not
                                        if(obj[pturn].gotis_home[goti_no]==true && std::find(dice_store.begin(), dice_store.end(), 6) != dice_store.end()){// If the selected goti is at home then take it out.
                                            int *points=returnHome(pturn);
                                            obj[pturn].decGoti_home();
                                            obj[pturn].gotis_home[goti_no]=false;
                                            std::vector<int>::iterator position = std::find(dice_store.begin(), dice_store.end(), 6);
                                                    if (position != dice_store.end()){ 
                                                        dice_store.erase(position);
                                                    }
                                            obj[pturn].setPosition(goti_no,points[0],points[1]);;
                                            movement=-1;
                                        }else if(obj[pturn].gotis_home[goti_no]==false){ // If goti is not at home
                                                
                                                if(movement>0){
                                                    // The following if check whether the player can go home or not, if he can normal movement, else movements to go home
                                                    if(canGoHome(movement,pturn,goti_no)==false ){  
                                                            for(int i=0;i<movement;i++){

                                                        
                                                            move_goti(pturn,obj[pturn].playerGoti[goti_no][0],obj[pturn].playerGoti[goti_no][1]);
                                                            if(getSavePoint(obj[pturn].playerGoti[goti_no][0],obj[pturn].playerGoti[goti_no][1])==false){
                                                                check_collision(pturn,goti_no);
                                                            }
                                                        
                                                    }
                                                    }else{
                                                        for(int i=0;i<movement;i++){

                                                        if(goingHome(false,pturn,obj[pturn].playerGoti[goti_no][0],obj[pturn].playerGoti[goti_no][1])==true ){
                                                            //cout<<"boxes to home are = "<<boxes_to_home(pturn,goti_no)<<endl;
                                                            if(boxes_to_home(pturn,goti_no)>=movement){
                                                                    goingHome(true,pturn,obj[pturn].playerGoti[goti_no][0],obj[pturn].playerGoti[goti_no][1],movement);
                                                            }
                                                        }else{
                                                            move_goti(pturn,obj[pturn].playerGoti[goti_no][0],obj[pturn].playerGoti[goti_no][1]);
                                                            if(getSavePoint(obj[pturn].playerGoti[goti_no][0],obj[pturn].playerGoti[goti_no][1])==false){
                                                                check_collision(pturn,goti_no);
                                                            }
                                                        }

                                                            if(checkHome(pturn,goti_no)==true ){  // After the goti movement this check whether the goti has gone home or not
                                                            obj[pturn].gotiPass[goti_no]=true;
                                                            if(obj[pturn].passed()){ // If all gotis have passed then remove player.
                                                                std::vector<int>::iterator position = std::find(players.begin(), players.end(), pturn);
                                                                if (position != dice_store.end()){ // == myVector.end() means the element was not found
                                                                    Winners.push_back(pturn);
                                                                    players.erase(position);
                                                                    size-=1;
                                                                }
                                                            }

                                                            if(players.size()==1){  // If number of players are 1 then close the game
                                                                    window.close();
                                                                    
                                                            }
                                                        }
                                                    }
                                                    }
                                                

                                                        // The following code removes the goti no which the user had selected
                                                    std::vector<int>::iterator position = std::find(dice_store.begin(), dice_store.end(), movement);
                                                    if (position != dice_store.end()){ 
                                                        dice_store.erase(position);
                                                    }
                                                    movement=0;
                                                ;

                                                }
                                        }

                                        //cout<<"Goti is = "<<goti_no<<endl;
                                    }
                                        else{
                                    }
                                        // This If checks whether the user has selected all the dice values or not, if yes then give resources to other player
                                        if(dice_store.size()==0){
                                            dice_store.clear();
                                            for(int i=0;i<4;i++){
                                                    obj[i].setTurn(false);
                                                }
                                            pthread_mutex_unlock(&DiceMutex);
                                            pthread_mutex_unlock (&BoardMutex);
                                            pthread_cancel(pthread_self());
                                            cur_done=true;
                                            pthread_exit(NULL);
                                        }

                                        

                                }
                            }
                        }
                    
                        window.clear();
                        
                        // The following code is used to draw backimage
                        window.draw(backimg);
                        
                        // Draws users
                        obj[0].draw(window); 
                        obj[1].draw(window);
                        obj[2].draw(window);
                        obj[3].draw(window);

                        // The following draws the rectangles for the dice values and the dice values
                        sf::RectangleShape rectangle1;
                            rectangle1.setSize(sf::Vector2f(50, 50));
                            rectangle1.setOutlineColor(sf::Color::Red);
                            rectangle1.setOutlineThickness(1);
                            rectangle1.setPosition(776, 553);
                            window.draw(rectangle1);
                        

                            sf::RectangleShape rectangle2;
                            rectangle2.setSize(sf::Vector2f(50, 50));
                            rectangle2.setOutlineColor(sf::Color::Red);
                            rectangle2.setOutlineThickness(1);
                            rectangle2.setPosition(830, 553);
                            window.draw(rectangle2);      
                        

                            sf::RectangleShape rectangle3;
                            rectangle3.setSize(sf::Vector2f(50, 50));
                            rectangle3.setOutlineColor(sf::Color::Red);
                            rectangle3.setOutlineThickness(1);
                            rectangle3.setPosition(884, 553);
                            window.draw(rectangle3);
                sf::Font font;
                font.loadFromFile("arial.ttf");

                if(dice_store.size()>=1){
                    
                sf::Text text;
                text.setFont(font);
                text.setString(to_string(dice_store[0]));
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Red);
                text.setPosition(778.f,573.f);
                    window.draw(text);
                    if(dice_store.size()>=2){
                                sf::Text text1;
                                text1.setFont(font);
                                text1.setString(to_string(dice_store[1]));
                                text1.setCharacterSize(24);
                                text1.setFillColor(sf::Color::Red);
                                text1.setPosition(830.f,573.f);
                                window.draw(text1);
                        if(dice_store.size()>=3){
                                        sf::Text text2;
                                        text2.setFont(font);
                                        text2.setString(to_string(dice_store[2]));
                                        text2.setCharacterSize(24);
                                        text2.setFillColor(sf::Color::Red);
                                        text2.setPosition(882.f,573.f);
                                        window.draw(text2);

                        }
                    }
                }

        // Display score of each player
                sf::Text text;
                text.setFont(font);
                text.setString("Player 1 Score : "+ to_string(obj[0].score));
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Red);
                text.setPosition(778.f,97.f);
                window.draw(text);


                text.setString("Player 2 Score : "+ to_string(obj[1].score));
                text.setPosition(778.f,138.f);
                window.draw(text);


                text.setString("Player 3 Score : "+ to_string(obj[2].score));
                text.setPosition(778.f,179.f);
                window.draw(text);


                text.setString("Player 4 Score : "+ to_string(obj[3].score));
                text.setPosition(778.f,220.f);
                window.draw(text);

        // The following display which users turn it is and which dice is selected

                if(pturn==0){
                        text.setString("Player RED turn");
                        text.setPosition(778.f,261.f);
                        window.draw(text);

                        if(movement<=0){
                        text.setString(" ");
                        }else{
                        text.setString("Dice Selected : "+ to_string(movement));
                        }
                        text.setPosition(778.f,302.f);
                        window.draw(text);
                }else if(pturn==1){
                    

                    text.setString("Player BLUE turn");
                        text.setPosition(778.f,261.f);
                        window.draw(text);

                        if(movement<=0){
                        text.setString(" ");
                        }else{
                        text.setString("Dice Selected : "+ to_string(movement));
                        }
                        text.setPosition(778.f,302.f);
                        window.draw(text);


                }else if(pturn==2){

                    text.setString("Player GREEN turn");
                        text.setPosition(778.f,261.f);
                        window.draw(text);

                        if(movement<=0){
                        text.setString(" ");
                        }else{
                        text.setString("Dice Selected : "+ to_string(movement));
                        }
                        text.setPosition(778.f,302.f);
                        window.draw(text);
                    
                }else if(pturn==3){


                    text.setString("Player YELLOW turn");
                        text.setPosition(778.f,261.f);
                        window.draw(text);

                        if(movement<=0){
                        text.setString(" ");
                        }else{
                        text.setString("Dice Selected : "+ to_string(movement));
                        }
                        text.setPosition(778.f,302.f);
                        window.draw(text);
                    
                }

                        
                        // Draw dice
                        if(dice_roll==1)
                        {
                            window.draw(r_1);
                        }
                        else if(dice_roll==2)
                        {
                            window.draw(r_2_1);
                            window.draw(r_2_2);
                        }
                        else if(dice_roll==3)
                        {
                            window.draw(r_3_1);
                            window.draw(r_3_2);
                            window.draw(r_3_3);
                        }
                        else if(dice_roll==4)
                        {
                            window.draw(r_4_1);
                            window.draw(r_4_2);
                            window.draw(r_4_3);
                            window.draw(r_4_4);
                        }
                        else if(dice_roll==5)
                        {
                            window.draw(r_5_1);
                            window.draw(r_5_2);
                            window.draw(r_5_3);
                            window.draw(r_5_4);
                            window.draw(r_5_5);
                        }
                        else if(dice_roll==6)
                        {
                            window.draw(r_6_1);
                            window.draw(r_6_2);
                            window.draw(r_6_3);
                            window.draw(r_6_4);
                            window.draw(r_6_5);
                            window.draw(r_6_6);
                        }

        
          
            
         window.display();
        
    }
    
    }
}


int main()
{
    bool menu=true; // variable fot menu
    // The following initializes the mutexes
  pthread_mutex_init(&BoardMutex,NULL);
  pthread_mutex_init(&DiceMutex,NULL);
    initialize();


    
    sf::Texture background;  // Background image variable
    background.loadFromFile("Home.png"); // Load the image
    menus.setTexture(background); // give the image to sprite to frae

    // the following code display menu
     while (window.isOpen() && menu==true)
     {
        
         sf::Event event;
         while (window.pollEvent(event))
         {
            
             if (event.type == sf::Event::Closed)
                 window.close();

                 if(event.type == sf::Event::MouseButtonPressed)
                            {
                                sf::Vector2i position = sf::Mouse::getPosition(window);
                                cout<<position.x<<" , "<<position.y<<endl;
                                if((position.x>=392 && position.x<=607)  &&  (position.y>=401  && position.y<=557)){
                                    window.clear();
                                    menu=false;
                                }
                            }
             }
             
            window.clear();
            window.draw(menus);
            window.display();

     }


    //obj[0].score=1;
    
    background.loadFromFile("BOARD_FINAL.jpg");
    backimg.setTexture(background);
    backimg.setScale(0.5f,0.5f);
    int player_turn=0;
    // The followng code calls the master thread
    int i=0;
        while(menu==false){
            if(players.size()>1){
                i+=1;
                srand(time(NULL));
                 player_turn= rand() % size;
            //player_turn=0;
                pthread_create(&master,NULL,&drawBoard,&players[player_turn]);
                pthread_join(master,NULL);
                if(!window.isOpen()){
                break;
             }
            }else{
                break;
            }
        }    




// The following display the winner screen.
        sf::Font font;
        font.loadFromFile("arial.ttf");
        
                
         while (window.isOpen())
     {
        
         sf::Event event;
         while (window.pollEvent(event))
         {
            
             if (event.type == sf::Event::Closed)
                 window.close();
             }
             if(event.type == sf::Event::MouseButtonPressed)
                            {
                                sf::Vector2i position = sf::Mouse::getPosition(window);
                                cout<<position.x<<" , "<<position.y<<endl;
                            }

         window.clear();
          sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(110, 50));
                rectangle.setOutlineColor(sf::Color::Red);
                rectangle.setOutlineThickness(5);
                rectangle.setPosition(426, 248);
                window.draw(rectangle);

                sf::Text text;
                text.setFont(font);
                text.setString("Player "+ to_string(Winners[0]));
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Red);
                text.setPosition(438.f,270.f);
                window.draw(text);

                rectangle.setPosition(426, 310);
                window.draw(rectangle);
                text.setString("Player "+ to_string(Winners[1]));
                text.setPosition(438.f,328.f);
                window.draw(text);


                rectangle.setPosition(426, 360);
                window.draw(rectangle);
                 text.setString("Player "+ to_string(Winners[2]));
                text.setPosition(438.f,376.f);
                window.draw(text);

                rectangle.setPosition(426, 420);
                window.draw(rectangle);
                 text.setString("Player "+ to_string(Winners[3]));
                text.setPosition(438.f,437.f);
                window.draw(text);
         window.display();
     }
    return 0;
}


