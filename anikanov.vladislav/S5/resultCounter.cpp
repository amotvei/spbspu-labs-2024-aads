#include <limits>
#include <stdexcept>
#include <Queue.hpp>
#include "resultCounter.hpp"

anikanov::ResultCounter::ResultCounter()
{
  result = 0;
}

void anikanov::ResultCounter::operator()(const std::pair< int, std::string > &key_value)
{
  bool isOverflow = result > std::numeric_limits< long long >::max() - key_value.first;
  bool isUndeflow = result < std::numeric_limits< long long >::min() - key_value.first;

  if (isOverflow) {
    throw std::overflow_error("Key sum overflow!");
  }
  else if (isUndeflow) {
    throw std::underflow_error("Key sum undeflow!");
  }
  result += key_value.first;
  values.push(key_value.second)
}

int anikanov::ResultCounter::getResult() const
{
  return result;
}

std::string anikanov::ResultCounter::getValues() const
{
  if (!values.empty()) {
    return values.substr(0, values.size() - 1);
  }
  return values;
}
