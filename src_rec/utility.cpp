#include "utility.hpp"

#include <iostream>

// Static template methods are defined in utility.hpp

std::set<std::string> Utility::bag;
std::list<std::list<std::string>> Utility::corpus_tokenized;

float Utility::cosine_similarity(const std::vector<float>& x,
                                 const std::vector<float>& y) {
    if (x.size() != y.size()) return 0;

    float xy = 0, norm_x = 0, norm_y = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        xy += x[i] * y[i];
        norm_x += x[i] * x[i];
        norm_y += y[i] * y[i];
    }

    return xy / (sqrt(norm_x) * sqrt(norm_y));
}

void Utility::clear_corpus(std::list<std::string>& corpus) {
    // Regex filter and Lowercase
    const std::regex str_extractor("[а-яa-zё]+");
    for (auto& str : corpus) {
        std::transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        auto str_begin =
            std::sregex_iterator(str.begin(), str.end(), str_extractor);
        std::string new_str = "";
        for (auto i = str_begin; i != std::sregex_iterator(); ++i) {
            new_str += i->str() + ' ';
        }
        str = new_str;
    }
}

void Utility::clear_str(std::string& str) {
    // Regex filter and Lowercase
    const std::regex str_extractor("[а-яa-zё]+");

    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    auto str_begin =
        std::sregex_iterator(str.begin(), str.end(), str_extractor);
    std::string new_str = "";
    for (auto i = str_begin; i != std::sregex_iterator(); ++i) {
        new_str += i->str() + ' ';
    }
    str = new_str;
}

void Utility::word_tokenize_corpus(const std::list<std::string>& corpus) {
    std::stringstream token_stream;

    for (auto str : corpus) {
        std::list<std::string> str_tokenized;

        token_stream.str(str);
        std::string token;
        while (token_stream >> token) {
            str_tokenized.push_back(token);
        }

        corpus_tokenized.push_back(str_tokenized);
        token_stream.clear();
    }
}
std::list<std::string> Utility::word_tokenize_str(const std::string& str) {
    std::stringstream token_stream(str);

    std::list<std::string> str_tokenized;
    std::string token;
    while (token_stream >> token) {
        str_tokenized.push_back(token);
    }

    return str_tokenized;
}

void Utility::create_bag_of_words() {
    // std::set<std::string> bag;
    for (auto l : corpus_tokenized) {
        for (auto word : l) {
            bag.insert(word);
        }
    }
    // return bag;
}

std::vector<std::vector<float>> Utility::TfIdfVectorizer(
    const std::list<std::string>& corpus) {
    word_tokenize_corpus(corpus);
    create_bag_of_words();

    std::vector<std::vector<float>> TfIdf;

    for (auto doc : corpus_tokenized) {
        std::vector<float> tfidf_vector;

        for (auto it = bag.begin(); it != bag.end(); ++it) {
            float tf =
                static_cast<float>(std::count(doc.begin(), doc.end(), *it)) /
                doc.size();
            float idf = std::log(
                static_cast<float>(corpus_tokenized.size()) /
                std::count_if(corpus_tokenized.begin(), corpus_tokenized.end(),
                              [&](std::list<std::string> _doc) {
                                  return std::find(_doc.begin(), _doc.end(),
                                                   *it) != _doc.end();
                              }));
            tfidf_vector.push_back(tf * idf);
        }
        tfidf_vector.shrink_to_fit();
        TfIdf.push_back(tfidf_vector);
    }

    return TfIdf;
}

std::vector<float> Utility::TfIdfVectorizeStr(const std::string& str) {
    std::vector<float> tfidf_vector;

    std::list<std::string> doc = word_tokenize_str(str);

    for (auto it = bag.begin(); it != bag.end(); ++it) {
        float tf = static_cast<float>(std::count(doc.begin(), doc.end(), *it)) /
                   doc.size();
        float idf = std::log(
            static_cast<float>(corpus_tokenized.size()) /
            std::count_if(corpus_tokenized.begin(), corpus_tokenized.end(),
                          [&](std::list<std::string> _doc) {
                              return std::find(_doc.begin(), _doc.end(), *it) !=
                                     _doc.end();
                          }));
        tfidf_vector.push_back(tf * idf);
    }
    tfidf_vector.shrink_to_fit();

    return tfidf_vector;
}
