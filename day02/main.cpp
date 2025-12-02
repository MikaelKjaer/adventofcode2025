//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  struct entry
  {
    entry(std::size_t l, std::size_t u) :
      lower{l}, lower_digits{0}, upper{u}, upper_digits{0}
    {
      lower_digits = aoc::utility::count_digits(lower);
      upper_digits = aoc::utility::count_digits(upper);
    }

    std::size_t lower;
    std::size_t lower_digits;
    std::size_t upper;
    std::size_t upper_digits;
  };

  using entries_t = std::vector<entry>;

  entries_t parse(aoc::utility::input_t& input)
  {
    using namespace std::string_view_literals;

    auto to_number = [](std::string_view value) -> std::size_t {
      const std::string str{value};
      return std::stoull(str);
    };

    entries_t entries{};
    std::string_view view{ input[0].begin(), input[0].end() };
    auto range = std::views::split(view, ","sv) | std::ranges::to<std::vector>();

    for (auto& each : range)
    {
      auto numbers = std::views::split(each, "-"sv) | std::ranges::to<std::vector>();
      entries.emplace_back( to_number(std::string_view{numbers[0]}), to_number(std::string_view{numbers[1]}) );
    }

    return entries;
  }

  std::size_t part_one(const entries_t& entries)
  {
    std::size_t result = 0uz;

    for (const auto& entry : entries)
    {
      std::size_t lower_bound = entry.lower;
      if (entry.lower_digits % 2 != 0)
      {
        for ()
      }
    }

    return result;
  }

  std::size_t part_two(const entries_t&)
  {
    return 0uz;
  }
}


int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day02.txt");
    auto entries = parse(input);

    aoc::utility::run_part(1, part_one, entries);
    aoc::utility::run_part(2, part_two, entries);
  }
  catch (const std::exception &e)
  {
    std::print("{}\n", e.what());
    return -1;
  }
  return 0;
}
