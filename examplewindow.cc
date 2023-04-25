#include "examplewindow.h"
#include "Sudoku.h"

ExampleWindow::ExampleWindow() : m_grid(), buttons()  {
    set_title("SUDOKU");
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
//            buttons[i][j] = gtk_bi;
            if (sudoku.Current[i][j] == 0) {
                buttons[i][j] = Gtk::Button("");
            } else {
                buttons[i][j] = Gtk::Button(std::to_string(sudoku.Current[i][j]).c_str());
            }
            m_grid.attach(buttons[i][j], i, j);
        }
    }
    m_grid.set_margin(12);
    set_child(m_grid);

//    m_grid.attach_next_to(m_button_quit, m_button_1, Gtk::PositionType::BOTTOM, 2, 1);
//
//    button_1.signal_clicked().connect(
//            sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), "button 1") );
//    m_button_2.signal_clicked().connect(
//            sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), "button 2") );
//    m_button_3.signal_clicked().connect(
//            sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), "button 3") );
//    m_button_4.signal_clicked().connect(
//            sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), "button 4") );

}

ExampleWindow::~ExampleWindow() {
}

void ExampleWindow::on_button_quit() {
    hide();
}

void ExampleWindow::on_button_numbered(const Glib::ustring& data) {
    int num;
    std::cin >> num;
    std::cout << data << " was pressed" << std::endl;
//    button_1.set_label(std::to_string(num));
}