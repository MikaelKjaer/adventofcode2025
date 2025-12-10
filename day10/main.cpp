#include <utility>

//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  using sequence_t = std::bitset<16>;
  using button_sequences_t = std::vector<sequence_t>;
  using joltage_t = std::int64_t;
  using joltages_t = std::vector<joltage_t>;

  struct instruction
  {
    constexpr instruction() = default;
    constexpr instruction(sequence_t on, button_sequences_t sequences, joltages_t jolts) :
      machine_on_sequence{on}, button_sequences{std::move(sequences)}, joltages{std::move(jolts)}
    {}
    constexpr ~instruction() = default;

    sequence_t machine_on_sequence;
    button_sequences_t button_sequences;
    joltages_t joltages;
  };

  std::vector<instruction> parse(const aoc::utility::input_t &input)
  {
    std::vector<instruction> instructions;
    for (const auto& line : input)
    {
      auto part_ranges = std::views::split(line, ' ') | std::ranges::to<std::vector>();
      joltages_t joltages;
      button_sequences_t button_sequences;
      sequence_t on_sequence{};

      for (const auto& range : part_ranges)
      {
        std::string_view sequence{range};
        if (not sequence.empty())
        {
          std::string_view subspan{ sequence.begin() + 1uz, sequence.end() - 1uz };
          if (sequence.front() == '[')
          {
            //Parse into on_off set
            std::size_t i = 0;
            for (auto& c : subspan)
            {
              on_sequence[i++] = c == '#';
            }
          }
          else if (sequence.front() == '(')
          {
            //Parse into a button_sequence
            auto number_ranges = std::views::split(subspan, ',') | std::ranges::to<std::vector>();
            std::vector<std::size_t> numbers;
            for (const auto& nr : number_ranges)
            {
              std::string_view number_as_sv{ nr };
              auto number = 0uz;
              if (auto [_, ec] = std::from_chars(number_as_sv.data(), number_as_sv.data() + number_as_sv.size(), number); ec == std::errc{})
              {
                numbers.emplace_back( number );
              }
            }

            sequence_t buttons{ on_sequence };
            for (std::size_t i = 0; i < buttons.size(); ++i)
            {
              buttons[i] = false;
            }

            for (auto& number : numbers)
            {
              buttons[number] = true;
            }

            button_sequences.emplace_back(buttons);
          }
          else if (sequence.front() == '{')
          {
            //Parse into joltage
            auto number_ranges = std::views::split(subspan, ',') | std::ranges::to<std::vector>();
            for (const auto& nr : number_ranges)
            {
              std::string_view number_as_sv{ nr };
              auto number = 0ll;
              if (auto [_, ec] = std::from_chars(number_as_sv.data(), number_as_sv.data() + number_as_sv.size(), number); ec == std::errc{})
              {
                joltages.emplace_back( number );
              }
            }
          }
        }
      }

      if (not button_sequences.empty() and not joltages.empty())
      {
        instructions.emplace_back(on_sequence, button_sequences, joltages);
      }
    }
    return instructions;
  }

  std::size_t part_one(const std::vector<instruction>& instructions)
  {
    std::vector<std::size_t> smallest;
    smallest.reserve(instructions.size());

    for (const auto& instruction : instructions)
    {
      auto smallest = std::numeric_limits<std::size_t>::max();

      auto target = instruction.machine_on_sequence;
      for (const auto& sequence : instruction.button_sequences)
      {
        
      }
    }

    return std::accumulate(smallest.begin(), smallest.end(), 0uz);
  }
}

int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day10.txt");
    auto instructions = parse(input);
    aoc::utility::run_part(1, part_one, instructions);
    //aoc::utility::run_part(2, part_two, instructions);
  }
  catch (const std::exception &e)
  {
    std::print("{}\n", e.what());
    return -1;
  }
  return 0;
}
