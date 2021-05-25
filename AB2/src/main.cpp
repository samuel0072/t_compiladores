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

    

    bool acp = sint.Parse();
    /*if(acp) {
        std::cout << "Programa aceito!";
    }
    else {
        std::cout << "Programa recusado!";
    }*/
    
    

    
    return 0;

}