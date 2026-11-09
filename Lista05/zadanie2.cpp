#include "lexer.hpp"

#include <cctype>
#include <optional>
#include <stack>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <string>
#include <deque>
#include <map>
#include <unordered_map>
#include <forward_list>
#include <print>
#include <algorithm>
#include <span>
#include <vector>

enum class Token {
    NUM, CONST, VAR, FUN, OP, COMMA, LPAR, RPAR
};

class Symbol : public std::tuple<Token, std::optional<double>, std::optional<std::string>, int>
{
    using base = std::tuple<Token, std::optional<double>, std::optional<std::string>, int>;

    public:
        Symbol(Token tk, std::optional<double> value = std::nullopt,
            std::optional<std::string> name = std::nullopt, int priority = 0) :
            base(tk, value, std::move(name), priority) {}

        Token getToken() const { return std::get<0>(*this); }

        const std::optional<double>& getValue() const { return std::get<1>(*this); }

        const std::optional<std::string>& getName() const { return std::get<2>(*this); }

        int getPriority() const { return std::get<3>(*this); }
};

class Parser
{
    std::unordered_map<std::string, double> variables = {
        {"x", 6}, {"y", 7},
    };

    inline static const std::map<std::string, double> constants = {
        {"pi", 3.1415926535}, {"e", 2.7182818284},
    };

    inline static const std::deque<std::string> op_names = {
        "+", "-", "*", "/", "%"
    };

    inline static const std::deque<std::string> fun_names = {
        "max", "min", "gcd", "pow",
    };

    inline static int op_priority(const std::string& op) {
        return (op == "+" || op == "-") ? 1 : 2;
    }

    public:
        std::forward_list<Symbol> to_symbols(std::string& expr)
        {
            std::forward_list<Symbol> res;
            auto last = res.before_begin();

            auto add = [&](Symbol s) {
                last = res.insert_after(last, std::move(s));
            };

            for (std::span<char> token : Lexer::tokenize(expr))
            {
                std::string str(token.data(), token.size());
                const char c = str[0];

                if (std::isdigit(static_cast<unsigned char>(c)))
                    add(Symbol(Token::NUM, std::stod(str), str));
                else if (str == "(")
                    add(Symbol(Token::LPAR, std::nullopt, "("));
                else if (str == ")")
                    add(Symbol(Token::RPAR, std::nullopt, ")"));
                else if (str == ",")
                    add(Symbol(Token::COMMA, std::nullopt, ","));
                else if (auto it = constants.find(str); it != constants.end())
                    add(Symbol(Token::CONST, it->second, str));
                else if (auto it = variables.find(str); it != variables.end())
                    add(Symbol(Token::VAR, it->second, str));
                else if (std::ranges::find(fun_names, str) != fun_names.end())
                    add(Symbol(Token::FUN, std::nullopt, str, 4));
                else if (std::ranges::find(op_names, str) != op_names.end())
                    add(Symbol(Token::OP, std::nullopt, str, op_priority(str)));
                else
                    throw std::invalid_argument("Nieznany symbol: " + str);
            }

            return res;
        }
};

// https://pl.wiki7.org/wiki/Алгоритм_сортировочной_станции

std::forward_list<Symbol> to_postfix(const std::forward_list<Symbol>& infix)
{
    std::stack<Symbol> stack;
    bool expect_operand = true;
    bool after_fun = false;

    std::forward_list<Symbol> res;
    auto last = res.before_begin();
    auto add = [&](const Symbol& s) {
        last = res.insert_after(last, s);
    };

    for (const Symbol& s : infix)
    {
        const Token t = s.getToken();

        if (after_fun && t != Token::LPAR)
            throw std::invalid_argument("Po funkcji " + stack.top().getName().value() + " oczekiwano nawiasu otwierającego");

        after_fun = false;

        if (t == Token::NUM || t == Token::CONST || t == Token::VAR)
        {
            if (!expect_operand)
                throw std::invalid_argument("Dwa operandy pod rząd, nadmierne: " + s.getName().value());

            add(s);
            expect_operand = false;
        }

        else if (t == Token::FUN)
        {
            if (!expect_operand)
                throw std::invalid_argument("Po otwarciu nawiasu funkcji nie może być operatora: " + s.getName().value());

            stack.push(s);
            after_fun = true;
        }

        else if (t == Token::COMMA)
        {
            if (expect_operand)
                throw std::invalid_argument("Przed przecinkiem w funkcji nie ma operandu!");

            while (!stack.empty() && !(stack.top().getToken() == Token::LPAR))
            {
                add(stack.top());
                stack.pop();
            }

            if (stack.empty())
                throw std::invalid_argument("Przecinek poza nawiasami funkcji!");

            expect_operand = true;
        }

        else if (t == Token::OP)
        {
            if (expect_operand)
                throw std::invalid_argument("Operator " + s.getName().value() + " bez lewego argumentu");

            while (!stack.empty() && stack.top().getToken() == Token::OP &&
                stack.top().getPriority() >= s.getPriority())
            {
                add(stack.top());
                stack.pop();
            }

            stack.push(s);
            expect_operand = true;
        }

        else if (t == Token::LPAR)
        {
            if (!expect_operand)
                throw std::invalid_argument("Nawias otwierający po operandzie");

            stack.push(s);
        }

        else if (t == Token::RPAR)
        {
            if (expect_operand)
                throw std::invalid_argument("Brakuje operandu przed nawiasem zamykającym");

            while (!stack.empty() && !(stack.top().getToken() == Token::LPAR))
            {
                add(stack.top());
                stack.pop();
            }

            if (stack.empty())
                throw std::invalid_argument("Brakuje nawiasu otwierającego");

            stack.pop();

            if (!stack.empty() && stack.top().getToken() == Token::FUN)
            {
                add(stack.top());
                stack.pop();
            }

            expect_operand = false;
        }
    }

    if (expect_operand)
        throw std::invalid_argument("Niekompletne wyrażenie");

    while (!stack.empty())
    {
        if (stack.top().getToken() == Token::LPAR)
            throw std::invalid_argument("Brakuje nawiasu zamykającego");

        add(stack.top());
        stack.pop();
    }

    return res;
}

std::string to_string(const std::forward_list<Symbol>& list)
{
    std::string res;

    for (const Symbol& s : list)
    {
        if (!res.empty())
            res += ' ';

        if (s.getName())
            res += *s.getName();
        else if (s.getValue())
            res += *s.getValue();
        else
            res += '?';
    }

    return res;
}

int main()
{
    Parser par = Parser();

    std::vector<std::string> examples = {
        "(5 * (2 + 1)) - 3",
        "max(1 + 2, 3 * 4)",
        "min(5 + 2 6) - 7",
        "min(5 + 2.6) - 7",
    };

    std::vector<std::pair<std::string, std::string>> results;

    // https://cpp-lang.net/docs/std/algo/ranges/transform/

    std::ranges::transform(examples, std::back_inserter(results), [&](std::string& str) {
        std::string res;
        try { res = to_string(to_postfix(par.to_symbols(str))); }
        catch (const std::invalid_argument& e) { res = e.what(); }
        return std::pair{str, res};
    });

    for (const auto& [infix, postfix] : results)
        std::println("{}:\n{}\n", infix, postfix);

    return 0;
}
