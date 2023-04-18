#include <FastLED.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


// FOR THE BALL DROP ANIMATION
void ball_drop();
void update_ball(CRGB colour = CRGB::Yellow);

// GAME CONTROL
void show_screen();
void clear_screen();
void update_screen();
void update_walls();
void move_walls();
void reset_ball_pos();
void rain_drop_clear_screen();
void random_wall();
void reset_game();
void next_frame_calculation();
void idle_frame_calculation();
void win_game_rgb();
void set_up_speaker();
void collided_screen_display();
bool detect_motion();

// UTILITY FUNCTIONS
int get_index(int x, int y);
int get_bit(int x, int y);
void set_bit(int &number, int x, bool one);
int get_lst_y(int y);

/* GAME DESIGN
Y
^
2
1
0 1 2 -> X
*/

// =======================GAME VARIABLES=======================
#define GAME_WIDTH 18
#define GAME_HEIGHT 25
#define WALL_WIDTH 3
#define WALL_HEIGHT 1
#define BALL_HEIGHT 2
#define START_BALL_X 8
#define START_BALL_Y 23
int  wall_layer = 0;
int ballBitMap[GAME_HEIGHT] = {0}; // Bit map storage for the location of ball
bool collided;
int ball_y;
int ball_x;
byte walls[10][3];
CRGB colours[2] = { CRGB::Blue, CRGB::Blue}; // Variables for alternating walls if needed
bool trash_detected = true;
int loop_count;

// =======================LED VARIABLES======================= //
#define NUM_LEDS 450
#define DATA_PIN 5
#define BRIGHTNESS 150
CRGB leds[NUM_LEDS];
// IMAGE GENERATION

// =======================MOTION SENSOR VARIABLES======================= //
#define MOTION_PIN 6
#define IR_PIN A0


// =======================SOUND VARIABLES======================= //
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


// =======================SETUP======================= // 
void setup() {
  mySoftwareSerial.begin(9600);
  s

  set_up_speaker();

  // Set up ir sensor
  pinMode(MOTION_PIN, INPUT);     // declare sensor as input
  // Set up ir sensor
  pinMode(IR_PIN, INPUT);     // declare sensor as input

  // Set up led
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Reset the game variables
  reset_game();
}


// =======================MAIN LOOP======================= // 
// Creating the main loop logic for the trash bin arcade machine to increase vibrancy of the location.
void loop() {
  if(trash_detected) {
    // if trash is detected start the game
    if(!collided) {
      update_screen();
      show_screen();
      delay(500);

      if(ball_y <= 0) {
        play_music(3);
        win_game_rgb();
        reset_game();
      }
      else{
        clear_screen();
        next_frame_calculation();
      }
    }
    else {
      play_music(5);
      collided_screen_display();
      reset_game();
    }
  }
  else {
    play_background();
    if(detect_motion()) {
      trash_detected = true;
      play_music(4);
    }
    else {
      update_screen();
      show_screen();
      delay(500);
      clear_screen();
      idle_frame_calculation();
    }
  }
}

// =======================SET UP CONTROL======================= //
void reset_game() {
  // Clear led data.
  clear_screen();

  // Set up ball pos_bit_map and ball_x and ball_y to start_x and start_y
  reset_ball_pos();

  // Set up random wall locations.
  randomSeed(369369);
  random_wall();

  trash_detected = false;
  collided = false;
  loop_count = 0;

  play_music(1);
}

// Reset the bit map containing the ball position.
void reset_ball_pos() {
  ball_x = START_BALL_X;
  ball_y = START_BALL_Y;

  // Resetting the ball bit map.
  for(int y = 0; y < GAME_HEIGHT; y++) {
    ballBitMap[y] = 0;
  }

  // Generating new ball bitmap.
  for (int i = 0; i < BALL_HEIGHT; i++) {
    for(int j = 0; j < BALL_HEIGHT; j++) {
      set_bit(ballBitMap[get_lst_y(ball_y + j)], ball_x + i, 1);
    }
  }
}

// Randomly generate number of walls starting from y = 0 with a random aomunt of pixel gap.
void random_wall() {
  wall_layer = 0;
  for(int y = 0; y < GAME_HEIGHT - 3; y += random(2, 4)) {
    walls[wall_layer][1] = y;
    if(wall_layer%2 == 0) {
      walls[wall_layer][0] = random(2, 8);
      walls[wall_layer][2] = 1;
    }
    else{
      walls[wall_layer][0] = random(8, 14);
      walls[wall_layer][2] = -1;
    }
    wall_layer++;
  }
}

// Set up speaker function
void set_up_speaker() {
   // SET up speaker
  Serial.println();
  Serial.println(F("Initializing...)"));

  while (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));

    delay(1000);
  }
  Serial.println(F("Online."));
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  myDFPlayer.volume(30);  //Set volume value (0~30).

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_BASS);
}

bool detect_motion() {
  delay(10);
  int val = analogRead(IR_PIN);
  if(val <= 100) {
    return true;
  }
  return false;
}

// =======================VOLUME CONTROL======================= // 
void play_music(int number) {
  myDFPlayer.playMp3Folder(number);
}

void play_background() {
  Serial.println(myDFPlayer.readState());
  if (myDFPlayer.readState() == 512) {
    myDFPlayer.playMp3Folder(1);
  }
}


