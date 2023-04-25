#pragma once
#include <gtkmm.h>
#include "Sudoku.h"
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
//    Gtk::Grid m_grid;
    Gtk::Box box1;
    GtkWidget *buttons[81][81];
    Sudoku sudoku;

};
