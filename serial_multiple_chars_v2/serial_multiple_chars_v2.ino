/* Receive serial message with START and END marker */
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
  receiveWithStartAndEndMarker();
  showNewData();
}

void receiveWithStartAndEndMarker(void)
{
  static bool receiveInProgress = false;
  static byte idx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char receivedChar;

  while (Serial.available() > 0 && newData == false)
  {
    receivedChar = Serial.read();
    
    if (receiveInProgress == true)
    {
      if (receivedChar != endMarker)
      {
        /* receivedChar is part of the message */
        receivedChars[idx] = receivedChar;
        idx++;
        if (idx >= numChars)
        {
          idx = numChars - 1;
        }
      }
      else
      {
        /* end of message */
        receivedChars[idx] = '\0'; /* terminate the string */
        receiveInProgress = false;
        idx = 0;
        newData = true;
      }
    }
    else if (receivedChar == startMarker)
    {
      /* Start of a new message */
      receiveInProgress = true;
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
