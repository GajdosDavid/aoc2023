#include <string>
#include <iostream>
#include <vector>
#include <tuple>

std::vector<std::uint32_t> get_seeds(const std::string& line) {
    std::vector<std::uint32_t> out;

    auto colon_pos = line.find(':');
    // succ one more after colon
    colon_pos++;

    while (colon_pos < line.size()) {
        while (std::isspace(line[colon_pos])) colon_pos++;

        if (colon_pos == line.size()) break;

        std::uint32_t num = 0;
        while (colon_pos != line.size() && std::isdigit(line[colon_pos])) {
            num = num * 10 + (line[colon_pos] - '0');
            colon_pos++;
        }

        out.push_back(num);
    }

    return out;
}

void remap_values(std::vector<std::uint32_t>& vals,
                  const std::vector<std::tuple<std::uint32_t, std::uint32_t, std::uint32_t>>& triples) {
    for (auto& val : vals) {
        for (auto [dest, source, len] : triples) {
            if (val >= source && val <= source + len) {
                val = val - source + dest;
                break;
            }
        }
    }
}

int main() {
    std::string line;

    // seeds
    std::getline(std::cin, line);

    auto seeds = get_seeds(line);

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        if (line.find("map") != std::string::npos) {
            std::vector<std::tuple<std::uint32_t, std::uint32_t, std::uint32_t>> triples;
            while(std::getline(std::cin, line)) {
                if (line.empty()) break;

                std::vector<std::uint32_t> triple;
                std::size_t start = 0;
                while (start != std::string::npos) {
                    std::size_t end = line.find(' ', start + 1);

                    auto num = std::stoul(line.substr(start, end));

                    triple.push_back(num);
                    start = end;
                }

                triples.emplace_back(triple[0], triple[1], triple[2]);
            }

            remap_values(seeds, triples);
        }
    }

    auto min = seeds[0];
    for (auto seed : seeds) {
        if (seed < min) {
            min = seed;
        }
    }

    std::cout << min << '\n';
}