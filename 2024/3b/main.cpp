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
    bool enabled = true;

    std::string::size_type pos = 0;
    while (pos != std::string::npos)
    {
        if (pos != 0)
            pos++;

        auto dopos = string.find("do()", pos);
        auto dontpos = string.find("don't()", pos);

        auto npos = string.find("mul(", pos);
        if (npos == std::string::npos)
            break;

        if (auto mpos = std::min(dopos, dontpos); mpos < npos)
        {
            if (dopos < dontpos)
                enabled = true;
            else
                enabled = false;

            pos = mpos;
        }
        if (!enabled)
            continue;

        pos = npos;

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
