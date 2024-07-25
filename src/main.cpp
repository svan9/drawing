#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/utils.hpp>
#include <NAN/basic_widgets/Canvas.hpp>
#include <NAN/basic_widgets/HSLColorPicker.hpp>
#include <NAN/tools/Bounds.hpp>
#include <windows.h>

int main() {
  Nan::Window main_window(1000, 800);
  main_window.updateFrameRate(144);
  
  Nan::Context* ctx = main_window.get_context();
  ctx->config().background(sf::Color(0x22223bff));

  Nan::Canvas canvas(Nan::Tools::Boundu{40U, 40U, 600U, 600U});
  Nan::HSLColorPicker picker(Nan::Tools::Boundu{680U, 40U, 280U, 280U});

  canvas.add_picker(&picker);
  main_window.loop(canvas, picker);
}

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//   return main();
// }