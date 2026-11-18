#ifndef UART1_H_
#define UART1_H_

void uart1_init(void);
void uart1_transmit(char data);
char uart1_receive(void);
void uart1_print(const char *str);

#endif