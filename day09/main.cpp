//
// Created by mhk on 01.12.2025.
//

import std;
import utility;

namespace
{
  using points_t = std::vector<aoc::utility::point2d>;

  bool intersects(const aoc::utility::point2d& upper_left,
                  const aoc::utility::point2d& lower_right,
                  const aoc::utility::point2d& point_one,
                  const aoc::utility::point2d& point_two)
  {
    return point_one.x < lower_right.x and
           point_two.x > upper_left.x and
           point_one.y < lower_right.y and
           point_two.y > upper_left.y;
  }

  points_t parse(const aoc::utility::input_t& input)
  {
    points_t points;

    std::vector<std::size_t> numbers;
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

      if (numbers.size() == 2)
      {
        points.emplace_back(numbers[0], numbers[1]);
      }
    }

    return points;;
  }

  std::size_t part_one(const points_t& points)
  {
    std::vector<std::size_t> areas;
    areas.reserve(points.size() * points.size());

    for (auto i = 0uz; i < points.size(); ++i)
    {
      for (auto j = i + 1uz; j < points.size(); ++j)
      {
        auto upper_left = aoc::utility::minimum(points[i], points[j]);
        auto lower_right = aoc::utility::maximum(points[i], points[j]);

        auto area = std::abs(((lower_right.x - upper_left.x + 1z)) * (lower_right.y - upper_left.y + 1z));
        areas.emplace_back(area);
        std::ranges::push_heap(areas);
      }
    }

    return areas[0];
  }

  std::size_t part_two(const points_t& points)
  {
    struct data
    {
      std::size_t area = 0;
      aoc::utility::point2d upper_left = {};
      aoc::utility::point2d lower_right = {};
    };

    std::vector<data> areas;
    areas.reserve(points.size() * points.size());

    for (auto i = 0uz; i < points.size(); ++i)
    {
      for (auto j = i + 1uz; j < points.size(); ++j)
      {
        auto upper_left = aoc::utility::minimum(points[i], points[j]);
        auto lower_right = aoc::utility::maximum(points[i], points[j]);

        auto area = std::abs(((lower_right.x - upper_left.x + 1z)) * (lower_right.y - upper_left.y + 1z));
        areas.emplace_back(area, upper_left, lower_right);
        std::ranges::push_heap(areas, {}, [](auto&&obj) { return obj.area; });
      }
    }

    auto result = 0uz;
    while (not areas.empty())
    {
      auto [area, upper_left, lower_right] = areas[0];

      bool intersected = false;
      for (std::size_t i = 0; i < points.size(); i++)
      {
        auto point_one = points[i];
        auto point_two = points[(i + 1uz) % points.size()];

        std::tie(point_one, point_two) = std::tuple{ aoc::utility::minimum(point_one, point_two), aoc::utility::maximum(point_one, point_two)};
        if (intersects(upper_left, lower_right, point_one, point_two))
        {
          intersected = true;
          break;
        }
      }

      if (intersected)
      {
        std::ranges::pop_heap(areas, {}, [](auto &&obj) { return obj.area;  });
        areas.pop_back();
      }
      else
      {
        // Done
        result = area;
        break;
      }
    }

    return result;
  }
}

int main(int, char *[])
{
  try
  {
    const auto input = aoc::utility::read_file("day09.txt");
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
