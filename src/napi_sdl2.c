
#include <SDL2/SDL.h>
//#include <SDL.h>
//#include <SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

#define NAPI_VERSION 5
#include <node_api.h>

#include <stdio.h>
#include <stdint.h>

#define NAPI_DEFINE_CONSTANT(target, constant)                           \
  do {                                                                   \
    napi_value v = NULL;                                                 \
    napi_create_int32(env, constant, &v);                                \
    napi_set_named_property(env, target, #constant, v);                  \
  }                                                                      \
  while (0)


#define NAPI_SET_METHOD(target, name, callback)                         \
  do {                                                                  \
    napi_value fn = NULL;                                               \
    napi_create_function(env, NULL, 0, callback, NULL, &fn);            \
    napi_set_named_property(env, target, name, fn);                     \
  }                                                                     \
  while (0)


napi_value SDL_Init_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  
  int arg0 = 0;
  napi_get_value_int32(env, argv[0], &arg0);

  SDL_Init(arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_Quit_Callback(napi_env env, napi_callback_info info) {
  SDL_Quit();

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

// displays

napi_value SDL_GetNumVideoDisplays_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 0;
  napi_value argv[0];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int num;
  num = SDL_GetNumVideoDisplays();

  napi_value ret;
  napi_create_int64(env, (int64_t) num, &ret);
  return ret;
}

napi_value SDL_GetDesktopDisplayMode_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int displayIndex;
  napi_get_value_int32(env, argv[0], &displayIndex);

  SDL_DisplayMode dm;

  SDL_GetDesktopDisplayMode(displayIndex, &dm);

  // return array....
  napi_value ret;
  napi_create_array_with_length(env, 2, &ret);

  napi_value e1;
  napi_create_int32(env, dm.w, &e1);
  napi_set_element(env, ret, 0, e1);

  napi_value e2;
  napi_create_int32(env, dm.h, &e2);
  napi_set_element(env, ret, 1, e2);

  return ret;
}

// window functions....

napi_value SDL_CreateWindow_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 6;
  napi_value argv[6];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  char title[256];
  size_t len;
  napi_get_value_string_utf8(env, argv[0], title, 256, &len);

  int arg1, arg2, arg3, arg4, arg5;
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[2], &arg2);
  napi_get_value_int32(env, argv[3], &arg3);
  napi_get_value_int32(env, argv[4], &arg4);
  napi_get_value_int32(env, argv[5], &arg5);

  SDL_Window* window = SDL_CreateWindow(title, arg1, arg2, arg3, arg4, arg5);

  napi_value ret;
  napi_create_int64(env, (int64_t) window, &ret);
  return ret;
}

napi_value SDL_DestroyWindow_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  SDL_DestroyWindow((SDL_Window*) arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_GetWindowSize_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  int w, h;
  SDL_GetWindowSize((SDL_Window*) arg0, &w, &h);

  // return array....
  napi_value ret;
  napi_create_array_with_length(env, 2, &ret);

  napi_value e;
  napi_create_int32(env, w, &e);
  napi_set_element(env, ret, 0, e);

  napi_create_int32(env, h, &e);
  napi_set_element(env, ret, 1, e);

  //napi_value obj;
  //napi_create_object(env, &obj);

  return ret;
}

napi_value SDL_SetWindowSize_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 3;
  napi_value argv[3];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  int arg1, arg2;
  napi_get_value_int64(env, argv[0], &arg0);
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[2], &arg2);

  SDL_SetWindowSize((SDL_Window*) arg0, arg1, arg2);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_GetWindowSurface_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  SDL_Surface* screen = SDL_GetWindowSurface((SDL_Window*) arg0);

  napi_value ret;
  napi_create_int64(env, (int64_t) screen, &ret);
  
  return ret;
}

// Renderer
napi_value SDL_CreateRenderer_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 3;
  napi_value argv[3];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);
  int arg1, arg2;
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[2], &arg2);

  SDL_Renderer* renderer = SDL_CreateRenderer((SDL_Window*) arg0, arg1, arg2);

  napi_value ret;
  napi_create_int64(env, (int64_t) renderer, &ret);
  
  return ret;
}

napi_value SDL_DestroyRenderer_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  SDL_DestroyRenderer((SDL_Renderer*) arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  
  return ret;
}

napi_value SDL_RenderClear_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  SDL_RenderClear((SDL_Renderer*) arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  
  return ret;
}

