#include "OTA.h"
#include "credentials.h"
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

void led_set(uint8_t led_r,uint8_t led_g,uint8_t led_b);
void led_set2(void);

#define pin_rgb_hemisphere1 32
#define pin_rgb_hemisphere2 23

float Accel = 0;

uint8_t mode = 0;
uint8_t set_r = 0U;
uint8_t set_g = 0U;
uint8_t set_b = 0U;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); /* Assign a unique ID to this sensor at the same time */
Adafruit_NeoPixel pixel_rgb_hemisphere1 = Adafruit_NeoPixel(121, pin_rgb_hemisphere1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel_rgb_hemisphere2 = Adafruit_NeoPixel(121, pin_rgb_hemisphere2, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  setupOTA("RGBBall", mySSID, myPASSWORD);

  pixel_rgb_hemisphere1.setBrightness(25);
  pixel_rgb_hemisphere2.setBrightness(25);
  pixel_rgb_hemisphere1.begin(); 
  pixel_rgb_hemisphere2.begin(); 

 // led_set(255U,255U,255U);
  
  /* Initialise the sensor */
  if(!accel.begin()){
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }
  
  mode = 2U;
  delay(1000);
}

void loop() {
  ArduinoOTA.handle();
    if (mode == 1U){
      set_r = random(255U);
      set_g = random(255U);
      set_b = random(255U);
      led_set(set_r,set_g,set_b);   
      mode = 2U;    
    }    
    else if (mode == 2U){
        uint8_t i = random(121U);
        set_r = random(255U);
        set_g = random(255U);
        set_b = random(255U);
        pixel_rgb_hemisphere1.setPixelColor(i, set_r,set_g,set_b);   
        pixel_rgb_hemisphere2.setPixelColor(i, set_r,set_g,set_b); 
        pixel_rgb_hemisphere1.show();  
        pixel_rgb_hemisphere2.show();     
    }
    else if (mode == 3U){
      led_set2();   
    }
    else{
    }  

    /* Get a new sensor event */ 
    sensors_event_t accelEvent;  
    accel.getEvent(&accelEvent);    
    Accel = (abs(accelEvent.acceleration.x)) + abs((accelEvent.acceleration.y)) + abs((accelEvent.acceleration.z));
    
    if(Accel > 40.0){
      mode = 1U;
    }
    else{
      /*Skip*/
    }
}

void led_set(uint8_t led_r,uint8_t led_g,uint8_t led_b){
    uint8_t led_row = 0U;
    uint8_t led_column = 0U;
    
    for(led_row=0U; led_row<7U; led_row++){
      if(led_row == 0U){
        for(led_column=0U; led_column<16U; led_column++){  
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row), led_r, led_g, led_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row), led_r, led_g, led_b);    
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row+1U), led_r, led_g, led_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row+1U), led_r, led_g, led_b);       
        }    
      }
      else if(led_row == 1U){
        for(led_column=0U; led_column<16U; led_column++){  
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row+1U), led_r, led_g, led_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row+1U), led_r, led_g, led_b);    
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row+2U), led_r, led_g, led_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row+2U), led_r, led_g, led_b);       
        }    
      }
      else if(led_row<=4U){
        for(led_column=0U; led_column<16U; led_column++){
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row+2U), led_r, led_g, led_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row+2U), led_r, led_g, led_b);     
        }        
      }
      else if(led_row==5U){
        for(led_column=0U; led_column<8U; led_column++){
          pixel_rgb_hemisphere1.setPixelColor((120U - (8U - led_column)), led_r, led_g, led_b); 
          pixel_rgb_hemisphere2.setPixelColor((120U - (8U - led_column)), led_r, led_g, led_b);     
        }        
      }
      else{
        pixel_rgb_hemisphere1.setPixelColor(120U, led_r, led_g, led_b); 
        pixel_rgb_hemisphere2.setPixelColor(120U, led_r, led_g, led_b);  
      }
      pixel_rgb_hemisphere1.show();  
      pixel_rgb_hemisphere2.show();  
      delay(50);
    }
}

void led_set2(void){
    uint8_t led_row = 0U;
    uint8_t led_column = 0U;
    
    for(led_row=0U; led_row<7U; led_row++){
      if(led_row == 0U){
        set_r = random(255U);
        set_g = random(255U);
        set_b = random(255U);
        for(led_column=0U; led_column<16U; led_column++){  
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row), set_r, set_g, set_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row), set_r, set_g, set_b);    
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row+1U), set_r, set_g, set_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row+1U), set_r, set_g, set_b);       
        }    
      }
      else if(led_row == 1U){
          set_r = random(255U);
          set_g = random(255U);
          set_b = random(255U);
        for(led_column=0U; led_column<16U; led_column++){  
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row+1U), set_r, set_g, set_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row+1U), set_r, set_g, set_b);    
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row+2U), set_r, set_g, set_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row+2U), set_r, set_g, set_b);       
        }    
      }
      else if(led_row<=4U){
          set_r = random(255U);
          set_g = random(255U);
          set_b = random(255U);
        for(led_column=0U; led_column<16U; led_column++){
          pixel_rgb_hemisphere1.setPixelColor(((led_column*7U)+led_row+2U), set_r, set_g, set_b); 
          pixel_rgb_hemisphere2.setPixelColor(((led_column*7U)+led_row+2U), set_r, set_g, set_b);     
        }        
      }
      else if(led_row==5U){
          set_r = random(255U);
          set_g = random(255U);
          set_b = random(255U);
        for(led_column=0U; led_column<8U; led_column++){
          pixel_rgb_hemisphere1.setPixelColor((120U - (8U - led_column)), set_r, set_g, set_b); 
          pixel_rgb_hemisphere2.setPixelColor((120U - (8U - led_column)), set_r, set_g, set_b);     
        }        
      }
      else{
        pixel_rgb_hemisphere1.setPixelColor(120U, set_r, set_g, set_b); 
        pixel_rgb_hemisphere2.setPixelColor(120U, set_r, set_g, set_b);  
      }
      pixel_rgb_hemisphere1.show();  
      pixel_rgb_hemisphere2.show();  
      delay(50);
    }
}
