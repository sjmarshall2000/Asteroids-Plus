#pragma once

#include <vector>
#include <fstream>
#include <math.h>
#include "Animation.hpp"

using namespace std;

class Particle {
  SDL_Renderer *ren;
  Animation  *a;
  SDL_Rect *src;
  SDL_Rect dest;
  double x,y,vx,vy,ax,ay;

  double drag;
  

  
  int minx,miny,maxx,maxy;
  
  
  public:
  double direction = 0; //radians


  void incVelocity(double incVx,double incVy ) {
	  vx+=incVx;
	  vy+=incVy;
  }
  void incVelocityDir(double mag, double theta){ //calls above function with respect to angles
    incVelocity(mag * cos(theta), mag * sin(theta));
  }

  void incPosition(double incPx,double incPy) {
	  x+=incPx;
	  y+=incPy;
  }
  void incAcceleration(double incAx,double incAy) {
	  ax+=incAx;
	  ay+=incAy;
  }
  void incAccelerationdDir(double mag, double theta){ //calls above function with respect to angles
    incAcceleration(mag * cos(theta), mag * sin(theta));
  }
  void setVelocity(double newVx,double newVy) {
	  vx=newVx;
	  vy=newVy;
  }
  void setVelocityDir(double mag, double theta){ //calls above function with respect to angles
    setVelocity( mag * sin(theta), mag * cos(theta));
  }
  void setPosition(double newPx,double newPy) {
	  x=newPx;
	  y=newPy;
  }
  void setAcceleration(double newAx,double newAy) {
	  ax=newAx;
	  ay=newAy;
  }
  void setAccelerationDir(double mag, double theta){ //calls above function with respect to angles
    setAcceleration(mag * cos(theta), mag * sin(theta));
  }
  void setDrag(double mag){
    drag = mag;
  }
  void setDirection(double theta){
    direction = theta;
    a->setFrame(theta * (180 / M_PI) + 90);
  }
  void rotate(double dTheta){
    setDirection(direction + dTheta);
  }

  
  
  Particle(SDL_Renderer *newRen,Animation *newA, 
           SDL_Rect *newSrc,
           double newx=0.0,double newy=0.0,
           double newvx=0.0,double newvy=0.0,
           double newax=0.0,double neway=0.0) {
	  src=newSrc;
	  ren=newRen;
	  a=newA;
    a->staticAnimation = true;//TODO: move this to player only
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
	  if (maxx!=minx) {
		  if (x<=minx) { vx=-vx; x=minx; collision();}
		  if (x>=maxx) { vx=-vx; x=maxx; collision();}
	  }
	  if (maxy!=miny) {
		  if (y<=miny) { vy=-vy; y=miny; collision();}
		  if (y>=maxy) { vy=-vy; y=maxy; collision();}
      }
	  vx+=ax*dt;
    if(vx > 0){vx -= drag;}else{vx+=drag;}
    vy+=ay*dt; 
    if(vy > 0){vy -= drag;}else{vy+=drag;}
	  x+=vx*dt;
    y+=vy*dt;
	  dest.x=(int)x;
      dest.y=(int)y;
      a->update(dt);
      SDL_RenderCopy(ren, a->getTexture(), src, &dest);
  }
};
