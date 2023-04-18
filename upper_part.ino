#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

//################################ WIFI CONSTANTS ################################ 
const char* SSID = "";
const char* PASSWORD = "";

//################################ DATABASE CONSTANTS ################################ 
// Insert Firebase project API Key
#define API_KEY ""

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
#define DATA_NAME "bulb"


//################################ APPLICATION PROCESSES ################################ 
#define NUM_LEDS 114
#define DATA_PIN 5
#define BRIGHTNESS 220
#define NUM_IN_LAYER 19
#define NUM_LAYERS 6
#define END_COL 18
CRGB leds[NUM_LEDS];
CRGB temp_column[NUM_LAYERS];

//################################ ANIMATION CONTROL ################################ 
int logic_control = -1;
double time_since = 0;
unsigned long loop_count = 0;

void random_spiral_setup();
void random_spiral();
void spiral_wave();
void wave_form();
void sin_wave();

//################################ AMBIENCE ANIMATION ################################ //
// Used for ambience environment
void ambience();

//################################ UTILITY FUNCTIONS ################################ //
int transform_x_y(int x, int y);

//################################ WIFI AND DATABASE ################################ //
bool signupOK;
String displays[4] = {"ambience",  "ingame", "win", "lose"};
int data;
int db_get_data();
void database_setup();
void wifi_setup();

void setup() {
  Serial.begin(115200);

  // wifi_setup();
  // database_setup();

  // Set up led
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}


//################################ MAIN LOOP ################################ 
// When the number indicate 1 means that 
void loop() {
  sin_wave();
} 

//################################ SPIRAL BOTTOM UP ################################ 

void random_spiral_setup() {
  for(int i = 0; i < NUM_IN_LAYER; i++) {
    leds[i] = CRGB(random(1, 256), random(1, 256), random(1, 256)); 
  }
  FastLED.show();
}

void random_spiral() {
  for(int x = 0; x < NUM_IN_LAYER; x++) {
    for(int y = 1; y < NUM_LAYERS; y++) {
      if (x == 0) {
        leds[transform_x_y(x, y)] = leds[transform_x_y(END_COL, y - 1)];
      }
      else {
        leds[transform_x_y(x, y)] = leds[transform_x_y(x - 1, y - 1)];
      }
      FastLED.show();
    }
  }
  for(int i = 0; i < NUM_IN_LAYER; i++) {
    leds[i] = CRGB(random(1, 256), random(1, 256), random(1, 256)); 
  }
}

void spiral_wave() {
  if(logic_control != 2) {
    logic_control = 2;
    random_spiral_setup();
  }
  else {
    random_spiral();
  }
}



//################################ CREATING SIN WAVE ################################ 
void wave_form() {
  double divide = 6.28 / NUM_IN_LAYER;
  FastLED.clear();
  for(int x = 0; x < NUM_IN_LAYER; x++) {
    for(int y = 0; y < NUM_LAYERS; y++) {
      leds[transform_x_y(x, sin(0.1 * time_since + x * divide) * 3 + 3)] = CRGB(20, 20, 200); 
    }
  }
  FastLED.show();
}
void sin_wave() {
  if(logic_control != 1) {
    logic_control = 1;
    time_since = 0;
  }
  else {
    wave_form();
    time_since += 0.2;
  }
}


//################################ AMBIENCE ANIMATION ################################ //
void colour_spin_setup() {
  int increment = 254 / NUM_IN_LAYER;
  for(int x = 0; x < NUM_IN_LAYER; x++) {
    int rand1 = random(100, 200);
    int rand2 = random(100, 200);
    for(int y = 0; y < NUM_LAYERS; y++) {
      int tmp = (x + 1) * increment;
      leds[transform_x_y(x, y)] = CRGB(tmp,rand1,rand2); 
    }
  }
  FastLED.show();
}

void spin() {
  for(int i = 0; i < NUM_LAYERS; i++) {
    temp_column[i] = leds[transform_x_y(0, i)];
  }

  for(int x = 0; x < NUM_IN_LAYER - 1; x++) {
    for(int y = 0; y < NUM_LAYERS; y++) {
      leds[transform_x_y(x, y)] = leds[transform_x_y(x + 1, y)];
    }
  }

  for(int i = 0; i < NUM_LAYERS; i++) {
    leds[transform_x_y(END_COL, i)] = temp_column[i];
  }
  FastLED.show();
  delay(50);
}

void ambience() {
  if(logic_control != 0) {
    logic_control = 0;
    colour_spin_setup();
  }
  else {
    spin();
  }
}

//################################ UTILITY FUNCTIONS ################################ //
int transform_x_y(int x, int y) {
  return y * NUM_IN_LAYER + x;
}

//################################ WIFI AND DATABASE ################################ //
int db_get_data() {
  if (Firebase.ready() && signupOK) {
    if (Firebase.RTDB.getInt(&fbdo, DATA_NAME)) {
      return fbdo.intData();
    }
  }
  return 0;
}

// SET UP PROCESSES
void wifi_setup() {
  // Starting the wifi module for IOT application.
  WiFi.begin(SSID, PASSWORD);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void database_setup() {
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }


  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}