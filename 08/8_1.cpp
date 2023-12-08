#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>

int main() {
    std::string line;
    std::string traverse_string;
    std::getline(std::cin, traverse_string);

    std::unordered_map<std::string, std::pair<std::string, std::string>> graph;
    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;

        auto space_pos = line.find(' ');
        auto left_parenthesis = line.find('(');
        auto comma_pos = line.find(',');

        std::string node = line.substr(0, space_pos);
        std::string left_child = line.substr(left_parenthesis + 1, 3);
        std::string right_child = line.substr(comma_pos + 2, 3);

        graph.insert({std::move(node), { std::move(left_child), std::move(right_child)}});
    }

    std::size_t i = 0;
    int steps_count = 0;
    std::string current_node = graph.at("AAA").first;
    while (current_node != "ZZZ") {
        char step = traverse_string[i];

        if (step == 'L') {
            current_node = graph.at(current_node).first;
        } else {
            current_node = graph.at(current_node).second;
        }

        steps_count++;
        i = (i + 1) % traverse_string.size();
    }

    std::cout << steps_count << '\n';
}