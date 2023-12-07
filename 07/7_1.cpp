#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <cassert>

enum class HAND_TYPE {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
};

static const std::string card_values = "23456789TJQKA";
HAND_TYPE get_hand_type(const std::string& hand) {
    std::unordered_map<char, int> chars;
    for (char c : hand) {
        chars[c]++;
    }

    switch (chars.size()) {
        case 1:
            return HAND_TYPE::FIVE_OF_A_KIND;
        case 2:
            if (std::any_of(chars.begin(), chars.end(),
                            [](auto a) { return a.second == 4;}))
                return HAND_TYPE::FOUR_OF_A_KIND;

            return HAND_TYPE::FULL_HOUSE;
        case 3:
            if (std::any_of(chars.begin(), chars.end(),
                            [](auto a) { return a.second == 3;}))
                return HAND_TYPE::THREE_OF_A_KIND;

            return HAND_TYPE::TWO_PAIR;
        case 4:
            return HAND_TYPE::ONE_PAIR;
        case 5:
            return HAND_TYPE::HIGH_CARD;
    }

    // unreachable;
    return HAND_TYPE::HIGH_CARD;
}

auto get_hands() {
    std::string line;

    std::vector<std::tuple<std::string, std::uint32_t, HAND_TYPE>> hands;
    while (std::getline(std::cin, line)) {
        auto space_pos = line.find(' ');

        std::uint32_t bid = 0;
        auto i = space_pos + 1;
        while (i != line.size() && std::isdigit(line[i])) {
            bid = bid * 10 + (line[i] - '0');
            i++;
        }

        auto hand = line.substr(0, space_pos);
        auto hand_type = get_hand_type(hand);

        hands.emplace_back(std::move(hand), bid, hand_type);
    }

    return hands;
}

int main() {
    auto hands = get_hands();

    auto cmp = [](const auto& a, const auto& b) {
        if (std::get<2>(a) != std::get<2>(b)) {
            return std::get<2>(a) < std::get<2>(b);
        }

        const auto& hand_a = std::get<0>(a);
        const auto& hand_b = std::get<0>(b);
        int i = 0;

        assert(hand_a.length() == hand_b.length());
        while (i < hand_a.size() &&
               card_values.find(hand_a[i]) == card_values.find(hand_b[i])) i++;

        return card_values.find(hand_a[i]) < card_values.find(hand_b[i]);
    };

    std::sort(hands.begin(), hands.end(), cmp);

    int total_winning = 0;
    for (int i = 0; i < hands.size(); i++) {
        const auto& hand = hands[i];

        total_winning += (i + 1) * std::get<1>(hand);
    }

    std::cout << total_winning << '\n';
}