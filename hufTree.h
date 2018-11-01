#ifndef hufTree_h
#define hufTree_h

#include <stdio.h>
#include <string>
class hufTree{
    struct node{
        node * left = nullptr;
        node * right = nullptr;
        int byte = -1;
    };
public:
    // default constructor
    hufTree();
    
    /*
     @param:
        proByte: probability of each byte
        num: length of proByte, default to 256
     */
    hufTree(double * proByte, int num = 256);
    /*
     @param:
     proByte: code table
     num: length of code table, default to 256
     */
    hufTree(std::string * codeTable, int num = 256);
    
    // destructor
    ~hufTree();
    
    /*
     write code of each node to codeTable
     @param:
        codeTable: code of each byte
        num: length of codeTable, default to 256
     */
    void traverse(std::string * codeTable, int num = 256);

};
#endif /* hufTree_h */
