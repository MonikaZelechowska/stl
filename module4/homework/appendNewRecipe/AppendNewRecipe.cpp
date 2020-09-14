#include "AppendNewRecipe.hpp"
#include <algorithm>
#include <fstream>
#include <map>

bool AppendNewRecipe(std::vector<std::string> steps,
                     const std::list<std::string>& ingredients,
                     const std::deque<std::pair<size_t, char>>& amount) {
    constexpr auto filename = "recipes.txt";
    std::fstream recipes(filename, recipes.out | recipes.app);

    if (!recipes.is_open()) {
        return false;
    }

    std::stringstream recipiesSs = FormatRecipit(steps, ingredients, amount);
    recipes << recipiesSs.str();
    recipes.close();

    return true;
}

std::vector<std::string> FormatIngredients(const std::list<std::string>& ingredients,
                                           const std::deque<std::pair<size_t, char>>& amount) {
    const std::map<char, std::string> amountString{{'g', "gram"},
                                                   {'s', "szklanka(i)"},
                                                   {'m', "mililitrow"}};

    std::vector<std::string> formatedIngredientsVec;
    formatedIngredientsVec.reserve(ingredients.size());
    auto amountIt = amount.begin();
    auto ingredientsIt = ingredients.begin();

    std::transform(ingredients.begin(),
                   ingredients.end(),
                   amount.begin(),
                   std::back_inserter(formatedIngredientsVec),
                   [&amountString](const auto ingredient, const auto& value) {
                       std::stringstream ss;
                       ss << value.first << ' ' << (amountString.find(value.second))->second << ' ' << ingredient;
                       return ss.str();
                   });

    return formatedIngredientsVec;
}

std::stringstream FormatRecipit(std::vector<std::string> steps,
                                const std::list<std::string>& ingredients,
                                const std::deque<std::pair<size_t, char>>& amount) {
    std::stringstream outputSs;

    constexpr auto ingredientsStr = "Skladniki:\n";
    outputSs << ingredientsStr;
    std::vector<std::string> ingredientsVector = FormatIngredients(ingredients, amount);
    std::for_each(ingredientsVector.begin(),
                  ingredientsVector.end(),
                  [&outputSs](const auto& ingredientData) { outputSs << ingredientData << ",\n"; });

    constexpr auto stepsStr = "\nKroki:\n";
    outputSs << stepsStr;
    for (size_t counter = 0; counter < steps.size(); counter++) {
        outputSs << counter + 1 << ") " << steps[counter] << ".\n";
    }

    constexpr int separatorCount = 35;
    std::string separator(separatorCount, '_');
    outputSs << separator << '\n';

    return outputSs;
}
