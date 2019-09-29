#include <numeric>
#include <system_error>

#include <SDL_render.h>
#include <SDL_video.h>
#include <sdlxx/core/Renderer.h>
#include <sdlxx/core/Window.h>

using namespace sdlxx::core;

const int Window::WINDOW_CENTERED = SDL_WINDOWPOS_CENTERED;

const int Window::WINDOW_UNDEFINED = SDL_WINDOWPOS_UNDEFINED;

Window::Window(const std::string& title, int width, int height,
               const std::unordered_set<Option>& options, int position_x,
               int position_y) {
  Uint32 flags = std::accumulate(options.begin(), options.end(), 0,
                                 [](Uint32 flags, const Option& option) {
                                   return flags | static_cast<uint32_t>(option);
                                 });
  window_ptr = SDL_CreateWindow(title.c_str(), position_x, position_y, width,
                                height, flags);
  if (!window_ptr) {
    throw std::runtime_error("Could not create window: " +
                             std::string(SDL_GetError()));
  }
}

Window::Window(const void* data) {
  window_ptr = SDL_CreateWindowFrom(data);
  if (!window_ptr) {
    throw std::runtime_error("Could not create window: " +
                             std::string(SDL_GetError()));
  }
}

uint32_t Window::getId() const {
  return static_cast<uint32_t>(
      SDL_GetWindowID(static_cast<SDL_Window*>(window_ptr)));
}

std::unordered_set<Window::Option> Window::getOptions() const {
  Uint32 current = SDL_GetWindowFlags(static_cast<SDL_Window*>(window_ptr));
  std::unordered_set<Option> result;
  for (const Option& o : {Option::ALLOW_HIGHDPI, Option::ALWAYS_ON_TOP,
                          Option::BORDERLESS,    Option::FOREIGN,
                          Option::FULLSCREEN,    Option::FULLSCREEN_DESKTOP,
                          Option::HIDDEN,        Option::INPUT_FOCUS,
                          Option::INPUT_GRABBED, Option::MAXIMIZED,
                          Option::MINIMIZED,     Option::MOUSE_CAPTURE,
                          Option::MOUSE_FOCUS,   Option::OPENGL,
                          Option::POPUP_MENU,    Option::RESIZABLE,
                          Option::SHOWN,         Option::SKIP_TASKBAR,
                          Option::TOOLTIP,       Option::UTILITY,
                          Option::VULKAN}) {
    if (static_cast<uint32_t>(o) & current) {
      result.insert(o);
    }
  }
  return result;
}

Window::~Window() {
  if (window_ptr) {
    SDL_DestroyWindow(static_cast<SDL_Window*>(window_ptr));
    window_ptr = nullptr;
  }
}

void Window::setTitle(const std::string& title) {
  SDL_SetWindowTitle(static_cast<SDL_Window*>(window_ptr), title.c_str());
}

std::string Window::getTitle() const {
  return {SDL_GetWindowTitle(static_cast<SDL_Window*>(window_ptr))};
}

void Window::setPosition(const Point& position) {
  SDL_SetWindowPosition(static_cast<SDL_Window*>(window_ptr), position.x,
                        position.y);
}

Point Window::getPosition() const {
  int x, y;
  SDL_GetWindowPosition(static_cast<SDL_Window*>(window_ptr), &x, &y);
  return {x, y};
}

Dimensions Window::getSize() const {
  int w, h;
  SDL_GetWindowSize(static_cast<SDL_Window*>(window_ptr), &w, &h);
  return {static_cast<unsigned>(w), static_cast<unsigned>(h)};
}

void Window::setBordered(bool bordered) {
  SDL_SetWindowBordered(static_cast<SDL_Window*>(window_ptr),
                        bordered ? SDL_TRUE : SDL_FALSE);
}

void Window::setResizable(bool resizable) {
  SDL_SetWindowResizable(static_cast<SDL_Window*>(window_ptr),
                         resizable ? SDL_TRUE : SDL_FALSE);
}

void Window::show() { SDL_ShowWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::hide() { SDL_HideWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::raise() { SDL_RaiseWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::maximize() {
  SDL_MaximizeWindow(static_cast<SDL_Window*>(window_ptr));
}

void Window::minimize() {
  SDL_MinimizeWindow(static_cast<SDL_Window*>(window_ptr));
}

void Window::restore() {
  SDL_RestoreWindow(static_cast<SDL_Window*>(window_ptr));
}

void Window::setFullscreen(const std::unordered_set<Option>& options) {
  Uint32 flags = std::accumulate(options.begin(), options.end(), 0,
                                 [](Uint32 flags, const Option& option) {
                                   return flags | static_cast<uint32_t>(option);
                                 });
  int return_code =
      SDL_SetWindowFullscreen(static_cast<SDL_Window*>(window_ptr), flags);
  if (return_code != 0) {
    throw std::system_error(
        return_code, std::generic_category(),
        "Unable to set fullscreen mode: " + std::string(SDL_GetError()));
  }
}

Renderer Window::getRenderer() const {
  SDL_Renderer* renderer_ptr =
      SDL_GetRenderer(static_cast<SDL_Window*>(window_ptr));
  if (!renderer_ptr) {
    std::string err = SDL_GetError();
    throw std::runtime_error("Unable to get the renderer: " +
                             std::string(SDL_GetError()));
  }
  return {renderer_ptr};
}
