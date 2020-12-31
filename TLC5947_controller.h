#pragma once
#include <TLC5947.h>
#include <SPI.h>

#define UPDATE_RATE 10000

typedef enum {
    LED_OFF=0,
    LED_ON,
    LED_FADE_OFF,
    LED_FADE_ON
} led_mode_t;

typedef enum {
    AUTOMATIC=0,
    MANUAL
} update_mode_t;

typedef struct {
    led_mode_t mode;
    float intensity;
    uint16_t final_intensity;
    float step;
} led_t;

class TLC5947_controller : public TLC5947 {
    public:
        TLC5947_controller(uint8_t latch_pin);
        void begin();
        void set_led(uint8_t led, led_mode_t mode);
        void set_led(uint8_t led, led_mode_t mode, uint16_t rate);
        void set_led(uint8_t led, led_mode_t mode, uint16_t intensity, uint16_t rate);
        void set_mode(update_mode_t mode, void (*callback)());
        void update();
    private:
        update_mode_t updateMode;
        IntervalTimer tick;
        led_t led[24];
        bool active_update;
};



