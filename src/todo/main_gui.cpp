#include "todo/TodoGUI.h"
#include <QApplication>
#include <memory>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    // Use smart pointer to handle memory automatically
    std::unique_ptr<TodoGUI> gui(new TodoGUI());
    gui->show();
    
    return app.exec();
}