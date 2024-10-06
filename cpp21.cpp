#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Log {
private:
    string logFile;
public:
    Log(const string& fileName) : logFile(fileName) {}

    void addLog(int code, const string& message, const string& type) {
        ofstream file(logFile, ios::app);
        if (file.is_open()) {
            file << "Code: " << code << ", Message: " << message << ", Type: " << type << endl;
            file.close();
        }
        else {
            cerr << "Не вдалося відкрити файл для запису!" << endl;
        }
    }

    void readLogs() {
        ifstream file(logFile);
        if (file.is_open()) {
            string line;
            while (std::getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        else {
            cerr << "Не вдалося відкрити файл для читання!" << endl;
        }
    }

    void copyLogs(const std::string& destinationFile) {
        ifstream srcFile(logFile);
        ofstream destFile(destinationFile);

        if (srcFile.is_open() && destFile.is_open()) {
            string line;
            while (std::getline(srcFile, line)) {
                destFile << line << endl;
            }
            srcFile.close();
            destFile.close();
        }
        else {
            cerr << "Не вдалося відкрити файли для копіювання!" << endl;
        }
    }

    void deleteLog(const std::string& messageToDelete) {
        ifstream file(logFile);
        ofstream tempFile("temp.log");

        if (file.is_open() && tempFile.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (line.find(messageToDelete) == string::npos) {
                    tempFile << line << endl;
                }
            }
            file.close();
            tempFile.close();

            remove(logFile.c_str());
            rename("temp.log", logFile.c_str());
        }
        else {
            cerr << "Не вдалося відкрити файли для видалення логу!" << endl;
        }
    }

    void clearLogs() {
        ofstream file(logFile, ios::trunc);
        if (file.is_open()) {
            file.close();
        }
        else {
            cerr << "Не вдалося відкрити файл для очищення!" << endl;
        }
    }
};

int main() {
    Log logger("logs.txt");

    logger.addLog(1001, "System started", "INFO");
    logger.addLog(1002, "Error occurred", "ERROR");

    std::cout << "Logs:\n";
    logger.readLogs();

    logger.copyLogs("logs_copy.txt");

    logger.deleteLog("System started");

    std::cout << "\nLogs after deletion:\n";
    logger.readLogs();

    logger.clearLogs();

    std::cout << "\nLogs after clearing:\n";
    logger.readLogs();

}
