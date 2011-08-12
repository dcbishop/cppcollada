#include "ViewWindowSDL.hpp"

#include <iostream>
using namespace std;

#include "SDL.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "../Debug/console.h"

#include "../Render/Renderable.hpp"
#include "../GameObjects/Camera.hpp"
#include "../Collada/Collada.hpp"
#include "../Render/RendererGL.hpp"
#include "../Render/Renderer.hpp"
#include "../GameData/Grid.hpp"
#include "../GameObjects/Area.hpp"


ViewWindowSDL::ViewWindowSDL(const int width, const int height): ViewWindow(width, height) {
   DEBUG_M("ViewWindowSDL spawning...");

   if(SDL_Init(SDL_INIT_VIDEO) < 0) {
      ERROR("SDL: Failed to init video: ", SDL_GetError());
      throw "SDL init";
   }

   if(SDL_SetVideoMode(getWidth(), getHeight(), 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
      ERROR("SDL: Failed to set video mode: ", SDL_GetError());
      SDL_Quit();
      throw "SDL setvideo";
   }

   renderer_.setSize(getWidth(), getHeight());

   grid_ = shared_ptr<Grid>(new Grid);
   cam_move_ = false;
   finished_ = false;
}

void ViewWindowSDL::setTitle(const string title) {
   SDL_WM_SetCaption(title.c_str(), NULL);
}

 /**
 * Renders the scene using OpenGL.
 */
void ViewWindowSDL::draw_() {
   static int frame = 0;
   static int last_render_time = 0;
   static int last_fps_time = 0;
   static bool limit_fps_ = true;
   static int fps_ = 0;
   static int mpf_ = 0;
   
   int current_time = getComputerTime_();

   // Limit framerate
   if(limit_fps_ && !( (current_time - last_render_time) >= 1000/60) ) {
      return;
   }

   // Calculate FPS
   frame++;
   if(current_time - last_fps_time > 1000) {
      fps_ = frame*1000.0f/(current_time-last_fps_time);
      last_fps_time = current_time;
      frame = 0;
      LOG("FPS: %d,\tMPF: %d",fps_, mpf_);
      /*char title[255];
      snprintf(title, 254, "CppCollada: \"%s\" FPS: %d, MPF: %d", fps_, mpf_);
      setTitle(title);*/
   }
   last_render_time = current_time;

   renderer_.preFrame();

   CameraPtr camera = getCamera();
   shared_ptr<Area> area;

   if(camera != CameraPtr()) {
      camera->setCamera();
      area = camera->getArea();
   }

   if(area != shared_ptr<Area>()) {
      area->render();
   }

   grid_->render();

   renderer_.postFrame();
   SDL_GL_SwapBuffers();

   mpf_ = getComputerTime_() - current_time;
}

void ViewWindowSDL::handleKeyUp_(const SDL_Event& event) {
   static bool fullscreen = false;
   switch(event.key.keysym.sym) {
      case(SDLK_f):
         fullscreen = !fullscreen;
         DEBUG_M("Toggling fullscreen...");
         if(fullscreen) {
            SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL | SDL_FULLSCREEN);
         } else {
            SDL_SetVideoMode(getWidth(), getHeight(), 0, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL | SDL_RESIZABLE);
         }
         break;
      case(SDLK_q):
         DEBUG_M("Quitting...");
         finished_ = true;
         break;
      default:
         DEBUG_M("Unknown key pressed.");
         break;
   }
}

/**
 * Checks for any SDL events that have occured.
 */
void ViewWindowSDL::checkEvents_() {
   SDL_Event event;
   while(SDL_PollEvent(&event)) {
      switch(event.type) {
         case SDL_QUIT:
            finished_ = true;
            break;
         case SDL_KEYDOWN:
            //handleKeyDown_(event);
            //finished_ = true;
            break;
         case SDL_KEYUP:
            handleKeyUp_(event);
            break;
         case SDL_MOUSEMOTION:
            mx_ = event.motion.x;
            my_ = event.motion.y;
            DEBUG_H("Mouse motion %f %f)", (GLfloat)event.motion.xrel, (GLfloat)event.motion.yrel );
            if(cam_move_) {
               getCamera()->setRotX(getCamera()->getRotX() + (GLfloat)event.motion.xrel / getWidth() * 100);
               getCamera()->setRotY(getCamera()->getRotY() - (GLfloat)event.motion.yrel / getHeight() * 100);
            }
            break;
         case SDL_MOUSEBUTTONDOWN:
            DEBUG_L("Mouse button %d down at (%d, %d)", event.button.button, event.button.x, event.button.y);

            if(event.button.button == 1) {
               cam_move_ = true;
            }
            break;
         case SDL_MOUSEBUTTONUP:
            DEBUG_L("Mouse button %d up at (%d, %d)", event.button.button, event.button.x, event.button.y);
            switch(event.button.button) {
               case 1:
                  cam_move_ = false;
                  break;
               case 2:
                  break;
               case 3:
                  break;
               case 5:
                  getCamera()->setZoom(getCamera()->getZoomTarget() + ZOOM_STEP);
                  break;
               case 4:
                  getCamera()->setZoom(getCamera()->getZoomTarget() - ZOOM_STEP);
                  break;
            }
            break;
         case SDL_VIDEORESIZE:
            DEBUG_M("SDL_VIDEORESIZE %d %d", getWidth(), getHeight());
            setSize(event.resize.w, event.resize.h);
            SDL_SetVideoMode(getWidth(), getHeight(), 0, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL | SDL_RESIZABLE);
            renderer_.setSize(getWidth(), getHeight());
            break;
         default:
            DEBUG_L("Unknown event occured...");
            break;
      }
   }
}

/**
 * The main rendering and input loop.
 */
void ViewWindowSDL::mainLoop() {
   DEBUG_L("Interface::mainLoop()");

   while(!finished_) {
      checkEvents_();
      draw_();
   }
   
   DEBUG_M("Finished...");
}

/**
 * Returns the current time that the interface has been running.
 * @return The time.
 */
int ViewWindowSDL::getComputerTime_() {
   return SDL_GetTicks();
}

Renderer* ViewWindowSDL::getRenderer() {
   return &renderer_;
}