napi_value SDL_RenderPresent_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  SDL_RenderPresent((SDL_Renderer*) arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  
  return ret;
}

napi_value SDL_RenderFillRect_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  /*
  int arg1, arg2, arg3, arg4;
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[2], &arg2);
  napi_get_value_int32(env, argv[3], &arg3);
  napi_get_value_int32(env, argv[4], &arg4);

  SDL_SetRenderDrawColor((SDL_Renderer*) arg0, arg1, arg2, arg3, arg4);
*/

  int args[4];
  for(int i = 0; i < 4; i++) {
    napi_value e;
    napi_get_element(env, argv[1], i, &e);
    int v;
    napi_get_value_int32(env, e, &v);
    args[i] = (int) v;
  }
  SDL_Rect fillRect;
  fillRect.x = args[0];
  fillRect.y = args[1];
  fillRect.w = args[2];
  fillRect.h = args[3];

  SDL_RenderFillRect((SDL_Renderer*) arg0, &fillRect);

  napi_value ret;
  napi_get_undefined(env, &ret);
  
  return ret;
}

napi_value SDL_SetRenderDrawColor_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

/*
  int arg1, arg2, arg3, arg4;
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[2], &arg2);
  napi_get_value_int32(env, argv[3], &arg3);
  napi_get_value_int32(env, argv[4], &arg4);

  SDL_SetRenderDrawColor((SDL_Renderer*) arg0, arg1, arg2, arg3, arg4);
*/
  int args[4];
  for(int i = 0; i < 4; i++) {
    napi_value e;
    napi_get_element(env, argv[1], i, &e);
    int v;
    napi_get_value_int32(env, e, &v);
    args[i] = (int) v;
  }
  SDL_SetRenderDrawColor((SDL_Renderer*) arg0, args[0], args[1], args[2], args[3]);

  napi_value ret;
  napi_get_undefined(env, &ret);
  
  return ret;
}

napi_value SDL_RenderCopy_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 4;
  napi_value argv[4];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0, arg1;
  napi_get_value_int64(env, argv[0], &arg0);
  napi_get_value_int64(env, argv[1], &arg1);

  int arg2, arg3;
  napi_get_value_int32(env, argv[2], &arg2);
  napi_get_value_int32(env, argv[3], &arg3);

  // to do implement
  SDL_RenderCopy((SDL_Renderer*) arg0, (SDL_Texture*) arg1, NULL, NULL);

  napi_value ret;
  napi_get_undefined(env, &ret);
  
  return ret;
}

napi_value SDL_CreateTexture_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 5;
  napi_value argv[5];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);
  int arg1, arg2, arg3, arg4;
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[2], &arg2);
  napi_get_value_int32(env, argv[3], &arg3);
  napi_get_value_int32(env, argv[4], &arg4);

  SDL_Texture* texture = SDL_CreateTexture((SDL_Renderer*) arg0, arg1, arg2, arg3, arg4);

  napi_value ret;
  napi_create_int64(env, (int64_t) texture, &ret);
  
  return ret;
}

napi_value SDL_DestroyTexture_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 4;
  napi_value argv[4];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);
  SDL_DestroyTexture((SDL_Texture*) arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  
  return ret;
}

napi_value SDL_UpdateTexture_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 4;
  napi_value argv[4];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);
  int arg1, arg3;
  uint8_t* data;
  size_t len;
  napi_get_buffer_info(env, argv[1], (void**) &data, &len);
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[3], &arg3);

  // to do implement
  SDL_UpdateTexture((SDL_Texture*) arg0,  NULL, data, 640*4);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_CreateTextureFromSurface_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1;
  napi_get_value_int32(env, argv[0], &arg0);
  napi_get_value_int32(env, argv[1], &arg1);

  SDL_Texture *texture = SDL_CreateTextureFromSurface((SDL_Renderer*)arg0, (SDL_Surface*)arg1);

  napi_value ret;
  napi_create_int64(env, (int64_t) texture, &ret);
  return ret;
}

