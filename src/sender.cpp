#include <Arduino.h>
#include "WiFi.h"
#include "esp_now.h"

uint8_t broadcast_address[] = {0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,};

typedef struct __attribute__((packed)){
  char a[240];
}message;

message data;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
  Serial.println("\r\nLast Packet Send Status:\t");
  Serial.println(status== ESP_NOW_SEND_SUCCESS? "Success" : "Fail");
}

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());

  if(esp_now_init() != ESP_OK){
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcast_address, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if(esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop(){
  strcpy(data.a, "Voluptatem repudiandae aut non maiores maiores. Omnis vero occaecati delectus aut voluptatibus numquam. Earum sit quidem eius molestiae. Omnis eligendi eveniet accusantium. Dignissimos qui maxime fugit in voluptatibus");
  // data.b = random(1, 20);
  // data.c = 1.2;
  // data.d = false;

  esp_err_t res = esp_now_send(broadcast_address, (uint8_t *) &data, sizeof(data));

  if(res == ESP_OK){
    Serial.println("Sent");
  }else Serial.println("Error in sending");
  delay(1000);
}