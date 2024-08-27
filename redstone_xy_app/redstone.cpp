#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <Windows.h>
#include "constants.h"
using namespace std;
class Redstone {
public:
    string text[TEXT_MAX_SIZE];
    Redstone() {
        for (int i = 0; i < TEXT_MAX_SIZE; i++) text[i] = " ";
    }
    void run() {
        printf("System: Initializing Pad...\n");
    }
    void InsertRedStoneBlock(int position[2]) {
        int maxPosition = static_cast<int>(std::sqrt(TEXT_MAX_SIZE));
        if (position[0] >= maxPosition || position[1] >= maxPosition || position[0] < 0 || position[1] < 0) {
            std::cout << "System|ERROR|: position outside scope " << maxPosition << "*" << maxPosition << "\n";
        }
        else {
            int index_to_read = position[1] * maxPosition + position[0];
            text[index_to_read] = REDSTONE_TORCH_L;
        }
    }
    void show() {
        for (int i = 0, n = 0; i < TEXT_MAX_SIZE; i++, n++) {
            if (n >= WHEN_NEWLINE) {
                cout << "\n";
                n = 0;
            }
            cout << text[i];
        }
    }
};

int main() {
    Redstone rs;
    int type;
    int pos[2];

    while (true) {
        std::cout << "Please enter a type(0 to 13,for more information,please see ): ";
        std::cin >> pos[0] >> pos[1];
        rs.InsertRedStoneBlock(pos);
        std::cout << "\033[2J\033[1;1H"; // ANSI escape codes for clearing the screen (works on most terminals)
        rs.show();
    }
}