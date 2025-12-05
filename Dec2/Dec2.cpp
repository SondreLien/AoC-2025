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

    if (id == "111")
      bool a = false;

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
      std::cout << "ID: " << id << " is INVALID" << std::endl;
      return true;
    }

    return repeatingStringsRecursive(id, pos + 1);
    /*if (id == "824824824")
    {
      bool hello = false;
    }

    if (id_check.size() == 0)
    {
      return false;
    }
    
    std::string half1 = "";
    if (id_check.size() % 2 == 0)
    {
      half1 = id_check.substr(0, id_check.size() / 2);
    }
    else if (id_check.size() % 3 == 0)
    {
      half1 = id_check.substr(0, id_check.size() / 3);
    }
    else
    {
      return false;
    }

    size_t elementSize = half1.size();
    size_t prevIdx = elementSize;
    std::vector<std::string> elements;

    while (true)
    {
      elements.push_back(id.substr(prevIdx, elementSize));
      if (prevIdx + elementSize >= id.size())
      {
        break;
      }
      prevIdx += elementSize;
    }

    bool isInvalid = true;
    for (const auto& element : elements)
    {
      if (element != half1)
      {
        isInvalid = false;
        break;
      }
    }

    if (isInvalid)
    {
      std::cout << "ID: " << id << " is invalid" << std::endl;
      return true;
    }

    if (half1.size() <= 1)
    {
      return false;
    }*/
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
    // START

    std::string range = data.substr(prevcol, nextsize);
    //std::cout << range << std::endl;
    
    // FUNC

    size_t bindPos = range.find('-');
    std::array<unsigned long long, 2> IDs;


    auto a = std::stoull(range.substr(0, bindPos));
    auto b = std::stoull(range.substr(bindPos + 1));
    
    IDs[0] = std::stoull(range.substr(0, bindPos));
    IDs[1] = std::stoull(range.substr(bindPos + 1));

    //for (const std::string& id : IDs)
    //{
    //  //std::cout << "ID : " << id << std::endl;

    //  // Ignore if odd number
    //  if (id.size() % 2 != 0)
    //  {
    //    std::cout << "ID : " << id << " is odd. Ignoring..." << std::endl;
    //    continue;
    //  }

    //  // Split IDs in half
    //  //std::string half1 = id.substr(0, id.size() / 2);
    //  //std::string half2 = id.substr(id.size() / 2);

    //  //std::cout << "ID : " << id << ", first half: " << half1 << ", second half: " << half2 << std::endl;

    //  if (half1 == half2)
    //  {
    //    idSum += std::stol(id);
    //    std::cout << "INVALID ID! Current id sum is: " << std::to_string(idSum) << std::endl;
    //  }
    //}

    if (IDs[0] > IDs[1])
    {
      std::cout << "Range : " << range << " has lower start value than end value..." << std::endl;
    }

    for (unsigned long long id = IDs[0]; id <= IDs[1]; id++)
    {
      // Split IDs in half
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
        //std::cout << "INVALID ID! (" << idStr << ") Current id sum is : " << std::to_string(idSum) << std::endl;
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

  std::cout << "ID SUM : " << std::to_string(idSum2) << std::endl;
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
