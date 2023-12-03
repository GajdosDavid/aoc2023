#include <vector>
#include <map>
#include <utility>
#include <string>
#include <iostream>

std::vector<std::pair<int, int>> adjacent_positions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
};

bool is_symbol(char c) {
    return c != '.' && !std::isdigit(c);
}

bool is_symbol_around(int row, int col, const std::vector<std::string>& lines) {

    for (auto [y, x]: adjacent_positions) {
        if (row + y < 0 || row + y >= lines.size() ||
            col + x < 0 || col + x >= lines[row + y].size())
            continue;

        char c = lines[row + y][col + x];
        if (is_symbol(c))
            return true;
    }

    return false;
}


std::uint32_t sum_numbers(const std::vector<std::string>& lines) {
    std::uint32_t sum = 0;

    for (int row = 0; row < lines.size(); row++) {
        const auto& line = lines[row];
        int num = 0;
        int has_symbol_around = false;

        for (int col = 0; col < line.length(); col++) {
            const char& c = line[col];

            if (::isdigit(c)) {
                has_symbol_around |= is_symbol_around(row, col, lines);
                num = num * 10 + (c - '0');
            }
            else {
                if (has_symbol_around)
                    sum += num;

                num = 0;
                has_symbol_around = false;
            }

            if (col == line.length() - 1 && has_symbol_around)
                sum += num;
        }
    }

    return sum;
}

int main() {
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(std::cin, line)) {
        lines.push_back(std::move(line));
    }

    auto sum = sum_numbers(lines);

    std::cout << sum << '\n';
}
