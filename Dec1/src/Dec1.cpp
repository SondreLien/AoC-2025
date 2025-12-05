// Dec1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Data.h"
#include <iostream>

namespace
{
  const long MIN_1 = 0;
  const long MAX_1 = 99;

  const std::vector<std::string> Testdata{
    "L68",
    "L30",
    "R48",
    "L5",
    "R60",
    "L55",
    "L1",
    "L99",
    "R14",
    "L82"
  };

  const std::vector<std::string> TestData2{
    "L50",
    "L1",
    "R1",
    "L1",
    "L1",
    "L1",
    "L1",
    "R4",
    "R200",
    "L1000",
    "L1001",
  };

  void turnLeftRecursive(long& position, long& zeroPasses, const long ticks)
  {
    if (ticks <= position)
    {
      position = position - ticks;
      if (position == 0)
      {
        std::cout << "PASSWORD INCREMENTED!" << std::endl;
        zeroPasses++;
      }
      return;
    }

    if (position != 0)
    {
      std::cout << "PASSWORD INCREMENTED!" << std::endl;
      zeroPasses++;
    }

    long newTicks = ticks - position;
    position = 100;
    turnLeftRecursive(position, zeroPasses, newTicks);
  }

  void turnRightRecursive(long& position, long& zeroPasses, const long ticks)
  {
    if (ticks <= 99 - position)
    {
      position = position + ticks;
      return;
    }

    zeroPasses++;
    std::cout << "PASSWORD INCREMENTED!" << std::endl;
    long newTicks = ticks - (99 - position);
    position = -1;
    turnRightRecursive(position, zeroPasses, newTicks);
  }
}

int main()
{

  const long initPoint = 50;
  long currentPoint = initPoint;
  long passwordInc = 0;
  long passwordInc2 = 0;

  for (const auto& data : DATA_1)
  {
    std::string direction = data.substr(0, 1);
    long ticks = std::stoi(data.substr(1));

    std::cout << "Direction: " << direction << ", ticks: " << std::to_string(ticks) << std::endl;

    long _currentPoint = currentPoint;
    if (direction == "L")
    {
      turnLeftRecursive(_currentPoint, passwordInc2, ticks);
    }
    else if (direction == "R")
    {
      turnRightRecursive(_currentPoint, passwordInc2, ticks);
    }

    //while (_currentPoint < MIN_1)
    //{
    //  _currentPoint = MAX_1 + 1 + _currentPoint;
    //  ++passwordInc2;

    //  if (_currentPoint == 0)
    //  {
    //    passwordInc2--;
    //  }
    //}
    //while (_currentPoint > MAX_1)
    //{
    //  _currentPoint = _currentPoint - (MAX_1 + 1);
    //  ++passwordInc2;

    //  if (_currentPoint == 0)
    //  {
    //    passwordInc2--;
    //  }
    //}

    currentPoint = _currentPoint;

    std::cout << "CURRENT: " << std::to_string(currentPoint) << std::endl;

    if (currentPoint == 0)
    {
      ++passwordInc;
      //std::cout << "PASSWORD INCREMENTED!" << std::endl;
    }
  }

  std::cout << "PASSWORD 1: " << std::to_string(passwordInc) << std::endl;
  std::cout << "PASSWORD 2: " << std::to_string(passwordInc2) << std::endl;

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
