#include <string>
#include <iostream>
#include <vector>
#include <cassert>

std::vector<int> get_numbers(const std::string& line) {
    std::vector<int> out;

    auto colon_pos = line.find(':');
    colon_pos++;

    while (colon_pos < line.size()) {
        while (colon_pos < line.size() && std::isspace(line[colon_pos])) colon_pos++;

        int num = 0;
        while (colon_pos != line.size() && std::isdigit(line[colon_pos])) {
            num = num * 10 + (line[colon_pos] - '0');
            colon_pos++;
        }

        out.push_back(num);
    }

    return out;
}

int get_winning_ways_count(int time, int distance) {
    int count = 0;
    for (int speed = 0; speed <= time; speed++) {
        int moving_duration = time - speed;

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

    auto times = get_numbers(time_line);
    auto distances = get_numbers(distance_line);

    assert(times.size() == distances.size());

    int product = 1;
    for (std::size_t i = 0; i < distances.size(); i++) {
        int time = times[i];
        int distance = distances[i];

        int count = get_winning_ways_count(time, distance);

        product *= count;
    }

    std::cout << product << '\n';
}