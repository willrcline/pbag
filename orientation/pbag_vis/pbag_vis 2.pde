/*
    Arduino and ADXL345 Accelerometer - 3D Visualization Example 
     by Dejan, https://howtomechatronics.com
*/

import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

PShape pbag;

Serial myPort;

String data="";
float roll, pitch;

void setup() {
  size (960, 640, P3D);
  myPort = new Serial(this, "/dev/cu.usbserial-1410", 115200); // starts the serial communication
  myPort.bufferUntil('\n');
  
  //pbag = loadShape("red_cylinder.obj");
}

void draw() {
  translate(width/2, height/2, 0);
  background(33);
  textSize(22);
  text("Roll: " + int(roll) + "     Pitch: " + int(pitch), -100, 265);
  
  print(roll);
  print(pitch);

  // Rotate the object
  rotateX(radians((roll+90)*-1));
  rotateY(radians(pitch));
  
  // 3D 0bject
  //textSize(30);  
  box (80, 80, 380); // Draw box
  fill(230,0,0);
  
  //(shape file, x, y, width, height)
  //shape(pbag, 0, 0, 0, 250);
  //textSize(25);
  //text("Punching Bag", -183, 10, 101);

  //delay(10);
  //println("ypr:\t" + angleX + "\t" + angleY); // Print the values to check whether we are getting proper values
}

// Read data from the Serial Port
void serialEvent (Serial myPort) { 
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('\n');

  // if you got any bytes other than the linefeed:
  if (data != null) {
    data = trim(data);
    // split the string at "/"
    String items[] = split(data, '/');
    if (items.length > 1) {

      //--- Roll,Pitch in degrees
      roll = float(items[1]);
      pitch = float(items[0]);
      
    }
  }
}
