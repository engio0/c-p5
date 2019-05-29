/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <windows.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char szBuffer[81];

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		wsprintf( szBuffer, szBuffer, "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        MessageBox(NULL, szBuffer, "Error", MB_OK);
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			wsprintf( szBuffer, szBuffer, "Warning: Linear texture filtering not enabled!" );
            MessageBox(NULL, szBuffer, "Error", MB_OK);
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			wsprintf( szBuffer, szBuffer, "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            MessageBox(NULL, szBuffer, "Error", MB_OK);

			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				wsprintf( szBuffer, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                MessageBox(NULL, szBuffer, "Error", MB_OK);

				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					wsprintf( szBuffer, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    MessageBox(NULL, szBuffer, "Error", MB_OK);

					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load texture
	gTexture = loadTexture( "viewport.png" );
	if( gTexture == NULL )
	{
		wsprintf( szBuffer, "Failed to load texture image!\n" );
        MessageBox(NULL, szBuffer, "Error", MB_OK);

		success = false;
	}

	//Nothing to load
	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		wsprintf( szBuffer, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        MessageBox(NULL, szBuffer, "Error", MB_OK);

	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			wsprintf( szBuffer, "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
            MessageBox(NULL, szBuffer, "Error", MB_OK);

		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		wsprintf( szBuffer, "Failed to initialize!\n" );
        MessageBox(NULL, szBuffer, "Error", MB_OK);

	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			wsprintf( szBuffer, "Failed to load media!\n" );
            MessageBox(NULL, szBuffer, "Error", MB_OK);

		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Top left corner viewport
				SDL_Rect topLeftViewport;
				topLeftViewport.x = 0;
				topLeftViewport.y = 0;
				topLeftViewport.w = SCREEN_WIDTH / 2;
				topLeftViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport( gRenderer, &topLeftViewport );
				
				//Render texture to screen
				SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );


				//Top right viewport
				SDL_Rect topRightViewport;
				topRightViewport.x = SCREEN_WIDTH / 2;
				topRightViewport.y = 0;
				topRightViewport.w = SCREEN_WIDTH / 2;
				topRightViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport( gRenderer, &topRightViewport );
				
				//Render texture to screen
				SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );


				//Bottom viewport
				SDL_Rect bottomViewport;
				bottomViewport.x = 0;
				bottomViewport.y = SCREEN_HEIGHT / 2;
				bottomViewport.w = SCREEN_WIDTH;
				bottomViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport( gRenderer, &bottomViewport );

				
				//Render texture to screen
				SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );


				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
