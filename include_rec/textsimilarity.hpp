#pragma once

#include <list>
#include <string>
#include <numeric>

#include "utility.hpp"

class TextSimilarity {
   private:
    std::vector<int> users_id;
    std::vector<std::vector<float>> TfIdf;

   public:
    TextSimilarity() = default;
    ~TextSimilarity() = default;

    void fit(std::list<std::string>& corpus, std::vector<int> _users_id = std::vector<int>(0));
    float predict(const int user1_id, const int user2_id);
};
