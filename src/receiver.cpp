#include <Arduino.h>
#include "esp_now.h"
#include "WiFi.h"

typedef struct __attribute__((packed)){
    char a[240];
} message;


message data;

void OnDataRecv(const uint8_t* mac, const uint8_t *incoming_data, int len){
    memcpy(&data, incoming_data, sizeof(data));
    Serial.println("Bytes recieved: ");
    Serial.println(len);    
    Serial.println("Data: ");
    Serial.println(data.a);
    Serial.println();
}


void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    if(esp_now_init()!=ESP_OK){
        Serial.println("Init error");   
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
}

void loop(){
    
}