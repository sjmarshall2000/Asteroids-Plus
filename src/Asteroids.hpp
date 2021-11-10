
#pragma once

#include <vector>
#include <fstream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Animation.hpp"

using namespace std;

class Asteroid {
  SDL_Renderer *ren;
  Animation  *small, *big;
  SDL_Rect *src;
  SDL_Rect dest;
  double x,y,vx,vy,ax,ay;
  
  int minx,miny,maxx,maxy;
  public:

  double direction = 0; //radians

  void setDirection(double theta){
    direction = theta;
    a->staticAnimation = true;
    a->setFrame(theta * (180 / M_PI) + 90);
  }
  void rotate(double dTheta){
    setDirection(direction + dTheta);
  }
  
  
  Asteroid(SDL_Renderer *newRen,Animation *newA, 
           SDL_Rect *newSrc,
           double newx=0.0,double newy=0.0,
           double newvx=0.0,double newvy=0.0,
           double newax=0.0,double neway=0.0, 
           double newdrag=0.0, double newforwardaccel=0.0) {
	  src=newSrc;
	  ren=newRen;
	  a=newA;
    // a->staticAnimation = true;//TODO: move this to player only
    a->setFrame(direction * (180 / M_PI));
	  dest.w=src->w;
      dest.h=src->h;
      dest.x=newx;
      dest.y=newy;
      x=newx;
      y=newy;
      vx=newvx; // px/s
      vy=newvy; // px/s
      ax=newax;
      ay=neway;  // px/s/s
      drag=newdrag;
      forwardAccel = newforwardaccel;
      setBound();
  }
  void setBound(int newMinX=0,int newMinY=0,int newMaxX=0,int newMaxY=0) {
      minx=newMinX;
      maxx=newMaxX;
      miny=newMinY;
      maxy=newMaxY;
  }
  virtual void collision() {
  }
  void update(double dt) {
    int spritewidth = dest.w;
    int half = spritewidth / 2;

	  if (maxx!=minx) {
		  if (x<minx-half) { x=maxx-half; collision();}
		  if (x>maxx-half) { x=minx-half; collision();}
	  }
	  if (maxy!=miny) {
		  if (y<miny-half) { y=maxy-half; collision();}
		  if (y>maxy-half) { y=miny-half; collision();}
    }

    if(isMovingForward){
      setAccelerationDir(forwardAccel, direction);
    } else {
      setAccelerationDir(0, direction);
    }

	  vx+=ax*dt;
    vx *= drag * (1-dt);
      // if(vx > drag){vx -= drag * vx;}else if(vx < -1 * drag * vx){vx+=drag;}
    
    
    vy+=ay*dt;// - drag; 
    vy *= drag * (1-dt);
    // if(vy > drag){vy -= drag * vy;}else if(vy < -1 * drag * vy){vy+=drag;}
	  
    
    x+=vx*dt;
    y+=vy*dt;
	  dest.x=(int)x;
      dest.y=(int)y;
      a->update(dt);
      SDL_RenderCopy(ren, a->getTexture(), src, &dest);
  }
};
