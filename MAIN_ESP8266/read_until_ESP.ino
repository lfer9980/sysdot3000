// This function goes and finds a keyword received from the ESP
//  const char keyword1[] = the keyword that this function will look for and return '1' when found
//  int key_size = size of that keyword - sizeof()
//  int timeout_val - timeout if the keword is not found (in milliseconds 5000=5sec)
//  byte mode - if '1', this function will save every byte received to 'sch_data_ESP[]' with length of 'scratch_length' - useful for parsing between keywords

boolean read_until_ESP(const char keyword1[], int key_size, int timeout_val, byte mode) {
  timeout_start_val = millis(); 
  char data_in[20];            
  int scratch_length = 1;  
  key_size--;

  for (byte i = 0; i < key_size; i++) {
    while (!ESP8266.available()) {
      if ((millis() - timeout_start_val) > timeout_val) {
        Serial.println("timeout 1");
        return 0;
      }
    }
    data_in[i] = ESP8266.read(); 
    if (mode == 1) {
      sch_data_ESP[scratch_length] = data_in[i];
      sch_data_ESP[0] = scratch_length;
      scratch_length++;
    }
  }

  while (1) {
    for (byte i = 0; i < key_size; i++) {
      if (keyword1[i] != data_in[i]) {
        break;
      }

      if (i == (key_size - 1)) {
        return 1;
      }
    }

    for (byte i = 0; i < (key_size - 1); i++) {
      data_in[i] = data_in[i + 1];
    }

    while (!ESP8266.available()) {
      if ((millis() - timeout_start_val) > timeout_val) {
        Serial.println("timeout 2");
        return 0;
      }
    } 

    data_in[key_size - 1] = ESP8266.read();

    if (mode == 1) {
      sch_data_ESP[scratch_length] = data_in[key_size - 1];
      sch_data_ESP[0] = scratch_length;
      scratch_length++;
    }
  }
}