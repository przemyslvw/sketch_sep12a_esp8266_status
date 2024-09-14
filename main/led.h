#ifndef BLINK_LED_H
#define BLINK_LED_H

// Definicja pinu diody LED
#define LED_BUILTIN D4  // Dioda wbudowana podłączona do GPIO2 (D4)
#define LED_GPIO4 D2    // Zewnętrzna dioda podłączona do GPIO4 (D2)

// Deklaracja funkcji blinkLED
void blinkLED();

#endif
