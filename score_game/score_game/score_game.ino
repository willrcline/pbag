//CONTENTS
//Include libraries
//Define Variables
//Setup
//Loop


#include <LiquidCrystal_I2C.h> //used for screen; Library manager: library by Marco Schwartz
#include <SoftwareSerial.h> //used for sound


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
long up_debounce_prevmillis = 0;  // the last time the output pin was toggled
long mid_debounce_prevmillis = 0;
long down_debounce_prevmillis = 0;
long auto_return_to_startscreen_prevmillis = 0;
//(time intervals)
long debounce_interval = 200;    //Debounce time for buttons; increase if the output flickers
long auto_return_to_mainscreen_interval = 30000;


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
int hit_count = 0;
int big = 0;
int med = 0;
int small = 0;

//Score game time length variable(the length the full game is set for); init at 1(Min).
int score_game_time_length = 1;

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
}

void loop() {

  //POLLS FOR MID BUTTON GIVEN THAT DEBOUNCE TIME INTERVAL HAS PASSED
  if ( (millis() - mid_debounce_prevmillis > debounce_interval) and (digitalRead(mid_btn_pin) == HIGH) ) {
    mid_btn();

    mid_debounce_prevmillis = millis();
 }
  
  //POLLS FOR UP BUTTON GIVEN THAT DEBOUNCE TIME INTERVAL HAS PASSED AND DIRECTION_BTN_POLLING IS SET TO "ON".
  if ( (millis() - up_debounce_prevmillis > debounce_interval) and (digitalRead(up_btn_pin) == HIGH) and (direction_btn_polling == "ON") ) {
    up_btn();
    
    up_debounce_prevmillis = millis();
 }

  //POLLS FOR DOWN BUTTON GIVEN THAT DEBOUNCE TIME INTERVAL HAS PASSED AND DIRECTION_BTN_POLLING IS SET TO "ON".
  if ( (millis() - down_debounce_prevmillis > debounce_interval) and (digitalRead(down_btn_pin) == HIGH) and (direction_btn_polling == "ON") ) {
    down_btn();

    down_debounce_prevmillis = millis();
 }

  //send_command_to_MP3_player(play_second_song, 6);
  //delay(8000);
}
