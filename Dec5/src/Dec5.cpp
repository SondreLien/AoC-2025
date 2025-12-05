// Dec5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <unordered_set>

#include "Data.h"

namespace
{
  std::vector<std::string> testRanges =
  {
    "3-5",
    "10-14",
    "16-20",
    "12-18"
  };

  std::vector<std::string> testIngredients =
  {
    "1",
    "5",
    "8",
    "11",
    "17",
    "32"
  };
}

std::vector<std::pair<unsigned long long, unsigned long long>> recursiveMergeRanges(const std::vector<std::pair<unsigned long long, unsigned long long>>& validIdRanges)
{
  std::vector<std::pair<unsigned long long, unsigned long long>> updatedValidIdRanges;
  std::vector<std::pair<unsigned long long, unsigned long long>> validIdRanges_cpy = validIdRanges;


  for (size_t i = 0; i < validIdRanges_cpy.size(); i++)
  { 
    auto& validIdRange_a = validIdRanges_cpy[i];

    if (validIdRange_a == std::make_pair(0, 0))
    {
      continue;
    }

    updatedValidIdRanges.push_back(validIdRange_a);
    auto& currentRange = updatedValidIdRanges[updatedValidIdRanges.size() - 1];

    for (size_t j = i; j < validIdRanges_cpy.size(); j++)
    {
      auto& validIdRange_b = validIdRanges_cpy[j];

      if (i == j || validIdRange_b == std::make_pair(0, 0))
      {
        continue;
      }

      if (currentRange.first == 7 && currentRange.second == 20)
      {
        bool _breake = false;
      }

      if ((currentRange.first <= validIdRange_b.second && currentRange.first >= validIdRange_b.first) || (currentRange.second >= validIdRange_b.first && currentRange.second <= validIdRange_b.second))
      {
        unsigned long long first = validIdRange_b.first;
        unsigned long long second = validIdRange_b.second;

        if (currentRange.first < validIdRange_b.first)
        {
          first = currentRange.first;
        }
        if (currentRange.second > validIdRange_b.second)
        {
          second = currentRange.second;
        }

        currentRange = (std::make_pair(first, second));
        
        std::cout << "\tMerged range " << currentRange.first << " to " << currentRange.second << " with " << validIdRange_b.first << " to " << validIdRange_b.second << ". Result: " << first << " to " << second << std::endl;
        
        validIdRange_b = std::make_pair(0, 0);
      }
      else if (validIdRange_b.first > currentRange.first && validIdRange_b.second < currentRange.second)
      {
        std::cout << "\tDISCARDED range " << currentRange.first << " to " << currentRange.second << " with " << validIdRange_b.first << " to " << validIdRange_b.second << std::endl;
        validIdRange_b = std::make_pair(0, 0);
      }
    }

  }

  if (validIdRanges == updatedValidIdRanges)
  {
    return updatedValidIdRanges;
  }

  std::cout << "\n";

  return recursiveMergeRanges(updatedValidIdRanges);
}


int main()
{
    const auto& ranges = RANGE_1;
    const auto& ingredients = INGREDIENTS_1;

    std::vector<std::pair<unsigned long long, unsigned long long>> validIdRanges;

    for (const auto& range : ranges)
    {
      size_t bindPos = range.find('-');
      unsigned long long first = std::stoull(range.substr(0, bindPos));
      unsigned long long second = std::stoull(range.substr(bindPos + 1));

      validIdRanges.push_back(std::make_pair(first, second));
    }

    // Find overlapping ranges
    std::vector<std::pair<unsigned long long, unsigned long long>> updatedValidIdRanges = recursiveMergeRanges(validIdRanges);

    std::unordered_set<unsigned long long> validIngredients;

    for (const auto& ingredient : ingredients)
    {
      unsigned long long ingredientVal = std::stoull(ingredient);

      for (const auto& range : validIdRanges)
      {
        if (ingredientVal >= range.first && ingredientVal <= range.second)
        {
          validIngredients.insert(ingredientVal);
        }
      }
    }

    unsigned long long totalValidIngredients = 0;
    for (const auto& range : updatedValidIdRanges)
    {
      totalValidIngredients += (range.second - range.first + 1);
    }

    std::cout << "Total valid ingredients (PART1) : " << std::to_string(validIngredients.size()) << std::endl;
    std::cout << "Total valid ingredients (PART2) : " << std::to_string(totalValidIngredients) << std::endl;
}
