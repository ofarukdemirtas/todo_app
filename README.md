# Todo Application

A simple Todo application with both GUI and console interfaces built using Qt5 and C++.

## Features
- Add new tasks
- Remove existing tasks
- Mark tasks as completed
- Persistent storage using file system
- Both GUI and console interfaces

## Prerequisites
```bash
# Install required packages
sudo apt-get update
sudo apt-get install qtbase5-dev qt5-qmake qtbase5-dev-tools
```

## Building

```bash
# Create build directory
mkdir -p build
cd build

# Configure and build
cmake ..
make
```

## Running

### GUI Version
```bash
# From build directory
./todo_gui
```

### Console Version
```bash
# From build directory
./todo_console
```

## Project Structure
```
todo_app/
├── include/todo/       # Header files
├── src/todo/          # Source files
├── CMakeLists.txt     # Build configuration
└── README.md          # This file
```

## Usage
- GUI: Use the input field and buttons to manage tasks
- Console: Follow the numbered menu options
- Tasks are automatically saved to 'tasks.txt'

## License
MIT License
