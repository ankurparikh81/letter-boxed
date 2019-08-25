#include "LetterBox.hxx"

#include <algorithm>
#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

LetterBox::LetterBox(const std::string &letters, const std::string &filename) :
    letters_(letters),
    filename_(filename),
    posExpr_(matchLetters(letters_)),
    negExpr_(dontMatchLetters(letters_)),
    words_()
{
    assert(letters.size() == 12);
}

LetterBox::~LetterBox()
{
}

std::string LetterBox::matchLetters(const std::string &letters) const
{
    assert(letters.size() == 12);
    std::string s = (std::string("^[") + letters + std::string("]{3,}$"));
    return s;
}

std::string LetterBox::dontMatchLetters(const std::string &letters) const
{
    assert(letters.size() == 12);
    std::string s;
    for (int i=0; i<12; i+=3) {
        if ( !s.empty() ) {
            s = s + "|";
        }
        s = s + "[";
        for (int j=0; j < 3; ++j) {
            s += letters[i+j];
        }
        s = s + "]{2}";
    }
    return s;
}

void LetterBox::solve()
{
    readFile(filename_);

    std::unordered_map<char, unsigned> charToPos;
    unsigned i = 0;
    for (char c : letters_) {
        charToPos[c] = i++;
    }

    auto hash = [&charToPos](const std::string &word) -> std::bitset<12> {
        std::bitset<12> b;
        for(char c : word) {
            b.set(charToPos[c], true);
        }
        return b;
    };

    auto matchingHash = [&charToPos, &hash](const std::string &word) -> std::bitset<12> {
        std::bitset<12> b = hash(word).flip();
        b.set(charToPos[word.back()], true);
        return b;
    };

    std::unordered_map<std::bitset<12>, std::vector<std::string> > hashToWords;
    for (const std::string &word : words_) {
        hashToWords[hash(word)].push_back(word);
    }

    for (const std::string &word : words_) {
        auto s = matchingHash(word);

        std::vector<std::string> solutions;
        for ( const auto &hashWordsPair : hashToWords ) {
            const std::bitset<12> &h = hashWordsPair.first;
            const std::vector<std::string> &candidates = hashWordsPair.second;

            if ( (s & h) == s ) {
                for(const std::string &candidate : candidates) {
                    if ( candidate.front() == word.back() ) {
                        solutions.push_back(candidate);
                    }
                }
            }
        }
        
        if ( ! solutions.empty() ) {
            std::cout << std::setw(14) << word << " : { ";
            for (const std::string &sol : solutions) {
                std::cout << sol << " ";
            }
            std::cout << "}" << std::endl;
        }
    }

    return;
}

bool LetterBox::isValid(const std::string &word) const
{
    return !word.empty() && regex_match(word, posExpr_) && !regex_search(word, negExpr_);
}

void
LetterBox::readFile(const std::string &filename)
{
    std::ifstream ifs(filename, std::ifstream::in);

    while ( ifs.good() && !ifs.eof() ) {
        std::string word;
        ifs >> word;
        if (isValid(word)) {
            words_.push_back(word);
        }
    }

    ifs.close();

    return;
}

