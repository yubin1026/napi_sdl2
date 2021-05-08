# napi_sdl2

The goal of this library provides SDL2 bindings for node using N-API.
It is heavily inspired in [node-sdl](https://github.com/creationix/node-sdl).
It is heavily inspired in [napi-sdl2](https://github.com/yubin1026/napi_sdl2).

## Supported OS

 * Linux

## Installation

### Prepare base system

#### Linux

```sh
sudo apt install libsdl2-ttf-dev libsdl2-dev
```
### Setup Node module

```javascript
npm install @vit1251/napi_sdl2
```

## Usage

```javascript
import SDL2 from '@vit1251/napi_sdl2';
```

## Example

Initialize and create SDL window

```javascript
SDL2.SDL_Init(SDL2.SDL_INIT_EVERYTHING);

let [screen_width, screen_height] = [800, 800];
let sdl_window = SDL2.SDL_CreateWindow("SDL Sample", 
	0, 0, screen_width, screen_height, SDL2.SDL_WINDOW_SHOWN | SDL2.SDL_WINDOW_RESIZABLE);
	let sdl_renderer = SDL2.SDL_CreateRenderer( sdl_window, -1, SDL2.SDL_RENDERER_ACCELERATED );
//Initialize renderer color
SDL2.SDL_SetRenderDrawColor( sdl_renderer, [0xFF, 0xFF, 0xFF, 0xFF]);
```

Handling SDL events using SDL_PeepEvents. You also can use SDL_WaitEvent or SDL_PollEvent.
```javascript
let event = {};
SDL2.SDL_PumpEvents();
while(1) {
	let ret = SDL2.SDL_PeepEvents(event, 1, SDL2.SDL_GETEVENT, SDL2.SDL_FIRSTEVENT, SDL2.SDL_LASTEVENT);
	if(ret == 1) break;
	SDL2.SDL_Delay(10);
	render(context);
	SDL2.SDL_PumpEvents();
}
```

Rendering graphics
```javascript
const [screen_width, screen_height] = SDL2.SDL_GetWindowSize(context.window);
//Clear screen
SDL2.SDL_SetRenderDrawColor( context.renderer, [0xFF, 0xFF, 0xFF, 0xFF] );
SDL2.SDL_RenderClear( context.renderer );

//Render red filled quad
SDL2.SDL_SetRenderDrawColor( context.renderer, [0xFF, 0x00, 0x00, 0xFF] );
SDL2.SDL_RenderFillRect( context.renderer, [screen_width / 4, screen_height / 4, screen_width / 2, screen_height / 2 ] );

//Update screen
SDL2.SDL_RenderPresent( context.renderer );
```
