//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  std::size_t part_one(const aoc::utility::input_t& input)
  {
    auto splits = 0uz;

    return splits;
  }
}

int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day08.txt");

    aoc::utility::run_part(1, part_one, input);
    //aoc::utility::run_part(2, part_two, input);
  }
  catch (const std::exception &e)
  {
    std::print("{}\n", e.what());
    return -1;
  }
  return 0;
}
