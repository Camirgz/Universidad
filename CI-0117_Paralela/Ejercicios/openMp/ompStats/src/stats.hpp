// Copyright 2024 ECCI-UCR CC-BY 4.0
#pragma once

#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>

template <typename Type>
Type minimum(const std::vector<Type>& values) {
  Type result = std::numeric_limits<Type>::max();
  for (size_t index = 0; index < values.size(); ++index) {
    if (values[index] < result) {
      result = values[index];
    }
  }
  return result;
}

template <typename Type>
Type maximum(const std::vector<Type>& values) {
  Type result = std::numeric_limits<Type>::min();
  for (size_t index = 0; index < values.size(); ++index) {
    if (values[index] > result) {
      result = values[index];
    }
  }
  return result;
}

template <typename Type>
Type sum(const std::vector<Type>& values) {
  Type result = Type();
  for (size_t index = 0; index < values.size(); ++index) {
    result += values[index];
  }
  return result;
}

template <typename Type>
double average(const std::vector<Type>& values) {
  return values.size() > 0 ? double(sum(values)) / values.size() : 0.0;
}

template <typename Type>
inline Type square(const Type& value) {
  return value * value;
}

template <typename Type>
double std_dev(const std::vector<Type>& values) {
  if (values.size() >= 2) {
    const double avg = average(values);
    double square_sum = 0.0;
    for (size_t index = 0; index < values.size(); ++index) {
      square_sum += square(values[index] - avg);
    }
    return std::sqrt(square_sum / (values.size() - 1));
  }
  return 0.0;
}

template <typename Type>
double median(std::vector<Type>& values) {
  const size_t count = values.size();
  if (count > 0) {
    std::sort(values.begin(), values.end());
    if (count % 2) {
      return values[count / 2];
    } else {
      return (values[count / 2] + values[count / 2 - 1]) / 2.0;
    }
  }
  return 0.0;
}