napi_value SDL_FreeSurface_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  napi_get_value_int32(env, argv[0], &arg0);

  SDL_FreeSurface((SDL_Surface*)arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

///////////////////
// Open GL Functions
napi_value SDL_GL_SetAttribute_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1;
  napi_get_value_int32(env, argv[0], &arg0);
  napi_get_value_int32(env, argv[1], &arg1);

  SDL_GL_SetAttribute((SDL_GLattr)arg0, arg1);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_GL_CreateContext_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);


  SDL_GLContext context = SDL_GL_CreateContext((SDL_Window *)arg0);

  napi_value ret;
  napi_create_int64(env, (int64_t) context, &ret);
  return ret;
}

napi_value SDL_GL_SetSwapInterval_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0 = 0;
  napi_get_value_int32(env, argv[0], &arg0);

  SDL_GL_SetSwapInterval(arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_GL_SwapWindow_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  SDL_GL_SwapWindow((SDL_Window *)arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

/// 
// event
napi_value SDL_Delay_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0 = 0;
  napi_get_value_int32(env, argv[0], &arg0);

  SDL_Delay(arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_GetTicks_Callback(napi_env env, napi_callback_info info) {
  unsigned int v = SDL_GetTicks();

  napi_value ret;
  napi_create_int64(env, (int64_t) v, &ret);
  return ret;
}

////////////////////


// borrowed from https://github.com/creationix/node-sdl/blob/master/src/event.cc
napi_value SDLEventToJavascriptObject(napi_env env, SDL_Event event, napi_value obj) {

    switch (event.type) {
      case SDL_TEXTINPUT:
        {
          napi_value v;
          napi_create_string_utf8(env, "TEXTINPUT", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);    

          napi_create_string_utf8(env, event.text.text, NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "text", v);    
        }
        break;
      case SDL_TEXTEDITING:
        {
          napi_value v;
          napi_create_string_utf8(env, "TEXTEDITING", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);    

          napi_create_string_utf8(env, event.text.text, NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "text", v);    

          napi_create_int32(env, event.edit.start, &v);
          napi_set_named_property(env, obj, "start", v);    

          napi_create_int32(env, event.edit.length, &v);
          napi_set_named_property(env, obj, "length", v);    
        }
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        {
          napi_value v;
          napi_create_string_utf8(env, event.type == SDL_KEYDOWN ? "KEYDOWN" : "KEYUP", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);    

          napi_create_int32(env, event.key.keysym.scancode, &v);
          napi_set_named_property(env, obj, "scancode", v);    

          napi_create_int32(env, event.key.keysym.sym, &v);
          napi_set_named_property(env, obj, "sym", v);    

          napi_create_int32(env, event.key.keysym.mod, &v);
          napi_set_named_property(env, obj, "mod", v);    
        }
        break;
      case SDL_MOUSEWHEEL:
        {
          napi_value v;
          napi_create_string_utf8(env, "MOUSEWHEEL", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);  

          napi_create_int32(env, event.wheel.x, &v);
          napi_set_named_property(env, obj, "x", v);     

          napi_create_int32(env, event.wheel.y, &v);
          napi_set_named_property(env, obj, "y", v);     
        }
        break;
      case SDL_MOUSEMOTION: 
        {
          napi_value v;
          napi_create_string_utf8(env, "MOUSEMOTION", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);  
          
          napi_create_int32(env, event.motion.state, &v);
          napi_set_named_property(env, obj, "state", v);     

          napi_create_int32(env, event.motion.which, &v);
          napi_set_named_property(env, obj, "which", v);     

          napi_create_int32(env, event.motion.x, &v);
          napi_set_named_property(env, obj, "x", v);     

          napi_create_int32(env, event.motion.y, &v);
          napi_set_named_property(env, obj, "y", v);   

          napi_create_int32(env, event.motion.xrel, &v);
          napi_set_named_property(env, obj, "xrel", v);     

          napi_create_int32(env, event.motion.yrel, &v);
          napi_set_named_property(env, obj, "yrel", v);    
        }
        break;
      case SDL_MOUSEBUTTONDOWN: 
      case SDL_MOUSEBUTTONUP: 
        {
          napi_value v;
          napi_create_string_utf8(env, event.type == SDL_MOUSEBUTTONDOWN ? "MOUSEBUTTONDOWN" : "MOUSEBUTTONUP", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);  
          
          napi_create_int32(env, event.button.state, &v);
          napi_set_named_property(env, obj, "state", v);     

          napi_create_int32(env, event.button.which, &v);
          napi_set_named_property(env, obj, "which", v);     

          napi_create_int32(env, event.button.x, &v);
          napi_set_named_property(env, obj, "x", v);     

          napi_create_int32(env, event.button.y, &v);
          napi_set_named_property(env, obj, "y", v);   

        }
        break;    
      case SDL_QUIT: 
        {
          napi_value v;
          napi_create_string_utf8(env, "QUIT", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);  
        }
        break;
      case SDL_WINDOWEVENT: 
        {
          napi_value v;
          napi_create_string_utf8(env, "WINDOWEVENT", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);          

          if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
            napi_create_string_utf8(env, "WINDOWEVENT_RESIZED", NAPI_AUTO_LENGTH, &v);
            napi_set_named_property(env, obj, "event", v);    
          } else if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            napi_create_string_utf8(env, "WINDOWEVENT_SIZE_CHANGED", NAPI_AUTO_LENGTH, &v);
            napi_set_named_property(env, obj, "event", v);    
          } else if(event.window.event == SDL_WINDOWEVENT_EXPOSED) {
            napi_create_string_utf8(env, "WINDOWEVENT_EXPOSED", NAPI_AUTO_LENGTH, &v);
            napi_set_named_property(env, obj, "event", v);    
          }
        }
        break;     
      default:
        {
          napi_value v;
          napi_create_string_utf8(env, "UNKNOWN", NAPI_AUTO_LENGTH, &v);
          napi_set_named_property(env, obj, "type", v);   

          napi_create_int32(env, event.type, &v);
          napi_set_named_property(env, obj, "typeCode", v);     
        }
        break;
    }
    return obj;
}

napi_value SDL_PumpEvents_Callback(napi_env env, napi_callback_info info) {

  SDL_PumpEvents();

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}


napi_value SDL_PeepEvents_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 5;
  napi_value argv[5];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);


  int arg1, arg2, arg3, arg4;
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[2], &arg2);
  napi_get_value_int32(env, argv[3], &arg3);
  napi_get_value_int32(env, argv[4], &arg4);

  napi_value obj;
  napi_coerce_to_object(env, argv[0], &obj);


  SDL_Event e;
  //int err = SDL_PeepEvents(&e, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
  int err = SDL_PeepEvents(&e, arg1, arg2, arg3, arg4);
  SDLEventToJavascriptObject(env, e, obj);

  napi_value ret;
  napi_create_int32(env, err, &ret);
  return ret;
}

