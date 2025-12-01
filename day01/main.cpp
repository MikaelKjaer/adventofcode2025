//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  enum struct direction_t : std::uint8_t
  {
    left,
    right
  };

  struct action
  {
    direction_t direction;
    std::size_t clicks;
  };

  struct dial
  {
    constexpr explicit dial() :
      _position{50},
      _zeroed{0},
      _passed_zero{0}
    {}

    void handle(const action& action)
    {
      if (action.direction == direction_t::left)
      {
        turn_left(action.clicks);
      }
      else
      {
        turn_right(action.clicks);
      }

      if (_position == 0)
      {
        ++_zeroed;
      }
    }

    std::size_t zeroed() const { return _zeroed; }
    std::size_t passed_zero() const { return _passed_zero; }

  private:
    constexpr static std::int8_t upper_limit = 99;

    void turn_left(std::size_t clicks)
    {
      for (std::size_t i = 0; i < clicks; ++i)
      {
        if (_position - 1 < 0)
        {
          _position = upper_limit;
        }
        else
        {
          --_position;
        }
        if (_position == 0)
        {
          ++_passed_zero;
        }
      }
    }

    void turn_right(std::size_t clicks)
    {
      for (std::size_t i = 0; i < clicks; ++i)
      {
        if (_position + 1 > upper_limit)
        {
          _position = 0;
        }
        else
        {
          ++_position;
        }
        if (_position == 0)
        {
          ++_passed_zero;
        }
      }
    }

    std::int8_t _position;
    std::size_t _zeroed;
    std::size_t _passed_zero;
  };

  std::vector<action> parse(const aoc::utility::input_t& input)
  {
    std::vector<action> entries;
    for (const auto& line : input)
    {
      auto number = 0uz;
      auto direction = direction_t::left;
      if (line[0] == 'R')
      {
        direction = direction_t::right;
      }
      std::from_chars(line.data() + 1, line.data() + line.size(), number);
      entries.emplace_back(action{.direction = direction, .clicks = number});
    }
    return entries;
  }

  std::size_t part_one(const std::vector<action>& entries)
  {
    dial d{};
    for (auto& action : entries)
    {
      d.handle(action);
    }

    return d.zeroed();
  }

  std::size_t part_two(const std::vector<action>& entries)
  {
    dial d{};
    for (auto& action : entries)
    {
      d.handle(action);
    }

    return d.passed_zero();
  }
}

int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day01.txt");
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
