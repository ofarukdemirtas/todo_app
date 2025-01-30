#include "todo/TodoGUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QApplication>

// ...existing code...

TodoGUI::TodoGUI(QWidget* parent) : QMainWindow(parent) {
    todoList = new TodoList();
    try {
        todoList->loadFromFile("tasks.txt");
    } catch (...) {
        // Ignore file loading errors
    }

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Create input area
    QHBoxLayout* inputLayout = new QHBoxLayout();
    inputTask = new QLineEdit();
    addButton = new QPushButton("Add");
    inputLayout->addWidget(inputTask);
    inputLayout->addWidget(addButton);

    // Create task list
    taskList = new QListWidget();

    // Create button area
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    removeButton = new QPushButton("Remove");
    completeButton = new QPushButton("Complete");
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(completeButton);

    // Add all layouts to main layout
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(taskList);
    mainLayout->addLayout(buttonLayout);

    // Connect signals and slots
    connect(addButton, &QPushButton::clicked, this, &TodoGUI::addTask);
    connect(removeButton, &QPushButton::clicked, this, &TodoGUI::removeTask);
    connect(completeButton, &QPushButton::clicked, this, &TodoGUI::completeTask);

    setWindowTitle("Todo App");
    resize(400, 300);
    updateTaskList();
}

TodoGUI::~TodoGUI() {
    save();
    delete todoList;
}

void TodoGUI::addTask() {
    QString task = inputTask->text();
    if (!task.isEmpty()) {
        todoList->addTask(task.toStdString());
        inputTask->clear();
        updateTaskList();
    }
}

void TodoGUI::removeTask() {
    QListWidgetItem* item = taskList->currentItem();
    if (item) {
        QString text = item->text();
        int idStart = text.indexOf("ID:") + 3;
        int idEnd = text.indexOf(" ", idStart);
        int taskId = text.mid(idStart, idEnd - idStart).toInt();
        todoList->removeTask(taskId);
        updateTaskList();
    }
}

void TodoGUI::completeTask() {
    QListWidgetItem* item = taskList->currentItem();
    if (item) {
        QString text = item->text();
        int idStart = text.indexOf("ID:") + 3;
        int idEnd = text.indexOf(" ", idStart);
        int taskId = text.mid(idStart, idEnd - idStart).toInt();
        todoList->markAsCompleted(taskId);
        updateTaskList();
    }
}

void TodoGUI::updateTaskList() {
    taskList->clear();
    std::vector<Task> tasks = todoList->getTasks();
    for (const auto& task : tasks) {
        QString status = task.completed ? "[✓] " : "[ ] ";
        QString line = QString("ID:%1 %2%3")
            .arg(task.id)
            .arg(status)
            .arg(QString::fromStdString(task.description));
        taskList->addItem(line);
    }
}

void TodoGUI::save() {
    try {
        todoList->saveToFile("tasks.txt");
    } catch (...) {
        // Handle save errors if needed
    }
}