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

  auto createToken = [&](auto start, auto end) {
    return Token(source, start, end);
  };

  std::transform(spaces.begin(), spaces.end()-1, spaces.begin()+1, 
                 std::inserter(tokens, tokens.end()), createToken);

  auto checkContent = [](Token t) {
    return t.content.size() < 1;
  };

  std::erase_if(tokens, checkContent);
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  return std::set<Misspelling>();
};

/* Helper methods */

#include "utils.cpp"