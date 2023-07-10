#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>

using namespace simplecpp;

class MovingObject : public Sprite {
  vector<Sprite*> parts;
  double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
  }
 public:
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)
    : Sprite() {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
   double angle_rad = angle_deg*PI/180.0;
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}

//coin.h
#ifndef __COIN_H__
#define __COIN_H__



class Coin : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();
  void resetCoin();

}; // End class Coin
#endif
//bonus.h
#ifndef __BONUS_H__
#define __BONUS_H__
class Bonus : public MovingObject {
  double bonus_start_x;
  double bonus_start_y;
  double release_speed;
  double release_angle_deg;
  double bonus_ax;
  double bonus_ay;

  // Moving parts
  Circle bonus_circle;

 public:
 Bonus(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    bonus_ax = argax;
    bonus_ay = argay;
    initBonus();
  }

  void initBonus();
  void resetBonus();

};
#endif
//end of class bonus
//bomb.h
#ifndef __BOMB_H__
#define __BOMB_H__
class Bomb: public MovingObject{
double bomb_start_x,bomb_start_y,release_speed, release_angle_deg,bomb_ax,bomb_ay;
//Moving parts
Circle bomb_circle;

public:
 Bomb(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {release_speed = speed;
    release_angle_deg = angle_deg;
    bomb_ax = argax;
    bomb_ay = argay;
    initbomb();
  }

  void initbomb();
  void resetbomb();

};
#endif

//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.01

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1
double factor=7.0/16;
#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define BOMB_SPEED 100
#define COIN_ANGLE_DEG 90

#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
int LASSO_RADIUS=50;
#define COIN_SIZE 5
int aax=0;

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Coin *the_coin;
  Bomb *the_bomb;
  Bonus *the_bonus;
  int num_coins;
  bool num_bonus;
  bool caughtb;


  void initLasso();
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);
  void nextStep(double t);
  void check_for_coin(Coin *coin);
  void check_for_bomb(Bomb *bomb);
  void check_for_bonus(Bonus *bonus);
  int getNumCoins() { return num_coins; }
  bool checkbonus(){ return num_bonus;}
  bool caught(){return caughtb;}
  void updateb(bool v){
   num_bonus=v;
  }

}; // End class Lasso

#endif

//coin.h

