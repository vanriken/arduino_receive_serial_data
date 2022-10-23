// Receiving binary data

const byte numBytes = 32;
byte receivedBytes[numBytes];
byte numReceived = 0;

bool newData = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveBytesWithStartAndEndMarkers();
  showNewData();
}

void receiveBytesWithStartAndEndMarkers(void)
{
  static bool receiveInProgress = false;
  static byte idx = 0;
  byte startMarker = 0x3C;
  byte endMarker = 0x3E;
  byte receivedByte;

  while (Serial.available() > 0 && newData == false)
  {
    receivedByte = Serial.read();

    if (receiveInProgress == true)
    {
      if (receivedByte != endMarker)
      {
        receivedBytes[idx] = receivedByte;
        idx++;
        if (idx >= numBytes)
        {
          idx = numBytes - 1;
        }
      }
      else
      {
        receivedBytes[idx] = '\0';  // terminate the string
        receiveInProgress = false;
        numReceived = idx;  // save the number for use when printing
        idx = 0;
        newData = true;
      }
    }
    else if (receivedByte == startMarker)
    {
      receiveInProgress = true;
    }
  }
}

void showNewData(void)
{
  if (newData == true)
  {
    /* print received bytes as HEX */
    Serial.print("Received data (HEX): ");
    for (byte n = 0; n < numReceived; n++)
    {
      Serial.print(receivedBytes[n], HEX);
      Serial.print(' ');
    }
    Serial.println();

    /* print received bytes as BIN */
    Serial.print("Received data (BIN): ");
    for (byte n = 0; n < numReceived; n++)
    {
      Serial.print(receivedBytes[n], BIN);
      Serial.print(' ');
    }
    Serial.println();

    /* print received bytes as ascii chars */
    Serial.print("Received data (ASCII): ");
    for (byte n = 0; n < numReceived; n++)
    {
      Serial.print((char) receivedBytes[n]);
      Serial.print(' ');
    }
    Serial.println();
    newData = false;
  }
}