napi_value SDL_WaitEvent_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  napi_value obj;
  napi_coerce_to_object(env, argv[0], &obj);

  SDL_Event e;
  int err = SDL_WaitEvent(&e);

  SDLEventToJavascriptObject(env, e, obj);

  napi_value ret;
  napi_create_int32(env, err, &ret);
  return ret;
}


napi_value SDL_PollEvent_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  napi_value obj;
  napi_coerce_to_object(env, argv[0], &obj);

  SDL_Event e;
  int err = SDL_PollEvent(&e);

  SDLEventToJavascriptObject(env, e, obj);

  napi_value ret;
  napi_create_int32(env, err, &ret);
  return ret;
}

napi_value SDL_PushEvent_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  napi_value obj;
  napi_coerce_to_object(env, argv[0], &obj);

  // not yet : need obj to event conversion
  SDL_Event e;
  //int err = SDL_PushEvent(&e);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_RegisterEvents_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  napi_get_value_int32(env, argv[0], &arg0);

  uint32_t v;
  v = SDL_RegisterEvents(arg0);

  napi_value ret;
  napi_create_uint32(env, v, &ret);
  return ret;
}

///////////

napi_value SDL_StartTextInput_Callback(napi_env env, napi_callback_info info) {

  SDL_StartTextInput();

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_StopTextInput_Callback(napi_env env, napi_callback_info info) {

  SDL_StopTextInput();

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_SetTextInputRect_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 4;
  napi_value argv[4];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1, arg2, arg3;
  napi_get_value_int32(env, argv[0], &arg0);
  napi_get_value_int32(env, argv[1], &arg1);
  napi_get_value_int32(env, argv[2], &arg2);
  napi_get_value_int32(env, argv[3], &arg3);

  SDL_Rect rect;
  rect.x = arg0;
  rect.y = arg1;
  rect.w = arg2;
  rect.h = arg3;

  SDL_SetTextInputRect(&rect);
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

// cursor
napi_value SDL_ShowCursor_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  napi_get_value_int32(env, argv[0], &arg0);
  SDL_ShowCursor(arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_SetCursor_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);
  SDL_SetCursor((SDL_Cursor*) arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value SDL_GetCursor_Callback(napi_env env, napi_callback_info info) {

  SDL_Cursor* cursor = SDL_GetCursor();

  napi_value ret;
  napi_create_int64(env, (int64_t) cursor, &ret);
  return ret;
}

napi_value SDL_CreateCursor_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 6;
  napi_value argv[6];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  uint8_t* data;
  size_t len;
  napi_get_buffer_info(env, argv[0], (void**) &data, &len);
  uint8_t* mask;
  napi_get_buffer_info(env, argv[1], (void**) &data, &len);

  int arg2, arg3, arg4, arg5;
  napi_get_value_int32(env, argv[2], &arg2); 
  napi_get_value_int32(env, argv[3], &arg3); 
  napi_get_value_int32(env, argv[4], &arg4); 
  napi_get_value_int32(env, argv[5], &arg5); 

  SDL_Cursor* cursor = SDL_CreateCursor((const uint8_t*)data, (const uint8_t*)mask, arg2, arg3, arg4, arg5);

  napi_value ret;
  napi_create_int64(env, (int64_t) cursor, &ret);
  return ret;
}

napi_value SDL_CreateSystemCursor_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  napi_get_value_int32(env, argv[0], &arg0);  
  SDL_Cursor* cursor = SDL_CreateSystemCursor((SDL_SystemCursor)arg0);

  napi_value ret;
  napi_create_int64(env, (int64_t) cursor, &ret);
  return ret;
}

/////

napi_value TTF_Init_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 0;
  napi_value argv[0];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  TTF_Init();

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value TTF_OpenFont_Callback(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  char path[256] = {0};
  size_t len;
  napi_get_value_string_utf8(env, argv[0], path, 256, &len);

  int size;
  napi_get_value_int32(env, argv[1], &size);

  TTF_Font* font = TTF_OpenFont(path, size);

  napi_value ret;
  napi_create_int64(env, (int64_t) font, &ret);
  return ret;
}

napi_value TTF_CloseFont_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 1;
  napi_value argv[1];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  TTF_CloseFont((TTF_Font*)arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value TTF_RenderText_Solid_Callback(napi_env env, napi_callback_info info) {

  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  napi_get_value_int64(env, argv[0], &arg0);

  char arg1[512] = {0};
  size_t len;
  napi_get_value_string_utf8(env, argv[1], arg1, 512, &len);

  SDL_Color color = { 0x00, 0xC0, 0x00 };

  SDL_Surface *surface = TTF_RenderText_Solid((TTF_Font*)arg0, arg1, color);

  napi_value ret;
  napi_create_int64(env, (int64_t) surface, &ret);
  return ret;
}

/////

napi_value Init(napi_env env, napi_value exports) {

  NAPI_DEFINE_CONSTANT(exports, SDL_INIT_VIDEO);
  NAPI_DEFINE_CONSTANT(exports, SDL_INIT_EVERYTHING);
  NAPI_DEFINE_CONSTANT(exports, SDL_QUIT);
  NAPI_DEFINE_CONSTANT(exports, SDL_WINDOWPOS_UNDEFINED);
  NAPI_DEFINE_CONSTANT(exports, SDL_WINDOW_RESIZABLE);
  NAPI_DEFINE_CONSTANT(exports, SDL_WINDOW_OPENGL);
  NAPI_DEFINE_CONSTANT(exports, SDL_WINDOW_SHOWN);
  NAPI_DEFINE_CONSTANT(exports, SDL_WINDOW_FULLSCREEN);
  NAPI_DEFINE_CONSTANT(exports, SDL_PIXELFORMAT_ARGB8888);


  NAPI_DEFINE_CONSTANT(exports, SDL_WINDOWEVENT);
  NAPI_DEFINE_CONSTANT(exports, SDL_MOUSEWHEEL);
  NAPI_DEFINE_CONSTANT(exports, SDL_WINDOWEVENT_RESIZED);
  NAPI_DEFINE_CONSTANT(exports, SDL_MOUSEBUTTONDOWN);
  NAPI_DEFINE_CONSTANT(exports, SDL_KEYDOWN);
  NAPI_DEFINE_CONSTANT(exports, SDL_TEXTINPUT);
  NAPI_DEFINE_CONSTANT(exports, SDL_TEXTEDITING);
  NAPI_DEFINE_CONSTANT(exports, SDL_FIRSTEVENT);
  NAPI_DEFINE_CONSTANT(exports, SDL_LASTEVENT);
  NAPI_DEFINE_CONSTANT(exports, SDL_ADDEVENT);
  NAPI_DEFINE_CONSTANT(exports, SDL_PEEKEVENT);
  NAPI_DEFINE_CONSTANT(exports, SDL_GETEVENT);


  NAPI_DEFINE_CONSTANT(exports, SDLK_ESCAPE);
  NAPI_DEFINE_CONSTANT(exports, SDLK_LEFT);
  NAPI_DEFINE_CONSTANT(exports, SDLK_RIGHT);
  NAPI_DEFINE_CONSTANT(exports, SDLK_UP);
  NAPI_DEFINE_CONSTANT(exports, SDLK_DOWN);
  NAPI_DEFINE_CONSTANT(exports, SDLK_RETURN);
  NAPI_DEFINE_CONSTANT(exports, SDLK_TAB);
  NAPI_DEFINE_CONSTANT(exports, SDLK_BACKSPACE);
  NAPI_DEFINE_CONSTANT(exports, SDLK_DELETE);

  NAPI_DEFINE_CONSTANT(exports, KMOD_LSHIFT);
  NAPI_DEFINE_CONSTANT(exports, KMOD_RSHIFT);
  NAPI_DEFINE_CONSTANT(exports, KMOD_LCTRL);
  NAPI_DEFINE_CONSTANT(exports, KMOD_RCTRL);
  NAPI_DEFINE_CONSTANT(exports, KMOD_LALT);
  NAPI_DEFINE_CONSTANT(exports, KMOD_RALT);
  NAPI_DEFINE_CONSTANT(exports, KMOD_CAPS);
  NAPI_DEFINE_CONSTANT(exports, KMOD_CTRL);
  NAPI_DEFINE_CONSTANT(exports, KMOD_SHIFT);
  NAPI_DEFINE_CONSTANT(exports, KMOD_ALT);


  NAPI_DEFINE_CONSTANT(exports, SDL_GL_CONTEXT_FLAGS);
  NAPI_DEFINE_CONSTANT(exports, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  NAPI_DEFINE_CONSTANT(exports, SDL_GL_DOUBLEBUFFER);
  NAPI_DEFINE_CONSTANT(exports, SDL_GL_MULTISAMPLEBUFFERS);
  NAPI_DEFINE_CONSTANT(exports, SDL_GL_MULTISAMPLESAMPLES);
  NAPI_DEFINE_CONSTANT(exports, SDL_GL_DEPTH_SIZE);
  NAPI_DEFINE_CONSTANT(exports, SDL_GL_STENCIL_SIZE);
  NAPI_DEFINE_CONSTANT(exports, SDL_GL_CONTEXT_MAJOR_VERSION);
  NAPI_DEFINE_CONSTANT(exports, SDL_GL_CONTEXT_MINOR_VERSION);


  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_ARROW);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_IBEAM);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_WAIT);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_CROSSHAIR);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_WAITARROW);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_SIZENWSE);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_SIZENESW);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_SIZEWE);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_SIZENS);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_SIZEALL);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_NO);
  NAPI_DEFINE_CONSTANT(exports, SDL_SYSTEM_CURSOR_HAND);


  NAPI_SET_METHOD(exports, "SDL_Init", SDL_Init_Callback);
  NAPI_SET_METHOD(exports, "SDL_Quit", SDL_Quit_Callback);

  NAPI_SET_METHOD(exports, "SDL_GetNumVideoDisplays", SDL_GetNumVideoDisplays_Callback);
  NAPI_SET_METHOD(exports, "SDL_GetDesktopDisplayMode", SDL_GetDesktopDisplayMode_Callback);

  NAPI_SET_METHOD(exports, "SDL_CreateWindow", SDL_CreateWindow_Callback);
  NAPI_SET_METHOD(exports, "SDL_DestroyWindow", SDL_DestroyWindow_Callback);
  NAPI_SET_METHOD(exports, "SDL_GetWindowSize", SDL_GetWindowSize_Callback);
  NAPI_SET_METHOD(exports, "SDL_SetWindowSize", SDL_SetWindowSize_Callback);
  NAPI_SET_METHOD(exports, "SDL_GetWindowSurface", SDL_GetWindowSurface_Callback); 

  NAPI_SET_METHOD(exports, "SDL_CreateRenderer", SDL_CreateRenderer_Callback);
  NAPI_SET_METHOD(exports, "SDL_DestroyRenderer", SDL_DestroyRenderer_Callback);
  NAPI_SET_METHOD(exports, "SDL_RenderClear", SDL_RenderClear_Callback);  
  NAPI_SET_METHOD(exports, "SDL_RenderPresent", SDL_RenderPresent_Callback);
  NAPI_SET_METHOD(exports, "SDL_SetRenderDrawColor", SDL_SetRenderDrawColor_Callback);
  NAPI_SET_METHOD(exports, "SDL_RenderCopy", SDL_RenderCopy_Callback);
  NAPI_SET_METHOD(exports, "SDL_RenderFillRect", SDL_RenderFillRect_Callback);

  NAPI_SET_METHOD(exports, "SDL_CreateTexture", SDL_CreateTexture_Callback);
  NAPI_SET_METHOD(exports, "SDL_DestroyTexture", SDL_DestroyTexture_Callback);
  NAPI_SET_METHOD(exports, "SDL_UpdateTexture", SDL_UpdateTexture_Callback);

  NAPI_SET_METHOD(exports, "SDL_CreateTextureFromSurface", SDL_CreateTextureFromSurface_Callback);

  NAPI_SET_METHOD(exports, "SDL_FreeSurface", SDL_FreeSurface_Callback);

  NAPI_SET_METHOD(exports, "SDL_Delay", SDL_Delay_Callback);
  NAPI_SET_METHOD(exports, "SDL_GetTicks", SDL_GetTicks_Callback);
  NAPI_SET_METHOD(exports, "SDL_PumpEvents", SDL_PumpEvents_Callback);
  NAPI_SET_METHOD(exports, "SDL_WaitEvent", SDL_WaitEvent_Callback);
  NAPI_SET_METHOD(exports, "SDL_PollEvent", SDL_PollEvent_Callback);
  NAPI_SET_METHOD(exports, "SDL_PushEvent", SDL_PushEvent_Callback);
  NAPI_SET_METHOD(exports, "SDL_PeepEvents", SDL_PeepEvents_Callback);
  NAPI_SET_METHOD(exports, "SDL_RegisterEvents", SDL_RegisterEvents_Callback);

  NAPI_SET_METHOD(exports, "SDL_StartTextInput", SDL_StartTextInput_Callback);
  NAPI_SET_METHOD(exports, "SDL_StopTextInput", SDL_StopTextInput_Callback);
  NAPI_SET_METHOD(exports, "SDL_SetTextInputRect", SDL_SetTextInputRect_Callback);
  NAPI_SET_METHOD(exports, "SDL_SetTextInputRect", SDL_SetTextInputRect_Callback);

  NAPI_SET_METHOD(exports, "SDL_ShowCursor", SDL_ShowCursor_Callback);
  NAPI_SET_METHOD(exports, "SDL_GetCursor", SDL_GetCursor_Callback);
  NAPI_SET_METHOD(exports, "SDL_SetCursor", SDL_SetCursor_Callback);
  NAPI_SET_METHOD(exports, "SDL_CreateCursor", SDL_CreateCursor_Callback);
  NAPI_SET_METHOD(exports, "SDL_CreateSystemCursor", SDL_CreateSystemCursor_Callback);

  NAPI_SET_METHOD(exports, "SDL_GL_SetAttribute", SDL_GL_SetAttribute_Callback);
  NAPI_SET_METHOD(exports, "SDL_GL_CreateContext", SDL_GL_CreateContext_Callback);
  NAPI_SET_METHOD(exports, "SDL_GL_SetSwapInterval", SDL_GL_SetSwapInterval_Callback);
  NAPI_SET_METHOD(exports, "SDL_GL_SwapWindow", SDL_GL_SwapWindow_Callback);

  NAPI_SET_METHOD(exports, "TTF_Init", TTF_Init_Callback);
  NAPI_SET_METHOD(exports, "TTF_OpenFont", TTF_OpenFont_Callback);
  NAPI_SET_METHOD(exports, "TTF_CloseFont", TTF_CloseFont_Callback);
  NAPI_SET_METHOD(exports, "TTF_RenderText_Solid", TTF_RenderText_Solid_Callback);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)