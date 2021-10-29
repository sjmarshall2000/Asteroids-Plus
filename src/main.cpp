// Example program:
// Using SDL2 to create an application window

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <map>
#include "Exception.hpp"
#include "MediaManager.hpp"
#include "Game.hpp"
#include "Particle.hpp"

using namespace std;

class MyParticle:public Particle {//TODO: merge MyParticle and Player
	Mix_Chunk *sample;
	public:
	MyParticle(SDL_Renderer *ren,Animation *a,Mix_Chunk *newSample,SDL_Rect *src,
	  double x,double y,double vx,double vy,double ax,double ay, double drag, double forwardAccel):
	  Particle(ren,a,src,x,y,vx,vy,ax,ay, drag, forwardAccel) {
          setDrag(drag);
		  sample=newSample;
	}
	void collision() {
		Mix_PlayChannel(-1,sample,0);
	}
    void shoot(){
        Mix_PlayChannel(-1, sample, 0);
    }
};

class MyGame:public Game{	  
    SDL_Rect src;
    vector<Particle *> particles;
    Animation a,b;
	Mix_Chunk *sound;
    int jx,jy;
	public:
	MyGame(int w=1280,int h=720):Game("Asteroids+",w,h) {

	  sound=media->readWav("media/laser-gun.wav");
      
      for (int i=0;i<1;i++) { //TODO: This is a stupid, stupid little hackjob to get one player, need to move this to Player.hpp
		 int vx=0;
		 int vy=0;
		 a.read(media,"media/anim1.txt");
	//	 SDL_Texture *bitmapTex=media->read("media/obsticle.bmp");
		 src.x=0; src.y=0;
		 SDL_QueryTexture(a.getTexture(), NULL, NULL, &src.w, &src.h);
         particles.push_back(new MyParticle(ren,&a,sound,&src,w/2,h/2,vx,vy,0,0, 0.999, 1000.0));
         particles[i]->setBound(0,0,w,h);
       }
       jx=w/2;
       jy=w/2;

		TTF_Init();
		TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
		SDL_Color White = {255, 255, 255};
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "testing", White); 
		SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
		SDL_Rect Message_rect; 
		Message_rect.x = 0;  
		Message_rect.y = 0; 
		Message_rect.w = 100;
		Message_rect.h = 100;
		SDL_RenderCopy(ren, Message, NULL, &Message_rect);

       b.read(media,"media/background.txt");
       src.x=0; src.y=0; src.w=640; src.h=480;
	}
	void handleKeyUp(SDL_Event keyEvent) {
        switch(keyEvent.key.keysym.sym){ //TODO:switch doesnt allow simultaneous key presses
			
			case SDLK_w:
			case SDLK_UP:
				cout << "Up key released" <<endl;
				// particles[0]->setVelocityDir(100,particles[0]->direction);
				particles[0]->stopGoingForward();

			break;

			case SDLK_s:
			case SDLK_DOWN:
				cout << "Down key released" <<endl;

			break;

			// case SDLK_LEFT:
			// 	cout << "Left key released" <<endl;
			// 	particles[0]->rotate(-1*(M_PI_4 / 4.0));
			// break;

			// case SDLK_RIGHT:
			// 	cout << "Right key released" <<endl;
			// 	particles[0]->rotate(M_PI_4 / 4.0);
			// break;
		}

	}
	void handleKeyDown(SDL_Event keyEvent) {
		
        switch(keyEvent.key.keysym.sym){ //TODO:switch doesnt allow simultaneous key presses
            case SDLK_w:
			case SDLK_UP:
                cout << "Up key pressed" <<endl;
		        // particles[0]->setVelocityDir(100,particles[0]->direction);
      		    particles[0]->goForward();
				  //setAccelerationDir(1000,(particles[0]->direction));

            break;

			case SDLK_s:
            case SDLK_DOWN:
                cout << "Down key pressed" <<endl;
      		    // particles[0]->setAccelerationDir(1000,(particles[0]->direction + M_PI));

            break;
			
			case SDLK_a:
            case SDLK_LEFT:
                cout << "Left key pressed" <<endl;
			    particles[0]->rotate(-1*(M_PI_4 / 4.0));
            break;
			
			case SDLK_d:	
            case SDLK_RIGHT:
                cout << "Right key pressed" <<endl;
			    particles[0]->rotate(M_PI_4 / 4.0);
            break;

            case SDLK_SPACE:
                //particles[0]->shoot();
			break;

        }
	}
	void handleButtonDown(SDL_Event joyEvent) {
		if (joyEvent.jbutton.button==0 && joyEvent.jbutton.which==0)
		  particles[0]->incVelocity(0,-100);
	}
	void handleAxisMovement(SDL_Event joyEvent) {
		if (joyEvent.jaxis.axis==0 && joyEvent.jaxis.which==0)
		  jx=((joyEvent.jaxis.value)*100)/32768;
		if (joyEvent.jaxis.axis==1 && joyEvent.jaxis.which==0)
		  jy=((joyEvent.jaxis.value)*100)/32768;
		particles[0]->setAcceleration(jx,jy);
	}
	void update(double dt) {
      SDL_RenderClear(ren);
      b.update(dt);
      
      SDL_RenderCopy(ren, b.getTexture(), &src, &src);
      for (unsigned i=0;i<particles.size();i++) 
        particles[i]->update(dt);
      SDL_RenderPresent(ren);
	}
	~MyGame() {
	}
};

int main(int argc, char* argv[]) {
    try {
		MyGame g;
		g.run();
	} catch (Exception e) {
		cerr << e ;
	}
	return 0;
}
