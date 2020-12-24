# napi_sdl2

The goal of this library provides SDL2 bindings for node using N-API.  
It is heavily inspired in [node-sdl](https://github.com/creationix/node-sdl).  
You can use napi_sdl2 alone but recommend to use it with [napi_openvg](https://github.com/yubin1026/napi_openvg).  

## Supported OS

 * macOS
 * Linux

## Installation

### Prepare base system

#### MacOS

```sh
brew install SDL2
```

#### Linux

```sh
sudo apt install libsdl2-ttf-dev libsdl2-dev
```

### Setup  Node module

```javascript
npm install napi_sdl2
```

## Usage

```javascript
const SDL2 = require('napi_sdl2');
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
let [screen_width, screen_height] = SDL2.SDL_GetWindowSize(context.window);
//Clear screen
SDL2.SDL_SetRenderDrawColor( context.renderer, [0xFF, 0xFF, 0xFF, 0xFF] );
SDL2.SDL_RenderClear( context.renderer );

//Render red filled quad
SDL2.SDL_SetRenderDrawColor( context.renderer, [0xFF, 0x00, 0x00, 0xFF] );
SDL2.SDL_RenderFillRect( context.renderer, [screen_width / 4, screen_height / 4, screen_width / 2, screen_height / 2 ] );

//Update screen
SDL2.SDL_RenderPresent( context.renderer );
```

## License

(The MIT License)

Copyright (c) 2018 Yubin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

