#include <iostream>
#include <limits>
#include <utility>
#include <string>
#include <cstring>
#include "List.hpp"


int main()
{
  using namespace taskaev;
  List< int > sums;
  List< std::pair< std::string, List < int > > > list;
  std::string name;
  std::cin >> name;
  while(std::cin)
  {
    list.pushFront({name, List<int>()});
    while (std::cin >> name && std::isdigit(name[0]))
    {
      list.front().second.pushBack(std::stoll(name));
    }
  }
  if(list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  list.reverse();
  typename List<std::pair<std::string, List<int>>>::ListIterator< std::pair< std::string, List<int>>> i = list.begin();
  while(i != list.end())
  {
   std::cout << i->first << " ";
    ++i;
  }
  std::cout << "\n";
  int maxNum = 1;
  i = list.begin();
  while (i != list.end())
  {
    int j = 0;
    auto it = i->second.begin();
    while (it != i->second.end())
    {
      j++;
      maxNum = (maxNum > j) ? maxNum : j;
      it++;
    }
    i++;
  }
  bool bools = false;
  int j = 0;
  int sum;
  while (j < maxNum)
  {
    j++;
    sum = 0;
    i = list.begin();
    while (i != list.end())
    {
      if (!i->second.empty())
      {
        if (sum > 0 || bools)
        {
          std::cout << " ";
        }
        std::cout << i->second.front();
        if (sum < (std::numeric_limits< int >::max() - i->second.front()))
        {
          sum += i->second.front();
        }
        else
        {
          bools = true;
        }
        i->second.popFront();
      }
      i++;
    }
    std::cout << "\n";

    if (bools)
    {
      std::cerr << " Stack Overflow error!\n";
      return 1;
    }
    sums.pushFront(sum);
  }
  return 0;
}