void Coin::initCoin() {
  coin_start_x = (PLAY_X_START+WINDOW_X)*factor;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("yellow"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = aax;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
//bonus.h
void Bonus::initBonus() {
  bonus_start_x = (PLAY_X_START+WINDOW_X)*7/8;
  bonus_start_y = PLAY_Y_HEIGHT;
  bonus_circle.reset(bonus_start_x, bonus_start_y, COIN_SIZE);
  bonus_circle.setColor(COLOR(0,255,120));
  bonus_circle.setFill(true);
  addPart(&bonus_circle);
}

void Bonus::resetBonus() {
  double bonus_speed = COIN_SPEED;
  double bonus_angle_deg = COIN_ANGLE_DEG;
  bonus_ax = aax;
  bonus_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(bonus_start_x, bonus_start_y, bonus_speed, bonus_angle_deg, bonus_ax, bonus_ay, paused, rtheta);
}
//bomb.h

void Bomb::initbomb() {
  bomb_start_x = (PLAY_X_START+WINDOW_X)*factor;
  bomb_start_y = PLAY_Y_HEIGHT;
  bomb_circle.reset(bomb_start_x, bomb_start_y, COIN_SIZE);
  bomb_circle.setColor(COLOR("black"));
  bomb_circle.setFill(true);
  addPart(&bomb_circle);
}

void Bomb::resetbomb(){
  double bomb_speed = BOMB_SPEED;
  double bomb_angle_deg = COIN_ANGLE_DEG;
  bomb_ax = aax;
  bomb_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(bomb_start_x, bomb_start_y, bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
}
//lasso.cpp
void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("black"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  the_bomb=NULL;
  the_bonus=NULL;
  num_coins = 0;
  num_bonus=false;
  caughtb=false;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("black"));

  lasso_band.setColor(COLOR("blue"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if(the_coin != NULL) {
    num_coins++;
    the_coin->resetCoin();
    the_coin = NULL;
  }
  else if(the_bomb!=NULL){
    num_coins--;
    the_bomb->resetbomb();
    the_bomb=NULL;
  }
  else if(the_bonus!=NULL){
    num_coins+=2;
    the_bonus->resetBonus();
    the_bonus=NULL;
    num_bonus=true;
  }
} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
}
void Lasso::check_for_bonus(Bonus *bonusPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double bonus_x = bonusPtr->getXPos();
  double bonus_y = bonusPtr->getYPos();
  double xdiff = (lasso_x - bonus_x);
  double ydiff = (lasso_y - bonus_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_bonus = bonusPtr;
    the_bonus->getAttachedTo(this);
    caughtb=true;
  }
}
void Lasso::check_for_bomb(Bomb *bombPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double bomb_x = bombPtr->getXPos();
  double bomb_y = bombPtr->getYPos();
  double xdiff = (lasso_x - bomb_x);
  double ydiff = (lasso_y - bomb_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_bomb = bombPtr;
    the_bomb->getAttachedTo(this);
  }
} // End Lasso::check_for_coin()


main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  int level=1;
  int score=0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  double difficult=0,dx=0,dy=0;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  char Level[20];
  char Score[20];
  char diff [3][20]={"Hard","Medium","Easy"};
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  sprintf(Level, "level: %d", level);
  sprintf(Score, "high score: %d", score);
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);
  Rectangle R1(PLAY_X_START+500,50,100,20);
  R1.setColor(COLOR("red"));
  R1.setFill(true);
  Rectangle R2(PLAY_X_START+500,70,100,20);
  R2.setColor(COLOR("yellow"));
  R2.setFill(true);
  Rectangle R3(PLAY_X_START+500,90,100,20);
  R3.setColor(COLOR("green"));
  R3.setFill(true);
  Text level1(PLAY_X_START+500,50,diff[0]);
  Text level2(PLAY_X_START+500,70,diff[1]);
  Text level3(PLAY_X_START+500,90,diff[2]);
  Text Levelno(PLAY_X_START+500, PLAY_Y_HEIGHT+50, Level);
  Text scr(PLAY_X_START+500, PLAY_Y_HEIGHT+20, Score);
  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double bomb_speed= 0;
  double bonus_speed=0,bomb_speed1=0;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double bonus_angle_deg=COIN_ANGLE_DEG;
  double coin_ax = aax;
  double coin_ay = COIN_G;
  factor=8.0/16;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  factor=7.0/16;
  Bomb bomb(bomb_speed,coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  factor=9.0/16;
  aax=-10;
  Bomb bomb1(bomb_speed1,coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  aax=0;
  factor=10.0/16;
  Coin coin2(coin_speed, coin_angle_deg, aax, coin_ay, paused, rtheta);
  aax=-20;
  Bonus bonus(bonus_speed, bonus_angle_deg, coin_ax, coin_ay, paused, rtheta);
  aax=0;
  // After every COIN_GAP sec, make the coin and bomb jump
  double last_coin_jump_end = 0;
  double last_bomb_jump_end = 0;
  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
   // When q is pressed, quit
   difficult=getClick();
   dx=floor(difficult/65536);
   dy=difficult-dx*65536;
  if(dx>PLAY_X_START+450&&dx<PLAY_X_START+550&&dy>40&&dy<60)
    stepTime=0.08;
  else if(dx>PLAY_X_START+450&&dx<PLAY_X_START+550&&dy>60&&dy<80)
   stepTime=0.04;
  else if(dx>PLAY_X_START+450&&dx<PLAY_X_START+550&&dy>80&&dy<100)
   stepTime=0.01;

 R1.hide();
 level1.hide();
 R2.hide();
 level2.hide();
 R3.hide();
 level3.hide();

  while(level<=10) {
    if((runTime > 0) && (currTime > runTime)) { break; }
    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
    if(level==5&&!lasso.checkbonus())   //intialises bonus's speed
    {
      bonus_speed=BOMB_SPEED;
    }
    else
     bonus_speed=0;
    if(level>=2)                       //intialises bomb#1's speed
    {
      bomb_speed=BOMB_SPEED;
    }
    if(level>5){                       //intialises bomb#2's speed
     bomb_speed1=BOMB_SPEED;
     }
    switch(c) {
     case 't':
	           lasso.unpause();
	           break;
     case 'y':
	           lasso.yank();
	           break;
     case 'l':
	           lasso.loopit();
	           if(level==5&&!lasso.checkbonus()){
	            lasso.check_for_bonus(&bonus);
	            }
               lasso.check_for_coin(&coin);
               lasso.check_for_coin(&coin2);
               lasso.check_for_bomb(&bomb);
               lasso.check_for_bomb(&bomb1);
	           LASSO_RADIUS=23+(10-level)*3;
	           wait(STEP_TIME*5);
	           break;
     case '[':
	          if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	          break;
     case ']':
	          if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	          break;
     case '-':
	          if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	          break;
     case '=':
              if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	          break;
     case 'q':
	          exit(0);
     default:
	         break;
      }
    }

    lasso.nextStep(stepTime);
    coin.nextStep(stepTime);
    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }
    coin2.nextStep(stepTime);
    if(coin2.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin2.unpause();
      }
    }
    if(level>1){
    bomb.nextStep(stepTime);
    if(bomb.isPaused()) {
      if((currTime-last_bomb_jump_end) >= COIN_GAP) {
	bomb.unpause();
      }
     }
    }
    if(level>5){
    bomb1.nextStep(stepTime);
    if(bomb1.isPaused()) {
      if((currTime-last_bomb_jump_end) >= COIN_GAP) {
	bomb1.unpause();
      }
     }
    }
    if(level==5&&!lasso.checkbonus())
    {bonus.nextStep(stepTime);
    if(bonus.isPaused()) {
      if((currTime-last_bomb_jump_end) >= COIN_GAP) {
	bonus.unpause();
      }
     }
    }
    if(coin.getYPos() > PLAY_Y_HEIGHT) {
    if(level>5)
      aax=10;
     coin.resetCoin();
     if(level==6){
     aax=-10;
     coin2.resetCoin();
     }
     aax=0;
     last_coin_jump_end = currTime;

    }
    if(coin2.getYPos() > PLAY_Y_HEIGHT) {
     if(level>5)
      aax=-10;
     coin2.resetCoin();
     if(level==6){
     aax=10;
     coin.resetCoin();
     }
     aax=0;

     last_coin_jump_end = currTime;
    }
    if(level>1){
     if(bomb.getYPos() > PLAY_Y_HEIGHT) {
      if(level>5)
       aax=10;
      bomb.resetbomb();
      aax=0;
      last_bomb_jump_end = currTime;
     }
    }
    if(level>5){
     if(bomb1.getYPos() > PLAY_Y_HEIGHT) {
      aax=-10;
      bomb1.resetbomb();
      aax=0;
      last_bomb_jump_end = currTime;
     }
    }
    if(level==5&&!lasso.checkbonus()){
     if(bonus.getYPos() > PLAY_Y_HEIGHT) {
     aax=-20;
      bonus.resetBonus();
      aax=0;
      if(lasso.caught()){
       bool z=true;
       lasso.updateb(z);
      }
      last_bomb_jump_end = currTime;
     }
    }
    if(level!=5)
    {aax=-20;
     bonus.resetBonus();
    aax=0;}
    if(level<5){
     aax=-10;
     bomb1.resetbomb();
     aax=0;
    }
    if(level<=5){
    bomb1.resetbomb();
    }
    score=max(score,lasso.getNumCoins());
    if(lasso.checkbonus()){
     level=lasso.getNumCoins()-1;}
    else
     level=lasso.getNumCoins()+1;
    if(lasso.getNumCoins()<0){
     Text t1(WINDOW_X/2,WINDOW_Y/2,"GAME OVER");
     t1.imprint();
     wait(5);
     exit(0);
    }
    if(level==11){
     Text t2(WINDOW_X/2,WINDOW_Y/2,"GAME OVER");
     Text t3(WINDOW_X/2,WINDOW_Y/2+20,Score);
     t2.imprint();
     t3.imprint();
     }
    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    sprintf(Level, "level: %d", level);
    sprintf(Score, "high score: %d", score);
    coinScore.setMessage(coinScoreStr);
    Levelno.setMessage(Level);
    scr.setMessage(Score);
    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End for while
  wait(3);
} // End main_program

