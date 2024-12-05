#include <algorithm>
#include <print>
#include <sstream>
#include <fstream>
#include <vector>
#include <ranges>
#include <cstddef>

int main()
{
    namespace ranges = std::ranges;
    namespace views = ranges::views;

    std::stringstream input;
    input << std::ifstream("input.txt").rdbuf();

    const auto lines = input.str() |
        views::split('\n') |
        views::filter([](const auto &line) { return !line.empty(); }) |
        views::transform([](const auto &line) {
            return line |
                views::split(' ') |
                views::filter([](const auto &item) { return !item.empty(); }) |
                views::transform([](const auto &item) {
                    return std::stoi(item | ranges::to<std::string>());
                });
        }) | ranges::to<std::vector<std::vector<int>>>();

    std::size_t result = 0;
    ranges::for_each(lines, [&result](const auto &line) {
        auto is_safe = [](const auto &line)
        {
            if (!ranges::is_sorted(line) && !ranges::is_sorted(line, ranges::greater()))
                return false;

            for (const auto &[first, second] : line | views::pairwise)
            {
                auto diff = std::abs(first - second);
                if (diff < 1 || diff > 3)
                    return false;
            }
            return true;
        };

        for (std::size_t i = 0; i < line.size(); i++)
        {
            auto copy = line;
            copy.erase(copy.begin() + i);
            if (is_safe(copy))
            {
                result++;
                return;
            }
        }
    });

    std::println("{}", result);
}