// =======================SCREEN CONTROL======================= // 
// Function to reflect the latest state of the led screen.
void show_screen() {
  FastLED.show();
}

void clear_screen() {
  FastLED.clear();
}

void update_screen() {
  update_walls();
  update_ball();
}

// Idle frame control
void idle_frame_calculation() {
  move_walls();
}

// Loop for the collided screen display.
void collided_screen_display() {
  for(int i = 0; i < 5; i++) {
    update_ball();
    FastLED.show();
    delay(200);
    update_ball(CRGB::Black);
    update_walls();
    FastLED.show();
    delay(100);
  }
  rain_drop_clear_screen();
}

// Clear screen in a raindrop format.
void rain_drop_clear_screen() {
  // clearing the walls
  for(auto & info: walls) {
    for(int x = info[0]; x < info[0] + WALL_WIDTH; x++) {
      for(int y = info[1] - 1; y >= 0; y--) {
        leds[get_index(x, y)] = leds[get_index(x, y + 1)];
        leds[get_index(x, y + 1)] = CRGB::Black;
        FastLED.show();
        delay(5);
      }
      leds[get_index(x, 0)] = CRGB::Black;
      FastLED.show();
    }
  }
}

// Clear screen in a raindrop format.
void win_game_rgb() {
  // clearing the walls
  for(int x = 0; x < GAME_WIDTH; x++) {
    for(int y = 0; y < GAME_HEIGHT; y++) {
      leds[get_index(x, y)] = CRGB(random(1, 256), random(1, 256), random(1, 256)); 
    }
    FastLED.show();
  }

  for(int i = 0; i < 50; i++) {
    for(int x = 0; x < GAME_WIDTH; x++) {
      for(int y = 0; y < GAME_HEIGHT; y++) {
        leds[get_index(x, y)] = CRGB(random(1, 256), random(1, 256), random(1, 256)); 
      }
    }
    FastLED.show();
    clear_screen();
    delay(200);
  }
  
}


// =======================GAME CONTROL======================= // 
// Calculate the information of the next frame.
// Drop ball first to update bitmap for collision detection.
void next_frame_calculation() {
  ball_drop();
  move_walls();
}

// Update the position of walls in the led list.
void update_walls() {
  for(int i = 0; i < wall_layer; i++) {
    auto &info = walls[i];
    CRGB colour = colours[info[1]/2 % 2];
    for(int i = 0; i < WALL_HEIGHT; i++) {
      leds[get_index(info[0], info[1]+i)] = colour;
      leds[get_index(info[0] + 1, info[1]+i)] = colour;
      leds[get_index(info[0] + 2, info[1]+i)] = colour;
    }
  }
}

// Update the wall information after a move.
void move_walls() {
   for(int i = 0; i < wall_layer; i++) {
    auto &info = walls[i];
    if(info[2] == 1) {
      if(info[0] == GAME_WIDTH - WALL_WIDTH) {
        info[2] = -1;
      }
    }
    else {
      if(info[0] == 0) {
        info[2] = 1;
      }
    }
    info[0] += info[2];
    for(int i = 0; i < WALL_WIDTH; i++){
       if(get_bit(info[0] + i, info[1])) {
         collided = true;
       }
    }
  }
}

// Updates the leds list with the ball position and colour.
void update_ball(CRGB colour = CRGB::Yellow) {
  for (int i = 0; i < BALL_HEIGHT; i++) {
    for(int j = 0; j < BALL_HEIGHT; j++) {
      leds[get_index(ball_x + i, ball_y + j)] = colour;
    }
  }
}

// Update the ball x and ball y after a drop. Updates the ballBitMap.
void ball_drop() {
  if(ball_y == 1) {
    ball_y -= 1;
  }
  else {
    ball_y -= 2;
  }
  int start_y = ball_y;
  int end_y = ball_y + BALL_HEIGHT;
  for(int y = start_y; y < end_y; y++) {
    ballBitMap[get_lst_y(y)] = ballBitMap[get_lst_y(y + 2)];
  }
  ballBitMap[get_lst_y(end_y)] = 0;
  ballBitMap[get_lst_y(end_y + 1)] = 0;
}

/*
HELPER FUNCTIONS
*/

// Get the bit number for a certain led.
int get_bit(int x, int y) {
  return (ballBitMap[get_lst_y(y)] >> (GAME_WIDTH - x - 1)) & 1;
}

// Set the referenced number's x digit to one or zero.
void set_bit(int &number, int x, bool one) {
  number = (number | (one << (GAME_WIDTH - x - 1)));
}

// Convert the x and y coordinate into led position in the list.
int get_index(int x, int y) {
  if(y % 2 == 0) {
    return (GAME_HEIGHT - y - 1) * GAME_WIDTH + x;
  }
  else {
    return (GAME_HEIGHT - y - 1) * GAME_WIDTH + (GAME_WIDTH - x - 1);
  }
}

// Convert y to the list y.
int get_lst_y(int y) {
  return GAME_HEIGHT - y - 1;
}

// Utility function to print data on screen for debugging.
void output_screen() {
  for(int y = GAME_HEIGHT - 1; y >= 0; y--) {
    for(int x = 0; x < GAME_WIDTH; x++) {
      if(get_bit(x, y) == 1) {
        Serial.print('1');
      }
      else {
        Serial.print('0');
      }
    }
    Serial.println(' ');
  }
}

