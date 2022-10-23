// Receive with start and end markers combined with parsing

#define WELCOME_MSG "This demo expects 3 pieces of data: text, integer and a float."
#define INSTRUCTIONS "Enter data in this style <HelloWorld, 12, 24.7>" 

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars]; // temporary array used when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;

boolean newData = false;



void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(WELCOME_MSG);
  Serial.println(INSTRUCTIONS);
  Serial.println();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  receiveWithStartAndEndMarkers();
  if (newData == true)
  {
    /* temporary copy is neccesary to protect the original
     * data because strtok() used in parseData() replaces 
     * the commas with '\0' */
    strcpy(tempChars, receivedChars);
    parseData();
    showParsedData();
    newData = false;
  }
}

void receiveWithStartAndEndMarkers(void) 
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
        receivedChars[idx] = receivedChar;
        idx++;
        if (idx >= numChars)
        {
          idx = numChars - 1;
        }
      }
      else
      {
        receivedChars[idx] = '\0';
        receiveInProgress = false;
        idx = 0;
        newData = true;
      }
    }
    else if (receivedChar == startMarker)
    {
      receiveInProgress = true;
    }
  }
}

void parseData()
{
  /* split the received data into parts */
    
  /* INFO ON strtok() 
   * prototype: char *strtok(char *str, const char *delim)
   * 
   * The strtok algorithm scans through the string str looking for delim chars.
   * If a delim char is found, the chars up to the delim char 
   * are returned as a char pointer (string).
   * In subsequent calls, the str parameter is set to NULL,
   * so that the algorithm knows to obtain the next token. */
 
  char *tokenPtr;  
  
  tokenPtr = strtok(tempChars, ",");  // get the first part, the string
  strcpy(messageFromPC, tokenPtr);

  tokenPtr = strtok(NULL, ",");  // continues where the previous call left off
  integerFromPC = atoi(tokenPtr);  // convert this part to an integer

  tokenPtr = strtok(NULL, ",");
  floatFromPC = atof(tokenPtr);  // convert this part to a float
}

void showParsedData(void) {
  Serial.print("Received Chars: ");
  Serial.println(receivedChars);
  Serial.print("Temp Chars: ");
  Serial.println(tempChars);
  Serial.print("Message: ");
  Serial.println(messageFromPC);
  Serial.print("Integer: ");
  Serial.println(integerFromPC);
  Serial.print("Float: ");
  Serial.println(floatFromPC);
}
