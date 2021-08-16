
////MPU mod
void update_orientation_data() {
//    Serial.print('\n');
//    Serial.print("Orientation data update called");
//    Serial.print('\n');
    raw_yaw = mpu.getYaw();
    raw_pitch = mpu.getPitch();
    raw_roll = mpu.getRoll();

    alpha= mpu.getEulerX();
    gamma=mpu.getEulerY();
    beta=mpu.getEulerZ();

    // Adjusted Euler angles for pbag
    //note that if greater than 90 degrees tilt, unpredictable things happen(very high reading or negative). Not an issue since bag will rarely tilt beyond.
    pitch = abs(raw_pitch);
    roll = abs(raw_roll - 90);
}

void serial_print_accel_data() {
  Serial.print(F("Roll: "));
  Serial.println(angle_roll_output);

  
  Serial.print(F("Pitch: "));
  Serial.println(angle_pitch_output);
}
