#include <print>
#include <sstream>
#include <fstream>
#include <vector>
#include <ranges>

int main()
{
    namespace ranges = std::ranges;
    namespace views = ranges::views;

    std::stringstream input;
    input << std::ifstream("input.txt").rdbuf();

    const auto data = input.str() |
        views::split('\n') |
        views::filter([](const auto &line) { return !line.empty(); }) |
        ranges::to<std::vector<std::string>>();

    std::size_t resulta = 0;
    std::size_t resultb = 0;

    const auto m = data[0].length();
    const auto n = data.size();

    for (auto y : views::iota(0zu, n))
    {
        for (auto x : views::iota(0zu, m))
        {
            // part 1
            auto check = [&](const auto &str) { resulta += (str == "XMAS" || str == "SAMX"); };
            if (y + 3 < n)
            {
                auto str = [&](int dx) {
                    return std::string { data[y][x], data[y + 1][x + 1 * dx], data[y + 2][x + 2 * dx], data[y + 3][x + 3 * dx] };
                };
                check(str(0));
                if (x + 3 < m)
                    check(str(1));
                if (x - 3 < m)
                    check(str(-1));
            }
            if (x + 3 < m)
                check(data[y].substr(x, 4));

            // part 2
            if (x + 2 < m && y + 2 < n)
            {
                if (data[y + 1][x + 1] == 'A')
                {
                    std::string str = { data[y][x], data[y][x + 2], data[y + 2][x], data[y + 2][x + 2] };
                    if (str == "MSMS" || str == "SMSM" || str == "MMSS" || str == "SSMM")
                        resultb++;
                }
            }
        }
    }

    std::println("Part 1: {}", resulta);
    std::println("Part 2: {}", resultb);
}
