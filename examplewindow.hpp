#pragma once
#include <iostream>
#include "Sudoku.h"
#include <gtkmm.h>

class ExampleWindow : public Gtk::Window {
public:
    ExampleWindow();

    virtual ~ExampleWindow();

private:
    void on_button_quit();

    void on_button_numbered(int, int);

    void on_panel_clicked(int);

    void easy_mode() {
        sudoku = Sudoku(0);
        redraw();
    }

    void medium_mode() {
        sudoku = Sudoku(1);
        redraw();
    }

    void hard_mode() {
        sudoku = Sudoku(2);
        redraw();
    }

    void redraw() {
        for (int i = 8; i >= 0; --i) {
            for (int j = 8; j >= 0; --j) {
                if (sudoku.Current[i][j] == 0) {
                    buttons[i][j].set_label("");
                } else {
                    buttons[i][j].set_label(std::to_string(sudoku.Current[i][j]).c_str());
                }
            }
        }
    }

    int current_choice = 0;

    Gtk::Grid m_grid{};
    Gtk::Button buttons[9][9]{};
    Gtk::Button exit_button{};
    Gtk::Button moves[9]{};
    Gtk::Button easy{}, medium{}, hard{};

};


ExampleWindow::ExampleWindow() {
    set_title("SUDOKU");
    m_grid.insert_row(9);
    for (int i = 8; i >= 0; --i) {
//        m_grid.insert_column(i);
        for (int j = 8; j >= 0; --j) {
//            m_grid.insert_row(j);
            if (sudoku.Current[i][j] == 0) {
                buttons[i][j] = Gtk::Button("");
            } else {
                buttons[i][j] = Gtk::Button(std::to_string(sudoku.Current[i][j]).c_str());
            }
            m_grid.attach(buttons[i][j], i, j);
            buttons[i][j].signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), i, j));
        }
    }
    for (int i = 0; i < 9; ++i) {
        moves[i] = Gtk::Button(std::to_string(i + 1).c_str());
        m_grid.attach(moves[i], i % 3, 10 + i / 3);
        moves[i].signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_panel_clicked), i + 1));
    }
    exit_button.set_label("EXIT");
    easy.set_label("easy");
    medium.set_label("medium");
    hard.set_label("hard");
    m_grid.attach(exit_button, 0, 9, 9, 1);
    m_grid.attach(easy, 3, 10, 6, 1);
    m_grid.attach(medium, 3, 11, 6, 1);
    m_grid.attach(hard, 3, 12, 6, 1);
    exit_button.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_quit)));
    easy.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &ExampleWindow::easy_mode)));
    medium.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &ExampleWindow::medium_mode)));
    hard.signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &ExampleWindow::hard_mode)));
    set_child(m_grid);

}

ExampleWindow::~ExampleWindow() {
}

void ExampleWindow::on_button_quit() {
    hide();
}

void ExampleWindow::on_panel_clicked(int x) {
    current_choice = x;
}


void ExampleWindow::on_button_numbered(int i, int j) {
    std::cout << i << " " << j << std::endl;
    int num = current_choice;
    if (sudoku.Fill(i, j, num)) {
        buttons[i][j].set_label(std::to_string(num));
    } else {
        std::cout << "JA PIERDOLE\n";
    }

}
