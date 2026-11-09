#pragma once

#include <cctype>
#include <cstddef>
#include <forward_list>
#include <span>
#include <string>
#include <unordered_set>
#include <string_view>
#include <algorithm>

class Lexer
{
    inline static const std::unordered_set<std::string_view> ariop = {
        "+", "-", "*", "/", "%", "++",
        "--", "+=", "-=", "*=", "/=", "%="
    };

    inline static const std::unordered_set<std::string_view> relop = {
        "<", ">", "<=", ">=", "==", "!="
    };

    static std::size_t longest_in_set(const std::unordered_set<std::string_view>& set) {
        return std::ranges::max(set, {}, &std::string_view::size).size();
    }

    inline static const std::size_t ariop_max = longest_in_set(ariop);

    inline static const std::size_t relop_max = longest_in_set(relop);

    static std::size_t match_op(const std::unordered_set<std::string_view>& ops,
        std::size_t maxlen, const char* cur, const char* end)
    {
        const std::size_t available = static_cast<std::size_t>(end - cur);

        for (std::size_t i = std::min(maxlen, available); i > 0; i--)
            if (ops.contains(std::string_view(cur, i)))
                return i;

        return 0;
    }

    static std::forward_list<std::span<char>> tokenize_range(char* cur, char* end)
    {
        std::forward_list<std::span<char>> res;
        auto last = res.before_begin();

        auto add = [&](char* b, char* e) {
            last = res.insert_after(last, std::span<char>(b, e));
        };

        auto skip_digits = [&] {
            while (cur < end && std::isdigit(static_cast<unsigned char>(*cur)))
                cur++;
        };

        while (cur < end)
        {
            if (std::isspace(static_cast<unsigned char>(*cur))) {
                cur++; continue;
            }

            char* start = cur;

            // Identyfikatory
            if (std::isalpha(static_cast<unsigned char>(*cur)))
                while (cur < end && (std::isalnum(static_cast<unsigned char>(*cur))))
                    cur++;

            // Liczby
            else if (std::isdigit(static_cast<unsigned char>(*cur)))
            {
                skip_digits();
                if (cur + 1 < end && *cur == '.' && std::isdigit(static_cast<unsigned char>(cur[1])))
                {
                    cur++;
                    skip_digits();
                }
            }

            // Operatory relacyjne
            else if (std::size_t n = match_op(relop, relop_max, cur, end))
                cur += n;

            // Operatory arytmetyczne
            else if (std::size_t n = match_op(ariop, ariop_max, cur, end))
                cur += n;

            // Nieznany znak, nawiasy, interpunkcja
            else
                cur++;

            add(start, cur);
        }

        return res;
    }

    public:
        static std::forward_list<std::span<char>> tokenize(std::string& str) {
            return tokenize_range(str.data(), str.data() + str.size());
        }
};
