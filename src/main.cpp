// main.cpp
#include "logger.h"
#include "io_handling.h"
#include "simulator.h"
#include "speedom_algorithm.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        logger.log(FATAL, std::format("one argument required - inputfile, got {}", int(argc - 1)));
    }

    std::string input_file_path = argv[1];
    std::string output_file_path = "output_" + input_file_path;

    Simulator simulator;
    simulator.readHouseFile(input_file_path);

    simulator.setAlgorithm(std::make_shared<SpeedomAlgorithm>());
    simulator.run();

    return EXIT_SUCCESS;


}