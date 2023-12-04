#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

std::unordered_set<int> get_winning_numbers(std::size_t colon_pos, std::size_t pipe_pos, const std::string& line) {
    std::unordered_set<int> out;

    // skip the colon
    colon_pos++;
    while (colon_pos < pipe_pos) {
        while (std::isspace(line[colon_pos])) colon_pos++;

        if (colon_pos == pipe_pos) break;

        int num = 0;
        while (colon_pos < pipe_pos && std::isdigit(line[colon_pos])) {
            num = num * 10 + (line[colon_pos] - '0');
            colon_pos++;
        }

        if (num != 0) {
            out.insert(num);
        }
    }

    return out;
}

int get_hit_count_for_card(std::size_t pipe_pos, const std::string& line, const std::unordered_set<int>& winning_nums) {
    int hit_count = 0;

    // move after the pipe
    pipe_pos++;
    while (pipe_pos < line.size()) {
        while (std::isspace(line[pipe_pos])) pipe_pos++;

        if (pipe_pos == line.size()) break;

        int num = 0;
        while (pipe_pos != line.size() && std::isdigit(line[pipe_pos])) {
            num = num * 10 + (line[pipe_pos] - '0');
            pipe_pos++;
        }

        if (winning_nums.contains(num)) hit_count++;
    }

    return hit_count;
}

int main() {
    std::string line;
    std::unordered_map<int, int> cards;

    int current_card_no = 1;
    while (std::getline(std::cin, line)) {
        auto colon_pos = line.find(':');
        auto pipe_pos = line.find('|');

        if (colon_pos == std::string::npos || pipe_pos == std::string::npos) {
            std::cout << "'" << line << "' contains no colon or pipe symbols!";
            continue;
        }

        auto winning_nums = get_winning_numbers(colon_pos, pipe_pos, line);
        auto hit_count = get_hit_count_for_card(pipe_pos, line, winning_nums);

        cards[current_card_no]++;
        while (hit_count) {
            cards[current_card_no + hit_count] += cards[current_card_no];
            hit_count--;
        }

        current_card_no++;
    }

    int sum = 0;
    for (auto [card, count] : cards) {
        sum += count;
    }

    std::cout << sum << '\n';
}