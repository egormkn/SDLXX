#include <numeric>
#include <system_error>
#include <type_traits>

#include <SDL_render.h>
#include <SDL_video.h>
#include <sdlxx/core/renderer.h>
#include <sdlxx/core/surface.h>
#include <sdlxx/core/window.h>

using namespace sdlxx::core;

// Convert options into bit mask
template <typename Flag>
Uint32 GetFlagsMask(const std::unordered_set<Flag>& flags) {
  return std::accumulate(flags.begin(), flags.end(), 0, [](Uint32 flags, const Flag& flag) {
    return flags | static_cast<std::underlying_type_t<Flag>>(flag);
  });
}

static_assert(Window::WINDOW_POS_CENTERED == SDL_WINDOWPOS_CENTERED);

static_assert(Window::WINDOW_POS_UNDEFINED == SDL_WINDOWPOS_UNDEFINED);

Window::Window(const std::string& title, int width, int height, const Window::Flags& flags,
               int position_x, int position_y) {
  Uint32 flags_mask = GetFlagsMask(flags);
  window_ptr = SDL_CreateWindow(title.c_str(), position_x, position_y, width, height, flags_mask);
  if (!window_ptr) {
    throw std::runtime_error("Could not create window: " + std::string(SDL_GetError()));
  }
}

Window::Window(const void* data) {
  window_ptr = SDL_CreateWindowFrom(data);
  if (!window_ptr) {
    throw std::runtime_error("Could not create window: " + std::string(SDL_GetError()));
  }
}

Window::Window(Window::Id id) {
  window_ptr = SDL_GetWindowFromID(id);
  if (!window_ptr) {
    throw std::runtime_error("Could not find window: " + std::string(SDL_GetError()));
  }
}

Window::Id Window::GetId() const {
  return static_cast<uint32_t>(SDL_GetWindowID(static_cast<SDL_Window*>(window_ptr)));
}

Window::Flags Window::GetFlags() const {
  Uint32 current = SDL_GetWindowFlags(static_cast<SDL_Window*>(window_ptr));
  Flags result;
  for (const Flag& f : {Flag::ALLOW_HIGHDPI, Flag::ALWAYS_ON_TOP, Flag::BORDERLESS,
                        Flag::FOREIGN,       Flag::FULLSCREEN,    Flag::FULLSCREEN_DESKTOP,
                        Flag::HIDDEN,        Flag::INPUT_FOCUS,   Flag::INPUT_GRABBED,
                        Flag::MAXIMIZED,     Flag::MINIMIZED,     Flag::MOUSE_CAPTURE,
                        Flag::MOUSE_FOCUS,   Flag::OPENGL,        Flag::POPUP_MENU,
                        Flag::RESIZABLE,     Flag::SHOWN,         Flag::SKIP_TASKBAR,
                        Flag::TOOLTIP,       Flag::UTILITY,       Flag::VULKAN,
                        Flag::METAL}) {
    if (static_cast<uint32_t>(f) & current) {
      result.insert(f);
    }
  }
  return result;
}

Window::~Window() {
  if (renderer) {
    renderer.reset();
  }
  if (window_ptr) {
    SDL_DestroyWindow(static_cast<SDL_Window*>(window_ptr));
    window_ptr = nullptr;
  }
}

Display Window::GetDisplay() const {
  if (int index = SDL_GetWindowDisplayIndex(static_cast<SDL_Window*>(window_ptr)); index != -1) {
    return Display(index);
  } else {
    throw std::runtime_error("Can't get display for the window");
  }
}

void Window::SetDisplayMode(const Display::Mode& mode) {
  SDL_DisplayMode new_mode = {mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata};
  int return_code = SDL_SetWindowDisplayMode(static_cast<SDL_Window*>(window_ptr), &new_mode);
  if (return_code == -1) {
    throw std::runtime_error("Can't set display mode for the window");
  }
}

void Window::SetDefaultDisplayMode() {
  int return_code = SDL_SetWindowDisplayMode(static_cast<SDL_Window*>(window_ptr), NULL);
  if (return_code == -1) {
    throw std::runtime_error("Can't set default display mode for the window");
  }
}

Display::Mode Window::GetDisplayMode() const {
  SDL_DisplayMode mode;
  int return_code = SDL_GetWindowDisplayMode(static_cast<SDL_Window*>(window_ptr), &mode);
  if (return_code == -1) {
    throw std::runtime_error("Can't get display mode for the window");
  }
  return {mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata};
}

uint32_t Window::GetPixelFormat() const {
  return static_cast<uint32_t>(SDL_GetWindowPixelFormat(static_cast<SDL_Window*>(window_ptr)));
}

void Window::SetTitle(const std::string& title) {
  SDL_SetWindowTitle(static_cast<SDL_Window*>(window_ptr), title.c_str());
}

std::string Window::GetTitle() const {
  return {SDL_GetWindowTitle(static_cast<SDL_Window*>(window_ptr))};
}

