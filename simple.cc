#include <gtkmm.h>

class MyWindow : public Gtk::Window
{
public:
    MyWindow();
};

MyWindow::MyWindow()
{
    set_title("абоба");
    set_default_size(200, 200);
}

int main(int argc, char* argv[])
{
//    setlocale(LC_ALL, "");
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<MyWindow>(argc, argv);
}