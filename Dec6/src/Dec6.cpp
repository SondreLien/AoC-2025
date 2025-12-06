#include <iostream>
#include <optional>
#include <algorithm>
#include "Data.h"

namespace
{
    void recursiveGetResult(const std::vector<std::string>& input, unsigned long long& sum)
    {
        // Get next value
        std::vector<std::string> currentStrings;
        std::vector<std::string> input_modified = input;

        for (size_t i = 0; i < input.size(); i++)
        {
            const auto& entry = input[i];

            std::optional<size_t> startPos;
            std::optional<size_t> strSize;
            
            for (size_t pos = 0; pos < entry.size(); pos++)
            {
                const char& character = entry[pos];

                if (character == ' ')
                {
                    if (startPos.has_value())
                    {
                        strSize = pos - startPos.value();
                        break;
                    }

                    continue;
                }
                
                if (!startPos.has_value())
                {
                    startPos = pos;
                }
            }

            if (!startPos.has_value())
            {
                return;
            }

            if (!strSize.has_value())
            {
                strSize = entry.size() - startPos.value();
            }
            
            currentStrings.push_back(entry.substr(startPos.value(), strSize.value()));
            input_modified[i].erase(0, startPos.value() + strSize.value()); 
        }

        if (input_modified == input)
        {
            return;
        }

        const std::string _operator = currentStrings[currentStrings.size() - 1];
        unsigned long long localRes = 0;

        if (_operator == "*")
        {
            localRes = 1;
        }

        for (size_t i = 0; i < currentStrings.size() - 1; i++)
        {
            if (_operator == "*")
            {
                localRes *= std::stoull(currentStrings[i]);
            }
            else // (_operator == "+")
            {
                localRes += std::stoull(currentStrings[i]);
            }
        }

        sum += localRes;
        recursiveGetResult(input_modified, sum);
    }

    void recursiveGetResult2(const std::vector<std::string>& input, unsigned long long& sum)
    {
        // Get next value
        std::vector<std::string> currentStrings;
        std::vector<std::string> input_modified = input;

        std::string operatorDef = input[input.size() - 1];
        auto nextOperatorPos = operatorDef.find_last_not_of(' '); 
        
        if (nextOperatorPos == std::string::npos)
        {
            return;
        }

        const char nextOperator = operatorDef[nextOperatorPos];
        std::vector<std::string> numberSet;
        size_t breakPos = 0;

        for (size_t pos = input[0].size() - 1; pos >= 0 && pos < input[0].size(); pos--)
        {
            std::string currentNumber = "";

            for (size_t i = 0; i < input.size() - 1; i++)
            {   
                const char& currentChar = input[i][pos];
                if (currentChar == ' ')
                {
                    continue;
                }

                currentNumber.push_back(currentChar);
            }

            if (currentNumber.empty())
            {
                breakPos = pos;
                break;
            }
            
            numberSet.push_back(currentNumber);
        }

        unsigned long long localRes = 0;
        
        if (nextOperator == '*')
        {
            localRes = 1;
        }

        for (const auto number : numberSet)
        {
            if (nextOperator == '*')
            {
                localRes *= std::stoull(number);
            }
            else
            {
                localRes += std::stoull(number);
            }
        }

        sum += localRes;

        for (size_t i = 0; i < input.size(); i++)
        {
            input_modified[i].erase(breakPos); 
        }

        if (input_modified == input)
        {
            return;
        }

        recursiveGetResult2(input_modified, sum);
    }
}

int main()
{
    const auto& data = DATA_1;

    unsigned long long result = 0;
    unsigned long long result2 = 0;
    recursiveGetResult(data, result);
    recursiveGetResult2(data, result2);

    std::cout << "Result (Part 1): " << std::to_string(result) << std::endl;
    std::cout << "Result (Part 2): " << std::to_string(result2) << std::endl;
}