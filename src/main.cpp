#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/basic_widgets/Canvas.hpp>
#include <NAN/basic_widgets/HSLColorPicker.hpp>
#include <NAN/tools/Bounds.hpp>

int main() {
  Nan::Window main_window(1000, 800);
  main_window.updateFrameRate(144);
  
  Nan::Context* ctx = main_window.get_context();
  // ctx->load_shader("E:/so2u/GITHUB/cuba/drawing/shaders/main.frag");
  Nan::Canvas canvas(Nan::Tools::Boundu{0U, 0U, 600U, 400U});
  Nan::HSLColorPicker picker(Nan::Tools::Boundu{650U, 0U, 300U, 300U});

  canvas.add_picker(&picker);
  main_window.loop(canvas, picker);
}