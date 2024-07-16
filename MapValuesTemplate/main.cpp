#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <typename Container, typename FilterType = void *,
          typename ConvertType = void *>
auto getValues(const Container &container, FilterType filter = nullptr,
               ConvertType converter = nullptr) {
  std::vector<typename Container::mapped_type> result;
  result.reserve(container.size());
  for (const auto &pair : container) {
    if constexpr (!std::is_same_v<FilterType, void *>) {
      if (!filter(pair.first)) {
        continue;
      }
    }
    if constexpr (!std::is_same_v<ConvertType, void *>) {
      result.push_back(converter(pair.second));
    } else {
      result.push_back(pair.second);
    }
  }
  return result;
}

int main() {
  std::map<int, int> myMap{
      {1, 1},
      {2, 2},
  };

  const auto test1 = getValues(
      myMap, [](const auto &key) { return key > 1; },
      [](const auto &value) { return value * 2; });

  const auto test2 = getValues(myMap, [](const auto &key) { return key > 1; });

  const auto test3 = getValues(myMap);

  return 0;
}
