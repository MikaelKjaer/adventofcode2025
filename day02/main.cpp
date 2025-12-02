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

    std::size_t total = 0uz;
    for (const auto& entry : entries)
    {
      std::size_t lower_bound = entry.lower;
      if (entry.lower_digits % 2 != 0 and entry.upper_digits % 2 == 0)
      {
        while (aoc::utility::count_digits(lower_bound) % 2 != 0 and lower_bound < entry.upper)
        {
          ++lower_bound;
        }
      }

      std::size_t upper_bound = entry.upper;
      if (entry.upper_digits % 2 != 0 and entry.lower_digits % 2 == 0)
      {
        while (aoc::utility::count_digits(upper_bound) % 2 != 0 and upper_bound > entry.lower)
        {
          --upper_bound;
        }
      }

      for (std::size_t i = lower_bound; i <= upper_bound; ++i)
      {
        const auto digits = aoc::utility::count_digits(i);
        const auto divisor = static_cast<std::size_t>(std::pow(10uz, (digits / 2uz)));
        const auto upper = i / divisor;
        const auto lower = i % divisor;
        if (upper == lower)
        {
          //std::println("Part 1 found: {}", i);
          result += i;
          ++total;
        }
      }
    }
    std::println("Part 1 total found: {}", total);
    return result;
  }

  bool split_and_compare(std::size_t value, std::size_t digits)
  {
    const auto divisor = static_cast<std::size_t>(std::pow(10uz, digits));
    std::size_t previous = value / divisor;
    std::vector<std::size_t> remainders;
    remainders.emplace_back(value % divisor);

    while (previous > 0)
    {
      remainders.emplace_back(previous % divisor);
      previous /= divisor;
    }

    bool is_same = true;
    previous = remainders.front();
    for (auto& remainder : remainders)
    {
      if (previous != remainder)
      {
        is_same = false;
      }
    }
    return is_same;
  }

  std::size_t part_two(const entries_t& entries)
  {
    std::size_t result = 0uz;
    std::size_t total = 0uz;

    for (const auto& entry : entries)
    {
      std::size_t lower_bound = entry.lower;
      std::size_t upper_bound = entry.upper;

      for (std::size_t i = lower_bound; i <= upper_bound; ++i)
      {
        const auto digits = aoc::utility::count_digits(i);
        if (digits == 1)
        {
          continue;
        }

        for (std::size_t j = 1; j <= digits / 2; ++j)
        {
          if ((j == 1 or digits % j == 0) and split_and_compare(i, j))
          {
            //std::println("Part 2 found: {}", i);
            result += i;
            ++total;
            break;
          }
        }

      }
    }

    std::println("Part 2 total found: {}", total);
    return result;
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
