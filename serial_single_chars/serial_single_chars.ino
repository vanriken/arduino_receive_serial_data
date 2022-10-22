char receivedChar;
bool newData = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveOneChar();
  showNewData();
}

void receiveOneChar(void)
{
  /* Get the number of bytes (characters) available 
   * for reading from the serial port. 
   * This is data that’s already arrived 
   * and stored in the serial receive buffer (which holds 64 bytes).
   */
  if (Serial.available() > 0) 
  {
    receivedChar = Serial.read();
    newData = true;
  }
}

void showNewData(void)
{
  if (newData == true)
  {
    Serial.print("A new char has arrived: ");
    Serial.println(receivedChar);
    newData = false;
  }
}
