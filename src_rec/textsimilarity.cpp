#include "textsimilarity.hpp"

void TextSimilarity::fit(std::list<std::string>& corpus,
                         std::vector<int> _users_id) {
    if (_users_id.size() > 0) {
        assert(corpus.size() == _users_id.size());
        users_id = _users_id;
    } else {
        users_id = std::vector<int>(corpus.size());
        std::iota(users_id.begin(), users_id.end(), 0);
    }

    // Clear corpus
    Utility::clear_corpus(corpus);

    TfIdf = Utility::TfIdfVectorizer(corpus);
}

float TextSimilarity::predict(const int user1_id, const int user2_id) {
    int u1 =
        std::distance(users_id.begin(),
                      std::find(users_id.begin(), users_id.end(), user1_id));
    int u2 =
        std::distance(users_id.begin(),
                      std::find(users_id.begin(), users_id.end(), user2_id));

    return Utility::cosine_similarity(TfIdf[u1], TfIdf[u2]);
}
