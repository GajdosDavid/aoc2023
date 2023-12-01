#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

static const int SHORTEST_NUM_WORD_LEN = 3;
std::vector<std::string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int find_first_number_in_string(const std::string& s) {
    int found_num = 0;
    std::size_t curr_pos = s.size();

    auto it = std::find_if(s.cbegin(), s.cend(), ::isdigit);
    if (it != s.cend()) {
        found_num = *it - '0';

        curr_pos = std::distance(s.cbegin(), it);
        if (curr_pos < SHORTEST_NUM_WORD_LEN - 1) {
            //must be the first number
            return found_num;
        }
    }

    for (std::size_t i = 0; i < numbers.size(); i++) {
        std::size_t pos = s.find(numbers[i]);

        if (pos == std::string::npos) continue;

        if (pos < curr_pos) {
            curr_pos = pos;
            found_num = i + 1;
        }
    }

    return found_num;
}

int find_last_number_in_string(const std::string& s) {
    int found_num = 0;
    std::size_t curr_pos = 0;

    auto it = std::find_if(s.crbegin(), s.crend(), ::isdigit);
    if (it != s.crend()) {
        found_num = *it - '0';

        auto distance = std::distance(s.crbegin(), it);
        if (distance < SHORTEST_NUM_WORD_LEN - 1) {
            //must be the last number
            return found_num;
        }
        curr_pos = s.size() - distance - 1;
    }

    for (std::size_t i = 0; i < numbers.size(); i++) {
        std::size_t pos = s.rfind(numbers[i]);

        if (pos == std::string::npos) continue;

        if (pos > curr_pos) {
            curr_pos = pos;
            found_num = i + 1;
        }
    }

    return found_num;
}


int main() {
    std::string line;

    int sum = 0;
    while (std::getline(std::cin, line)) {
        int first = find_first_number_in_string(line);
        int last = find_last_number_in_string(line);

        sum += (first * 10) + last;
    }

    std::cout << sum << '\n';

    return 0;
}