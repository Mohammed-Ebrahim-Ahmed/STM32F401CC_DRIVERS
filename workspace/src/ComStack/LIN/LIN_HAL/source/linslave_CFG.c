#include "linslave.h"
#include "GPIO.h"
#include "UART_DRIVER.h"


message_t messages_FIRST;
message_t messages_SECOND;

extern signal_t signal_first [2];

extern signal_t signal_second [2];

extern LIN_UART_t LIN_UART ;

message_t messages [NUM_OF_MESSAGES] = {
  [0] = {
        .data = {'a','h'},
        .data_len = 2,
        .id = 0x10,
        .pid = 0x50,
        .s = &signal_first,
        .signal_len = 16,
        .type = SENDER
        },
  [1] = {
        .data = {'b','i'},
        .data_len = 2,
        .id = 0x12,
        .pid = 0x92,
        .s = &signal_second,
        .signal_len = 16,
        .type = SENDER
        }
};