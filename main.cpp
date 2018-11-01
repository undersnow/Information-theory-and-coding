#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>
#include "hufTree.h"
#include "fileIO.h"
#define N 256 // the number of source symbol
void compress(std::string file, std::string outDir = "output");
void extract(std::string file, std::string outDir = "output");

int main(int argc, const char * argv[]) {
    std::string inFile("test/news.txt");
    std::string outDir("output");
    clock_t start ,end;
    double costSec = 0;


    start = clock();
    compress(inFile, outDir);
    end = clock();
    costSec = (end - start) / CLOCKS_PER_SEC;
    std::cout << "Compressing " << inFile << " costs " << costSec << " seconds."<<std::endl;

    start = clock();
    extract(inFile, outDir);
    end = clock();
    costSec = (end - start) / CLOCKS_PER_SEC;
    std::cout << "Extracting " << inFile << " costs " << costSec << " seconds."<<std::endl;
    return 0;
}

void compress(std::string file, std::string outDir){
    std::string inFile = file;
    std::string outFile = outDir + "/" + inFile;
    
    std::string *codeTable = new std::string[N];
    memset(codeTable, 0, sizeof(codeTable) * N);
    
    double proByte[N] = {0};
    uint8_t byte = 0;
    
    fileIO fin(inFile, fileIO::READ);
    fileIO fout(outFile, fileIO::WRITE);
    while (fin.readByte(byte)) {
        proByte[int(byte)]++;
    }
    for (int i = 0; i < N; i++) {
        proByte[i] /= double (fin.byteNum());
    }
    
    hufTree t(proByte, N);
    t.traverse(codeTable, N);
    
    while (fin.readByte(byte)) {
        fout.writeCode(codeTable[byte]);
    }
    delete [] codeTable;
}
void extract(std::string file, std::string outDir){
    std::string inFile = file;
    std::string outFile = outDir + "/" + inFile;
    
    std::string *codeTable = new std::string[N];
    memset(codeTable, 0, sizeof(codeTable) * N);
    
    fileIO fin(inFile, fileIO::READ);
    fileIO fout(outFile, fileIO::WRITE);
    
    if(fin.getCodeTable(codeTable, N)){
        std::string code("");
        std::string * codePos = nullptr;
        uint8_t byte = 0;
        uint8_t tmp = 0;
        int count = 0;
        bool errCode = false;
        bool finish = false;
        while (!errCode && !finish) {
            
            // get code
            codePos = std::find(codeTable, codeTable + N, code);
            while (codePos == codeTable + N) {
                tmp = fin.readBit();
                if (tmp == '@') {
                    std::cout << "Finish reading the file." <<std::endl;
                    finish = true;
                    break;
                }
                count ++;
                if (count == N) {
                    std::cout << "Broken file." << std::endl;
                    errCode = true;
                    break;
                }
                code += tmp;
                codePos = std::find(codeTable, codeTable + N, code);
            }
        
            // write original byte to the file
            if (!errCode && !finish) {
                byte = uint8_t (codePos - codeTable);
                fout.writeByte(byte);
                code.clear();
            }
        }
    }
    else
        std::cout << "Broken file."<< std::endl;

    delete [] codeTable;
}
