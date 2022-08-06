#ifndef EXAMPLES_H_
#define EXAMPLES_H_

#define EXAMPLE_ADD   "LDA vara\n"     \
                      "ADD varb\n"     \
                      "OUT\n"       \
                      "HLT\n"       \
                      "vara db 2\n" \
                      "varb db 5\n"

#define EXAMPLE_SUB   "LDA 4\n"      \
                      "SUB 5\n"      \
                      "OUT\n"        \
                      "HLT\n"        \
                      "vara db 10\n" \
                      "varb db 5\n"

#define EXAMPLE_MUL   "LDA vara\n"     \
                      "MUL varb\n"     \
                      "OUT\n"       \
                      "HLT\n"       \
                      "vara db 2\n" \
                      "varb db 5\n"

#endif /* !EXAMPLES_H_ */