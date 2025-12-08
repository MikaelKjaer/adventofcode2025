//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  struct point3d
  {
    constexpr point3d() :
      x{0}, y{0}, z{0}
    {}
    constexpr point3d(const std::int64_t i, const std::int64_t j, const std::int64_t k) :
      x{i}, y{j}, z{k}
    {}
    constexpr point3d(const point3d&) = default;
    constexpr point3d(point3d&&) noexcept = default;
    constexpr ~point3d() = default;
    constexpr point3d& operator=(const point3d&) = default;
    constexpr point3d& operator=(point3d&&) noexcept = default;
    constexpr bool operator==(const point3d& rhs) const = default;
    constexpr std::strong_ordering operator<=>(const point3d& rhs) const = default;

    std::int64_t distance(const point3d& other) const
    {
      const auto diffX = std::pow(x - other.x, 2);
      const auto diffY = std::pow(y - other.y, 2);
      const auto diffZ = std::pow(z - other.z, 2);
      return static_cast<std::int64_t>(diffX + diffY + diffZ);
    }

    std::int64_t x, y, z;
  };

  struct circuit_connection
  {
    std::size_t first_index, second_index;
  };

  using points_t = std::vector<point3d>;

  points_t parse(const aoc::utility::input_t& input)
  {
    points_t points;

    std::vector<std::int64_t> numbers;
    for (const auto& line : input)
    {
      auto number_ranges = std::views::split(line, ',') | std::ranges::to<std::vector>();
      numbers.clear();
      for (const auto& range : number_ranges)
      {
        std::string_view number_as_sv{range};
        auto number = 0uz;
        if (const auto [ptr, ec] = std::from_chars(number_as_sv.data(), number_as_sv.data() + number_as_sv.size(), number); ec == std::errc{})
        {
          numbers.emplace_back(number);
        }
      }

      if (numbers.size() == 3)
      {
        points.emplace_back(numbers[0], numbers[1], numbers[2]);
      }
    }
    points.shrink_to_fit();
    return points;
  }

  std::int64_t part_one(const points_t& points)
  {
    std::vector<std::size_t> circuits(points.size());
    std::iota(circuits.begin(), circuits.end(), 0);

    const auto find = [&circuits](std::size_t index)
    {
      std::size_t target = index;
      while(circuits[target] != target)
      {
        target = circuits[target];
      }

      while(circuits[index] != index)
      {
        index = std::exchange(circuits[index], target);
      }

      return target;
    };

    const auto merge_circuits = [&circuits, &find](std::size_t lhs_index, std::size_t rhs_index)
    {
      lhs_index = find(lhs_index);
      rhs_index = find(rhs_index);

      circuits[lhs_index] = rhs_index;
    };

    const auto compare_connections = [&](const circuit_connection& lhs, const circuit_connection& rhs)
    {
      const auto lhs_dist = points[lhs.first_index].distance(points[lhs.second_index]);
      const auto rhs_dist = points[rhs.first_index].distance(points[rhs.second_index]);

      return rhs_dist < lhs_dist;
    };

    std::priority_queue<circuit_connection, std::deque<circuit_connection>, decltype(compare_connections)> connections{compare_connections};

    for(auto i = 0uz; i < points.size(); ++i)
    {
      for(auto j = i + 1uz; j < points.size(); ++j)
      {
        connections.emplace(i, j);
      }
    }

    for(auto i = 0uz; i < 1000uz; ++i)
    {
      const auto [first_index, second_index] = connections.top();
      connections.pop();
      merge_circuits(first_index, second_index);
    }

    std::unordered_map<std::size_t, std::int64_t> sizes_per_group;
    for(auto i = 0uz; i < circuits.size(); ++i)
    {
      ++sizes_per_group[find(i)];
    }

    std::vector<std::int64_t> sizes;
    for(const auto& size : sizes_per_group | std::views::values)
    {
      sizes.push_back(size);
    }

    std::ranges::nth_element(sizes, sizes.begin() + 3uz, std::greater<>{});
    return std::accumulate(sizes.begin(), sizes.begin() + 3uz, 1ll, std::multiplies<>{});
  }

  std::int64_t part_two(const points_t& points)
  {
    std::vector<std::size_t> circuits(points.size());
    std::iota(circuits.begin(), circuits.end(), 0);

    const auto find = [&circuits](std::size_t index)
    {
      std::size_t target = index;
      while(circuits[target] != target)
      {
        target = circuits[target];
      }

      while(circuits[index] != index)
      {
        index = std::exchange(circuits[index], target);
      }

      return target;
    };

    const auto merge_circuits = [&circuits, &find](std::size_t lhs_index, std::size_t rhs_index)
    {
      lhs_index = find(lhs_index);
      rhs_index = find(rhs_index);

      circuits[lhs_index] = rhs_index;
    };

    const auto compare_connections = [&](const circuit_connection& lhs, const circuit_connection& rhs)
    {
      const auto lhs_dist = points[lhs.first_index].distance(points[lhs.second_index]);
      const auto rhs_dist = points[rhs.first_index].distance(points[rhs.second_index]);

      return rhs_dist < lhs_dist;
    };

    std::priority_queue<circuit_connection, std::deque<circuit_connection>, decltype(compare_connections)> connections{compare_connections};

    for(auto i = 0uz; i < points.size(); ++i)
    {
      for(auto j = i + 1uz; j < points.size(); ++j)
      {
        connections.emplace(i, j);
      }
    }

    auto result = 0ll;
    while (not connections.empty())
    {
      const auto [first_index, second_index] = connections.top();
      connections.pop();
      if (find(first_index) != find(second_index))
      {
        merge_circuits(first_index, second_index);
        result = points[first_index].x * points[second_index].x;
      }
    }
    return result;
  }
}

int main(int, char *[])
{
  try
  {
    auto input = aoc::utility::read_file("day08.txt");
    auto points = parse(input);
    aoc::utility::run_part(1, part_one, points);
    aoc::utility::run_part(2, part_two, points);
  }
  catch (const std::exception &e)
  {
    std::print("{}\n", e.what());
    return -1;
  }
  return 0;
}
