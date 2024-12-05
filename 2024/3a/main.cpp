#include <print>
#include <sstream>
#include <fstream>
#include <expected>

int main()
{
    std::stringstream input;
    input << std::ifstream("input.txt").rdbuf();
    auto string = input.str();

    std::size_t result = 0;
    for (auto pos = string.find("mul("); pos != std::string::npos; pos = string.find("mul(", pos + 1))
    {
        auto comma = string.find(',', pos);
        if (comma - pos > 7)
            continue;

        auto close = string.find(')', comma);
        if (close - comma > 4)
            continue;

        auto read = [](const auto &str) -> std::optional<int>
        {
            int ret;
            try {
                ret = std::stoi(str);
            }
            catch (...) {
                return std::nullopt;
            }
            return ret;
        };

        auto val1 = read(string.substr(pos + 4, comma - pos - 4));
        if (!val1.has_value())
            continue;

        auto val2 = read(string.substr(comma + 1, close - comma - 1));
        if (!val2.has_value())
            continue;

        result += val1.value() * val2.value();
    }

    std::println("{}", result);
}
