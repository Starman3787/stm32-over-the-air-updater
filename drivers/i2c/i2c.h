#ifndef I2C_I2C_H_
#define I2C_I2C_H_

#include <stddef.h>

void init_i2c(void);
void start_i2c(void);
void stop_i2c(void);
void write_i2c(char byte);
char read_i2c(void);
void send_i2c(char bytes[], size_t bytesLength);

#endif