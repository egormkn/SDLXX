#include "sdlxx/core/gl.h"

#include <cstddef>

#include <SDL_stdinc.h>
#include <SDL_video.h>

#include "sdlxx/core/window.h"

using namespace sdlxx;

void GL::LoadLibrary(const std::string& path) {
  int return_code = SDL_GL_LoadLibrary(path.c_str());
  if (return_code != 0) {
    throw GlException("Failed to load GL library");
  }
}

void* GL::GetProcAddress(const std::string& proc) { return SDL_GL_GetProcAddress(proc.c_str()); }

void GL::UnloadLibrary() { SDL_GL_UnloadLibrary(); }

bool GL::Context::ExtensionSupported(const std::string& extension) {
  return SDL_GL_ExtensionSupported(extension.c_str()) == SDL_TRUE;
}

void GL::Context::ResetAttributes() { SDL_GL_ResetAttributes(); }

void GL::Context::SetAttribute(Attribute attr, int value) {
  int return_code = SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attr), value);
  if (return_code != 0) {
    throw GlException("Failed to set GL attribute");
  }
}

int GL::Context::GetAttribute(Attribute attr) {
  int value = 0;
  int return_code = SDL_GL_GetAttribute(static_cast<SDL_GLattr>(attr), &value);
  if (return_code != 0) {
    throw GlException("Failed to get GL attribute");
  }
  return value;
}

GL::Context::Context(Window& window) : context_ptr(SDL_GL_CreateContext(window.window_ptr.get())) {
  if (context_ptr == nullptr) {
    throw GlException("Failed to create GL context");
  }
}

GL::Context::~Context() {
  if (context_ptr != nullptr) {
    SDL_GL_DeleteContext(context_ptr);
    context_ptr = nullptr;
  }
}

void GL::Context::MakeCurrent(Window& window) {
  int return_code = SDL_GL_MakeCurrent(window.window_ptr.get(), context_ptr);
  if (return_code != 0) {
    throw GlException("Failed to set up an OpenGL context for a window");
  }
}

Window& GL::Context::GetCurrentWindow() {
  throw GlException("GL::Context::GetCurrentWindow() is not implemented");
}

void* GL::Context::GetCurrentContext() { return SDL_GL_GetCurrentContext(); }

Dimensions GL::Context::GetDrawableSize(Window& window) {
  Dimensions dimensions;
  SDL_GL_GetDrawableSize(window.window_ptr.get(), &dimensions.width, &dimensions.height);
  return dimensions;
}

void GL::Context::SetSwapInterval(int interval) {
  int return_code = SDL_GL_SetSwapInterval(interval);
  if (return_code != 0) {
    throw GlException("Failed to set swap interval");
  }
}

int GL::Context::GetSwapInterval() { return SDL_GL_GetSwapInterval(); }

void GL::Context::SwapWindow(Window& window) { SDL_GL_SwapWindow(window.window_ptr.get()); }
