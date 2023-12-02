#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

static const std::unordered_map<std::string, int> limits {
        {"red", 12},
        {"green", 13},
        {"blue", 14}
};

bool check_sub_game_limits(const std::string& sub_game) {
    for (const auto& [color, limit]: limits) {
        if (std::size_t color_pos; (color_pos = sub_game.find(color)) != std::string::npos) {
            auto pos_end = color_pos - 1;
            auto pos_start = pos_end - 1;

            while (::isdigit(sub_game[pos_start])) pos_start--;

            auto count = std::stoi(sub_game.substr(pos_start, pos_end));
            if (count > limit)
                return false;
        }
    }

    return true;
}

int main() {
    std::string line;
    int sum = 0;
    int game_counter = 1;

    while (std::getline(std::cin, line)) {
        const std::string sub_games = line.substr(line.find(':') + 1, std::string::npos);
        std::stringstream ss(sub_games);
        std::string sub_game;
        bool is_okay = true;

        while (std::getline(ss, sub_game, ';')) {
            is_okay &= check_sub_game_limits(sub_game);
        }

        if (is_okay) {
            sum += game_counter;
        }

        game_counter++;
    }

    std::cout << sum << '\n';
}