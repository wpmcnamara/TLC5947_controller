#include <TLC5947_controller.h>

TLC5947_controller::TLC5947_controller(uint8_t latch_pin) : TLC5947(latch_pin) {
    for(uint8_t i=0; i<24; i++) {
        led[i].mode=LED_OFF;
        led[i].intensity=0;
        channel(i, 0);
    }
    active_update=false;
    updateMode=MANUAL;
}

void TLC5947_controller::begin() {
    TLC5947::begin();
    //TLC5947::update();
}


void TLC5947_controller::set_led(uint8_t l, led_mode_t mode) {
    switch(mode) {
        case LED_OFF:
            led[l].mode=LED_OFF;
            led[l].intensity=0;
            active_update=true;
            break;
        case LED_ON:
            led[l].mode=LED_ON;
            led[l].intensity=4095;
            active_update=true;
            break;
        default:
            break;
    }

}
void TLC5947_controller::set_led(uint8_t l, led_mode_t mode, uint16_t rate) {
    float change;
    float l_intensity, l_final_intensity;
    if(rate<=0) {
        return;
    }
    if(mode==LED_FADE_OFF) {
        //led[l].step=led[l].intensity/(rate*ticksPerMs);
        led[l].final_intensity=0;
        l_intensity=led[l].intensity;
        l_final_intensity=0.0;
        change=l_final_intensity-l_intensity;
        led[l].step=(change/rate)*10.0;
        //Serial.printf("led=%d, intensity=%d, final intensity=%d, step=%f\n", l, (int)led[l].intensity, led[l].final_intensity, led[l].step);
        //led[l].step=(((float)(led[1].final_intensity-led[l].intensity))/1000.0)*10.0;
        led[l].mode=LED_FADE_OFF;
        active_update=true;
    } else {
        return;
    }
}

void TLC5947_controller::set_led(uint8_t l, led_mode_t mode, uint16_t intensity, uint16_t rate) {
    float change;
    float l_intensity, l_final_intensity;
    if(rate<=0) {
        return;
    }
    if(mode==LED_FADE_ON) {
        led[l].mode=LED_FADE_ON;
        led[l].final_intensity=intensity;
        l_final_intensity=intensity;
        l_intensity=led[l].intensity;
        change=l_final_intensity-l_intensity;
        led[l].step=(change/rate)*10.0;
        //Serial.printf("led=%d, intensity=%d, final intensity=%d, step=%f\n", l, (int)led[l].intensity, led[l].final_intensity, led[l].step);
        active_update=true;
    } else {
        return;
    }
}

void TLC5947_controller::set_mode(update_mode_t mode, void (*callback)()) {
    updateMode=mode;
    tick.end();
    if(updateMode==AUTOMATIC) {
         tick.begin(callback, UPDATE_RATE);
    } 
}

void TLC5947_controller::update() {
    bool update_controller=false;
    int int_temp;
    if(!active_update && updateMode==AUTOMATIC) {
        //Serial.printf("disabling callback\n");
        //tick.end();
        return;
    }
    active_update=false;
    for(uint8_t i=0; i<24; i++) {
        if(led[i].mode==LED_FADE_ON || led[i].mode==LED_FADE_OFF ) {
            active_update=true;
            int_temp=led[i].intensity;
            led[i].intensity+=led[i].step;
            if(led[i].step < 0 ) {
                if (led[i].intensity < led[i].final_intensity) {
                    led[i].intensity = led[i].final_intensity;
                    led[i].mode=LED_ON;
                }
            } else {
                if (led[i].intensity > led[i].final_intensity) {
                    led[i].intensity = led[i].final_intensity;
                    led[i].mode=LED_ON;
                }               
            }
            if(led[i].intensity>=4095) {
                led[i].intensity=4095;
                led[i].mode=LED_ON;
            } else if (led[i].intensity<=0) {
                led[i].intensity=0;
                led[i].mode=LED_ON;                    
            }
            //Serial.printf("Set led %d to %d\n", i, (int)led[i].intensity);
            if(int_temp != (int)led[i].intensity ) {
                channel(i, led[i].intensity);
                update_controller=true;
            }
        } else {
            //Serial.printf("Set led %d to %d\n", i, (int)led[i].intensity);
            channel(i, (int)led[i].intensity); 
            update_controller=true;
        }
    }
    if(update_controller) {
        TLC5947::update();
    }
}