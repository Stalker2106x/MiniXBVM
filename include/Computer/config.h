#ifndef CONFIG_H_
#define CONFIG_H_

#define WORD_SIZE 4
#define DWORD_SIZE 8

#define RAM_SIZE 16

#define OP_LDA    0b0000
#define OP_ADD    0b0001
#define OP_SUB    0b0010
#define OP_OUT    0b1110
#define OP_HLT    0b1111

typedef size_t wordSizeType; //Has to match bitset type...

typedef std::bitset<WORD_SIZE> word;
typedef std::bitset<DWORD_SIZE> dword;

#endif /* !CONFIG_H_ */