#include "compression.hpp"

#include <algorithm>
#include <iostream>

pairVector compressGrayscale(const std::array<std::array<uint8_t, width>, height>& inputMap) {
    pairVector outputVec;
    outputVec.reserve(width * height);

    // uint8_t color = 0;
    // int value = 0;
    // int column = 0;

    for (auto mapRow : inputMap) {
        uint8_t color = mapRow.front();
        int value = 0;
        int column = 0;

        std::transform(mapRow.begin(), mapRow.end(), mapRow.begin(),
                       [&color, &value, &column, &outputVec](auto rowElement) {
                           if (rowElement != color || column == width - 1) {
                               if (column == width - 1)
                                   value++;
                               outputVec.emplace_back(std::make_pair(color, (value)));
                               value = 1;
                               color = rowElement;
                           } else {
                               value++;
                           }
                           column++;
                           return rowElement;
                       });
    }
    /*
            for (const auto& rowElement : mapRow) {
            if (rowElement != color || column == width - 1) {
                if (column == width - 1)
                    value++;
                outputVec.emplace_back(std::make_pair(color, (value)));
                value = 1;
                color = rowElement;
            } else {
                value++;
            }
            column++;
        }
    }*/

    /*for (const auto& mapRow : inputMap) {
        color = mapRow.front();
        value = 0;
        column = 0;

        for (const auto& rowElement : mapRow) {
            if (rowElement != color || column == width - 1) {
                if (column == width - 1)
                    value++;
                outputVec.emplace_back(std::make_pair(color, (value)));
                value = 1;
                color = rowElement;
            } else {
                value++;
            }
            column++;
        }
    }*/

    outputVec.shrink_to_fit();
    return outputVec;
}

std::array<std::array<uint8_t, width>, height> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& inputVec) {
    std::array<std::array<uint8_t, width>, height> outputArr;
    size_t rowCounter = 0;
    size_t columnCounter = 0;

    for (const auto& pair : inputVec) {
        if (rowCounter < height) {
            for (size_t pairValue = 0; pairValue < pair.second; ++pairValue) {
                outputArr[rowCounter][columnCounter] = pair.first;
                if (columnCounter < width - 1)
                    columnCounter++;
                else {
                    columnCounter = 0;
                    rowCounter++;
                }
            }
        }
    }
    return outputArr;
}

void printMap(const std::array<std::array<uint8_t, width>, height>& inputMap) {
    for (const auto& mapRow : inputMap) {
        for (const auto& rowElement : mapRow) {
            std::cout << rowElement;
        }
        std::cout << '\n';
    }
}
