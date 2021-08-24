//#include "MPU9250.h"
//#include "eeprom_utils.h"
//
//MPU9250 mpu;
//float pitch;
//float roll;
////vis stands for visualization. These values are used in "Processing" code.
//float vis_pitch;
//float vis_roll;
//float raw_yaw;
//float raw_pitch;
//float raw_roll;
//float alpha;
//float beta;
//float gamma;
//
//void setup() {
//    Serial.begin(115200);
//    Wire.begin();
//    delay(2000);
//
//    if (!mpu.setup(0x69)) {  // change to your own address
//        while (1) {
//            Serial.println("MPU connection failed. Please check your connection");
//            delay(5000);
//        }
//    }
//    loadCalibration();
//    
//}
//
//void loop() {
//    if (mpu.update()) {
//        static uint32_t prev_ms = millis();
//        if (millis() > prev_ms + 25) {
//            raw_yaw = mpu.getYaw();
//            raw_pitch = mpu.getPitch();
//            raw_roll = mpu.getRoll();
//
//            alpha= mpu.getEulerX();
//            gamma=mpu.getEulerY();
//            beta=mpu.getEulerZ();
//
//            // Adjusted Euler angles for pbag
//            //note that if greater than 90 degrees tilt, unpredictable things happen(very high reading or negative). Not an issue since bag will rarely tilt beyond.
//            pitch = abs(raw_pitch);
//            roll = abs(raw_roll - 90);
//
//            // Non-absolute value euler angles for visualization
//            vis_pitch = raw_pitch;
//            vis_roll = raw_roll - 90;
//
//
//           //The numbers from this printout are interpreted by Processing software to produce visualization
//            Serial.print(vis_pitch,2);
//            Serial.print("/");
//            Serial.println(vis_roll,2);
//
//            //The numbers from this printout are what gets used by pbag
//            /*
//            Serial.print("pitch: ");
//            Serial.print(pitch,2);
//            Serial.print(" ");
//            Serial.print("roll: ");
//            Serial.print(roll,2);
//            */
//            
//            prev_ms = millis();
//        }
//    }
//}
