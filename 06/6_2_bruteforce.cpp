#include <string>
#include <iostream>
#include <vector>
#include <cassert>

std::uint64_t get_number(const std::string& line) {
    std::uint64_t num = 0;

    auto colon_pos = line.find(':');
    colon_pos++;

    while (colon_pos < line.size()) {
        while (colon_pos < line.size() && std::isspace(line[colon_pos])) colon_pos++;

        while (colon_pos != line.size() && std::isdigit(line[colon_pos])) {
            num = num * 10 + (line[colon_pos] - '0');
            colon_pos++;
        }
    }

    return num;
}

std::uint64_t get_winning_ways_count(std::uint64_t time, std::uint64_t distance) {
    std::uint64_t count = 0;

    for (std::uint64_t speed = 0; speed <= time; speed++) {
        std::uint64_t moving_duration = time - speed;

        if (moving_duration * speed > distance)
            count++;
    }

    return count;

}

int main() {
    std::string time_line;
    std::string distance_line;

    std::getline(std::cin, time_line);
    std::getline(std::cin, distance_line);

    std::uint64_t time = get_number(time_line);
    std::uint64_t distance = get_number(distance_line);

    std::uint64_t count = get_winning_ways_count(time, distance);

    std::cout << count << '\n';
}