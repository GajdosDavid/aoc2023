#include <vector>
#include <map>
#include <utility>
#include <string>
#include <iostream>

using coordinate = std::pair<int, int>;

std::vector<std::pair<int, int>> adjacent_positions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
};

auto get_num_with_coord(int x, const std::string& line) {
    int start = x;
    while (start - 1 >= 0 && std::isdigit(line[start - 1])) start--;

    int num = 0;
    int s = start;
    while (std::isdigit(line[s])) {
        num = num * 10 + (line[s] - '0');
        s++;
    }

    return std::make_pair(start, num);
}

int get_sum(const std::vector<std::string>& lines) {
    int sum = 0;

    for (auto row = 0; row < lines.size(); row++) {
        const auto& current_line = lines[row];
        for (auto col = 0; col < current_line.size(); col++) {
            if (current_line[col] == '*') {
                std::map<coordinate, int> adjacent_nums;

                for (auto [y, x] : adjacent_positions) {
                    if (row + y < 0 || row + y >= lines.size() ||
                        col + x < 0 || col + x >= lines[row + y].size())
                        continue;

                    char c = lines[row + y][col + x];

                    if (::isdigit(c)) {
                        auto [start, num] = get_num_with_coord(col + x, lines[row + y]);

                        adjacent_nums.insert({{start, row+y}, num});
                    }
                }

                if (adjacent_nums.size() == 2) {
                    int product = 1;
                    for (auto [coord, num] : adjacent_nums) {
                        product *= num;
                    }

                    sum += product;
                }
            }
        }
    }

    return sum;
}

int main() {
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    auto sum = get_sum(lines);

    std::cout << sum << '\n';
}