#include "commands.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <functional>
#include <utility>

std::string mihalchenko::resiveString(std::string &inputStr, size_t &pos, bool flag)
{
  std::string result = "";
  while (pos < inputStr.length() && inputStr[pos] != ' ')
  {
    if ((flag) || ((!flag) && std::isdigit(inputStr[pos])))
    {
      result += inputStr[pos++];
    }
    else if (!flag)
    {
      break;
    }
  }
  pos++;
  return result;
}

/*void mihalchenko::printErrorMessage(std::ostream & out) {
    out << "ERROR\n";
}*/

void mihalchenko::printInvalidCommand(std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}

void mihalchenko::printEmptyMessage(std::ostream &out)
{
  out << "<EMPTY>\n";
}

void mihalchenko::print(typeParam &AVLTree)
{
  std::string name;
  std::cin >> name;
  auto iterList = AVLTree.find(name);
  if (iterList == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  else if ((*iterList).second.empty())
  {
    printEmptyMessage(std::cout);
    return;
  }

  std::cout << (*iterList).first << " ";
  for (auto it = (*iterList).second.begin(); it != (*iterList).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    if ((++it) == (*iterList).second.end())
    {
      std::cout << "\n";
    }
    else
    {
      std::cout << ' ';
    }
    it--;
  }
}

void mihalchenko::complement(typeParam &AVLTree)
{
  std::string nameNewGlossary, nameOneGlossary, nameTwoGlossary;
  std::cin >> nameNewGlossary >> nameOneGlossary >> nameTwoGlossary;

  if (AVLTree.find(nameOneGlossary) == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree<long long, std::string> compTree{};
  for (auto it = (*AVLTree.find(nameOneGlossary)).second.begin(); it != (*AVLTree.find(nameOneGlossary)).second.end(); it++)
  {
    auto inSecondData = (*AVLTree.find(nameTwoGlossary)).second.find((*it).first);
    if (inSecondData == (*AVLTree.find(nameTwoGlossary)).second.end())
    {
      compTree.insert(*it);
    }
  }
  if (nameOneGlossary == nameNewGlossary)
  {
    AVLTree.erase(nameOneGlossary);
    AVLTree.insert(nameNewGlossary, compTree);
  }
  else
  {
    AVLTree.insert(nameNewGlossary, compTree);
  }
  if (AVLTree.find(nameNewGlossary) != AVLTree.end())
  {
    AVLTree.erase(nameNewGlossary);
  }
  AVLTree.insert(nameNewGlossary, compTree);
}

void mihalchenko::intersect(typeParam &AVLTree)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto firstData = AVLTree.find(nameFirst);
  auto Glossary = AVLTree.find(nameSecond);
  if (firstData == AVLTree.end() || Glossary == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree<long long, std::string> datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    auto inSecondData = (*AVLTree.find(nameSecond)).second.find((*it).first);
    if (inSecondData != (*AVLTree.find(nameSecond)).second.end())
    {
      datasets.insert(*it);
    }
  }
  if (AVLTree.find(name) != AVLTree.end())
  {
    AVLTree.erase(name);
  }
  AVLTree.insert(name, datasets);
}

void mihalchenko::unionAVL(typeParam &AVLTree)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto firstData = AVLTree.find(nameFirst);
  auto secondData = AVLTree.find(nameSecond);
  std::string nameTest = "test";
  if (firstData == AVLTree.end() || secondData == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree<long long, std::string> datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    datasets.insert(*it);
  }
  for (auto it = (*secondData).second.begin(); it != (*secondData).second.end(); it++)
  {
    auto inSet = datasets.find((*it).first);
    if (inSet == datasets.end())
    {
      datasets.insert(*it);
    }
  }
  // std::cout << "123" << std::endl;

  if (AVLTree.find(name) != AVLTree.end())
  {
    AVLTree.erase(name);
  }
  // std::cout << "456" << std::endl;
  AVLTree.insert(name, datasets);
  // std::cout << "789" << std::endl;
}

void mihalchenko::insertDataToTree(typeParam &TreeAndLeaves, std::string &inputStr)
{
  AVLTree<long long, std::string> branchAndLeaves{};
  size_t pos = 0;
  std::string nameGlossary = resiveString(inputStr, pos, true);
  while (pos < inputStr.length())
  {
    long long key = std::stoll(resiveString(inputStr, pos, false));
    std::string value = resiveString(inputStr, pos, true);
    branchAndLeaves.insert(key, value);
  }
  TreeAndLeaves.insert(nameGlossary, branchAndLeaves);
}
