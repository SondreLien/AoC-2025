// Dec3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/config.hpp>
#include "DATA.h"

namespace
{
  const std::vector<std::string> TEST_DATA =
  {
    "987654321111111",
    "811111111111119",
    "234234234234278",
    "818181911112111"
  };

  void recursiveRemoveNumbers(std::string& battery)
  {
    boost::multiprecision::cpp_int highestVoltage = 0;
    for (size_t i = 0; i < battery.size(); i++)
    {
      std::string newBattery = battery;
      newBattery.erase(i, 1);
      boost::multiprecision::cpp_int joltage = boost::multiprecision::cpp_int(newBattery);
      if (joltage > highestVoltage)
      {
        highestVoltage = joltage;
      }
    }

    battery = highestVoltage.str();
    if (battery.size() <= 12)
    {
      return;
    }

    recursiveRemoveNumbers(battery);
  }

  boost::multiprecision::cpp_int getHighestVoltage12(const std::string& batteries)
  {
    std::string modifiedBatteries = batteries;
    recursiveRemoveNumbers(modifiedBatteries);

    return boost::multiprecision::cpp_int(modifiedBatteries);
  }

}

int main()
{
  const auto& data = DATA;
  unsigned long long totalJoltage = 0;
  boost::multiprecision::cpp_int totalSecondaryJoltage = 0;

  for (const auto& batteries : data)
  {
    boost::multiprecision::cpp_int highestSecondaryJoltage = getHighestVoltage12(batteries);
    unsigned long long highestVoltage = 0;
    for (size_t i = 0; i < batteries.size() - 1; i++)
    {
      for (size_t j = i + 1; j < batteries.size(); j++)
      {
        unsigned long long currentJoltage = std::stoull(batteries.substr(i, 1) + batteries.substr(j, 1));
        if (currentJoltage > highestVoltage)
        {
          highestVoltage = currentJoltage;
        }
      }
    }

    std::cout << "Highest joltage: " << std::to_string(highestVoltage) << std::endl;
    totalSecondaryJoltage += highestSecondaryJoltage;
    totalJoltage += highestVoltage;
  }

  std::cout << "TOTAL JOLTAGE: " << std::to_string(totalJoltage) << std::endl;
  std::cout << "TOTAL SECONDARY JOLTAGE: " << totalSecondaryJoltage.str() << std::endl;

}
