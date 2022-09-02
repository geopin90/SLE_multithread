#include "SLEConsoleView.h"

namespace s21 {

SLEConsoleView::SLEConsoleView() {
    runMenu();
    while (curCommand != exit) {
        try {
            if (std::cin.eof()) {
                std::cout << "^D" << std::endl;
                break;
            }
            waitCommand();
            chooseCommand();
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            runMenu();
        }
    }
}

void SLEConsoleView::runMenu() {
    curCommand = mainMenu;
    chooseCommand();
}

void SLEConsoleView::waitCommand() {
    std::string entry;
    std::cin >> entry;
    if (isNumber(entry)) {
        curCommand = std::stoi(entry);
        if (curCommand > 5) {
            print(wrongCommand);
        }
    } else {
        throw std::out_of_range("Wrong number\n");
    }
}

bool SLEConsoleView::isNumber(std::string entry) {
    bool result = true;
    for (int i = 0; i < entry.size(); i++) {
        if (!std::isdigit(entry[i])) {
            result = false;
        }
    }
    return result;
}

void SLEConsoleView::chooseCommand() {
    switch(curCommand) {
        case mainMenu:
            print(mainMenu);
            break;
        case loadFile:
        fileLoad();
            break;
        case createMatrix:
            break;
        case solve:
            break;
        case compare:
            break;
        case exit:
            print(exit);
            break;
        default:
            runMenu();
            break;
    }
}

void SLEConsoleView::fileLoad() {
    print(loadFile);
    std::string filePath;
    std::cin >> filePath;
    try {
        gauss.setFromFile(filePath);
        std::cout << "File loaded successfully\n";
    } catch (std::exception& e) {
        throw;
    }
    runMenu();
}

void SLEConsoleView::matrixEnter() {

}

void SLEConsoleView::solveMethod() {

}

void SLEConsoleView::compareMethod() {

}

void SLEConsoleView::print(const commands& com) {
    std::cout << "***" << std::endl;
    std::cout << printable[com];
    std::cout << "***" << std::endl;
}

}  // namespace s21

int main() {
    s21::SLEConsoleView con;
    return 0;
}