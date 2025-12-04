//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  enum struct slot : std::uint8_t
  {
    empty,
    paper
  };

  using line_t = std::vector<slot>;
  using lines_t = std::vector<line_t>;

  lines_t parse(const aoc::utility::input_t& input)
  {
    lines_t result;

    auto line_length = 0uz;
    for (const auto& line : input)
    {
      line_t line_of_slots;
      line_of_slots.emplace_back(slot::empty);
      for (const auto& ch : line)
      {
        if (ch == '.')
        {
          line_of_slots.emplace_back(slot::empty);
        }
        else if (ch == '@')
        {
          line_of_slots.emplace_back(slot::paper);
        }
      }
      line_of_slots.emplace_back(slot::empty);
      line_of_slots.shrink_to_fit();
      line_length = line_of_slots.size();
      result.emplace_back(line_of_slots);
    }

    line_t top_line, bottom_line;
    top_line.reserve(line_length);
    top_line.resize(line_length, slot::empty);
    bottom_line.reserve(line_length);
    bottom_line.resize(line_length, slot::empty);

    result.emplace(result.begin(), top_line);
    result.emplace_back(bottom_line);
    result.shrink_to_fit();
    return result;
  }

  std::size_t adjacent_papers(std::size_t line, std::size_t slot, const lines_t& lines)
  {
    auto count = 0uz;
    for (std::size_t i = line - 1; i < line + 2; ++i)
    {
      for (std::size_t j = slot - 1; j < slot + 2; ++j)
      {
        if (i == line and j == slot)
        {
          continue;
        }
        if (lines[i][j] == slot::paper)
        {
          ++count;
        }
      }
    }
    return count;
  }

  std::size_t part_one(const lines_t& lines)
  {
    auto result = 0uz;

    for (std::size_t line = 1; line < lines.size() - 1; ++line)
    {
      for (std::size_t slot = 1; slot < lines[line].size() - 1; ++slot)
      {
        if (lines[line][slot] == slot::paper)
        {
          if (adjacent_papers(line, slot, lines) < 4uz)
          {
            ++result;
          }
        }
      }
    }
    return result;
  }

  std::size_t remove_adjacent_papers(lines_t& lines)
  {
    auto result = 0uz;

    for (std::size_t line = 1; line < lines.size() - 1; ++line)
    {
      for (std::size_t slot = 1; slot < lines[line].size() - 1; ++slot)
      {
        if (lines[line][slot] == slot::paper)
        {
          if (adjacent_papers(line, slot, lines) < 4uz)
          {
            ++result;
            lines[line][slot] = slot::empty;
          }
        }
      }
    }
    return result;
  }

  std::size_t part_two(lines_t& lines)
  {
    auto result = 0uz;
    auto removed = 0uz;
    do
    {
      removed = remove_adjacent_papers(lines);
      result += removed;
    } while (removed > 0uz);
    return result;
  }
}

int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day04.txt");
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
