// io_handling.cpp
#include "io_handling.h"


std::vector<std::string> FileReader::split(const std::string &str, const char delimiter) const {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

size_t FileReader::readArgument(const std::string &str) const {
    std::vector<std::string> splits = split(str, '=');
    if (splits.size() != 2) {
        logger.log(ERROR, "Invalid format: " + str);
        std::exit(EXIT_FAILURE);
    }

    std::string str_arg = trim(splits[1]);
    return strToSize_t(str_arg);
}

size_t FileReader::strToSize_t(const std::string &str) const {
    try {
        size_t res = std::stoull(str);
        return res;
    } catch (const std::invalid_argument& e) {
        logger.log(ERROR, "Invalid argument: " + std::string(e.what()));
        std::exit(EXIT_FAILURE);
    } catch (const std::out_of_range& e) {
        logger.log(ERROR, "Out of range: " + std::string(e.what()));
        std::exit(EXIT_FAILURE);
    }
}

std::string FileReader::trim(const std::string &str) const {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        ++start;
    }

    auto end = str.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

House::Location FileReader::parseLocation(const std::string &str) const {
    auto tmp_vec = split(str, '|');
    return House::Location(
        strToSize_t(tmp_vec[0].substr(1)),                            // row
        strToSize_t(tmp_vec[1].substr(0, tmp_vec[1].size() - 1))      // col
    );
}


void FileReader::ParseHouse(std::ifstream &file, std::shared_ptr<House> house) const {
    if (!file.is_open()) {
        logger.log(ERROR, "error reading house from file");
        std::exit(EXIT_FAILURE);
    }
    size_t num_of_rows = house->getRowsCount();
    size_t num_of_cols = house->getColsCount();
    std::string line;
    size_t row_index = 0;
    while (std::getline(file, line) && row_index < num_of_rows) {
        std::vector<char> vec_line(line.begin(), line.end());
        size_t width = vec_line.size() < num_of_cols ? vec_line.size() : num_of_cols;
        for (size_t col_index = 0; col_index < width; col_index++) {
            char c  = vec_line[col_index];
            if (c == 'D') {
                house->getTile(row_index, col_index).setAsDockingStation();
                logger.log(INFO, std::format("Set a Docking Station ({},{})", row_index, col_index));
            } else if (c == 'W') {
                house->getTile(row_index, col_index).setAsWall();
                logger.log(INFO, std::format("Set a Wall ({},{})", row_index, col_index));
            } else if (c == ' ') {
                house->getTile(row_index, col_index).setDirtLevel(0);
                logger.log(INFO, std::format("Set an empty Tile ({},{})", row_index, col_index));
            } else if (isdigit(c)) {
                house->getTile(row_index, col_index).setDirtLevel(int(c - '0'));
                logger.log(INFO, std::format("Set an dirty Tile ({},{}). Diet level: {}", row_index, col_index, int(c - '0')));
            } else {
                logger.log(ERROR, std::format("Invalid charecter in house map ({},{})", row_index, col_index));
                std::exit(EXIT_FAILURE);
            }
        }
        row_index++;
    }
    logger.log(INFO, std::format("Populated house of size {} by {}",num_of_rows, num_of_cols));
}


FileReader::FileReader(const std::string& file_path) : file_path(file_path) {}


FileReader::file_reader_output FileReader::readFile() const {
    size_t max_num_of_steps;
    size_t max_battery_steps;
    size_t rows_count;
    size_t cols_count;
    House::Location docking_loc;

    std::ifstream file(file_path);

    if (!file.is_open()) {
        logger.log(ERROR, "Failed to open the file: " + file_path);
        std::exit(EXIT_FAILURE);
    }

    std::string line;

    if (!std::getline(file, line)) {
        logger.log(ERROR, "Failed to read first line of input file");
        std::exit(EXIT_FAILURE);
    }

    if (std::getline(file, line)) {
        max_num_of_steps = readArgument(line);
    } else {
        logger.log(ERROR, "Failed to read 2nd line with MaxSteps");
        std::exit(EXIT_FAILURE);
    }

    if (std::getline(file, line)) {
        max_battery_steps = readArgument(line);
    } else {
        logger.log(ERROR, "Failed to read 3rd line with MaxBattery");
        std::exit(EXIT_FAILURE);
    }

    if (std::getline(file, line)) {
        rows_count = readArgument(line);
    } else {
        logger.log(ERROR, "Failed to read 4th line with Rows");
        std::exit(EXIT_FAILURE);
    }

    if (std::getline(file, line)) {
        cols_count = readArgument(line);
    } else {
        logger.log(ERROR, "Failed to read 5th line with Cols");
        std::exit(EXIT_FAILURE);
    }

    std::shared_ptr<House> house = std::make_shared<House>(rows_count, cols_count);
    ParseHouse(file, house);
    file.close();

    return {max_battery_steps, max_num_of_steps, docking_loc, house};
}

FileWriter::FileWriter(const std::string& file_path) : file_path(file_path) {
    std::ofstream file(file_path);
    file.close();
}

void FileWriter::writePath(const Path& path) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "Could not open file for writing" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    file << path;
    file << "Total number of steps performed: " << (path.getLength() - 1) << std::endl;

    file.close();
}

// void FileWriter::writeHouse(const House& house) {
//     // std::ofstream file(file_path, std::ios_base::app);
//     // if (!file.is_open()) {
//     //     std::cout << "Could not open file for writing" << std::endl;
//     //     std::exit(EXIT_FAILURE);
//     // }

//     // size_t rows = house.getRowsCount();
//     // size_t cols = house.getColsCount();

//     // for (size_t row = 0; row < rows; row++) {
//     //     FileWriter::printTopWall(file, house, row, cols);
//     //     FileWriter::printDirt(file, house, row, cols);
//     // }

//     // // Print the bottom wall segment of the last row
//     // printBottomWall(file, house, rows - 1, cols);

//     // file.close();
// }

void FileWriter::writedDirt(size_t dirt) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "Could not open file for writing" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    file << "Final amount of dirt: " << dirt << std::endl;
    file.close();
}

void FileWriter::writedBat(size_t battery) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "Could not open file for writing" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    file << "Battery level on finish: " << battery << std::endl;
    file << (battery > 0 ? "Battery was not exhausted" :  "Battery is dead") << std::endl;
    file.close();
}

void FileWriter::writedAccomplish(size_t dirt, bool isInDock) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "Could not open file for writing" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if (dirt == 0 && isInDock) {
        file << "Misson Accomplished!" << std::endl;
    } else {
        file << "Misson Not Accomplished..." << std::endl;
    }
    file.close();
}



