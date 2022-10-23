// Receive a number as text and convert it to an int

const byte numChars = 8;
char receivedChars[numChars];
boolean newData = false;
int dataNumber = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveWithEndMarker();
  showData();
}

void receiveWithEndMarker(void) {
  static byte idx = 0;
  char endMarker = '\n';
  char receivedChar;

  if (Serial.available() > 0)
  {
    receivedChar = Serial.read();
    if (receivedChar != endMarker)
    {
      receivedChars[idx] = receivedChar;
      idx++;
      if (idx >= numChars)
      {
        idx = numChars-1;
      }
    }
    else
    {
      receivedChars[idx] = '\0'; // terminate the string
      idx = 0;
      newData = true;
    }
  }
}

void showData(void) {
  if (newData == true)
  {
    dataNumber = 0;
    dataNumber = atoi(receivedChars);
    Serial.print("Data Received: ");
    Serial.println(receivedChars);
    Serial.print("Data as Number: ");
    Serial.println(dataNumber);
    newData = false;
  }
}
