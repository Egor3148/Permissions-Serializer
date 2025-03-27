#include <iostream>
#include "../inc/cli_interface.h"

#ifdef USE_FLTK
#include "gui_interface.h"
#endif

int main(int argc, char** argv) {

    std::cout << "Starting Permissions Serializer..." << std::endl;

#ifdef USE_FLTK

    std::cout << "FLTK is available. Using GUI." << std::endl;
    run_gui(argc, argv);
#else
    std::cout << "FLTK is not available. Using CLI." << std::endl;
    run_cli();
#endif

    return 0;
}