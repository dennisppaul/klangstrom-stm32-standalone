#include <stddef.h>
#include <errno.h>
#include <unistd.h>

#include "ApplicationStub.h"

int getentropy(void* buffer, size_t length) {
    (void) buffer;
    (void) length;
    return -ENOSYS;
}

int main(void) {
    setup();
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (1) {
        loop();
    }
#pragma clang diagnostic pop
}

#include "KlangstromEnvironment.h"
#ifdef KLST_PANDA_STM32

#include "stm32h7xx_hal.h"

void delay(uint32_t delay_ms) {
    HAL_Delay(delay_ms);
}

#endif // KLST_PANDA_STM32
