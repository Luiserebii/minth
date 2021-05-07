#include <iostream>

#include <cxxopts.hpp>
#include <termcolor/termcolor.hpp>

#include "../../include/cli/cli.h"

using std::cout;
using std::endl;

namespace cli {

int run(int argc, char* argv[]) {
    cxxopts::Options mainopts(PROG_NAME, PROG_DESC);
    mainopts.add_options()
        ("h,help", "display this help and exit")
    ;

    auto result = mainopts.parse(argc, argv);

    if(result.count("help")) {
        cout << mainopts.help() << endl;
        return 0;
    } else {
        //Nothing matched, so just display help and exit
        cout << mainopts.help() << endl;
        cout << termcolor::blue;
        return 0;
    }
}

}
