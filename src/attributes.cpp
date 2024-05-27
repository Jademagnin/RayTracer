/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** attributes
*/

#include <csignal>
#include <iostream>

void segfault_handler(int signal) {
    (void)signal;

    std::cerr << "Segmentation fault" << std::endl;
    exit(84);
}

__attribute__((constructor))
void exception_handler() {
    std::signal(SIGSEGV, segfault_handler);
    std::set_terminate([]() {
        try {
            throw;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        } catch (...) {
            std::cerr << "An unknown exception occurred" << std::endl;
        }
        exit(84);
    });
}
