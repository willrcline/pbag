//CONTENTS
//Include libraries
//Define Variables
//Setup
//Loop


#include <LiquidCrystal_I2C.h> //used for screen; Library manager: library by Marco Schwartz
#include <SoftwareSerial.h> //used for sound
#include "MPU9250.h" //Used for Orientation sensor; Built by UnityLab on Fiver
#include "eeprom_utils.h" //Used for Orientation sensor calibration; Built by UnityLab on Fiver

//VARIABLES

//--------------MP3 stuff----------------//
// Define the RX and TX pins to establish UART communication with the MP3 Player Module.
#define MP3_RX 8 // to TX
#define MP3_TX 9 // to RX

// Define the required MP3 Player Commands:

// Select storage device to TF card
static int8_t select_SD_card[] = {0x7e, 0x03, 0X35, 0x01, 0xef}; // 7E 03 35 01 EF
// Play with index: /01/001xxx.mp3
static int8_t play_first_song[] = {0x7e, 0x04, 0x41, 0x00, 0x01, 0xef}; // 7E 04 41 00 01 EF
// Play with index: /01/002xxx.mp3
static int8_t play_second_song[] = {0x7e, 0x04, 0x41, 0x00, 0x02, 0xef}; // 7E 04 41 00 02 EF
// Play the song.
static int8_t play_third_song[] = {0x7e, 0x04, 0x41, 0x00, 0x03, 0xef}; // 7E 04 41 00 02 EF
// Play the song.
static int8_t play[] = {0x7e, 0x02, 0x01, 0xef}; // 7E 02 01 EF
// Pause the song.
static int8_t pause[] = {0x7e, 0x02, 0x02, 0xef}; // 7E 02 02 EF
//stop song
static int8_t stop_song[] = {0x7E, 0x02, 0x0E, 0xEF};
//set volume. on 2nd to last, 0F = 15 and 1E = 30
static int8_t set_volume[] = {0x7E, 0x03, 0x31, 0x0F, 0xEF};

// Define the Serial MP3 Player Module.
SoftwareSerial MP3(MP3_RX, MP3_TX);
//------------------------------------------------//


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Millis variables
//(time keeper variable-holds previous snapshot of millis)
long general_debug_info_prevmillis = 0;
long orientation_debug_info_prevmillis = 0;
long up_debounce_prevmillis = 0;  // the last time the output pin was toggled
long mid_debounce_prevmillis = 0;
long down_debounce_prevmillis = 0;
long auto_return_to_startscreen_prevmillis = 0;
long orientation_update_prevmillis = 0;
long add_to_score_prevmillis = 0;
long score_game_time_length_prevmillis = 0;
//(time intervals)
long general_debug_info_interval = 5000;
long orientation_debug_info_interval = 400;
long debounce_interval = 200;    //Debounce time for buttons; increase if the output flickers
long auto_return_to_mainscreen_interval = 30000;
long orientation_update_interval = 25;
long add_to_score_interval = 100;

//VARIABLES CONTINUED...

//Button variables
//(pin numbers)
int led_pin = 13;
int mid_btn_pin = 11;
int up_btn_pin = 12;
int down_btn_pin = 10;
//(will be set to on or off)
String direction_btn_polling;

//keep track of which screen was last printed
String current_screen = "start";

//Score variables
int score = 0;
int unweighted_score = 0;
int big_hit = 0;
int med_hit = 0;
int small_hit = 0;

//Variables for time remaining in score_game
long score_game_total_sec_remaining = 0;
int score_game_min_remaining = 0;
int score_game_sec_remaining = 0;

//Score game time length variable(the length the full game is set for); init at 1(Min).
int score_game_time_length = 1;

//Orientation sensor variables
MPU9250 mpu;
float pitch;
float roll;
float raw_yaw;
float raw_pitch;
float raw_roll;
float alpha;
float beta;
float gamma;


void setup() {
  //INIT SERIAL MONITOR
  Serial.begin(115200);
  Serial.println(F("serial init"));
  
  //INIT LCD
  lcd.init();
  Serial.println(F("lcd init"));
  //set LCD backlight
  lcd.backlight();
  //call LCD start_screen to start
  start_screen();
  //start_screen();
  Serial.println(F("lcd start screen function called"));

  //INIT MP3 PLAYER 
  MP3.begin(9600);
  Serial.println(F("MP3 player init"));

  //INIT ORIENTATION SENSOR
  Wire.begin();
  delay(2000);

  if (!mpu.setup(0x69)) {  // change to your own address
      while (1) {
          Serial.println("MPU connection failed. Please check your connection");
          delay(5000);
      }
  }
  loadCalibration();
}

