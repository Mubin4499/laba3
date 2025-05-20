#include "GUI.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "База данных: " << std::filesystem::absolute("data/fiesta.db") << std::endl;

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.fiesta");
    FiestaWindow window;
    return app->run(window);
}