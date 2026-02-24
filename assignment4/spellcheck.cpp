#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  std::vector<std::string::iterator> spaces = find_all(source.begin(), source.end(),
                                                       [](char c) { return std::isspace(c);});
  if (spaces.size() < 1) {
    return Corpus();
  }

  Corpus tokens;

  auto create_token = [&](auto start, auto end) {
    return Token(source, start, end);
  };

  std::transform(spaces.begin(), spaces.end()-1, spaces.begin()+1, 
                 std::inserter(tokens, tokens.end()), create_token);

  auto check_content = [](Token t) {
    return t.content.empty();
  };

  std::erase_if(tokens, check_content);
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;
  auto misspelled_view = rv::filter(source, [&](Token t) { 
    return !dictionary.contains(t.content);
  });

  if (misspelled_view.empty()) {
    return std::set<Misspelling>();
  }

  auto create_misspelling = [&](Token t) {
    auto suggestion_view = rv::filter(dictionary, [&t](std::string word) {
      return levenshtein(t.content, word) == 1;
    });

    std::set<std::string> suggestions(suggestion_view.begin(), suggestion_view.end());
    return Misspelling(t, suggestions);
  };

  auto transform_view = misspelled_view | rv::transform(create_misspelling);
  auto filtered_view = rv::filter(transform_view, [](Misspelling m) {
    return !m.suggestions.empty();
  });

  std::set<Misspelling> misspelled_words(filtered_view.begin(), filtered_view.end());
  return misspelled_words;
};

/* Helper methods */

#include "utils.cpp"