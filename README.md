# Information-theory-and-coding

This is a term project for course IS205 Information theory and coding in SJTU.

---------------

##  Huffman

### 压缩

1. 每byte读文件，统计byte（256种）中出现的次数，计算出概率
2. 构造哈夫曼树，共256个叶节点
3. 遍历哈夫曼树，得到信源符号和对应的编码符号，用一张表储存
4. 再次每byte读取文件，在表里面查询对应的编码符号，写入压缩文件

### 解压

1. 读取文件，获得原文件的文件名和扩展名，以及编码的表
2. 根据编码的表重构哈夫曼树
3. 逐bit读取，按照读取的bit深入哈夫曼树，如果到达叶节点，向新的文件写入叶节点的内容，并从哈夫曼的树根开始重新深入哈夫曼树

### 类

- 按bit读取文件：class readBitFile
- 哈夫曼树：class hufTree

### 码表

一维数组 codeTable[256], [ ]内为byte转换成对应的十进制数字，返回编码的符号

一维数组 proByte[256], [ ]内为byte转换成对应的十进制数字, 返回信源符号的概率