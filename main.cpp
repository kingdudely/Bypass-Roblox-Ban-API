#include <iostream>
#include <filesystem>
#include <string>
#include <conio.h>

using namespace std;
using namespace filesystem;

int main() {
    try {
        char* localAppData = nullptr;
        if (_dupenv_s(&localAppData, nullptr, "LOCALAPPDATA") || !localAppData) {
            cerr << "Failed to retrieve LOCALAPPDATA environment variable." << endl;
            return 1;
        }

        path localStoragePath = path(localAppData) / "Roblox" / "LocalStorage";
        free(localAppData);

        if (exists(localStoragePath) && is_directory(localStoragePath)) {
            for (const auto& entry : recursive_directory_iterator(localStoragePath)) {
                try {
                    remove_all(entry.path());
                    cout << "Deleted: " << entry.path() << endl;
                }
                catch (const exception& error) {
                    cerr << "Error deleting file " << entry.path() << ": " << error.what() << endl;
                }
            }

            cout << "All files deleted successfully!" << endl;
        }
        else {
            cerr << "Roblox LocalStorage directory not found." << endl;
        }
    }
    catch (const exception& error) {
        cerr << "Error: " << error.what() << endl;
    }

    cout << "Press any key to close . . .";
    _getch();

    return 0;
}
