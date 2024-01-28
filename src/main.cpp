#include "interface.h"

int main() {
    interface interface;
    interface.main_menu();

    std::ofstream student_file("data/student_db");

    return 0;
}
