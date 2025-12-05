// Dec2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <array>

namespace
{
  std::string DATA_1 = "3335355312-3335478020,62597156-62638027,94888325-95016472,4653-6357,54-79,1-19,314-423,472-650,217886-298699,58843645-58909745,2799-3721,150748-178674,9084373-9176707,1744-2691,17039821-17193560,2140045-2264792,743-1030,6666577818-6666739950,22946-32222,58933-81008,714665437-714803123,9972438-10023331,120068-142180,101-120,726684-913526,7575737649-7575766026,8200-11903,81-96,540949-687222,35704-54213,991404-1009392,335082-425865,196-268,3278941-3383621,915593-991111,32-47,431725-452205";
  std::string DATA_2 = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

  bool repeatingStringsRecursive(const std::string& id, const size_t pos)
  {
    if (pos > id.size() / 2)
    {
      return false;
    }

    std::string templ = id.substr(0, pos);

    bool valid = false;
    for (size_t checkPos = pos; checkPos < id.size(); checkPos += pos)
    {
      std::string checkStr = id.substr(checkPos, pos);
      if (checkStr != templ)
      {
        valid = true;
        break;
      }
    }

    if (!valid)
    {
      std::cout << "ID TASK 2: " << id << " is INVALID" << std::endl;
      return true;
    }

    return repeatingStringsRecursive(id, pos + 1);
  }

  bool isInvalid(const std::string& id)
  {
    return repeatingStringsRecursive(id, 1);
  }
}

int main()
{
  const auto& data = DATA_1;

  size_t prevcol = 0;
  size_t nextsize = data.find(',');
  bool _break = false;
  unsigned long long idSum = 0;
  unsigned long long idSum2 = 0;

  while (true)
  {
    std::string range = data.substr(prevcol, nextsize);

    size_t bindPos = range.find('-');
    std::array<unsigned long long, 2> IDs;

    auto a = std::stoull(range.substr(0, bindPos));
    auto b = std::stoull(range.substr(bindPos + 1));
    
    IDs[0] = std::stoull(range.substr(0, bindPos));
    IDs[1] = std::stoull(range.substr(bindPos + 1));

    for (size_t i = 0; i < IDs.size(); i++)
    {
      const std::string id = std::to_string(IDs[i]);

      // Ignore if odd number
      if (id.size() % 2 != 0)
      {
        std::cout << "ID : " << id << " is odd. Ignoring..." << std::endl;
        continue;
      }

      // Split IDs in half
      std::string half1 = id.substr(0, id.size() / 2);
      std::string half2 = id.substr(id.size() / 2);

      if (half1 == half2)
      {
        idSum += std::stol(id);
        std::cout << "INVALID ID! Current id sum is: " << std::to_string(idSum) << std::endl;
      }
    }

    for (unsigned long long id = IDs[0]; id <= IDs[1]; id++)
    {
      std::string idStr = std::to_string(id);
      if (isInvalid(idStr))
      {
        idSum2 += id;
      }

      // Ignore if odd size
      if (idStr.size() % 2 != 0)
      {
        continue;
      }

      std::string half1 = idStr.substr(0, idStr.size() / 2);
      std::string half2 = idStr.substr(idStr.size() / 2);

      if (half1 == half2)
      {
        idSum += id;
        std::cout << "ID TASK 1: " << id << " is INVALID" << std::endl;
      }
    }

    // END

    if (_break)
    {
      break;
    }
    
    prevcol += nextsize + 1;
    size_t nextCol = data.find(',', prevcol + 1);

    if (nextCol == std::string::npos)
    {
      _break = true;
    }

    nextsize = nextCol - prevcol;
  }

  std::cout << "ID SUM 1: " << std::to_string(idSum) << std::endl;
  std::cout << "ID SUM 2: " << std::to_string(idSum2) << std::endl;
}
