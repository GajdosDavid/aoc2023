#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
#include <cassert>

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

auto get_maps() {
    std::string line;
    std::vector<std::vector<std::tuple<std::uint32_t, std::uint32_t, std::uint32_t>>> maps;

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

            maps.push_back(std::move(triples));
        }
    }

    return maps;
}

bool does_trace_to_seed(std::uint32_t x, auto& maps, const auto& seeds) {

    for (int i = maps.size() - 2; i >= 0; i--) {
        const auto& map = maps[i];
        for (auto [dest, source, len]: map) {
            if (x >= dest && x <= dest + len) {
                x = x - dest + source;
                break;
            }
        }
    }

    assert(seeds.size() % 2 == 0);
    for (std::size_t i = 0; i < seeds.size(); i += 2) {
        auto start = seeds[i];
        auto len = seeds[i + 1];

        if (x >= start && x <= start + len) {
            return true;
        }
    }

    return false;
}

int main() {
    std::string line;

    // seeds
    std::getline(std::cin, line);

    auto seeds = get_seeds(line);
    auto maps = get_maps();

    auto cmp = [](const auto& a, const auto& b) { return  std::get<0>(a) < std::get<0>(b);};
    auto& locations = maps.back();
    std::sort(locations.begin(), locations.end(), cmp);

    std::size_t i = 0;
    for (auto [dest, source, len] : locations) {
        if (i < dest) {
            for (; i < dest; i++) {
                if (does_trace_to_seed(i, maps, seeds)) {
                    std::cout << i << '\n';
                    return 0;
                }
            }
        }

        for (i = dest; i < dest + len; i++) {
            if (does_trace_to_seed(i - dest + source, maps, seeds)) {
                std::cout << i << '\n';
                return 0;
            }
        }
    }
}