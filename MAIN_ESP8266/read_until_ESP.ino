// This function goes and finds a keyword received from the ESP
//  const char keyword1[] = the keyword that this function will look for and return '1' when found
//  int key_size = size of that keyword - sizeof()
//  int timeout_val - timeout if the keword is not found (in milliseconds 5000=5sec)
//  byte mode - if '1', this function will save every byte received to 'scratch_data_from_ESP[]' with length of 'scratch_length' - useful for parsing between keywords
boolean read_until_ESP(const char keyword1[], int key_size, int timeout_val, byte mode) {
  timeout_start_val = millis(); 
  char data_in[20];            
  int scratch_length = 1;  
  key_size--;

  // FILL UP THE BUFFER
  for (byte i = 0; i < key_size; i++) {
    // timing control
    while (!ESP8266.available()) {
      if ((millis() - timeout_start_val) > timeout_val) {
        Serial.println("timeout 1");
        return 0;
      }
    }

    data_in[i] = ESP8266.read(); 
    if (mode == 1) {
      scratch_data_from_ESP[scratch_length] = data_in[i];
      scratch_data_from_ESP[0] = scratch_length;
      scratch_length++;
    }
    } // for i

  // THE BUFFER IS FULL, SO START ROLLING NEW DATA IN AND OLD DATA OUT
  while (1)
  { // stay in here until the keyword found or a timeout occurs
    // run through the entire buffer and look for the keyword
    // this check is here, just in case the first thing out of the ESP was the keyword, meaning the buffer was actually filled with the keyword
    for (byte i = 0; i < key_size; i++)
    {
      if (keyword1[i] != data_in[i]) // if it doesn't match, break out of the search now
        break;                       // get outta here

      if (i == (key_size - 1))
      {           // we got all the way through the keyword without breaking, must be a match!
        return 1; // return a 1 and get outta here!
      }           // if
    }             // for byte i

    // start rolling the buffer
    for (byte i = 0; i < (key_size - 1); i++)
    {                              // keysize-1 because everthing is shifted over - see next line
      data_in[i] = data_in[i + 1]; // so the data at 0 becomes the data at 1, and so on.... the last value is where we'll put the new data
    }                              // for
      // timing control
    while (!ESP8266.available())
    { // same thing as done in the buffer
      if ((millis() - timeout_start_val) > timeout_val)
      {
        Serial.println("timeout 2");
        return 0;
      } // timeout
    }   // while !avail

    data_in[key_size - 1] = ESP8266.read(); // save the new data in the last position in the buffer

    if (mode == 1)
    { // continue to save everything if this is set
      scratch_data_from_ESP[scratch_length] = data_in[key_size - 1];
      scratch_data_from_ESP[0] = scratch_length;
      scratch_length++;
    }
  }
