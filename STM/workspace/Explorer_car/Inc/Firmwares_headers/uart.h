#ifndef UART_H_
#define UART_H_

void uart_init(void);
void uart_transmit(char data);
char uart_receive(void);
void uart_print(const char *str);

#endif /* UART_H_ */