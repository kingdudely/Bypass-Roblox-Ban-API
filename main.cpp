// #define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <filesystem>
#include <string>
#include <conio.h> // just for _getch bro

using namespace std;
using namespace filesystem;

int main() {
    try {
        /*
        char* userPath = getenv("USERPROFILE");
        if (!userPath) {
            cerr << "Failed to retrieve USERPROFILE environment variable." << endl;
            return 1;
        }
        */

        /*
        Instead of just getenv("USERPROFILE") I have to do all this because it's "deprecated"???
        */

        char* userPath = nullptr;
        if (_dupenv_s(&userPath, nullptr, "USERPROFILE") || !userPath) {
            cerr << "Failed to retrieve USERPROFILE environment variable." << endl;
            return 1;
        }

        path localStoragePath = path(userPath) / "AppData" / "Local" / "Roblox" / "LocalStorage";
        free(userPath);

        if (exists(localStoragePath) && is_directory(localStoragePath)) {
            for (const auto& entry : recursive_directory_iterator(localStoragePath)) {
                try {
                    remove_all(entry.path());
                    cout << "Deleted: " << entry.path() << endl;
                }
                catch (const exception& e) {
                    cerr << "Error deleting file " << entry.path() << ": " << e.what() << endl;
                }
            }

            cout << "All files deleted successfully!" << endl;
        }
        else {
            cerr << "Roblox LocalStorage directory not found." << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    cout << "Press any key to close . . .";
    _getch();

    return 0;
}
