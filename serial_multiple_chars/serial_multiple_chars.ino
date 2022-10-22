/* Receive serial message with an end marker */

const byte numChars = 32;
char receivedChars[numChars];
bool newData = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveWithEndMarker();
  showNewData();
}

void receiveWithEndMarker(void)
{
  static byte idx = 0;
  char endMarker = '\n';
  char receivedChar;

  while (Serial.available() > 0 && newData == false)
  {
    receivedChar = Serial.read();

    if (receivedChar != endMarker)
    {
      receivedChars[idx] = receivedChar;
      idx++;
      if (idx >= numChars)
      {
        idx = numChars - 1;
      }
    }
    else
    {
      receivedChars[idx] = '\0'; /* terminate the string */
      idx = 0;
      newData = true; 
    }
  }
}

void showNewData(void)
{
  if (newData == true)
  {
    Serial.print("New data arrived: ");
    Serial.println(receivedChars);
    newData = false;
  }
}
