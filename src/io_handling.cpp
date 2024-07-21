// io_handling.cpp
#include "io_handling.h"

FileReader::StepHouse::StepHouse(std::__1::ifstream &file) {
    std::string line;
    rows = 0;
    max_col = 0;
    while (std::getline(file, line)) {
        size_t cur_col = line.size();
        max_col = cur_col > max_col ? cur_col : max_col;
        this->mat.emplace_back(line.begin(), line.end());
        rows++;
    }
}

void FileReader::StepHouse::print() const {
    for (const auto& row : mat) {
        for (char ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
}

std::vector<std::string> FileReader::split(const std::string &str, const char delimiter) const {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

size_t FileReader::strToSize_t(const std::string &str) const {
    try {
        size_t res = std::stoull(str);
        return res;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

House::Location FileReader::parseLocation(const std::string &str) const {
    auto tmp_vec = split(str, '|');
    return House::Location(
        strToSize_t(tmp_vec[0].substr(1)),                            // row
        strToSize_t(tmp_vec[1].substr(0, tmp_vec[1].size() - 1))      // col
    );
}

std::pair<size_t, size_t> FileReader::getHouseDimensions(const std::string& filename) const {
    // opens a new fd, to avoid seek when returns
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // remove first line with the args
    std::string first_line;
    if (!std::getline(file, first_line)) {
        std::cerr << "Error or empty file content." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::istringstream stream(content);
    std::string line;
    size_t rows = 0;
    size_t cols = 0;

    while (std::getline(stream, line)) {
        if (!line.empty()) {
            rows++;
            if (cols == 0) {
            cols = line.size();
        }
        }
    }
    file.close();
    return {(rows - 1) / 2, (cols - 1) / 2};
}

bool FileReader::isTransition(const StepHouse& step_house, size_t i1, size_t j1, size_t i2, size_t j2) const {
    char x = step_house.mat[i1][j1];
    char y = step_house.mat[i2][j2];
    return (isdigit(x) != isdigit(y));
}

void FileReader::surroundHouseWithWalls(const StepHouse& step_house, House &house) const {
    size_t num_step_rows = step_house.mat.size();
    size_t num_step_cols = step_house.mat[0].size();
    // for each row, from left to right
    size_t house_i = 0;
    for (size_t step_i = 1; step_i < num_step_rows; step_i += 2) {
        size_t house_j = 0;
        for (size_t step_j = 1; step_j < step_house.mat[step_i].size() - 2; step_j += 2) {
            if (FileReader::isTransition(step_house, step_i, step_j, step_i, step_j + 2)) {
                house.getTile(house_i, house_j).setEastWall(true);
                house.getTile(house_i, house_j + 1).setWestWall(true);
            }
            house_j++;
        }
        house_i++;
    }

    // for each col, from top to buttom
    size_t house_j = 0;
    for (size_t step_j = 1; step_j < num_step_cols; step_j += 2) {
        size_t house_i = 0;
        for (size_t step_i = 1; step_i < num_step_rows - 2; step_i += 2) {
            if (FileReader::isTransition(step_house, step_i, step_j, step_i + 2, step_j)) {
                house.getTile(house_i, house_j).setSouthWall(true);
                house.getTile(house_i + 1, house_j).setNorthWall(true);
            }
            house_i++;
        }
        house_j++;
    }

    // take care of the tiles on the borders
    // top and buttom rows:
    house_j = 0;
    for (size_t step_j = 1; step_j < num_step_cols; step_j += 2) {
        if (isdigit(step_house.mat[1][step_j])) {
            house.getTile(0, house_j).setNorthWall(true);
        }
        if (isdigit(step_house.mat[num_step_rows - 2][step_j])) {
            house.getTile(house.getRowsCount() - 1, house_j).setSouthWall(true);
        }
        house_j++;
    }

    house_i = 0;
    for (size_t step_i = 1; step_i < step_house.mat.size(); step_i += 2) {
        if (isdigit(step_house.mat[step_i][1])) {
            house.getTile(house_i, 0).setWestWall(true);
        }
        if (isdigit(step_house.mat[step_i][num_step_cols - 2])) {
            house.getTile(house_i, house.getColsCount() - 1).setEastWall(true);
        }
        house_i++;
    }
}

void FileReader::parseHouse(const StepHouse& step_house, House &house) const {
    size_t num_step_rows = step_house.mat.size();
    size_t house_i = 0;
    for (size_t step_i = 1; step_i < num_step_rows; step_i += 2) {
        size_t house_j = 0;
        for (size_t step_j = 1; step_j < step_house.mat[step_i].size(); step_j += 2) {

            House::Tile& tile = house.getTile(house_i, house_j);
            char val = step_house.mat[step_i][step_j];

            // Read and set dirt values
            if (isdigit(val)) {
                tile.setDirt(val - '0');
            }

            // Add walls
            // North wall
            if (step_i > 0 && step_house.mat[step_i - 1][step_j] == '-') {
                tile.setNorthWall(true);
            }
            // South wall
            if (step_i < num_step_rows - 1 && step_house.mat[step_i + 1][step_j] == '-') {
                tile.setSouthWall(true);
            }
            // West wall
            if (step_j > 0 && step_house.mat[step_i][step_j - 1] == '|') {
                tile.setWestWall(true);
            }
            // East wall
            if (step_j < step_house.mat[step_i].size() - 1 && step_house.mat[step_i][step_j + 1] == '|') {
                tile.setEastWall(true);
            }

            house_j++;
        }
        house_i++;
    }
}


FileReader::FileReader(const std::string& file_path) : file_path(file_path) {}


FileReader::file_reader_output FileReader::readFile() const {
    size_t max_battery_steps;
    size_t max_num_of_steps;
    House::Location docking_loc;

    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << file_path << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string first_line;
    if (std::getline(file, first_line)) {
        auto args = split(first_line, ',');
        max_battery_steps = strToSize_t(args[0]);
        max_num_of_steps = strToSize_t(args[1]);
        docking_loc = parseLocation(args[2]);
    } else {
        std::cerr << "Failed to read first line of input file" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    auto [rows, cols] = getHouseDimensions(file_path);
    StepHouse step_house(file);
    House house = House(rows, cols);
    parseHouse(step_house, house);
    surroundHouseWithWalls(step_house, house);
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

void FileWriter::writeHouse(const House& house) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "Could not open file for writing" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    size_t rows = house.getRowsCount();
    size_t cols = house.getColsCount();

    for (size_t row = 0; row < rows; row++) {
        FileWriter::printTopWall(file, house, row, cols);
        FileWriter::printDirt(file, house, row, cols);
    }

    // Print the bottom wall segment of the last row
    printBottomWall(file, house, rows - 1, cols);

    file.close();
}

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


void FileWriter::printTopWall(std::ofstream& file, const House& house, size_t row, size_t cols) const {
    file << "+";
    for (size_t col = 0; col < cols; col++) {
        file << (house.getTile(row, col).getNorthWall() ? "-+" : " +");
    }
    file << std::endl;
}

void FileWriter::printDirt(std::ofstream& file, const House& house, size_t row, size_t cols) const {
    for (size_t col = 0; col < cols; col++) {
        const auto& tile = house.getTile(row, col);
        file << (tile.getWestWall() ? "|" : " ") << tile.getDirt();
    }
    file << (house.getTile(row, cols - 1).getEastWall() ? "|" : " ") << std::endl;
}

void FileWriter::printBottomWall(std::ofstream& file, const House& house, size_t row, size_t cols) const {
    file << "+";
    for (size_t col = 0; col < cols; col++) {
        file << (house.getTile(row, col).getSouthWall() ? "-+" : " +");
    }
    file << std::endl;
}


