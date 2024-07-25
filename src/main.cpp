// main.cpp
#include "logger.h"
#include "io_handling.h"
#include "simulator.h"
#include "my_algorithm.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "one argument required - inputfile, got " << argc << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string input_file_path = argv[1];
    logger.log(INFO, "~~~~~~~~~~~~~~~~~~~~~~~ Vacuum Cleaner ~~~~~~~~~~~~~~~~~~~~~~~");
    std::string output_file_path = "output_" + input_file_path;

    MySimulator simulator;
    simulator.readHouseFile(input_file_path);

    simulator.setAlgorithm(std::make_shared<MyAlgorithm>());
    simulator.run();

    // FileWriter fw(output_file_path);
    // fw.writePath(vacuumCleaner.getPath());
    // fw.writedDirt(result.dirt_left);
    // fw.writedBat(result.battery_level);
    // fw.writedAccomplish(result.dirt_left, result.is_in_doc);
    return EXIT_SUCCESS;


}