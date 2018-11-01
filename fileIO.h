#ifndef fileIO_h
#define fileIO_h

#include <stdio.h>
#include <iostream>
#include <string>
#include "hufTree.h"
class fileIO{
    // the file name
    std::string file;
    // the number of bytes read and written already
    int byteCount;
    /*
     the cache to read and write bits to file
     read from top left
     write from top right
     can store 8 bits
     @member:
        reg: cache
        occupy: the number of empty bits
     */
    const int cacheSize = 8;
    struct cache{
        uint8_t reg;
        int remain;
    } Cache;
    
    
    /*
     flush the cache
     @return:
        content in the cache
     */
    uint8_t flush();
    /*
     write a bit the cache
     @params:
        bit: the bit to write
     */
    void cacheWrite(const uint8_t bit);
public:
    enum Mode{READ, WRITE};
    
    // default constructor
    fileIO(Mode m = READ);
    
    /*
     @param:
        filename: the file to read and write
     */
    fileIO(const std::string fileName, Mode m = READ);
    
    // destructor
    ~fileIO();
    
    /*
     @return:
        the filename that is being IOed now
     */
    std::string fileName()const;
    
    /*
     @return:
        the number of bytes read and written already
     */
    int byteNum()const;
    
    /*
     read a byte from the file
     @params:
        byte: store the byte read
     @return:
        true: a byte read
        false: no byte available
     */
    bool readByte(uint8_t & byte)const;
    
    /*
     write a byte to the file
     @return:
        the byte to be written
     */
    void writeByte(const uint8_t byte);
    
    /*
     read a bit from the file and expand to a 8-bit integer
     @return:
        the bit read,
        if there is no bit available, return '@';
     */
    uint8_t readBit();
    
    /*
     write the code to the file
     @params:
        the code
     @return:
        false: the code is not correct
        true: default
     */
    bool writeCode(const std::string code);
    
    /*
     get the code table from the compressed file
     @params:
        codeTable: the codeTable to store
        num: the length of codeTable
     @return:
        false: no codeTable provided in the file
        true: default
     */
    bool getCodeTable(std::string * codeTable, int num);
    
private:
    enum Mode mode;
};
#endif /* fileIO_h */
