#include <Arduino.h>
#include "esp_now.h"
#include "packet.hpp"

const int CACHE_SIZE = 256;
Packet cache[CACHE_SIZE];
// send
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
        Serial.println("\r\nLast Packet Send Status:\t");
        Serial.println(status== ESP_NOW_SEND_SUCCESS? "Success" : "Fail");
}

void broadcast(){
    
}