#include "examplewindow.hpp"
#include <gtkmm/application.h>
#include "Sudoku.h"

int main(int argc, char *argv[])
{
    sudoku.printans();
    auto app = Gtk::Application::create("org.gtkmm.example");

    // Shows the window and returns when it is closed.
    return app->make_window_and_run<ExampleWindow>(argc, argv);
}