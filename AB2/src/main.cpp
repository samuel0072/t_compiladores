#include <iostream>
#include <string>
#include <fstream>
#include "syntaticanalyzer.h"

int main(int argc, char * argv[]) {
    if(argc < 2) {
        std::cout << "O nome do arquivo não foi especificado";
        exit(EXIT_FAILURE);
    }
    std::string file(argv[1]);
    SyntaticAnalyzer sint(file);

    

    sint.Parse();
    
    

    
    return 0;

}