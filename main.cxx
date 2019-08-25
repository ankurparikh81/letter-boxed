#include <iostream>
#include <string>
#include "LetterBox.hxx"

int main ( int argc, char *argv[] )
{
    if ( argc < 3 ) {
        std::cout << "Usage: " << argv[0]
            << " <12-letters-of-square-sides> "
            << " <dictionary-file>"
            << std::endl;
        return 1;
    }

    std::string letters(argv[1]);
    std::string filename(argv[2]);

    if ( letters.size() != 12 ) {
        return 1;
    }

    LetterBox letterbox(letters, filename);
    letterbox.solve();

    return 0;
}
