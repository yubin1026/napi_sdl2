
import SDL2 from '../index.mjs';

const context = {
    window : null,
    rendere : null,
    font : null
};

function render(context)
{

    let [screen_width, screen_height] = SDL2.SDL_GetWindowSize(context.window);

    //Clear screen
    SDL2.SDL_SetRenderDrawColor( context.renderer, [0xC0, 0xC0, 0xC0, 0xFF] );
    SDL2.SDL_RenderClear( context.renderer );

    //Render text message
    if (context.font) {

        const msgSurface = SDL2.TTF_RenderText_Solid(context.font, "Hello, wrold!", [255, 255, 255]);
        const newTexture = SDL2.SDL_CreateTextureFromSurface(context.renderer, msgSurface);

        SDL2.SDL_RenderCopy(context.renderer, newTexture, null, null);
        SDL2.SDL_FreeSurface(msgSurface);
        SDL2.SDL_DestroyTexture(newTexture);

    }

    //Update screen
    SDL2.SDL_RenderPresent( context.renderer );

}

function main() {

    SDL2.SDL_Init(SDL2.SDL_INIT_EVERYTHING);
    SDL2.TTF_Init();

    context.font = SDL2.TTF_OpenFont("FreeSans.ttf", 24);

    const numVideoDisplays = SDL2.SDL_GetNumVideoDisplays();
    console.log(`Number video displays: ${numVideoDisplays}`);

    const displayIndex = 0;
    const [w, h] = SDL2.SDL_GetDesktopDisplayMode(displayIndex);

    console.log(`Display resolution: ${w} x ${h}`);

    const [screen_width, screen_height] = [w, h];

    const sdl_window = SDL2.SDL_CreateWindow("SDL Sample", 0, 0, screen_width, screen_height, SDL2.SDL_WINDOW_FULLSCREEN);
    const sdl_renderer = SDL2.SDL_CreateRenderer( sdl_window, -1, SDL2.SDL_RENDERER_ACCELERATED );

    //Initialize renderer color

    SDL2.SDL_SetRenderDrawColor(sdl_renderer, [0xFF, 0xFF, 0xFF, 0xFF]);

    let quit = false;

    context.window = sdl_window;
    context.renderer = sdl_renderer;
    render(context);

    const cursor = SDL2.SDL_CreateSystemCursor(SDL2.SDL_SYSTEM_CURSOR_ARROW);
    SDL2.SDL_SetCursor(cursor);
    SDL2.SDL_ShowCursor(1);

    while(!quit)
    {
        const event = {};

        const ret = SDL2.SDL_PollEvent(event);
        if (ret == 1) {
            //console.log(`Event: Type = ${event.type}`);
            if (event.type === 'QUIT')
            {
                quit = true;
                break;
            }
        }

        render(context);
        SDL2.SDL_Delay(100);

    }

    SDL2.TTF_Quit();
    SDL2.SDL_DestroyRenderer(context.renderer);
    SDL2.SDL_DestroyWindow(context.window);
    SDL2.SDL_Quit();

}

main();

