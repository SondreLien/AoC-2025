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

  void recursiveRemovePaper(const std::vector<std::string> storage, unsigned long& removedPaper, const bool runOnce)
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
    
    if (removedPaper == initRemovedPaper || runOnce)
    {
      return;
    }

    recursiveRemovePaper(modifiedStorage, removedPaper, runOnce);
  }
}

int main()
{
    const auto& data = DATA_1;

    unsigned long removedTp1 = 0;
    unsigned long removedTp2 = 0;
    recursiveRemovePaper(data, removedTp1, true);
    recursiveRemovePaper(data, removedTp2, false);

    std::cout << "Task 1: Total removed toilet paper: " << std::to_string(removedTp1) << std::endl;
    std::cout << "Task 2: Total removed toilet paper: " << std::to_string(removedTp2) << std::endl;
}
