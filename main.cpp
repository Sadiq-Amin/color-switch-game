/*Compilation Commands:
g++ -c main.cpp -I"Path of include folder in this directory"

g++ main.o -o main -L"Path of lib folder in this directory" -lsfml-graphics -lsfml-window -lsfml-system

*/

/*Execution Commands:

./main

*/

/* Run This line in terminal to run program(Add paths):

g++ -c main.cpp -I"Path of include folder in this directory";g++ main.o -o main -L"Path of lib folder in this directory" -lsfml-graphics -lsfml-window -lsfml-system;./main

Example:
g++ -c main.cpp -I"C:\Users\Abdul Rahman\Desktop\ColorSwitchProject\include";g++ main.o -o main -L"C:\Users\Abdul Rahman\Desktop\ColorSwitchProject\lib" -lsfml-graphics -lsfml-window -lsfml-system;./main

*/

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstring>
#include <chrono>
using namespace sf;
using namespace std;
using namespace chrono;


class Button:public Sprite{
    protected:
    Texture buttontexture;
    public:

    
    Button(string texturefilepath,float offsetx,float offsety){

        buttontexture.loadFromFile(texturefilepath);
        setTexture(buttontexture);
        setPosition(196,348);
        setOrigin(29,29);
        move(offsetx,offsety);
        
    }

    void drawButton(Button &obj,RenderWindow &win){
        win.draw(obj);
    }
};

// class EasyButton:public Button{};
// class HardButton:public Button{};
// class EditButton:public Button{};



class HomePage:public Sprite{
    Texture hometexture;
    public:
    Button easybutton = Button("Sprites\\easy.png",-70,-120);
    Button hardbutton = Button("Sprites\\hard.png",50,-120);
    Button editbutton = Button("Sprites\\edit.png",-10,-60);
    // TO DO:: Add ScoreBoard Object which shows highscore and/or top three scores
    

    
    
    HomePage(){
        
        hometexture.loadFromFile("Sprites\\home.png");
        setTexture(hometexture);
    }
    void drawHome(HomePage &home,RenderWindow &win){
        win.draw(home);
        easybutton.drawButton(easybutton,win);
        hardbutton.drawButton(hardbutton,win);
        editbutton.drawButton(editbutton,win);
    }


};

class Game{};

class GameOverPage{
    //texture
    //homebutton,current score
};

class Pentagon : public Drawable {
private:
    ConvexShape pentagonShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Pentagon(float size) {
        // Setup the pentagon shape
        pentagonShape.setPointCount(5);
        pentagonShape.setPoint(0, Vector2f(0, -size));
        pentagonShape.setPoint(1, Vector2f(size * 0.9511f, -size * 0.3090f));
        pentagonShape.setPoint(2, Vector2f(size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(3, Vector2f(-size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(4, Vector2f(-size * 0.9511f, -size * 0.3090f));
        pentagonShape.setFillColor(Color::Red); 
        pentagonShape.setOrigin(0, -size);
        pentagonShape.setPosition(196, 348);

        currentColor = Color::Red;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= 2.0f) {
            currentColor = Color(rand() % 256, rand() % 256, rand() % 256);
            pentagonShape.setFillColor(currentColor);
            colorChangeClock.restart(); 
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(pentagonShape, states);
    }
};

class Rectangle : public Drawable {
private:
    RectangleShape rectangleShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Rectangle(float width, float height) {
        rectangleShape.setSize(Vector2f(width, height));
        rectangleShape.setFillColor(Color::Blue); 
        rectangleShape.setOrigin(width / 2.0f, height / 2.0f); 
        rectangleShape.setPosition(400, 300);
        currentColor = Color::Blue;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= 2.0f) {
            currentColor = Color(rand() % 256, rand() % 256, rand() % 256);
            rectangleShape.setFillColor(currentColor);
            colorChangeClock.restart(); 
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(rectangleShape, states);
    }
};



int main()
{   
    //Intialising Objects
    RenderWindow window(VideoMode(392,696),"Color Switch",Style::Close | Style::Titlebar);
    HomePage home;

    // Main Loop
    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed){
                window.close();}

            //Check if left mouse button is pressed
            if (evnt.type == Event::MouseButtonPressed && evnt.mouseButton.button == Mouse::Left) {
                Vector2i currentMousePos = Mouse::getPosition(window);
                
                
                if (home.getGlobalBounds().contains(Vector2f(currentMousePos))) {
                    
                    home.move(-5000,0);
                    home.easybutton.move(-5000,0);
                    home.editbutton.move(-5000,0);
                    home.hardbutton.move(-5000,0);
                    
                }




            }

            
        }

    window.clear(Color::Black);
    
    // Draw Functions
    home.drawHome(home,window);
    
    window.display();

    }
    
    RenderWindow window(VideoMode(800, 600), "SFML Pentagon Color Change");

    Pentagon pentagon(50.0f); 

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        pentagon.updateColor();

        window.clear(Color::Black);
        window.draw(pentagon);
        window.display();
    }

    return 0;
}