// main.cpp
#include "logger.h"
#include "io_handling.h"
// #include "Simulation.h"

int main() {
    logger.log(INFO, "~~~~~~~~~~~~~~~~~~~~~~~ Vacuum Cleaner ~~~~~~~~~~~~~~~~~~~~~~~");
    std::string input_file_path = "input_a.txt";
    std::string output_file_path = "output_" + input_file_path;
    FileReader fr(input_file_path);
    FileReader::file_reader_output args = fr.readFile();
    args.house_map->print();
    return EXIT_SUCCESS;
}