#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string line;

    int sum = 0;
    while (std::getline(std::cin, line)) {
        auto first_it = std::find_if(line.cbegin(), line.cend(), ::isdigit);
        auto last_it = std::find_if(line.rbegin(), line.rend(), ::isdigit);

        if (first_it != line.end() && last_it != line.rend()) {
            int first = *first_it - '0';
            int last = *last_it - '0';

            sum += (first * 10) + last;
        }
    }

    std::cout << sum << '\n';

    return 0;
}