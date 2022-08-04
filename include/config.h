#ifndef CONFIG_H_
#define CONFIG_H_

#define WORD_SIZE 8
#define DWORD_SIZE 16

#define RAM_SIZE 16

typedef size_t wordSizeType; //Has to match bitset type... <size_t>

typedef std::bitset<WORD_SIZE> word;
typedef std::bitset<DWORD_SIZE> dword;

#endif /* !CONFIG_H_ */