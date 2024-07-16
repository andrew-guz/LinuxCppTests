#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <typename ContainerType>
concept is_dictionary = requires(ContainerType) {
  std::is_same_v<ContainerType,
                 std::map<typename ContainerType::key_type,
                          typename ContainerType::mapped_type>> ||
      std::is_same_v<ContainerType,
                     std::unordered_map<typename ContainerType::key_type,
                                        typename ContainerType::mapped_type>>;
};

template <typename ContainerType, typename ConverterType>
  requires is_dictionary<ContainerType>
struct output_type_helper {
  using type =
      typename std::invoke_result_t<ConverterType,
                                    typename ContainerType::mapped_type>;
};

template <typename ContainerType>
  requires is_dictionary<ContainerType>
struct output_type_helper<ContainerType, void *> {
  using type = typename ContainerType::mapped_type;
};

template <typename ContainerType>
  requires is_dictionary<ContainerType>
const auto DefaultFilter =
    [](const typename ContainerType::key_type &) { return true; };

template <typename ContainerType>
  requires is_dictionary<ContainerType>
const auto DefaultConverter =
    [](const typename ContainerType::mapped_type &value) { return value; };

template <typename ContainerType,
          typename FilterType = decltype(DefaultFilter<ContainerType>),
          typename ConverterType = decltype(DefaultConverter<ContainerType>)>
  requires is_dictionary<ContainerType>
auto getValues(const ContainerType &container, FilterType filter,
               ConverterType converter) {
  std::vector<typename output_type_helper<ContainerType, ConverterType>::type>
      result;
  result.reserve(container.size());
  for (const auto &pair : container) {
    if (filter(pair.first)) {
      result.push_back(converter(pair.second));
    }
  }
  return result;
}

template <typename ContainerType>
  requires is_dictionary<ContainerType>
auto getValues(const ContainerType &container) {
  return getValues(container, DefaultFilter<ContainerType>,
                   DefaultConverter<ContainerType>);
}

template <typename ContainerType, typename FilterType>
  requires is_dictionary<ContainerType> &&
           std::is_same_v<std::invoke_result_t<
                              FilterType, typename ContainerType::key_type>,
                          bool>
auto getValues(const ContainerType &container, FilterType filter) {
  return getValues(container, filter, DefaultConverter<ContainerType>);
}

template <typename ContainerType, typename ConverterType>
  requires is_dictionary<ContainerType>
auto getValues(const ContainerType &container, ConverterType converter) {
  return getValues(container, DefaultFilter<ContainerType>, converter);
}

int main() {
  {
    std::map<int, int> myMap{
        {1, 1},
        {2, 2},
    };

    const std::vector<int> test1 = getValues(
        myMap, [](const auto &key) { return key > 1; },
        [](const auto &value) { return value * 2; });

    const std::vector<int> test2 = getValues(myMap);

    const std::vector<int> test3 =
        getValues(myMap, [](const auto &key) { return key > 1; });

    const std::vector<std::string> test4 = getValues(
        myMap, [](const auto &value) { return std::to_string(value); });

    const std::vector<std::string> test5 = getValues(
        myMap, [](const auto &key) { return key > 1; },
        [](const auto &value) { return std::to_string(value); });
  }

  {
    std::unordered_map<int, int> myMap{
        {1, 1},
        {2, 2},
    };

    const std::vector<int> test1 = getValues(
        myMap, [](const auto &key) { return key > 1; },
        [](const auto &value) { return value * 2; });

    const std::vector<int> test2 = getValues(myMap);

    const std::vector<int> test3 =
        getValues(myMap, [](const auto &key) { return key > 1; });

    const std::vector<std::string> test4 = getValues(
        myMap, [](const auto &value) { return std::to_string(value); });

    const std::vector<std::string> test5 = getValues(
        myMap, [](const auto &key) { return key > 1; },
        [](const auto &value) { return std::to_string(value); });
  }

  return 0;
}
