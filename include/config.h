#ifndef CONFIG_H_
#define CONFIG_H_

#define WORD_SIZE 4
#define DWORD_SIZE 8
#define ADDRESS_SIZE 4

typedef size_t wordSizeType; //Has to match bitset type... <size_t>

typedef std::bitset<WORD_SIZE> word;
typedef std::bitset<DWORD_SIZE> dword;

#endif /* !CONFIG_H_ */