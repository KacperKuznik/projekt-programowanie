#include "History.hpp"

std::string History::findFileName() {
    auto getNewFileName = []() -> std::string {
        int fileNumber = 1;
        std::string fileName;

        while (true) {
            std::ostringstream oss;
            oss << ".\\history\\" << "history" << fileNumber << ".txt";
            fileName = oss.str();

            std::ifstream file(fileName);
            if (!file.good()) {
                break;
            }

            fileNumber++;
        }

        return fileName;
        };

    return getNewFileName();
}

void History::addTextToFile(std::string text, std::string history_file_name) {
    std::ofstream file(history_file_name, std::ios::app);
    file << text;
    file.close();
}
