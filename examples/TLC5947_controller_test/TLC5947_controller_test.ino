#include <TLC5947_controller.h>

#define LATCH_PIN 18

TLC5947_controller led_controller(LATCH_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  Serial.printf("begin setup\n");
  led_controller.begin();
  Serial.printf("finished controller begin\n");
  pinMode(MISO, INPUT_PULLUP);
  SPI.begin();
    Serial.printf("finished SPI begin\n");

}

void controller_update() {
    led_controller.update();
}

void loop() {
    int led=15;
    int last_led=14;
    int i,j;
    Serial.printf("begin loop\n");
    Serial.printf("start auto update\n");
    led_controller.set_mode(AUTOMATIC, &controller_update);
    /*
    led_controller.set_led(16, LED_FADE_ON, 2048, 500);
    led_controller.set_led(17, LED_FADE_ON, 2048, 500);
    led_controller.set_led(18, LED_FADE_ON, 2048, 500);
    delay(2000);
    led_controller.set_led(16, LED_FADE_ON, 4095, 500);
    led_controller.set_led(17, LED_FADE_ON, 1024, 500);
    led_controller.set_led(18, LED_FADE_ON, 3092, 500);
    delay(2000);
    while(1);
    */
    while(1) {
        for(i=0; i<100; i++) {
            led_controller.set_led(last_led, LED_FADE_OFF, 200);
            led_controller.set_led(led, LED_FADE_ON, 4095, 50);
            last_led=led;
            led++;
            if(led==24) {
                led=15;
            }
            delay(100);
        }
        led_controller.set_led(last_led, LED_FADE_OFF, 200);
        delay(3000);
        for(i=0; i<100; i++) {
            led_controller.set_led(last_led, LED_FADE_OFF, 200);
            led_controller.set_led(led, LED_FADE_ON, 4095, 50);
            last_led=led;
            led--;
            if(led==14) {
                led=23;
            }
            delay(100);
        }      
        led_controller.set_led(last_led, LED_FADE_OFF, 200);
        delay(3000); 
        led=0;
        for(i=0; i<100; i++) {
            for(j=0; j<9;j++) {
                if(led==j) {
                    led_controller.set_led(15+j, LED_FADE_ON, 4095, 100);
                } else {
                    led_controller.set_led(15+j, LED_FADE_ON, 1024, 100);
                }
            }
            led++;
            if(led==9) {
                led=0;
            }
            delay(100);
        }      
        delay(3000);  
        for(j=0; j<9;j++) {
            led_controller.set_led(15+j, LED_FADE_OFF, 50);
        }
        delay(500);
        led=0;
        last_led=0;
        for(i=0; i<100; i++) {  
            led_controller.set_led(15+led, LED_FADE_OFF, 10);
            led_controller.set_led(15+led+3, LED_FADE_OFF, 10);
            led_controller.set_led(15+led+6, LED_FADE_OFF, 10);
            last_led=led;
            led++;
            if(led==3) {
                led=0;
            }
            led_controller.set_led(15+led, LED_FADE_ON, 4095, 10);
            led_controller.set_led(15+led+3, LED_FADE_ON, 4095, 10);
            led_controller.set_led(15+led+6, LED_FADE_ON, 4095, 10);
            delay(200);
        }
        led=3;
        last_led=0;
        for(i=0; i<100; i++) {  
            led_controller.set_led(15+led, LED_FADE_OFF, 10);
            led_controller.set_led(15+led+3, LED_FADE_OFF, 10);
            led_controller.set_led(15+led+6, LED_FADE_OFF, 10);
            last_led=led;
            led--;
            if(led<0) {
                led=2;
            }
            led_controller.set_led(15+led, LED_FADE_ON, 4095, 10);
            led_controller.set_led(15+led+3, LED_FADE_ON, 4095, 10);
            led_controller.set_led(15+led+6, LED_FADE_ON, 4095, 10);
            delay(200);
        }
        delay(300);
    }
    /*
    Serial.printf("wait 1s\n");
    delay(1000);
    Serial.printf("turn led 15 on\n");
    led_controller.set_led(15, LED_ON);
    Serial.printf("wait 1s\n");
    delay(1000);
    Serial.printf("led 0 off, led 1 on\n");
    led_controller.set_led(15, LED_OFF);
    led_controller.set_led(16, LED_ON);
    Serial.printf("wait 1s\n");
    delay(1000);
    Serial.printf("Fade on led 17 (1s)\n");
    led_controller.set_led(17, LED_FADE_ON, 4095, 1000);
    delay(2000);
    led_controller.set_led(17, LED_FADE_OFF, 500);
    delay(1000);
    led_controller.set_led(18, LED_FADE_ON, 4095, 1000);
    delay(250);
    led_controller.set_led(19, LED_FADE_ON, 4095, 1000);
    delay(250);
    led_controller.set_led(20, LED_FADE_ON, 4095, 1000);
    delay(250);
    led_controller.set_led(21, LED_FADE_ON, 4095, 1000);
    delay(250);
    led_controller.set_led(18, LED_FADE_OFF, 1000);
    delay(250);
    led_controller.set_led(19, LED_FADE_OFF, 1000);
    delay(250);
    led_controller.set_led(20, LED_FADE_OFF, 1000);
    delay(250);
    led_controller.set_led(21, LED_FADE_OFF, 1000);
    delay(250);
    Serial.printf("busy wait\n");
    while(1){
        led_controller.set_led(22, LED_FADE_ON, 4095, 100);
        delay(100);
        led_controller.set_led(22, LED_FADE_OFF, 100);
        delay(100);
    };
    */
}