#include<iostream>
#include "SFML/Graphics.hpp"

class Dice{
public:

    
int dice_roll;
Dice(){
    dice_roll=0;
}



void draw(sf::RenderWindow &window,int &val){
    dice_roll = rand() % 6 + 1;
    val=dice_roll;
    std::cout<<"htere"<<std::endl;
    //1
    sf::CircleShape r_1(10.f);
    r_1.setFillColor(sf::Color::White);
    r_1.setPosition(632,92);
    //2
    sf::CircleShape r_2_1(10.f);
    r_2_1.setFillColor(sf::Color::White);
    r_2_1.setPosition(612,92);
    sf::CircleShape r_2_2(10.f);
    r_2_2.setFillColor(sf::Color::White);
    r_2_2.setPosition(652,92);
    //3
    sf::CircleShape r_3_1(10.f);
    r_3_1.setFillColor(sf::Color::White);
    r_3_1.setPosition(612,108);
    sf::CircleShape r_3_2(10.f);
    r_3_2.setFillColor(sf::Color::White);
    r_3_2.setPosition(652,108);
    sf::CircleShape r_3_3(10.f);
    r_3_3.setFillColor(sf::Color::White);
    r_3_3.setPosition(632,72);
    //4
    sf::CircleShape r_4_1(10.f);
    r_4_1.setFillColor(sf::Color::White);
    r_4_1.setPosition(612,112);
    sf::CircleShape r_4_2(10.f);
    r_4_2.setFillColor(sf::Color::White);
    r_4_2.setPosition(652,112);
    sf::CircleShape r_4_3(10.f);
    r_4_3.setFillColor(sf::Color::White);
    r_4_3.setPosition(612,72);
    sf::CircleShape r_4_4(10.f);
    r_4_4.setFillColor(sf::Color::White);
    r_4_4.setPosition(652,72);
    //5
    sf::CircleShape r_5_1(10.f);
    r_5_1.setFillColor(sf::Color::White);
    r_5_1.setPosition(612,112);
    sf::CircleShape r_5_2(10.f);
    r_5_2.setFillColor(sf::Color::White);
    r_5_2.setPosition(652,112);
    sf::CircleShape r_5_3(10.f);
    r_5_3.setFillColor(sf::Color::White);
    r_5_3.setPosition(612,72);
    sf::CircleShape r_5_4(10.f);
    r_5_4.setFillColor(sf::Color::White);
    r_5_4.setPosition(652,72);
    sf::CircleShape r_5_5(10.f);
    r_5_5.setFillColor(sf::Color::White);
    r_5_5.setPosition(632,92);
    //6
    sf::CircleShape r_6_1(10.f);
    r_6_1.setFillColor(sf::Color::White);
    r_6_1.setPosition(612,120);
    sf::CircleShape r_6_2(10.f);
    r_6_2.setFillColor(sf::Color::White);
    r_6_2.setPosition(652,120);
    sf::CircleShape r_6_3(10.f);
    r_6_3.setFillColor(sf::Color::White);
    r_6_3.setPosition(612,60);
    sf::CircleShape r_6_4(10.f);
    r_6_4.setFillColor(sf::Color::White);
    r_6_4.setPosition(652,60);
    sf::CircleShape r_6_5(10.f);
    r_6_5.setFillColor(sf::Color::White);
    r_6_5.setPosition(612,88);
    sf::CircleShape r_6_6(10.f);
    r_6_6.setFillColor(sf::Color::White);
    r_6_6.setPosition(652,88);
    
    std::cout<<"dice roll is = "<<dice_roll<<std::endl;
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
}

void reset(){
    dice_roll=0;
}


};