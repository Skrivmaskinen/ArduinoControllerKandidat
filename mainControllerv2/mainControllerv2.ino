/*
  Arduino controller.

  The output is a string 
    "xzXZ bB r"
  where:
    xz and XY are joytstick 1 and 2 respectively where
      0 = down,
      1 = neutral,
      2 = up
    bB are button 1 and 2 where
      0 = down,
      1 = up
    r is the rotary encoder where
      0 = spinning one way,
      2 = te other way
  
*/
/*
  ---------------WARNING-----------------
  Some variable names are very bad. They 
  are named one thing and does something else.
  Beware!
  ---------------WARNING-----------------
*/
/*
 * This program is to be run on an Arduino Duemilanove.
 * It handles input for 
 *    2 Joysticks(Analog)
 *    2 Buttons (Analog?)
 *    1 RotaryEncoder (with button)(Digital)
 */


const byte ledPin = 13; //Saves memoµry

/*---------------------JOYSTICK ONE---------------------*/
  // The integer input from the joystick, between 0 & 255(?)
  int greenInput, yellowInput, orangeInput, redInput;
  
  // Conversion from integer input to a bool 
  bool greenDown, yellowDown, orangeDown, redDown;

/*---------------------JOYSTICK TWO---------------------*/
  
  // The integer input from the joystick, between 0 & 255(?)
  int j2NorthInput, j2SouthInput, j2WestInput, j2EastInput;
  
  // Conversion from integer input to a bool 
  bool j2NorthDown, j2SouthDown, j2WestDown, j2EastDown;

/*-------------------------DIAL-------------------------*/
  volatile boolean turnDetected;
  volatile boolean up;
  
  const int PinCLK = 2; //Generates interrupts using CLK signal
  const int PinDT = 3; //Reads DT signals
  const int PinSW = 4; //Used for the push button switch(?)
  
  //Iterrupt service routing is executed when a HIGH or LOW transition is detected on CLK
  void isr() {  
    if (digitalRead(PinCLK))
      up = digitalRead(PinDT);
    else
      up = !digitalRead(PinDT);
  
   turnDetected = true;
  }
//---------------------------------------------------------------------------------------
// pressOn = is the button considered on? pressDown = is the button currently pressed down(comes from digital read) 
bool pressOn, pressDown;


/*---------------------BUTTON RED ONE---------------------*/


  const int RedOnePin = 7;
  bool redOneDown = false;
  
  const int RedTwoPin = 8;
  bool redTwoDown = false;
/*---------------------BUTTON RED TWO---------------------*/
/*---------------------BUTTON WHITE-----------------------*/
/*---------------------BUTTON YELLOW----------------------*/
/*---------------------BUTTON GREEN-----------------------*/



// ----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP//
// the setup routine runs once when you press reset:
void setup() {
  
  /*----------------------BIT-STREAM----------------------*/
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  /*---------------------JOYSTICK ONE---------------------*/
  greenDown = false;
  yellowDown = false;  
  orangeDown= false;
  redDown = false;
    
  /*---------------------JOYSTICK TWO---------------------*/
  j2NorthDown = false;
  j2SouthDown = false;  
  j2WestDown  = false;
  j2EastDown  = false;
  
  /*------------------------DIAL-------------------------*/
  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT);
  attachInterrupt(0, isr, FALLING); //Interrupt 0 is always connected to pin 2

  pressOn = false;
  pressDown = false;
  
}

// the loop routine runs over and over again forever:
void loop() {

  /*-----------------Initialize outputString----------------------*/
  String outputString = "";
  

  // When the button is pressed analogRead(__)== 0, otherwise it oscillated with high numbers.
  /*---------------------JOYSTICK ONE---------------------*/
  // GREEN: read the input on analog pin 0:
  greenInput = analogRead(A0);
  greenDown = (greenInput == 0);
   
  // YELLOW: read the input on analog pin 1:
  yellowInput = analogRead(A1);
  yellowDown = (yellowInput == 0);
  
  // ORANGE: read the input on analog pin 0:
  orangeInput = analogRead(A2);
  orangeDown = (orangeInput == 0);
  
  // RED: read the input on analog pin 1:
  redInput = analogRead(A3);
  redDown = (redInput == 0);  


  // ------------------- Add to outputString:
  
  // x direction
  if(greenDown)
  {
    outputString = outputString + "2";
  } else if (yellowDown)
  {  
    outputString = outputString + "0";
  } else
  {
    outputString = outputString + "1";
  }
  // Create separator
  outputString = outputString + " ";
  
  // z direction
  if(orangeDown)
  {
    outputString = outputString + "2";
  } else if (redDown)
  {  
    outputString = outputString + "0";
  } else
  {
    outputString = outputString + "1";
  }
  
  // Create separator
  outputString = outputString + " ";
  
  /*---------------------JOYSTICK TWO---------------------*/
  // North: read the input on analog pin 4:
  j2NorthInput = analogRead(A5);
  j2NorthDown = (j2NorthInput == 0);
   
  // South: read the input on analog pin 5:
  j2SouthInput = analogRead(A4);
  j2SouthDown = (j2SouthInput == 0);
  
  // West: read the input on analog pin 6:
  j2WestInput = analogRead(A7);
  j2WestDown = (j2WestInput == 0);
  
  // East: read the input on analog pin 7:
  j2EastInput = analogRead(A6);
  j2EastDown = (j2EastInput == 0);


  // ------------------- Add to outputString:
  

  // x direction
  if(j2WestDown)
  {
    outputString = outputString + "2";
  } else if (j2EastDown)
  {  
    outputString = outputString + "0";
  } else
  {
    outputString = outputString + "1";
  }
  
  // Create separator
  outputString = outputString + " ";
  
  // z direction
  if(j2NorthDown)
  {
    outputString = outputString + "2";
  } else if (j2SouthDown)
  {  
    outputString = outputString + "0";
  } else
  {
    outputString = outputString + "1";
  }

  // JOYSTICK TWO
 
  /*------------------BUTTON RED ONE------------------*/  
  
  //Is pushbutton pressed?
  redOneDown = !digitalRead(RedOnePin);
  
  // Create separator
  outputString = outputString + " ";
  // Red one
  if(redOneDown)
  {
    outputString = outputString + "1";
  } else
  {
    outputString = outputString + "0";
  }

  
  /*------------------BUTTON RED TWO------------------*/ 
  
  //Is pushbutton pressed?
  redTwoDown = !digitalRead(RedTwoPin);
  
  // Create separator
  outputString = outputString + " ";
  // Red two
  if(redTwoDown)
  {
    outputString = outputString + "1";
  } else
  {
    outputString = outputString + "0";
  }

  // Create separator
  outputString = outputString + " ";
  
  /*-------------------------DIAL-------------------------*/

  if (turnDetected) { //Is rotation detected
    if (up)
      outputString = outputString + "2";
      //virtualPosition++;
     else
      outputString = outputString + "0";
      //virtualPosition--;

     turnDetected = false; //Do not repeat if (turnDetected) in loop until another rotation is detected
     
     //turnString = "C " + virtualPosition;
     //Serial.println(virtualPosition);
  }else
  {
    
      outputString = outputString + "1";
  }
  /*---------------------BUTTON WHITE-----------------------*/
  /*---------------------BUTTON YELLOW----------------------*/
  /*---------------------BUTTON GREEN-----------------------*/

  /*---------------------COMMON---------------------*/ 
  
  Serial.println(outputString);
  delay(100);        // delay in between reads for stability
}
