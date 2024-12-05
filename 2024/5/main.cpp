#include <print>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>

int main()
{
    namespace ranges = std::ranges;
    namespace views = ranges::views;

    std::stringstream input;
    input << std::ifstream("input.txt").rdbuf();

    auto str = input.str();
    auto separator = str.rfind("\n\n");
    auto view = views::all(str);

    auto rules = view |
        views::take(separator) | views::split('\n') |
        views::filter([](const auto &line) { return !line.empty(); }) |
        views::transform([](const auto &line) {
            auto view = line | views::split('|') |
                views::filter([](const auto &item) { return !item.empty(); }) |
                views::transform([](const auto &item) {
                    return std::stoi(item | ranges::to<std::string>());
                });
            return std::make_pair<int, int>(
                (view | views::take(1)).front(),
                (view | views::drop(1) | views::take(1)).front()
            );
        }) | ranges::to<std::multimap<int, int>>();

    auto updates = view |
        views::drop(separator + 2) | views::split('\n') |
        views::filter([](const auto &line) { return !line.empty(); }) |
        views::transform([](const auto &line) {
            return line | views::split(',') |
                views::filter([](const auto &item) { return !item.empty(); }) |
                views::transform([](const auto &item) {
                    return std::stoi(item | ranges::to<std::string>());
                }) | ranges::to<std::vector<int>>();
        }) | ranges::to<std::vector<std::vector<int>>>();

    auto is_after = [&rules](const auto &before, const auto &page)
    {
        auto it = rules.equal_range(page);
        auto range = ranges::subrange(it.first, it.second) | views::values;

        for (const auto &value : before)
        {
            if (ranges::contains(range, value))
                return false;
        }
        return true;
    };

    auto is_correct = [&is_after](const auto &update)
    {
        for (const auto &[idx, page] : views::enumerate(update))
        {
            auto range = ranges::subrange(update.begin(), std::next(update.begin(), idx));
            if (!is_after(range, page))
                return false;
        }
        return true;
    };

    std::size_t resulta = 0;
    std::size_t resultb = 0;

    for (auto &update : updates)
    {
        if (!is_correct(update))
        {
            ranges::sort(update, [&is_after](const auto &lhs, const auto &rhs) {
                return is_after(std::array { lhs }, rhs);
            });
            resultb += update.at(update.size() / 2);
        }
        else resulta += update.at(update.size() / 2);
    }

    std::println("Part 1: {}", resulta);
    std::println("Part 2: {}", resultb);
}
