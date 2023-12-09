#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::int32_t> parse_line(const std::string& line) {
    std::vector<std::int32_t> out;
    std::stringstream ss(line);
    std::string num;

    while (std::getline(ss, num, ' ')) {
        std::int32_t n = 0;
        std::size_t i = 0;

        bool is_negative = false;
        if (num[0] == '-') {
            is_negative = true;
            i++;
        }

        while (i != num.size()) {
            n = n * 10 + (num[i] - '0');

            i++;
        }

        if (is_negative)
            n = n * (-1);

        out.push_back(n);
    }


    return out;
}

void extrapolate_next_num(std::vector<std::int32_t>& nums) {
    if (std::all_of(nums.begin(), nums.end(), [](auto n){ return n == 0;})) {
        return;
    }

    std::vector<std::int32_t> differences;

    for (std::size_t i = 0; i < nums.size() - 1; i++) {
        differences.push_back(nums[i + 1] - nums[i]);
    }
    extrapolate_next_num(differences);

    nums.insert(nums.begin(), nums.front() - differences.front());
}

std::int32_t get_solution() {
    std::string line;
    std::int32_t sum = 0;

    while (std::getline(std::cin, line)) {
        auto nums = parse_line(line);

        extrapolate_next_num(nums);

        sum += nums.front();
    }

    return sum;
}

int main() {
    std::cout << get_solution() << '\n';
}