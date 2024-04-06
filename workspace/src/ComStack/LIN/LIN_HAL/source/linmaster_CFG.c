#include "linmaster.h"
#include "GPIO.h"
#include "UART_DRIVER.h"

message_t messages_FIRST;
message_t messages_SECOND;

signal_t signal_first [2] = {
  [0] = {
        .idx = 0,
        .len = 8,
        .mes = &messages_FIRST
        },
  [1] = {
        .idx = 1,
        .len = 8,
        .mes = &messages_FIRST
        }
};

signal_t signal_second [2] = {
  [0] = {
        .idx = 0,
        .len = 8,
        .mes = &messages_SECOND
        },
  [1] = {
        .idx = 1,
        .len = 8,
        .mes = &messages_SECOND
        }
};

LIN_UART_t LIN_UART = {
  .baudrate = 9600,
  .oversampling = OVERSAMPLING_16,
  .stopBits = ONE_STOP_BIT,
  .wordLength = WORDLENGTH_8BITS,
  .UART_NO = UART1,
  .RxUart_pin = {.Mode = GPIO_AF_PP,
                 .Port = GPIO_PORTB,
                 .Pin = GPIO_PIN7,
                 .Speed = GPIO_SPEED_HIGH },

    .TxUart_pin = {.Mode = GPIO_AF_PP,
                 .Port = GPIO_PORTB,
                 .Pin = GPIO_PIN6,
                 .Speed = GPIO_SPEED_HIGH },
};

message_t messages_FIRST = {
  .data = "",
  .data_len = 2,
  .id = 0x10,
  .pid = 0x50,
  .s = &signal_first,
  .signal_len = 16,
  .type = RECEIVER
};

message_t messages_SECOND = {
  .data ="",
  .data_len = 2,
  .id = 0x12,
  .pid = 0x92,
  .s = &signal_second,
  .signal_len = 16,
  .type = RECEIVER
};

schedTableEntry primary_sched_table[NUM_OF_MESSAGES] = {
  [0] = {
    .m = &messages_FIRST,
    .slotMS = 20
  },
  [1] = {
    .m = &messages_SECOND,
    .slotMS = 30
  }
};