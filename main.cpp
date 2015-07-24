#include "main.h"
#include "tree.h"
#include "camera.h"
#include <iostream>
#include <stdio.h>

Tree *t;
Camera *c;
//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

	glEnable(GL_TEXTURE_2D);
    return true;
}

bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        return false;
    }

    //Enable unicode
    SDL_EnableUNICODE( SDL_TRUE );

    //Initialize OpenGL
    if( initGL() == false )
    {
        return false;
    }
	//create camera
	c = new Camera(SCREEN_WIDTH,SCREEN_HEIGHT);
    //Set caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(90,1, 0.1, 100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

   // glShadeModel(GL_FLAT);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	t = new Tree(12,0);
	c->updateCamera();
	t->init();
	t->trunk->scaleSegment(0,t->trunk->n_edges+1,0.5);
	t->trunk->scaleSegment(t->trunk->n_edges+1,(t->trunk->n_edges+1)*2,0.5);
	t->extrude();

    return true;
}

void handleKeys( unsigned char key, int x, int y )
{
	if(key == SDLK_d){
	 
	}
	if(key == SDLK_a){
	  
	}
	if(key == SDLK_w){
	  
	}
	if(key == SDLK_s){

	}
}

void handleMouseRelease( unsigned char button, int x, int y ){
	if(button == SDL_BUTTON_LEFT){
		c->mousePosRelease(x,y);
		m_mouseClick = false;
	}
}

void handleMousePress(  unsigned char button, int x, int y ){
	if(button == SDL_BUTTON_LEFT){
		c->mousePosPress(x,y);
		m_mouseClick = true;
	}
	if(button == SDL_BUTTON_WHEELUP){

		c->setDistance(c->distance-1);
	}
	if(button == SDL_BUTTON_WHEELDOWN){
		c->setDistance(c->distance+1);
	}
}
void update()
{
}

void render()
{
    //Clear color buffer
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	double distance = c->distance;
	gluLookAt((c->mX)*distance,(c->mY)*distance,(c->mZ)*distance,0,0,0,0,1,0);
	glColor3f(0.4f,0.4f,0.8f);
//	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	t->draw();
//	axes->draw();
    //Render
	glClearDepth(1.0);
    //Update screen
    SDL_GL_SwapBuffers();
}

void handleMouseMovement( unsigned char button, int x, int y ){
	if (m_mouseClick)
    {
		c->updateMousePos(x,y);
		
    }
}

void clean_up()
{
    //Quit SDL
    SDL_Quit();
}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int main( int argc, char *argv[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //The frame rate regulator
    Timer fps;

	//Wait for user exit
	while( quit == false )
	{
        //Start the frame timer
        fps.start();

        //While there are events to handle
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
                quit = true;
            }
            else if( event.type == SDL_KEYDOWN )
            {
                //Handle keypress with current mouse position
                int x = 0, y = 0;
                SDL_GetMouseState( &x, &y );
                handleKeys( event.key.keysym.unicode, x, y );
            }
			else if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                //Handle keypress with current mouse position
                handleMousePress(  event.button.button, event.button.x, event.button.y );
            }
			else if( event.type == SDL_MOUSEBUTTONUP )
            {
                //Handle keypress with current mouse position
                handleMouseRelease(  event.button.button, event.button.x, event.button.y );
            }
			else if(event.type == SDL_MOUSEMOTION)
			{
				handleMouseMovement(event.button.button, event.button.x, event.button.y);
			}
		}

        //Run frame update
        update();

        //Render frame
        render();

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
	}

	//Clean up
	clean_up();

	return 0;
}
