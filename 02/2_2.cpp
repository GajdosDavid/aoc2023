#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

static const std::vector<std::string> colors = { "red", "green", "blue" };

std::tuple<int, int, int> get_fewest_possible_counts(const std::string& line) {
    int counts[] = {1, 1, 1};

    for (std::size_t i = 0; i < colors.size(); i++) {
        const auto& color = colors[i];
        auto& max_count = counts[i];

        std::size_t pos = 0;
        while ((pos = line.find(color, pos + 1)) != std::string::npos) {
            auto pos_end = pos - 1;
            auto pos_start = pos_end - 1;

            while (::isdigit(line[pos_start])) pos_start--;

            auto count = std::stoi(line.substr(pos_start, pos_end));

            if (count > max_count)
                max_count = count;
        }
    }

    return std::make_tuple(counts[0], counts[1], counts[2]);
}

int main() {
    std::string line;
    int sum = 0;

    while (std::getline(std::cin, line)) {
        auto [reds_count, greens_count, blues_count] = get_fewest_possible_counts(line);

        sum += (reds_count * greens_count * blues_count);
    }

    std::cout << sum << '\n';
}