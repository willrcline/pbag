//CONTENTS
//send_command_to_MP3_player(command name, number of bytes)

void send_command_to_MP3_player(int8_t command[], int len){
  Serial.println("\nMP3 Command => ");
  for(int i=0;i<len;i++){ MP3.write(command[i]); Serial.print(command[i], HEX); }
  //delay(1000);
}
