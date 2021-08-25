//CONTENTS
//print general debug info: called throughout program(on all screens) at 5 sec intervals to show useful debug info
//print orientation debug info: Function called from millis if statement when current_screen is set such that orientation is used. Millis interval passes such that it is called every split second.

void print_general_debug_info() {
  Serial.println(F("GENERAL_DEBUG_INFO:"));
  Serial.print(F("current_screen: "));
  Serial.println(current_screen);
  Serial.print('\n');
}

void print_orientation_debug_info() {
  Serial.println(F("ORIENTATION_DEBUG_INFO:"));
  Serial.print(F("Roll: "));
  Serial.println(roll);
  Serial.print(F("Pitch: "));
  Serial.println(pitch);
  Serial.print(F("Score: "));
  Serial.println(score);
  Serial.print(F("Big_hit: "));
  Serial.println(big_hit);
  Serial.print(F("Med_hit: "));
  Serial.println(score);
  Serial.print(F("Small_hit: "));
  Serial.println(small_hit);
  Serial.print(score_game_min_remaining);
  Serial.print(F(":"));
  //printleadingZero
  Serial.print(score_game_sec_remaining);
  Serial.print(F(" remaining of "));
  Serial.print(score_game_time_length);
  Serial.println(F(" min(s)"));
  Serial.print('\n');
}
