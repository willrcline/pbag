//PAGE CONTENTS
//Include libraries
//Define Variables
//Setup
//Loop


#include <LiquidCrystal_I2C.h> //used for screen; Library manager: library by Marco Schwartz
//#include <SoftwareSerial.h> //used for sound
#include <AltSoftSerial.h> //used for sound
#include "MPU9250.h" //Used for Orientation sensor; Built by UnityLab on Fiver
#include "eeprom_utils.h" //Used for Orientation sensor calibration; Built by UnityLab on Fiver
#include <EEPROM.h> //Used for permanent storage of high scores of score game

//VARIABLE CONTENTS
//MP3 serial pins; send_command_to_MP3_player commands, SoftwareSerial variables connect to rx/tx pin variables
//LCD set i2c Address and display settings
//Fluid PrevMillis and const MillisInterval vars
//Button pin numbers; direction button (set to "ON" or "OFF")
//Current_screen
//Score variables(big,med,small,score,etc.)
//High score vars for each game time length(m): to be populated from eeprom
//Time remaining in score_game(min,sec,total_sec)
//Score game time length
//Orientation sensor(raw, interpreted)

//--------------MP3 stuff----------------//
// Define the RX and TX pins to establish UART communication with the MP3 Player Module.
#define MP3_RX 8 // to TX
#define MP3_TX 9 // to RX

// Define the required MP3 Player Commands:

// Select storage device to TF card
static int8_t select_SD_card[] = {0x7e, 0x03, 0X35, 0x01, 0xef}; // 7E 03 35 01 EF
// Play with index: /01/001xxx.mp3
static int8_t play_first_track[] = {0x7e, 0x04, 0x41, 0x00, 0x01, 0xef}; // 7E 04 41 00 01 EF
// Play with index: /01/002xxx.mp3
static int8_t play_second_track[] = {0x7e, 0x04, 0x41, 0x00, 0x02, 0xef}; // 7E 04 41 00 02 EF
// Play the song.
static int8_t play_third_track[] = {0x7e, 0x04, 0x41, 0x00, 0x03, 0xef}; // 7E 04 41 00 02 EF
// Play the song.
static int8_t play[] = {0x7e, 0x02, 0x01, 0xef}; // 7E 02 01 EF
// Pause the song.
static int8_t pause[] = {0x7e, 0x02, 0x02, 0xef}; // 7E 02 02 EF
//stop song
static int8_t stop_song[] = {0x7E, 0x02, 0x0E, 0xEF};
//set volume. on 2nd to last, 0F = 15 and 1E = 30
static int8_t set_volume[] = {0x7E, 0x03, 0x31, 0x0F, 0xEF};

// Define the Serial MP3 Player Module.
AltSoftSerial MP3(MP3_RX, MP3_TX);
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
long orientation_update_prevmillis = 0;
long add_to_score_prevmillis = 0;
long score_game_time_length_prevmillis = 0;
long auto_return_to_startscreen_prevmillis = 0;
long ding_track_prevmillis = 0;
//(time intervals)
const long general_debug_info_interval = 5000;
const long orientation_debug_info_interval = 400;
const long debounce_interval = 200;    //Debounce time for buttons; increase if the output flickers
const long orientation_update_interval = 25;
const long add_to_score_interval = 100;
const long auto_return_to_startscreen_interval = 30000;
const long ding_track_interval = 2000;

//Button variables
//(pin numbers)
const int led_pin = 13;
const int mid_btn_pin = 11;
const int up_btn_pin = 12;
const int down_btn_pin = 10;
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
long high_score_1m = EEPROM.read(1);
long high_score_2m = EEPROM.read(2);
long high_score_3m = EEPROM.read(3);
long high_score_4m = EEPROM.read(4);
long high_score_5m = EEPROM.read(5);
long high_score_6m = EEPROM.read(6);
long high_score_7m = EEPROM.read(7);
long high_score_8m = EEPROM.read(8);
long high_score_9m = EEPROM.read(9);
long high_score_10m = EEPROM.read(10);
//long high_score_1m = 0;
//long high_score_2m = 0;
//long high_score_3m = 0;
//long high_score_4m = 0;
//long high_score_5m = 0;
//long high_score_6m = 0;
//long high_score_7m = 0;
//long high_score_8m = 0;
//long high_score_9m = 0;
//long high_score_10m = 0;

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

//CONTENTS
//Init serial monitor at 115200 baud
//Init LCD and call function to print start_screen
//Init MP3 player at 9600 baud
//Init wire to read orientation sensor, load calibration for sensor

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

//CONTENTS
//General debug info (every 5 secs)
//Orientation debug info (during orientation sensing, every split second )
//Mid button polling (always occuring, delayed only by split second debounce interval)
//Up button polling (while set to certain LCD screen displays, delayed only by split second debounce interval)
//Down button polling (while set to certain LCD screen displays, delayed only by split second debounce interval)
//Update orientation vars (during orientation sensing, every split second)
//Score game repeated game functions (during score game screen, every split second)
//Final score screen printed after specified score game duration passes (during score game screen, occurs once after number of minutes specified on select_time screen passes)
//Start screen (during any screen where LCD interface inactivity can be interpreted as idleness, occurs after about 30 seconds)

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
     hit_sound_fx();
    calculate_score_game_time_remaining();
    score_game_screen();

    add_to_score_prevmillis = millis();
    }

  //FUNCTION CALLS TO SWITCH SCREENS AFTER SPECIFICED TIME INTERVAL AND GIVEN CERTAIN CONDITIONS//
  //CALLS FUNCTION TO PRINT FINAL_SCORE_SCREEN GIVEN THAT SCORE_GAME'S SPECIFIED TIME LENGTH HAS PASSED AND CURRENT_SCREEN IS SET TO "SCORE_GAME". PREVMILLIS VAR IS RESET TO MILLIS AT SWITCH FROM "SELECT_TIME" SCREEN TO "SCORE_GAME" SCREEN.
  if ( (current_screen == "score_game") and (millis() > score_game_time_length_prevmillis + score_game_time_length*60000) ) {
    compare_score_to_current_high_score();
    final_score_screen();

    score_game_time_length_prevmillis = millis();
    }

  //GIVEN THAT CURRENT_SCREEN NOT SET TO "START", "SCORE_GAME", OR "FINAL_SCORE", AFTER THE SUM OF PREVMILLIS AND THE TIME INTERVAL(OF ABOUT 30 SECS) BECOMES LESS THAN MILLIS(), START_SCREEN FUNCTION IS CALLED. 
  if ( (millis() >= auto_return_to_startscreen_prevmillis + auto_return_to_startscreen_interval) and (current_screen != "start") and (current_screen != "score_game") and (current_screen != "final_score") ) {
    start_screen();
    Serial.println(F("Auto returned to Start_Screen")); 
 }
 
}
