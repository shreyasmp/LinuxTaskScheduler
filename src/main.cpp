/**
 *  Main class for accepting input file in argument/command line
 *
 *  @author Shreyas Muthkur
 */

#include <algorithm>
#include "headers/RBTree.h"

using namespace std;

int main(__attribute__((unused)) int argc, const char *argv[]) {
    ifstream inFile;
    // Open file stream and check if file exists before opening
    inFile.open(argv[1]);
    redBlackTree::parseInput(inFile);
    return 0;
}

