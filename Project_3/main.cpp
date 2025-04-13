#include <iostream>
#include <dirent.h>
#include "searchengine.h" 
#include "userinterface.h"
using namespace std;

// Function to check if a directory exists
bool directoryExists(const string& dirPath) {
    DIR* dir = opendir(dirPath.c_str());
    if (dir) {
        closedir(dir);
        return true;
    }
    return false;
}

int main()
{
    // Check if data/archive directory exists using dirent.h
    if (!directoryExists("data/archive")) {
        cout << "Error: data/archive directory not found. Please make sure it exists." << endl;
        return 1;
    }
    
    // Create instance of UserInterface
    UserInterface ui;
    
    // Start user interface
    ui.initialQuestion();
    
    return 0;
}