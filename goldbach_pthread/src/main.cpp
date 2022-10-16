#include <cstdlib>
#include <iostream>
#include "GoldbachPthread.hpp"

int main(){
    int error = EXIT_SUCCESS;
    // goldbach_pthread := create_goldbach_pthread()
    GoldbachPthread* goldbach_pthread = new GoldbachPthread();

    if (goldbach_pthread) {
        // read(goldbach_pthread)
        error = goldbach_pthread->read_goldbach_numbers();
        if (error == EXIT_SUCCESS) {
            // process(goldbach_pthread)
            error = goldbach_pthread->process_goldbach_numbers();
            if (error == EXIT_SUCCESS) {
                // print_(goldbach_pthread)
                goldbach_pthread->print_goldbach_numbers();
            } else {
                std::cerr <<
                "error: could not process goldbach_pthread object";
                error = EXIT_FAILURE;
            }
        } else {
            std::cerr <<
            "error: could not read numbers into goldbach_pthread object";
            error = EXIT_FAILURE;
        }

        // destroy(goldbach_pthread)
        delete goldbach_pthread;
    } else {
        std::cerr << "error: could not allocate goldbach_pthread object";
        error = EXIT_FAILURE;
    }

    return error;
}
