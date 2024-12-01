CXX = g++

CXXFLAGS = -std=c++17 

# Source files
SOURCES = main.cpp user.cpp admin.cpp expense.cpp expense_manager.cpp user_manager.cpp main_menu.cpp

# Executable name
EXECUTABLE = expense_tracker

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	$(RM) $(EXECUTABLE)


