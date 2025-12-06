//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  enum struct operation_t : std::uint8_t
  {
    none,
    add,
    multiply
  };

  struct problem
  {
    std::vector<std::size_t> values;
    operation_t operation;
  };

  using problems_t = std::vector<problem>;

  problems_t parse_part_one(const aoc::utility::input_t& input)
  {
    using std::string_view_literals::operator""sv;

    problems_t problems;

    auto to_number = [](std::string_view value) -> std::size_t {
      std::string str{value};
      aoc::utility::trim(str);
      return std::stoull(str);
    };

    auto handle_number_line = [&problems, &to_number](const aoc::utility::input_t& line_input, std::size_t index){
      const auto& line = line_input[index];
      auto numbers_as_range = std::views::split(line, " "sv) | std::ranges::to<std::vector>();
      auto [first_to_remove, last_to_remove] = std::ranges::remove_if(numbers_as_range, [](const auto& value) {
        std::string_view str{value};
        return str.empty();
      });
      numbers_as_range.erase(first_to_remove, last_to_remove);
      for (std::size_t i = 0; i < numbers_as_range.size(); ++i)
      {
        std::string_view number_as_sv{numbers_as_range[i]};
        if (not number_as_sv.empty())
        {
          if (index == 0)
          {
            problems.emplace_back(problem{});
          }

          problems[i].values.emplace_back(to_number(number_as_sv));
        }
      }
    };

    auto handle_operators_line = [&problems](const aoc::utility::input_t& line_input, std::size_t index) {
      const auto& line = line_input[index];
      auto operators_as_range = std::views::split(line, " "sv) | std::ranges::to<std::vector>();

      auto [first_to_remove, last_to_remove] = std::ranges::remove_if(operators_as_range, [](const auto& value) {
        std::string_view str{value};
        return str.empty();
      });
      operators_as_range.erase(first_to_remove, last_to_remove);

      for (std::size_t i = 0; i < operators_as_range.size(); ++i)
      {
        problems[i].operation = operation_t::none;
        std::string_view operator_as_sv{operators_as_range[i]};
        if (not operator_as_sv.empty())
        {
          if (operator_as_sv.contains("+"sv))
          {
            problems[i].operation = operation_t::add;
          }
          else if (operator_as_sv.contains("*"sv))
          {
            problems[i].operation = operation_t::multiply;
          }
        }
      }
    };

    handle_number_line(input, 0);
    handle_number_line(input, 1);
    handle_number_line(input, 2);
    handle_number_line(input, 3);
    handle_operators_line(input, 4);

    problems.shrink_to_fit();
    return problems;
  }

  std::size_t part_one(const aoc::utility::input_t& input)
  {
    auto problems = parse_part_one(input);
    auto total = 0uz;

    for (const auto& [values, operation] : problems)
    {
      if (operation == operation_t::add)
      {
        total += std::ranges::fold_left(values, 0, std::plus{});
      }
      else if (operation == operation_t::multiply)
      {
        total += std::ranges::fold_left(values, 1, std::multiplies{});
      }
      else if (operation == operation_t::none)
      {
        std::println("Critical error: no operation with numbers: {}, {}, {}, {}", values[0], values[1], values[2], values[3]);
      }
    }
    return total;
  }

  std::size_t part_two(const aoc::utility::input_t& input)
  {
    auto total = 0uz;

    auto handle_line = [](const char c, std::size_t& value, std::size_t& digits) {
      if (std::isdigit(c))
      {
        std::string str{c};
        value += (std::stoull(str) * static_cast<std::size_t>(std::pow(10, digits)));
        ++digits;
      }
    };

    auto line_one_it = input[0].rbegin();
    auto line_two_it = input[1].rbegin();
    auto line_three_it = input[2].rbegin();
    auto line_four_it = input[3].rbegin();
    auto operator_line_it = input[4].rbegin();

    std::vector<std::size_t> values;
    for (; line_one_it != input[0].rend(); ++line_one_it, ++line_two_it, ++line_three_it, ++line_four_it, ++operator_line_it)
    {
      auto value = 0uz;
      auto digits = 0uz;

      handle_line(*line_four_it, value, digits);
      handle_line(*line_three_it, value, digits);
      handle_line(*line_two_it, value, digits);
      handle_line(*line_one_it, value, digits);

      if (value != 0uz)
      {
        values.emplace_back(value);
      }

      auto operator_c = *operator_line_it;
      if (operator_c == '+')
      {
        total += std::ranges::fold_left(values, 0, std::plus{});
        values.clear();
      }
      else if (operator_c == '*')
      {
        total += std::ranges::fold_left(values, 1, std::multiplies{});
        values.clear();
      }
    }

    return total;
  }
}

int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day06.txt");
    input[4].append("  ");
    aoc::utility::run_part(1, part_one, input);
    aoc::utility::run_part(2, part_two, input);
  }
  catch (const std::exception &e)
  {
    std::print("{}\n", e.what());
    return -1;
  }
  return 0;
  return 0;
}
