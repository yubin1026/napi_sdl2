# napi_sdl2

The goal of this library provides SDL2 bindings for node using N-API.


## Supported OS
Currently only macOS


## Installation

```javascript
brew install SDL2
```

```javascript
npm install napi_sdl2
```

## Usage

```javascript
const SDL2 = require('./napi_sdl2');
```

## Example

```javascript
const util = require("util");
const fs = require('fs');

const SDL2 = require('napi_sdl2');

let context = {
	window : null,
	rendere : null
}

function render(context)
{
	let [screen_width, screen_height] = SDL2.SDL_GetWindowSize(context.window);
    //Clear screen
    SDL2.SDL_SetRenderDrawColor( context.renderer, [0xFF, 0xFF, 0xFF, 0xFF] );
    SDL2.SDL_RenderClear( context.renderer );
    
    //Render red filled quad
    SDL2.SDL_SetRenderDrawColor( context.renderer, [0xFF, 0x00, 0x00, 0xFF] );
    SDL2.SDL_RenderFillRect( context.renderer, [screen_width / 4, screen_height / 4, screen_width / 2, screen_height / 2 ] );
    
    //Update screen
    SDL2.SDL_RenderPresent( context.renderer );
}

function main() {

	SDL2.SDL_Init(SDL2.SDL_INIT_EVERYTHING);

	let [screen_width, screen_height] = [800, 800];
	let sdl_window = SDL2.SDL_CreateWindow("SDL Sample", 
		0, 0, screen_width, screen_height, SDL2.SDL_WINDOW_SHOWN | SDL2.SDL_WINDOW_RESIZABLE);
 	let sdl_renderer = SDL2.SDL_CreateRenderer( sdl_window, -1, SDL2.SDL_RENDERER_ACCELERATED );
     //Initialize renderer color
    SDL2.SDL_SetRenderDrawColor( sdl_renderer, [0xFF, 0xFF, 0xFF, 0xFF]);
   
	let quit = false;

	context.window = sdl_window;
	context.renderer = sdl_renderer;
	render(context);
	
	let cursor = SDL2.SDL_CreateSystemCursor(SDL2.SDL_SYSTEM_CURSOR_ARROW);
	SDL2.SDL_SetCursor(cursor);
	SDL2.SDL_ShowCursor(1);
			
	while(!quit)
	{
		let event = {};
		SDL2.SDL_PumpEvents();
		while(1) {
			let ret = SDL2.SDL_PeepEvents(event, 1, SDL2.SDL_GETEVENT, SDL2.SDL_FIRSTEVENT, SDL2.SDL_LASTEVENT);
			if(ret == 1) break;
			SDL2.SDL_Delay(10);
			render(context);
			SDL2.SDL_PumpEvents();
		}

		switch(event.type)
		{
			case "MOUSEBUTTONDOWN":
				break;
			case "MOUSEBUTTONUP":
				break;
			case "MOUSEWHEEL":
				break;
			case "WINDOWEVENT":
				if(event.event == "WINDOWEVENT_RESIZED") {
					[screen_width, screen_height] = SDL2.SDL_GetWindowSize(context.window);

					render(context);
				} else if(event.event == "WINDOWEVENT_SIZE_CHANGED") {
		
				} else if(event.event == "WINDOWEVENT_EXPOSED") {
				}
				break;
			case "KEYDOWN":
				break;
			case "QUIT":
				quit = true;
				break;
		}
	}
	SDL2.SDL_DestroyRenderer(context.renderer );
	SDL2.SDL_DestroyWindow(context.window);
	SDL2.SDL_Quit();
}

main();
```

