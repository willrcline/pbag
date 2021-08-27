//CONTENTS
//add_to_score: Adds a certain ammount of points to score depending on current value of pitch and roll variables when function is called
//calculate score game time remaining: Takes current millis and prevmillis of timestamp when game began and uses them to calculate a total sec var which is used to get usable total min and total sec remaining in game to print to LCD.
//reset_score_vars_after_final_score_screen: Called anytime there is a transition away from final score screen(so that the score vars will be back to zero before score game screen comes around again)

void add_to_score() {
    //ADD TALLY TO BIG, MED, OR SMALL HIT VARIABLE DEPENDING ON CURRENT VALUE OF PITCH AND ROLL WHEN FUNCTION IS CALLED
    //Big hit:
    if ( (pitch > 69) or (roll > 69) ){
      big_hit += 1;
    }        
    //Med hit:
    else if ( (pitch > 55) or (roll > 55) ) {
      med_hit += 1;
    }
    //Small hit
    else if ( (pitch > 35) or (roll > 35) ) {
      small_hit += 1;
    }
    else {
      //Roll and pitch were below minimum required ammount to be considered a "small_hit"
    }
    //CALCULATE UPDATED SCORE VALUE BY WEIGHING AND SUMMING BIG, MED, AND SMALL HIT VALUES
    score = (big_hit*9) + (med_hit*3) + (small_hit);
    unweighted_score = (big_hit) + (med_hit) + (small_hit);

//    FIRST HIT
//    if (unweighted_hit_count == 1) {
//      first_hit += 1;
//      if (first_hit == 1) {
//        Serial.println(F("first hit on bag"));
//        send_command_to_MP3_player(play_third_track, 6); 
//      }
    }

void hit_sound_fx() {
  if ( (pitch > 69) or (roll > 69) and (millis() >= ding_track_prevmillis + ding_track_interval) ) {
      send_command_to_MP3_player(play_second_track, 6);

      ding_track_prevmillis = millis();
    }        
}

void calculate_score_game_time_remaining() {
  score_game_total_sec_remaining = score_game_time_length*60 - (millis() - score_game_time_length_prevmillis)/1000;
  score_game_min_remaining = score_game_total_sec_remaining / 60;
  score_game_sec_remaining = score_game_total_sec_remaining % 60;
}

void reset_score_vars_after_final_score_screen() {
  score = 0;
  unweighted_score = 0;
  big_hit = 0;
  med_hit = 0;
  small_hit = 0;
}

void read_current_high_scores() {
   high_score_1m = EEPROM.read(1);
   high_score_2m = EEPROM.read(2);
   high_score_3m = EEPROM.read(3);
   high_score_4m = EEPROM.read(4);
   high_score_5m = EEPROM.read(5);
   high_score_6m = EEPROM.read(6);
   high_score_7m = EEPROM.read(7);
   high_score_8m = EEPROM.read(8);
   high_score_9m = EEPROM.read(9);
   high_score_10m = EEPROM.read(10);
}

void write_new_high_score() {
  //write(memory address, information to store)
  EEPROM.write(score_game_time_length, score);
}

long return_particular_high_score(int score_game_time_length) {
  if (score_game_time_length == 1) {
    return high_score_1m;
  }
  else if (score_game_time_length == 2) {
    return high_score_2m;
  }
  else if (score_game_time_length == 3) {
    return high_score_3m;
  }
  else if (score_game_time_length == 4) {
    return high_score_4m;
  }
  else if (score_game_time_length == 5) {
    return high_score_5m;
  }
  else if (score_game_time_length == 6) {
    return high_score_6m;
  }
  else if (score_game_time_length == 7) {
    return high_score_7m;
  }
  else if (score_game_time_length == 8) {
    return high_score_8m;
  }
  else if (score_game_time_length == 9) {
    return high_score_9m;
  }
  else if (score_game_time_length == 10) {
    return high_score_10m;
  }
}

bool compare_score_to_current_high_score() {
  //get high score for current score game time length set to local var for comparison
  long current_high_score_for_that_game_time_length;
  current_high_score_for_that_game_time_length = return_particular_high_score(score_game_time_length);

  //Now that current_high_score_for_that_game_time_length is locally set  to the high score of the same score_game_time_length that was put in the parameters, check how it compares to the current score game's score
  //If there's a new high score:
  if (current_high_score_for_that_game_time_length < score) {
    //overwrite new high score to eeprom at location denoted by score game time length integer
    write_new_high_score();
    //overwrite high score vars to reflect updated high score for that game time length
    read_current_high_scores();

    //Play "new record" track to indicate to user new high score auditorally

    //return true to indicate to lcd print function that the current high score has been exceded.
    return true;
  }
  //If there's not a new high score:
  else {
    return false;
  }
}
