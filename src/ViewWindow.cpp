#include "ViewWindow.hpp"

#include <iostream>
using namespace std;

#include "SDL.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "Collada.hpp"
#include "ColladaRendererGL.hpp"


ViewWindow::ViewWindow(int width, int height) {
   width_ = width;
   height_ = height;

   if(SDL_Init(SDL_INIT_VIDEO) < 0) {
      cerr << "SDL: Failed to init video: " << SDL_GetError();
      throw "SDL init";
   }

   if(SDL_SetVideoMode(width_, height_, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
      cerr << "SDL: Failed to set video mode: " << SDL_GetError();
      SDL_Quit();
      throw "SDL setvideo";
   }
}

void ViewWindow::setCollada(Collada* collada) {
   collada_ = collada;
   collada_->setRenderer(&renderer_);
}

void ViewWindow::setTitle(const string title) {
	SDL_WM_SetCaption(title.c_str(), NULL);
}

void ViewWindow::setPerspective_() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, width_ / height_, 0.1f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
}

 /**
 * Renders the scene using OpenGL.
 */
void ViewWindow::draw_() {
   static int frame = 0;
   static int last_render_time = 0;
   static int last_fps_time = 0;
   static bool limit_fps_ = true;
   static int fps_ = 0;
   static int mpf_ = 0;
   
   int current_time = getComputerTime();

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
      cout << "FPS: " << fps_ << ",\t MPF: " << mpf_ << endl;
   }
   last_render_time = current_time;

   setPerspective_();
   glLoadIdentity();
   //camera_.Position();

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glTranslatef(0.0f, -2.0f, -20.0f);
   drawGrid_();

   if(collada_) {
      // DRAW THE MODEL!
      //ColladaRendererGL::render(collada_);
      collada_->render();
   }

   /*glBegin(GL_LINES);
      glVertex3f(0.0, 0.0, -1.0);
      glVertex3f(1.0, 0.0, -10.0);
   glEnd();*/


   glFlush();
   SDL_GL_SwapBuffers();

   mpf_ = getComputerTime() - current_time;
}

/**
 * Checks for any SDL events that have occured.
 */
void ViewWindow::checkEvents_() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				finished_ = true;
				break;
			case SDL_KEYDOWN:
				//handleKeyDown_(event);
            finished_ = true;
				break;
			case SDL_KEYUP:
				//handleKeyUp_(event);
				break;
			case SDL_MOUSEMOTION:
				//mx_ = event.motion.x;
				//my_ = event.motion.y;
				//if(cam_move_) {
					//camera_.setRotX(camera_.getRotX() + (GLfloat)event.motion.xrel / width_ * 100);
					//camera_.setRotY(camera_.getRotY() - (GLfloat)event.motion.yrel / height_ * 100);
				//}
				break;
			case SDL_MOUSEBUTTONDOWN:
				cout << "TODO FIXME: Mouse button %d down at (%d, %d)" << event.button.button <<  event.button.x << event.button.y << endl;

				if(event.button.button == 3) {
					//cam_move_ = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				cout << "TODO FIXME: Mouse button %d up at (%d, %d)" << event.button.button << event.button.x << event.button.y << endl;
				switch(event.button.button) {
					case 1:
						//handleMouse1_(event);
                  break;
					case 2:
						//handleMouse3_(event);
                  break;
					case 3:
						//cam_move_ = false;
                  break;
					case 5:
						//camera_.setZoom(camera_.getZoomTarget() + ZOOM_STEP);
                  break;
					case 4:
						//camera_.setZoom(camera_.getZoomTarget() - ZOOM_STEP);
                  break;
				}
				break;
			case SDL_VIDEORESIZE:
				//resizeEvent_(event);
				break;
			default:
				cout << "Unknown event occured...\n";
				break;
		}
	}
}

void ViewWindow::drawGrid_() {
   int size_x = 10;
   int size_y = 10;
   int size_z = 0;

   float spacing = 1.0f;

   // TODO: This is a stupid way of drawing grid
   glColor3f(1.0f, 1.0f, 1.0f);
   glBegin(GL_LINES);
   for(int y = 0; y < size_y; y++) {
      float y1 = y * spacing;
      float y2 = y1 + spacing;
      for(int x = 0; x < size_x; x++) {
         float x1 = x * spacing;
         float x2 = x1 + spacing;

         glVertex3f(x1, 0.0, y1);
         glVertex3f(x2, 0.0, y1);
         glVertex3f(x1, 0.0, y1);
         glVertex3f(x1, 0.0, y2);

         glVertex3f(x1, 0.0, -y1);
         glVertex3f(x2, 0.0, -y1);
         glVertex3f(x1, 0.0, -y1);
         glVertex3f(x1, 0.0, -y2);

         glVertex3f(-x1, 0.0, y1);
         glVertex3f(-x2, 0.0, y1);
         glVertex3f(-x1, 0.0, y1);
         glVertex3f(-x1, 0.0, y2);

         glVertex3f(-x1, 0.0, -y1);
         glVertex3f(-x2, 0.0, -y1);
         glVertex3f(-x1, 0.0, -y1);
         glVertex3f(-x1, 0.0, -y2);
      }
   }
   glEnd();
}

/**
 * The main rendering and input loop.
 */
void ViewWindow::mainLoop() {
	cout << "Interface::mainLoop()\n";

	while(!finished_) {
      checkEvents_();
		draw_();
	}
}

/**
 * Returns the current time that the interface has been running.
 * @return The time.
 */
int ViewWindow::getComputerTime() {
	return SDL_GetTicks();
}
