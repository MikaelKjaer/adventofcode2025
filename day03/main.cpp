//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  using entry_t = std::size_t;
  using line_t = std::vector<entry_t>;
  using lines_t = std::vector<line_t>;

  lines_t parse(aoc::utility::input_t& input)
  {
    using namespace std::string_view_literals;

    auto to_number = [](const char& value) -> std::size_t {
      auto result = 0uz;
      std::from_chars(&value, &value + 1, result);
      return result;
    };

    lines_t lines{};

    for (auto& line : input)
    {
      std::string_view view{ line.begin(), line.end() };

      line_t entries;
      for (auto& each : view)
      {
        if (std::isdigit(each))
        {
          entries.emplace_back(to_number(each));
        }
      }
      lines.emplace_back(entries);
    }

    return lines;
  }

  auto find_position_of_highest(std::ptrdiff_t start_position, std::ptrdiff_t end_position, const line_t& line)
  {
    auto highest_it = std::begin(line) + start_position;
    for (auto it = std::begin(line) + start_position; it < std::end(line) + end_position; ++it)
    {
      if (*it > *highest_it)
      {
        highest_it = it;
      }
    }
    return std::distance(std::begin(line), highest_it);
  }

  std::size_t part_one(const lines_t& lines)
  {
    std::size_t result = 0uz;

    for (const auto& line : lines)
    {
      const auto position_of_highest = find_position_of_highest(0, -1, line);
      const auto position_of_next_highest = find_position_of_highest(position_of_highest + 1, 0, line);

      const auto first = (*(std::begin(line) + position_of_highest)) * 10;
      const auto second = *(std::begin(line) + position_of_next_highest);
      result += first + second;
    }

    return result;
  }

  std::size_t part_two(const lines_t& lines)
  {
    auto result = 0uz;

    for (const auto& line : lines)
    {
      auto temp = 0uz;
      std::ptrdiff_t start = 0;
      std::ptrdiff_t end = -11;
      for (std::ptrdiff_t position = 11; position >= 0; --position)
      {
        const auto highest_for_position = find_position_of_highest(start, end, line);
        start = highest_for_position + 1;
        ++end;

        const auto value = *(std::begin(line) + highest_for_position) * static_cast<std::size_t>(std::pow(10, position));
        temp += value;
      }
      result += temp;
    }

    return result;
  }
}

int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day03.txt");
    auto lines = parse(input);

    aoc::utility::run_part(1, part_one, lines);
    aoc::utility::run_part(2, part_two, lines);
  }
  catch (const std::exception &e)
  {
    std::print("{}\n", e.what());
    return -1;
  }
  return 0;
}
