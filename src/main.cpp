#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class Exception {
    string description;
    public:
    Exception(string newDescription){
        description = newDescription;
    }
    void fun(/*exception *this */) {
    }
    friend ostream & operator << (ostream &out, const Exception &e){
        return out << "Error: " << e.description << endl;
    }
};

class Game {
    protected:
    SDL_Window *window;
    SDL_Renderer *ren;
    int ticks; //total ticks since start
    
    public:
    Game (string title, int w=640, int h=480){
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow(
            title.c_str(),              //window title
            SDL_WINDOWPOS_UNDEFINED,    //inital window x pos
            SDL_WINDOWPOS_UNDEFINED,    //intial window y pos
            w,                          //width, in px
            h,                          //height, in px
            SDL_WINDOW_OPENGL           //flags: renderer, etc
        );

        if(window==NULL){throw Exception("Failed to create window");}
        ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(ren==NULL){throw Exception("Failed to create renderer");}
        ticks=SDL_GetTicks();
    }

    void run() {
        int newTicks;
        while(1){
            newTicks=SDL_GetTicks();    
            SDL_Event e;
            if(SDL_PollEvent(&e)) {
                if(e.type == SDL_QUIT){
                    break;
                }
            }
            update(double(newTicks-ticks) / 1000.0);
            ticks=newTicks;
            // SDL_Delay(100);
        }
    }

    virtual void update(double dt)=0; //a derived class *has* to override update
    ~Game() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(ren);
        SDL_Quit();
    }

};
class Particle {
  SDL_Renderer *ren;
  SDL_Texture *bitmapTex;
  SDL_Rect *src;
  SDL_Rect dest;
  double x,y,vx,vy,ax,ay;
  public:
  Particle(SDL_Renderer *newRen,SDL_Texture *newBitmapTex, 
           SDL_Rect *newSrc,
           double newx=0.0,double newy=0.0,
           double newvx=0.0,double newvy=0.0,
           double newax=0.0,double neway=0.0) {
	  src=newSrc;
	  ren=newRen;
	  bitmapTex=newBitmapTex;
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
  }
    void update(double dt) {
        vx+=ax*dt; vy+=ay*dt; 
        x+=vx*dt;  y+=vy*dt;
        dest.x=(int)x;
        dest.y=(int)y;
        SDL_RenderCopy(ren, bitmapTex, src, &dest);
    }
};
class MyGame:public Game{
    SDL_Texture *bmpTexture;
    SDL_Rect src,dest;
    vector<Particle *> particles;

    public:
    MyGame(int w=640, int h=480):Game("my first game", w,h) {
        SDL_Surface *ob;

        ob=SDL_LoadBMP("media/arduino.bmp");
        if(ob==NULL){ throw Exception("Failed to load bitmap");}
    
        src.w=ob->w;
        src.h=ob->h;
        dest.w=src.w;
        dest.h=src.h;
        src.x=0;
        src.y=0;
        dest.x=0;
        dest.y=0;

        bmpTexture = SDL_CreateTextureFromSurface(ren, ob);
        if(bmpTexture==NULL){ throw Exception("Failed to create bitmap texture");}
        SDL_FreeSurface(ob);
        for (int i=0;i<100;i++) { 
            int vx=rand()%100-50;
            int vy=rand()%100-50;
            particles.push_back(new Particle(ren,bmpTexture,&src,100,100,vx,vy,0,-10));
        }
    }
    void update(double dt){
        SDL_RenderClear(ren);
        
        // my game code here
        // dest.x++; //TODO: make this respond to dt
        // dest.y++;

        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bmpTexture, &src, &dest);
        SDL_RenderPresent(ren);
        //SDL_Delay(100); //let the game handle this instead
    }
    ~MyGame(){
        SDL_DestroyTexture(bmpTexture);
    }
};

int main(int argc, char* argv[]){

    try {
        MyGame g;
        g.run();

    } catch (Exception e){
        cerr << e;
    }

    return 0;

}