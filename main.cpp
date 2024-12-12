#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <iostream>
#include <cstdlib>

const int HOR = 300;
const int VERT = 300;

void main_function(int (&array)[HOR][VERT]);

int main(int argc, char* argv[]){

    SDL_Window* window=nullptr;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    window = SDL_CreateWindow("C++ SDL2 cellular automaton demo", 500, 200, HOR*3, VERT*3, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Create a rectangle
    SDL_Rect rectangle;
	rectangle.w = 5;
	rectangle.h = 5;

	int game_array[HOR][VERT];
	for (int j = 0; j < VERT; j++)
		for (int i = 0; i < HOR; i++){
			game_array[i][j] = -1;
		}
	game_array[149][149] = 1;
	
    bool gameIsRunning = true;

    while(gameIsRunning){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
        }

        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        //SDL_RenderClear(renderer);

		for(int k = 0; k < 25; k++)
			main_function(game_array);

        // Do our drawing
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		
		
		for (int j = 0; j < VERT; j++)
			for (int i = 0; i < HOR; i++){
				rectangle.x = i*3;
				rectangle.y = j*3;
				
				//if (game_array[i][j])
				//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				//else
				//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

			int R, G, B;
			switch (game_array[i][j]) {
				case 1:
					R = 0;
					G = 0;
					B = 255;
					break;
				case 2:
					R = 0;
					G = 255;
					B = 0;
					break;
				case 3:
					R = 255;
					G = 0;
					B = 0;
					break;
				case 4:
					R = 0;
					G = 0;
					B = 0;
					break;
				case -1:
					R = 255;
					G = 255;
					B = 255;
			}			
				SDL_SetRenderDrawColor(renderer, R, G, B, SDL_ALPHA_OPAQUE);



				SDL_RenderFillRect(renderer, &rectangle);
			}


        // Finally show what we've drawn
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}






void main_function(int (&Field)[HOR][VERT]){


	// add particle
	int x, y;
	auto R = std::rand()%4;
	switch (R) {
		case 0:
			x = 0;
			y = 0;
			break;
		case 1:
			x = 0;
			y = VERT-1;
			break;
		case 2:
			x = HOR-1;
			y = 0;
			break;
		case 3:
			x = HOR-1;
			y = VERT-1;
			break;
	}


	int iter_num = 0;
	bool fix_part = false;
	while (!fix_part){
		iter_num++;

		if (x == 0){
			fix_part = fix_part || Field[x+1][y] > 0;
		} else if (x == HOR-1) {
			fix_part = fix_part || Field[x-1][y] > 0;
		} else {
			fix_part = fix_part || Field[x+1][y] > 0;
			fix_part = fix_part || Field[x-1][y] > 0;
		}
		
		
		
		if (y == 0) {
			fix_part = fix_part || Field[x][y+1] > 0;
		} else if (y == VERT-1) {
			fix_part = fix_part || Field[x][y-1] > 0;
		} else {
			fix_part = fix_part || Field[x][y+1] > 0;
			fix_part = fix_part || Field[x][y-1] > 0;
		}
		
		if (!fix_part) {
			x += (std::rand()%3 - 1);
			y += (std::rand()%3 - 1);
			
			if (x < 0)
				x = 0;
				
			if (y < 0)
				y = 0;
				
			if (x > HOR-1)
				x = HOR-1;
				
			if (y > VERT-1)
				y = VERT-1;
		}
	}

	
	Field[x][y] = R+1;
	//std::cout << iter_num << '\n';
	
}



