void loop() {
  //DEBUG INFO REGULARLY PRINTED TO THE SERIAL MONITOR//
  //GENERAL DEBUG INFO SENT TO SERIAL MONITOR EVERY 5 SECONDS
  if (millis() > general_debug_info_prevmillis + general_debug_info_interval) {
    print_general_debug_info();

    general_debug_info_prevmillis = millis();
  }

  //ORIENTATION DEBUG INFO SENT TO SERIAL MONITOR EVERY SPLIT SECOND WHEN CURRENT_SCREEN IS SUCH THAT ORIENTATION SENSING OCCURS.
  if ( (current_screen == "score_game") and (millis() > orientation_debug_info_prevmillis + orientation_debug_info_interval) ) {
    print_orientation_debug_info();

    orientation_debug_info_prevmillis = millis();
  }

  
  //BUTTON POLLING//
  //POLLS FOR MID BUTTON GIVEN THAT DEBOUNCE TIME INTERVAL HAS PASSED
  if ( (millis() > mid_debounce_prevmillis + debounce_interval) and (digitalRead(mid_btn_pin) == HIGH) ) {
    mid_btn();

    mid_debounce_prevmillis = millis();
  }
  
  //POLLS FOR UP BUTTON GIVEN THAT DEBOUNCE TIME INTERVAL HAS PASSED AND DIRECTION_BTN_POLLING IS SET TO "ON".
  if ( (millis() > up_debounce_prevmillis + debounce_interval) and (digitalRead(up_btn_pin) == HIGH) and (direction_btn_polling == "ON") ) {
    up_btn();
    
    up_debounce_prevmillis = millis();
  }

  //POLLS FOR DOWN BUTTON GIVEN THAT DEBOUNCE TIME INTERVAL HAS PASSED AND DIRECTION_BTN_POLLING IS SET TO "ON".
  if ( (millis() > down_debounce_prevmillis + debounce_interval) and (digitalRead(down_btn_pin) == HIGH) and (direction_btn_polling == "ON") ) {
    down_btn();

    down_debounce_prevmillis = millis();
  }

  //ORIENTATION VAR AND SCORING VAR UPDATES//
  //CALLS FOR UPDATE OF RAW ORIENTATION DATA AND SUBSEQUENTLY UPDATES ALL ORIENTATION VARS...
  //...GIVEN THAT CURRENT_SCREEN IS SET TO "SCORE_GAME", MPU.UPDATE() == TRUE, AND ORIENTATION UPDATE TIME INTERVAL HAS PASSED.
  if ( (current_screen == "score_game") and (mpu.update()) ) {
    static uint32_t orientation_update_prevmillis = millis();
    if (millis() > orientation_update_prevmillis + orientation_update_interval) {
      update_orientation_vars();
    }
  }
 
  //ADDS TALLY TO HIT VARIABLES AND UPDATES SCORE VALUE; CALLS FUNCTION THAT USES MILLIS() AND PREVMILLIS VAR TO CALCULATE VARS OF TIME REMAINING;...
  //...REPRINTS SCORE_GAME_SCREEN(TO DISPLAY UPDATED SCORE VAR)...
  //...GIVEN THAT CURRENT_SCREEN IS SET TO "SCORE_GAME" AND ADD_TO_SCORE_INTERVAL OF A SPLIT SECOND HAS PASSED SINCE LAST CALL.
  if ( (current_screen == "score_game") and (millis() > add_to_score_prevmillis + add_to_score_interval) ) {
    add_to_score();
    calculate_score_game_time_remaining();
    score_game_screen();

    add_to_score_prevmillis = millis();
    }
  //send_command_to_MP3_player(play_second_song, 6);

  //CALLS FUNCTION TO PRINT FINAL_SCORE_SCREEN GIVEN THAT SCORE_GAME'S SPECIFIED TIME LENGTH HAS PASSED AND CURRENT_SCREEN IS SET TO "SCORE_GAME". PREVMILLIS VAR IS RESET TO MILLIS AT SWITCH FROM "SELECT_TIME" SCREEN TO "SCORE_GAME" SCREEN.
  if ( (current_screen == "score_game") and (millis() > score_game_time_length_prevmillis + score_game_time_length*60000) ) {
    final_score_screen();

    score_game_time_length_prevmillis = millis();
    }
}
