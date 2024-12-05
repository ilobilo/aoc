#include <algorithm>
#include <print>
#include <sstream>
#include <fstream>
#include <vector>
#include <ranges>
#include <utility>

int main()
{
    namespace ranges = std::ranges;
    namespace views = ranges::views;

    std::stringstream input;
    input << std::ifstream("input.txt").rdbuf();

    const auto pairs = input.str() |
        views::split('\n') |
        views::filter([](const auto &line) { return !line.empty(); }) |
        views::transform([](const auto &line) {
            auto view = line |
                views::split(' ') |
                views::filter([](const auto &item) { return !item.empty(); }) |
                views::transform([](const auto &item) {
                    return std::stoi(item | ranges::to<std::string>());
                });
            return std::make_pair<int, int>(
                (view | views::take(1)).front(),
                (view | views::drop(1) | views::take(1)).front()
            );
        }) | ranges::to<std::vector<std::pair<int, int>>>();

    auto first = pairs | views::keys | ranges::to<std::vector<int>>();
    auto second = pairs | views::values | ranges::to<std::vector<int>>();

    ranges::sort(first);
    ranges::sort(second);

    const auto zipped = views::zip(first, second) | ranges::to<std::vector<std::pair<int, int>>>();
    const auto result = ranges::fold_left(zipped, 0, [](int val, const auto &pair) {
        return val + std::abs(pair.first - pair.second);
    });

    std::println("{}", result);
}
