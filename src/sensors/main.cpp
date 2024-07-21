// main.cpp
#include "io_handling.h"
// #include "Simulation.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "one argument required - inputfile, got " << argc << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::string input_file_path = argv[1];
    std::string output_file_path = "output_" + input_file_path;
    FileReader fr(input_file_path);
    FileReader::file_reader_output args = fr.readFile();
    VacuumCleaner vacuumCleaner(args.max_num_of_steps, args.max_battery_steps, args.house_map, args.docking_loc);

    VacuumCleaner::vacuum_cleaner_output result = vacuumCleaner.cleanHouse();
    FileWriter fw(output_file_path);
    fw.writePath(vacuumCleaner.getPath());
    fw.writedDirt(result.dirt_left);
    fw.writedBat(result.battery_level);
    fw.writedAccomplish(result.dirt_left, result.is_in_doc);
    return EXIT_SUCCESS;
}