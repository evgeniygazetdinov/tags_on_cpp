#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int ground = 150;

class Player{
  public:
    float dx, dy;// speed variables
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float currentFrame;
   Player(Texture &image){
    sprite.setTexture(image);
    rect = FloatRect(0, 0, 40, 50);
    dx = dy = 0;
    currentFrame = 0;
   }
   void update(float time){
      rect.left += dx * time;
      if(!onGround) {
        dy=dy + 0.0005 * time;
      } 
      rect.top += dy * time;
      onGround = false;
      currentFrame += 0.005 * time;

      if(currentFrame >6){
        currentFrame -=6;
      }
      sprite.setTextureRect(IntRect(40 * int(currentFrame), 244,40,50));
      if(dx>0){
        sprite.setTextureRect(IntRect(40 * int(currentFrame), 244,40,50));
      }
      if(dx<0){
        sprite.setTextureRect(IntRect(40 * int(currentFrame)+40, 244,-40,50));
      }

      
      if(rect.top > ground){
        rect.top = ground;
        dy = 0;
        onGround = true;
      } 
      sprite.setPosition(rect.left, rect.top);
      dx = 0;
   }

};




int main() {

  float currentFrame = 0;
  RenderWindow window(VideoMode(200, 200), "my turbo game");
  Texture myTexture;
  myTexture.loadFromFile("images/fang.png");

  Player myPlayer(myTexture);  
  Clock myclock;


  while (window.isOpen()) {
    float time = myclock.getElapsedTime().asMicroseconds();
    myclock.restart();
    time = time / 800;
    Event event;


    while (window.pollEvent(event)) {

      if (event.type == Event::Closed)
        window.close();
      if(Keyboard::isKeyPressed(Keyboard::Escape)){
        window.close();
      }
      if (Keyboard::isKeyPressed(Keyboard::Left)) {
         myPlayer.dx = -40;

      }
      if (Keyboard::isKeyPressed(Keyboard::Right)) {
          myPlayer.dx = 40;

      }
      if (Keyboard::isKeyPressed(Keyboard::Up)) {
          if(myPlayer.onGround){
            myPlayer.dy=-0.4; myPlayer.onGround = false;
          }
          
      }
    }
    myPlayer.update(time);
    window.clear();
    window.draw(myPlayer.sprite);
    window.display();
  }

  return 0;
}