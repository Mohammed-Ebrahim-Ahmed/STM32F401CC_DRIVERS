#include "lin_uart_bridge.h"
#include "GPIO.h"
#include "UART_DRIVER.h"


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