#include "fileIO.h"
fileIO::fileIO(Mode m){
    file = "";
    byteCount = 0;
    Cache.reg = 0;
    Cache.remain = cacheSize;
    mode = m;
}

fileIO::fileIO(const std::string filename, Mode m){
    file = filename;
    byteCount = 0;
    Cache.reg = 0;
    Cache.remain = cacheSize;
    mode = m;
}

fileIO::~fileIO(){
    writeByte(Cache.reg);
    file = "";
}

uint8_t fileIO::flush(){
    uint8_t content = Cache.reg;
    Cache.reg = 0;
    Cache.remain = cacheSize;
    return content;
}

void fileIO::cacheWrite(const uint8_t bit){
    if (mode == WRITE) {
        if (bit == 1) {
            Cache.reg += (bit << (Cache.remain - 1));
        }
        Cache.remain--;
    }
}

std::string fileIO::fileName()const{
    return file;
}

int fileIO::byteNum()const{
    return byteCount;
}

bool fileIO::readByte(uint8_t & byte) const{
    if (mode == READ)
	{
		fstream a;
	    a.open(file,ios::binary|ios::in);
		if(!a)
			return false;
		a.seekg(byteCount,ios::beg);
		a.read((char*)&byte,1);
		byteCount+=1;
		a.close();
		return true;
	}
	return false;
}

void fileIO::writeByte(const uint8_t byte){
    if (mode == WRITE)
	{
		fstream b;
		b.open(file,ios::out|ios::ate);
		if(!b)
			cout<<"wrong";
		b.write((char*)&byte,1);
		b.close();
	}
	cout<<"wrong";
}

uint8_t fileIO::readBit(){
    if (mode == READ) {
        if ((Cache.remain == cacheSize) && (readByte(Cache.reg) == false)) {
                return '@';
        }
        else{
            uint8_t ret = Cache.reg >> 7;
            Cache.reg = Cache.reg << 1;
            return ret;
        }
    }
    return '@';
}

bool fileIO::writeCode(const std::string code){
    if (mode == WRITE) {
        size_t length = code.length();
        for (size_t i = 0; i < length; i++) {
            if (Cache.remain == 0) {
                writeByte(Cache.reg);
                flush();
            }
            if (code[i] == '0')
                cacheWrite(0);
            else if (code[i] == '1')
                cacheWrite(1);
            else
                return false;
        }
        return true;
    }
    return false;
}

bool fileIO::getCodeTable(std::string * codeTable, int num){
fstream out_file;
	 out_file.open(file,ios::in);
	 if(!out_file)
		 return false;
	 for(int i=0;i<num;i++)
	 {
		 file>>*(codeTable+i);
	 }
	 out_file.close();
	 return true;
}

