#pragma once

#include <algorithm>
#include <cmath>
#include <iterator>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

class Utility {
   public:
    static float cosine_similarity(const std::vector<float>& x, const std::vector<float>& y);

    static void clear_corpus(std::list<std::string>& corpus);

    static std::list<std::list<std::string>> word_tokenize_corpus(
        const std::list<std::string>& corpus);

    static std::set<std::string> create_bag_of_words(
        const std::list<std::list<std::string>>& corpus_tokenized);

    template <typename T = int, typename V = std::string>
    static std::vector<T> LabelEncoder(const std::vector<V>& values);

    static std::vector<std::vector<float>> TfIdfVectorizer(
        const std::list<std::string>& corpus);
};

template <typename T, typename V>
std::vector<T> Utility::LabelEncoder(const std::vector<V>& values) {
    std::set<V> set_values(values.begin(), values.end());

    std::vector<T> labels(values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        labels[i] =
            std::distance(set_values.begin(), set_values.find(values[i]));
    }

    return labels;
}
