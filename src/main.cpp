#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/utils.hpp>
#include <NAN/basic_widgets/Widgets.hpp>
#include <NAN/tools/Bounds.hpp>
#include <windows.h>

int main() {
  Nan::Window main_window(1000, 800);
  main_window.updateFrameRate(144);
  
  Nan::Context* ctx = main_window.get_context();
  ctx->config().background(sf::Color(0x22223bff));

  Nan::Canvas canvas(Nan::Tools::Boundu{40U, 40U, 600U, 600U});
  Nan::Slider opacity_slider(Nan::Tools::Boundu{680U, 340U, 280U, 20U});
  Nan::Slider size_slider(Nan::Tools::Boundu{680U, 370U, 280U, 20U});
  Nan::HSLColorPicker picker(Nan::Tools::Boundu{680U, 40U, 280U, 280U});

  Nan::Container paint_tools({670U, 0U, 280U, main_window.getBounds().y});
  paint_tools.add(picker);
  paint_tools.add(opacity_slider);
  paint_tools.add(size_slider);

  canvas.add_picker(&picker);
  canvas.add_slider_opacity(&opacity_slider);
  canvas.add_slider_size(&size_slider);
  main_window.add_container(paint_tools);
  main_window.loop(canvas, picker, opacity_slider, size_slider);
}
