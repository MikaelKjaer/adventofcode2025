export module utility;

import std;

export namespace aoc::utility
{
  using input_t = std::vector<std::string>;

  std::size_t count_digits(std::uint64_t x)
  {
    constexpr static std::array<std::uint64_t, 65> digits = {19, 19, 19, 19, 18, 18, 18,
                                                             17, 17, 17, 16, 16, 16,
                                                             16, 15, 15, 15, 14, 14, 14,
                                                             13, 13, 13, 13, 12, 12,
                                                             12, 11, 11, 11, 10, 10, 10,
                                                             10, 9,  9,  9,  8,  8,
                                                             8,  7,  7,  7,  7,  6,  6,
                                                             6,  5,  5,  5,  4,  4,
                                                             4,  4,  3,  3,  3,  2,  2,
                                                             2,  1,  1,  1,  1,  1};
    constexpr static std::array<std::uint64_t, 65> table = { 18446744073709551615ULL,
                                                             18446744073709551615ULL,
                                                             18446744073709551615ULL,
                                                             18446744073709551615ULL,
                                                             999999999999999999ULL,
                                                             999999999999999999ULL,
                                                             999999999999999999ULL,
                                                             99999999999999999ULL,
                                                             99999999999999999ULL,
                                                             99999999999999999ULL,
                                                             9999999999999999ULL,
                                                             9999999999999999ULL,
                                                             9999999999999999ULL,
                                                             9999999999999999ULL,
                                                             999999999999999ULL,
                                                             999999999999999ULL,
                                                             999999999999999ULL,
                                                             99999999999999ULL,
                                                             99999999999999ULL,
                                                             99999999999999ULL,
                                                             9999999999999ULL,
                                                             9999999999999ULL,
                                                             9999999999999ULL,
                                                             9999999999999ULL,
                                                             999999999999ULL,
                                                             999999999999ULL,
                                                             999999999999ULL,
                                                             99999999999ULL,
                                                             99999999999ULL,
                                                             99999999999ULL,
                                                             9999999999ULL,
                                                             9999999999ULL,
                                                             9999999999ULL,
                                                             9999999999ULL,
                                                             999999999ULL,
                                                             999999999ULL,
                                                             999999999ULL,
                                                             99999999ULL,
                                                             99999999ULL,
                                                             99999999ULL,
                                                             9999999ULL,
                                                             9999999ULL,
                                                             9999999ULL,
                                                             9999999ULL,
                                                             999999ULL,
                                                             999999ULL,
                                                             999999ULL,
                                                             99999ULL,
                                                             99999ULL,
                                                             99999ULL,
                                                             9999ULL,
                                                             9999ULL,
                                                             9999ULL,
                                                             9999ULL,
                                                             999ULL,
                                                             999ULL,
                                                             999ULL,
                                                             99ULL,
                                                             99ULL,
                                                             99ULL,
                                                             9ULL,
                                                             9ULL,
                                                             9ULL,
                                                             9ULL,
                                                             0ULL};
  const auto log = static_cast<std::size_t>(std::countl_zero(x));
  const std::uint64_t low = table[log];
  const std::uint64_t high = digits[log];
  return (x > low) + high;
}

  input_t read_file(const std::filesystem::path& path)
  {
    input_t input;
    std::ifstream file_in(path);
    if (!file_in)
    {
      throw std::runtime_error(std::format("Unable to open input file: {0}", path.string()));
    }

    std::string line;
    while (std::getline(file_in, line))
    {
      input.push_back(line);
    }
    input.shrink_to_fit();
    return input;
  }

  inline void left_trim(std::string &s)
  {
    s.erase(s.begin(), std::ranges::find_if(s, [](unsigned char ch) {
      return !std::isspace(ch);
    }));
  }

  // trim from end (in place)
  inline void right_trim(std::string &s)
  {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
      return !std::isspace(ch);
    }).base(), s.end());
  }

  // trim from both ends (in place)
  inline void trim(std::string &s)
  {
    right_trim(s);
    left_trim(s);
  }

  void print_output(std::uint8_t part_no, auto& result, auto time_taken)
  {
    using namespace std::chrono_literals;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time_taken);
    if (ns > 1us)
    {
      if (ns > 1ms)
      {
        if (ns > 1s)
        {
          std::print("Part {0}: {1} in {2}s\n", part_no, result, std::chrono::duration_cast<std::chrono::milliseconds>(time_taken).count());
        }
        else
        {
          std::print("Part {0}: {1} in {2}ms\n", part_no, result, std::chrono::duration_cast<std::chrono::milliseconds>(time_taken).count());
        }
      }
      else
      {
        std::print("Part {0}: {1} in {2}us\n", part_no, result, std::chrono::duration_cast<std::chrono::microseconds>(time_taken).count());
      }
    }
    else
    {
      std::print("Part {0}: {1} in {2}ns\n", part_no, result, std::chrono::duration_cast<std::chrono::nanoseconds>(time_taken).count());
    }
  }

  template <typename...Args>
  void run_test(std::uint8_t test_no, auto to_run, Args&&... args)
  {
    const auto start = std::chrono::high_resolution_clock::now();
    auto result = to_run(std::forward<Args&&>(args)...);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto time_taken = end - start;
    std::print("Test {0}: {1} in {2} us\n", test_no, result, time_taken);
  }

  template <typename...Args>
  void run_part(std::uint8_t part_no, auto to_run, Args&&... args)
  {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = to_run(std::forward<Args&&>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_taken = end - start;
    print_output(part_no, result, time_taken);
  }
}