void Window::SetIcon(std::shared_ptr<Surface> icon) {}

void* Window::SetData(const std::string& name, void* userdata) {
  return SDL_SetWindowData(static_cast<SDL_Window*>(window_ptr), name.c_str(), userdata);
}

void* Window::GetData(const std::string& name) const {
  return SDL_GetWindowData(static_cast<SDL_Window*>(window_ptr), name.c_str());
}

void Window::SetPosition(const Point& position) {
  SDL_SetWindowPosition(static_cast<SDL_Window*>(window_ptr), position.x, position.y);
}

Point Window::GetPosition() const {
  Point position;
  SDL_GetWindowPosition(static_cast<SDL_Window*>(window_ptr), &position.x, &position.y);
  return position;
}

void Window::SetSize(Dimensions dimensions) {
  SDL_SetWindowSize(static_cast<SDL_Window*>(window_ptr), dimensions.width, dimensions.height);
}

Dimensions Window::GetSize() const {
  Dimensions dimensions;
  SDL_GetWindowSize(static_cast<SDL_Window*>(window_ptr), &dimensions.width, &dimensions.height);
  return dimensions;
}

Window::Borders Window::GetBorders() const {
  Window::Borders borders;
  SDL_GetWindowBordersSize(static_cast<SDL_Window*>(window_ptr), &borders.top, &borders.left,
                           &borders.bottom, &borders.right);
  return borders;
}

void Window::SetMinimumSize(Dimensions dimensions) {
  SDL_SetWindowMinimumSize(static_cast<SDL_Window*>(window_ptr), dimensions.width,
                           dimensions.height);
}

Dimensions Window::GetMinimumSize() const {
  Dimensions dimensions;
  SDL_GetWindowMinimumSize(static_cast<SDL_Window*>(window_ptr), &dimensions.width,
                           &dimensions.height);
  return dimensions;
}

void Window::SetMaximumSize(Dimensions dimensions) {
  SDL_SetWindowMaximumSize(static_cast<SDL_Window*>(window_ptr), dimensions.width,
                           dimensions.height);
}

Dimensions Window::GetMaximumSize() const {
  Dimensions dimensions;
  SDL_GetWindowMaximumSize(static_cast<SDL_Window*>(window_ptr), &dimensions.width,
                           &dimensions.height);
  return dimensions;
}

void Window::setBordered(bool bordered) {
  SDL_SetWindowBordered(static_cast<SDL_Window*>(window_ptr), bordered ? SDL_TRUE : SDL_FALSE);
}

void Window::setResizable(bool resizable) {
  SDL_SetWindowResizable(static_cast<SDL_Window*>(window_ptr), resizable ? SDL_TRUE : SDL_FALSE);
}

void Window::show() { SDL_ShowWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::hide() { SDL_HideWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::raise() { SDL_RaiseWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::maximize() { SDL_MaximizeWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::minimize() { SDL_MinimizeWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::restore() { SDL_RestoreWindow(static_cast<SDL_Window*>(window_ptr)); }

void Window::setFullscreen(const Flags& options) {
  Uint32 flags = GetFlagsMask(options);
  int return_code = SDL_SetWindowFullscreen(static_cast<SDL_Window*>(window_ptr), flags);
  if (return_code != 0) {
    throw std::system_error(return_code, std::generic_category(),
                            "Unable to set fullscreen mode: " + std::string(SDL_GetError()));
  }
}

std::shared_ptr<Surface> Window::getSurface() {
  SDL_Surface* surface_ptr = SDL_GetWindowSurface(static_cast<SDL_Window*>(window_ptr));
  if (!surface_ptr) {
    throw std::runtime_error("Unable to get the surface for the window: " +
                             std::string(SDL_GetError()));
  }
  if (!surface || surface->surface_ptr != surface_ptr) {
    surface.reset(new Surface(surface_ptr));
  }
  return surface;
}

void Window::updateSurface() {
  int return_code = SDL_UpdateWindowSurface(static_cast<SDL_Window*>(window_ptr));
  if (return_code != 0) {
    throw std::runtime_error("Failed to update the surface: " + std::string(SDL_GetError()));
  }
}

std::shared_ptr<Renderer> Window::getRenderer(int driver,
                                              const std::unordered_set<Renderer::Option>& options) {
  SDL_Renderer* renderer_ptr = SDL_GetRenderer(static_cast<SDL_Window*>(window_ptr));
  if (!renderer || renderer->renderer_ptr != renderer_ptr) {
    if (!renderer_ptr) {
      renderer.reset(new Renderer(window_ptr, driver, options));
    } else {
      renderer.reset(new Renderer(renderer_ptr));
    }
  }
  return renderer;
}

Window::Flags sdlxx::core::operator|(const Window::Flag& lhs, const Window::Flag& rhs) {
  return {lhs, rhs};
}

Window::Flags sdlxx::core::operator|(Window::Flags&& lhs, const Window::Flag& rhs) {
  lhs.insert(rhs);
  return lhs;
}
