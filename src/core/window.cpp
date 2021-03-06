#include "sdlxx/core/window.h"

#include <cmath>

#include <SDL_video.h>

#include "sdlxx/core/surface.h"

using namespace sdlxx;
using namespace std::literals::string_literals;

#define ASSERT_FLAGS(x) \
  static_assert(static_cast<SDL_WindowFlags>(Window::Flag::x) == SDL_WINDOW_##x);

ASSERT_FLAGS(FULLSCREEN);
ASSERT_FLAGS(OPENGL);
ASSERT_FLAGS(SHOWN);
ASSERT_FLAGS(HIDDEN);
ASSERT_FLAGS(BORDERLESS);
ASSERT_FLAGS(RESIZABLE);
ASSERT_FLAGS(MINIMIZED);
ASSERT_FLAGS(MAXIMIZED);
ASSERT_FLAGS(INPUT_GRABBED);
ASSERT_FLAGS(INPUT_FOCUS);
ASSERT_FLAGS(MOUSE_FOCUS);
ASSERT_FLAGS(FULLSCREEN_DESKTOP);
ASSERT_FLAGS(FOREIGN);
ASSERT_FLAGS(ALLOW_HIGHDPI);
ASSERT_FLAGS(MOUSE_CAPTURE);
ASSERT_FLAGS(ALWAYS_ON_TOP);
ASSERT_FLAGS(SKIP_TASKBAR);
ASSERT_FLAGS(UTILITY);
ASSERT_FLAGS(TOOLTIP);
ASSERT_FLAGS(POPUP_MENU);
ASSERT_FLAGS(VULKAN);
ASSERT_FLAGS(METAL);

static_assert(Window::WINDOW_POS_UNDEFINED == SDL_WINDOWPOS_UNDEFINED);
static_assert(Window::WINDOW_POS_CENTERED == SDL_WINDOWPOS_CENTERED);

std::unordered_map<SDL_Window*, Window&> Window::windows = {};

Window::Window(const std::string& title, int width, int height, BitMask<Flag> flags, int position_x,
               int position_y)
    : Window(SDL_CreateWindow(title.c_str(), position_x, position_y, width, height,
                              static_cast<Uint32>(flags.value))) {}

Window::Window(const std::string& title, Dimensions size, BitMask<Flag> flags, int position_x,
               int position_y)
    : Window(title, size.width, size.height, flags, position_x, position_y) {}

Window::Window(const void* data) : Window(SDL_CreateWindowFrom(data)) {}

Window::Window(SDL_Window* ptr) : window_ptr(ptr) {
  if (!window_ptr) {
    throw WindowException("Failed to create a window");
  }
  windows.emplace(ptr, *this);
}

Window::Window(Window::Id id) {
  throw WindowException("Getting a window by id is not implemented yet");
}

Window::Id Window::GetId() const { return static_cast<Id>(SDL_GetWindowID(window_ptr.get())); }

BitMask<Window::Flag> Window::GetFlags() const {
  return BitMask<Flag>{SDL_GetWindowFlags(window_ptr.get())};
}

Display Window::GetDisplay() const {
  if (int index = SDL_GetWindowDisplayIndex(window_ptr.get()); index != -1) {
    return Display(index);
  }
  throw WindowException("Failed to get display index for the window");
}

void Window::SetDisplayMode(const Display::Mode& mode) {
  SDL_DisplayMode new_mode = {mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata};
  int return_code = SDL_SetWindowDisplayMode(window_ptr.get(), &new_mode);
  if (return_code != 0) {
    throw WindowException("Failed to set display mode for the window");
  }
}

void Window::SetDefaultDisplayMode() {
  int return_code = SDL_SetWindowDisplayMode(window_ptr.get(), nullptr);
  if (return_code != 0) {
    throw WindowException("Failed to set display mode for the window");
  }
}

Display::Mode Window::GetDisplayMode() const {
  SDL_DisplayMode mode;
  int return_code = SDL_GetWindowDisplayMode(window_ptr.get(), &mode);
  if (return_code != 0) {
    throw WindowException("Failed to get display mode for the window");
  }
  return {mode.format, mode.w, mode.h, mode.refresh_rate, mode.driverdata};
}

uint32_t Window::GetPixelFormat() const {
  return static_cast<uint32_t>(SDL_GetWindowPixelFormat(window_ptr.get()));
}

void Window::SetTitle(const std::string& title) {
  SDL_SetWindowTitle(window_ptr.get(), title.c_str());
}

std::string Window::GetTitle() const { return SDL_GetWindowTitle(window_ptr.get()); }

void Window::SetIcon(const Surface& icon) {
  SDL_SetWindowIcon(window_ptr.get(), icon.surface_ptr.get());
}

void* Window::SetData(const std::string& name, void* userdata) {
  return SDL_SetWindowData(window_ptr.get(), name.c_str(), userdata);
}

void* Window::GetData(const std::string& name) const {
  return SDL_GetWindowData(window_ptr.get(), name.c_str());
}

void Window::SetPosition(Point position) {
  SDL_SetWindowPosition(window_ptr.get(), position.x, position.y);
}

Point Window::GetPosition() const {
  Point position;
  SDL_GetWindowPosition(window_ptr.get(), &position.x, &position.y);
  return position;
}

void Window::SetSize(Dimensions dimensions) {
  SDL_SetWindowSize(window_ptr.get(), dimensions.width, dimensions.height);
}

Dimensions Window::GetSize() const {
  Dimensions dimensions;
  SDL_GetWindowSize(window_ptr.get(), &dimensions.width, &dimensions.height);
  return dimensions;
}

Window::Borders Window::GetBordersSize() const {
  Window::Borders borders{};
  SDL_GetWindowBordersSize(window_ptr.get(), &borders.top, &borders.left, &borders.bottom,
                           &borders.right);
  return borders;
}

void Window::SetMinimumSize(Dimensions dimensions) {
  SDL_SetWindowMinimumSize(window_ptr.get(), dimensions.width, dimensions.height);
}

Dimensions Window::GetMinimumSize() const {
  Dimensions dimensions;
  SDL_GetWindowMinimumSize(window_ptr.get(), &dimensions.width, &dimensions.height);
  return dimensions;
}

void Window::SetMaximumSize(Dimensions dimensions) {
  SDL_SetWindowMaximumSize(window_ptr.get(), dimensions.width, dimensions.height);
}

Dimensions Window::GetMaximumSize() const {
  Dimensions dimensions;
  SDL_GetWindowMaximumSize(window_ptr.get(), &dimensions.width, &dimensions.height);
  return dimensions;
}

void Window::SetBordered(bool is_bordered) {
  SDL_SetWindowBordered(window_ptr.get(), is_bordered ? SDL_TRUE : SDL_FALSE);
}

void Window::SetResizable(bool is_resizable) {
  SDL_SetWindowResizable(window_ptr.get(), is_resizable ? SDL_TRUE : SDL_FALSE);
}

void Window::Show() { SDL_ShowWindow(window_ptr.get()); }

void Window::Hide() { SDL_HideWindow(window_ptr.get()); }

void Window::Raise() { SDL_RaiseWindow(window_ptr.get()); }

void Window::Maximize() { SDL_MaximizeWindow(window_ptr.get()); }

void Window::Minimize() { SDL_MinimizeWindow(window_ptr.get()); }

void Window::Restore() { SDL_RestoreWindow(window_ptr.get()); }

void Window::SetFullscreen() {
  auto flags_mask = static_cast<Uint32>(Flag::FULLSCREEN);
  int return_code = SDL_SetWindowFullscreen(window_ptr.get(), flags_mask);
  if (return_code != 0) {
    throw WindowException("Failed to set fullscreen mode");
  }
}

void Window::SetFullscreenDesktop() {
  auto flags_mask = static_cast<Uint32>(Flag::FULLSCREEN_DESKTOP);
  int return_code = SDL_SetWindowFullscreen(window_ptr.get(), flags_mask);
  if (return_code != 0) {
    throw WindowException("Failed to set fullscreen desktop mode");
  }
}

void Window::SetWindowed() {
  Uint32 flags_mask = 0;
  int return_code = SDL_SetWindowFullscreen(window_ptr.get(), flags_mask);
  if (return_code != 0) {
    throw WindowException("Failed to set windowed mode");
  }
}

Surface Window::GetSurface() const {
  SDL_Surface* surface_ptr = SDL_GetWindowSurface(window_ptr.get());
  if (surface_ptr == nullptr) {
    throw WindowException("Failed to get the surface for the window");
  }
  return Surface{surface_ptr};
}

void Window::UpdateSurface() {
  int return_code = SDL_UpdateWindowSurface(window_ptr.get());
  if (return_code != 0) {
    throw WindowException("Failed to update the window surface");
  }
}

void Window::UpdateSurfaceRectangles(const std::vector<Rectangle>& rectangles) {
  if (rectangles.empty()) {
    return;
  }
  std::vector<SDL_Rect> rects;
  rects.reserve(rectangles.size());
  for (Rectangle rectangle : rectangles) {
    rects.push_back({rectangle.x, rectangle.y, rectangle.width, rectangle.height});
  }
  int return_code = SDL_UpdateWindowSurfaceRects(window_ptr.get(), &rects.front(), rects.size());
  if (return_code != 0) {
    throw WindowException("Failed to update the window surface rectangles");
  }
}

void Window::SetGrab(bool is_grabbed) {
  SDL_SetWindowGrab(window_ptr.get(), is_grabbed ? SDL_TRUE : SDL_FALSE);
}

bool Window::GetGrab() const { return SDL_GetWindowGrab(window_ptr.get()) == SDL_TRUE; }

Window& Window::GetGrabbed() { throw WindowException("Getting grabbed window is not implemented"); }

void Window::SetBrightness(float brightness) {
  int return_code = SDL_SetWindowBrightness(window_ptr.get(), brightness);
  if (return_code != 0) {
    throw WindowException("Failed to set the brightness for a window");
  }
}

float Window::GetBrightness() const { return SDL_GetWindowBrightness(window_ptr.get()); }

void Window::SetOpacity(float opacity) {
  int return_code = SDL_SetWindowOpacity(window_ptr.get(), opacity);
  if (return_code != 0) {
    throw WindowException("Failed to set the opacity for a window");
  }
}

float Window::GetOpacity() const {
  float opacity = NAN;
  SDL_GetWindowOpacity(window_ptr.get(), &opacity);
  return opacity;
}

SDL_Window* Window::Release() { return window_ptr.release(); }

void Window::Deleter::operator()(SDL_Window* ptr) const {
  if (ptr != nullptr) {
    SDL_DestroyWindow(ptr);
  }
}
