
#include "attendancemanager.h"

#include <exception>
#include <iostream>

using namespace std;

int main() {
    try {
        AttendanceManager manager;
        manager.run();
    } catch (const exception& error) {
        cerr << "Unexpected error: " << error.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Unknown and unexpected error!" << endl;
        return 1; //program terminated with an error
    }

    return 0;
}
