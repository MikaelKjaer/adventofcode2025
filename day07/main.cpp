//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  std::optional<std::size_t> find_entry_point(const std::string& line)
  {
    for (std::size_t i = 0; i < line.size(); ++i)
    {
      if (line[i] == 'S')
      {
        return i;
      }
    }
    return {};
  }

  std::size_t part_one(const aoc::utility::input_t& input)
  {
    auto splits = 0uz;

    if (const auto maybe_start = find_entry_point(input[0]))
    {
      auto work_tree = input;
      auto current_line = 0uz;
      work_tree[current_line][maybe_start.value()] = '|';

      for (; current_line < work_tree.size(); ++current_line)
      {
        if (current_line + 1 < work_tree.size())
        {
          const std::size_t next_line = current_line + 1uz;
          for (std::size_t i = 0; i < work_tree[current_line].size(); ++i)
          {
            if (work_tree[current_line][i] == '|')
            {
              if (work_tree[next_line][i] == '.')
              {
                work_tree[next_line][i] = '|';
              }
              if (work_tree[next_line][i] == '^')
              {
                work_tree[next_line][i-1] = '|';
                work_tree[next_line][i+1] = '|';
                ++splits;
              }
            }
          }
        }
      }
    }

    return splits;
  }

  std::size_t part_two(const aoc::utility::input_t& input)
  {
    auto timelines = 0uz;
    if (const auto maybe_start = find_entry_point(input[0]))
    {
      auto work_tree = std::vector<std::vector<std::size_t>>{};
      for (const auto& line : input)
      {
        std::vector<std::size_t> entries;
        entries.reserve(line.size());
        entries.resize(line.size(), 0);
        work_tree.emplace_back(entries);
      }

      auto current_line = 0uz;
      work_tree[current_line][maybe_start.value()] = 1;

      for (; current_line < work_tree.size(); ++current_line)
      {
        if (current_line + 1 < work_tree.size())
        {
          const std::size_t next_line = current_line + 1uz;
          for (std::size_t i = 0; i < work_tree[current_line].size(); ++i)
          {
            if (work_tree[current_line][i] > 0)
            {
              if (input[next_line][i] == '.')
              {
                work_tree[next_line][i] += work_tree[current_line][i];
              }
              if (input[next_line][i] == '^')
              {
                work_tree[next_line][i-1] += work_tree[current_line][i];
                work_tree[next_line][i+1] += work_tree[current_line][i];
              }
            }
          }
        }
      }

      auto& last_line = work_tree.back();
      for (std::size_t value : last_line)
      {
        timelines += value;
      }
    }
    return timelines;
  }
}

int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day07.txt");

    aoc::utility::run_part(1, part_one, input);
    aoc::utility::run_part(2, part_two, input);
  }
  catch (const std::exception &e)
  {
    std::print("{}\n", e.what());
    return -1;
  }
  return 0;
}
