#ifndef _LETTERBOX_HXX
#define _LETTERBOX_HXX

#include <string>
#include <regex>
#include <vector>

class LetterBox
{
    public:
        LetterBox(const std::string &letters, const std::string &filename);
        virtual ~LetterBox();

        void solve();

    private:
        void readFile(const std::string &filename);
        bool isValid(const std::string &word) const;
        std::string matchLetters(const std::string &letters) const;
        std::string dontMatchLetters(const std::string &letters) const;

    private:
        std::string letters_;
        std::string filename_;
        std::regex posExpr_;
        std::regex negExpr_;
        std::vector<std::string> words_;
};

#endif
