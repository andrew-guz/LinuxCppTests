#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <typename ContainerType, typename ConverterType>
struct output_type_helper {
  using type =
      typename std::invoke_result_t<ConverterType,
                                    typename ContainerType::mapped_type>;
};

template <typename ContainerType>
struct output_type_helper<ContainerType, void *> {
  using type = typename ContainerType::mapped_type;
};

template <typename ContainerType, typename FilterType = void *,
          typename ConverterType = void *>
auto getValues(const ContainerType &container, FilterType filter = nullptr,
               ConverterType converter = nullptr) {
  std::vector<typename output_type_helper<ContainerType, ConverterType>::type>
      result;
  result.reserve(container.size());
  for (const auto &pair : container) {
    if constexpr (!std::is_same_v<FilterType, void *>) {
      if (!filter(pair.first)) {
        continue;
      }
    }
    if constexpr (!std::is_same_v<ConverterType, void *>) {
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

  const auto test4 = getValues(
      myMap, [](const auto &key) { return key > 1; },
      [](const auto &value) { return std::to_string(value); });

  return 0;
}
