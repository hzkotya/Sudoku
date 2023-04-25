#pragma once
#include <gtkmm.h>
#include <iostream>

class ExampleWindow : public Gtk::Window {
public:
    ExampleWindow();

    virtual ~ExampleWindow();

private:
    // Signal handlers:
    void on_button_quit();

    void on_button_numbered(const Glib::ustring &data);

    // Child widgets:
    Gtk::Grid m_grid;
//    Gtk::Box box1;
    Gtk::Button buttons[9][9]{};
//    Gtk::Button button1, button2;

};
