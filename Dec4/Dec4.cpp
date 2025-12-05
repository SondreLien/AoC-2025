// Dec4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

#include "Data.h"

namespace
{
  std::vector<std::string> TEST_DATA =
  {
    "..@@.@@@@.",
    "@@@.@.@.@@",
    "@@@@@.@.@@",
    "@.@@@@..@.",
    "@@.@@@@.@@",
    ".@@@@@@@.@",
    ".@.@.@.@@@",
    "@.@@@.@@@@",
    ".@@@@@@@@.",
    "@.@.@@@.@."
  };

  void recursiveRemovePaper(const std::vector<std::string> storage, unsigned long& removedPaper)
  {
    unsigned long initRemovedPaper = removedPaper;
    std::vector<std::string> modifiedStorage = storage;

    for (size_t i = 0; i < storage.size(); i++)
    {
      for (size_t j = 0; j < storage[i].size(); j++)
      {
        if (storage[i].substr(j, 1) != "@")
        {
          continue;
        }

        if (i == 4 && j == 9)
        {
          bool hest = false;
        }

        unsigned long adjacentTp = 0;

        // Top
        if (i > 0)
        {
          if (storage[i - 1].substr(j, 1) == "@")
          {
            adjacentTp++;
          }
        }

        // Bottom
        if (i < storage.size() - 1)
        {
          if (storage[i + 1].substr(j, 1) == "@")
          {
            adjacentTp++;
          }
        }

        // Left
        if (j > 0)
        {
          // Left
          if (storage[i].substr(j - 1, 1) == "@")
          {
            adjacentTp++;
          }

          // Top
          if (i > 0)
          {
            if (storage[i - 1].substr(j - 1, 1) == "@")
            {
              adjacentTp++;
            }
          }

          // Bottom
          if (i < storage.size() - 1)
          {
            if (storage[i + 1].substr(j - 1, 1) == "@")
            {
              adjacentTp++;
            }
          }
        }

        // Right
        if (j < storage[i].size() - 1)
        {
          // Right
          if (storage[i].substr(j + 1, 1) == "@")
          {
            adjacentTp++;
          }

          // Top
          if (i > 0)
          {
            if (storage[i - 1].substr(j + 1, 1) == "@")
            {
              adjacentTp++;
            }
          }

          // Bottom
          if (i < storage.size() - 1)
          {
            if (storage[i + 1].substr(j + 1, 1) == "@")
            {
              adjacentTp++;
            }
          }
        }

        if (adjacentTp < 4)
        {
          removedPaper++;
          modifiedStorage[i][j] = 'x';
          std::cout << "Removed tp at " << std::to_string(i) << "/" << std::to_string(j) << " with " << std::to_string(adjacentTp) << " adjacent toilet paper" << std::endl;
        }
      }
    }
    
    if (removedPaper == initRemovedPaper)
    {
      return;
    }

    recursiveRemovePaper(modifiedStorage, removedPaper);
  }
}

int main()
{
    const auto& data = DATA_1;

    unsigned long removedTp = 0;
    recursiveRemovePaper(data, removedTp);

    std::cout << "Total removed toilet paper: " << std::to_string(removedTp) << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
