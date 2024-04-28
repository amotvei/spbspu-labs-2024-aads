#include <iostream>
#include <fstream>
#include "inputFunctions.hpp"
#include "dataFunctions.hpp"

int main(int argc, char ** argv)
{
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    if (!input)
    {
      std::cerr << "Error: unable to open the file\n";
      return 2;
    }

    std::string description = "";
    redko::BSTree< std::string, redko::BSTree< int, std::string > > dataSets{};

    redko::BSTree<std::string, void (*)(redko::BSTree< std::string, redko::BSTree< int, std::string > > &, std::string &) > functions{};
    functions.insert({ "print", redko::print });
    functions.insert({ "complement", redko::complement });
    functions.insert({ "intersect", redko::intersect });
    functions.insert({ "union", redko::unite });

    std::string name = "";
    std::string elem = "";
    int key = 0;
    while (std::getline(input, description))
    {
      redko::BSTree< int, std::string > dataSet{};
      name = redko::cutName(description);
      while (!description.empty())
      {
        key = redko::cutKey(description);
        elem = redko::cutName(description);
        dataSet.insert({ key, elem });
      }
      dataSets.insert({ name, dataSet });
    }

    std::string command = "";
    while (std::getline(std::cin, description))
    {
      command = redko::cutName(description);
      if (functions.find(command) != functions.end())
      {
        try
        {
          functions[command](dataSets, description);
        }
        catch (const std::out_of_range & e)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
      else if (!std::cin.eof())
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    return 0;
  }
  else
  {
    std::cerr << "Error: wrong parameters\n";
    return 2;
  }
}
