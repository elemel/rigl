#ifndef RIGL_OPENGL_HPP
#define RIGL_OPENGL_HPP

#if __APPLE__
#include "TargetConditionals.h"
#endif

#if TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES2/gl.h>
#else
#include <SDL_opengl.h>
#endif

#endif
