#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/basic_widgets/Canvas.hpp>
#include <NAN/tools/Bounds.hpp>

int main() {
  Nan::Window main_window(600, 400);
  main_window.updateFrameRate(144);
  
  Nan::Context* ctx = main_window.get_context();
  // ctx->load_shader("E:/so2u/GITHUB/cuba/drawing/shaders/main.frag");
  Nan::Canvas canvas(Nan::Tools::Boundu{0U, 0U, 600U, 400U});
  // main_window.provide(canvas);
  main_window.loop(canvas);
}
