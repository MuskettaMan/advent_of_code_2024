#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <span>
#include <unordered_map>
#include <vector>


int main()
{
    std::string filename = "input.txt"; // Replace with your file name
    std::ifstream file(filename); // Open the file for reading

    if (!file) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));

    file.close(); // Close the file


    std::vector<int32_t> leftList;
    std::vector<int32_t> rightList;

    std::unordered_map<int32_t, int32_t> map;

    auto prev = content.begin();
    for(auto it = content.begin(); it != content.end(); ++it)
    {
        if(*it == '\n')
        {
            std::string_view line{prev, it};
            leftList.emplace_back(std::stoi(std::string{line.substr(0, 5)}));
            rightList.emplace_back(std::stoi(std::string{line.substr(8, 5)}));

            map[rightList.back()] += 1;

            prev = it + 1;
        }
    }

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    int32_t sum{0};
    for(size_t i = 0; i < leftList.size(); ++i)
    {
        sum += leftList[i] * map[leftList[i]];
    }

    std::cout << sum << std::endl;

    return 0;
}
