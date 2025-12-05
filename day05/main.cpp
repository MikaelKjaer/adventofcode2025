//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  struct fresh_ingredient_range
  {
    constexpr fresh_ingredient_range() :
      lower_bound{0}, upper_bound{0}
    {}

    constexpr fresh_ingredient_range(std::size_t lbound, std::size_t ubound) :
      lower_bound{lbound}, upper_bound{ubound}
    {}

    bool operator<(const fresh_ingredient_range &other) const
    {
      return lower_bound < other.lower_bound;
    }

    bool operator<=(const fresh_ingredient_range &other) const
    {
      return lower_bound <= other.lower_bound;
    }

    bool operator>(const fresh_ingredient_range &other) const
    {
      return upper_bound > other.upper_bound;
    }

    bool operator>=(const fresh_ingredient_range &other) const
    {
      return upper_bound >= other.upper_bound;
    }

    bool operator==(const fresh_ingredient_range &other) const = default;

    std::size_t lower_bound = 0uz;
    std::size_t upper_bound = 0uz;
  };

  using fresh_food_t = std::vector<fresh_ingredient_range>;
  using available_food_t = std::vector<std::size_t>;

  fresh_food_t parse_fresh_food_ranges(const aoc::utility::input_t& input)
  {
    using std::string_view_literals::operator""sv;

    fresh_food_t foods;

    auto to_number = [](std::string_view value) -> std::size_t {
      const std::string str{value};
      return std::stoull(str);
    };

    for (const auto& line : input)
    {
      auto numbers = std::views::split(line, "-"sv) | std::ranges::to<std::vector>();

      foods.emplace_back( to_number(std::string_view{numbers[0]}), to_number(std::string_view{numbers[1]}) );
    }

    std::ranges::sort(foods);
    return foods;
  }

  available_food_t parse_ingredients(aoc::utility::input_t& input)
  {
    available_food_t foods;
    for (auto& line : input)
    {
      aoc::utility::trim(line);
      auto value = std::stoull(line);
      foods.emplace_back(value);
    }
    return foods;
  }

  std::vector<fresh_ingredient_range> find_fresh_food(const std::size_t& ingredient, const fresh_food_t& fresh_foods)
  {
    std::vector<fresh_ingredient_range> ranges;

    for (const auto& range : fresh_foods)
    {
      if (ingredient >= range.lower_bound && ingredient <= range.upper_bound)
      {
        ranges.emplace_back(range);
      }
    }
    return ranges;
  }

  std::size_t part_one(const fresh_food_t& fresh_food_ranges, const available_food_t& available_foods)
  {
    auto result = 0uz;

    for (const auto& ingredient : available_foods)
    {
      const auto ranges = find_fresh_food(ingredient, fresh_food_ranges);
      if (not ranges.empty())
      {
        ++result;
      }
    }

    return result;
  }

  std::size_t part_two(const fresh_food_t& fresh_food_ranges)
  {
    auto result = 0uz;
    auto highest_seen = 0uz;

    for (const auto& range : fresh_food_ranges)
    {
      if (range.upper_bound >= highest_seen)
      {
        result += range.upper_bound - std::max(range.lower_bound, highest_seen) + 1uz;
        highest_seen = range.upper_bound + 1uz;
      }
    }

    return result;
  }
}

int main(int, char *[])
{
  try
  {
    auto fresh_input = aoc::utility::read_file("day05_1.txt");
    auto ingredients_input = aoc::utility::read_file("day05_2.txt");
    auto fresh_food_ranges = parse_fresh_food_ranges(fresh_input);
    auto available_ingredients = parse_ingredients(ingredients_input);

    aoc::utility::run_part(1, part_one, fresh_food_ranges, available_ingredients);
    aoc::utility::run_part(2, part_two, fresh_food_ranges);
  }
  catch (const std::exception &e)
  {
    std::print("{}\n", e.what());
    return -1;
  }
  return 0;
}
