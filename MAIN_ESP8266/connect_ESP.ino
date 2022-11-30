/*  returns 1 if successful or 0 if not */
boolean connect_ESP() {
  Serial.println("CONNECTING");
  ESP8266.print("AT+CIPSTART=0,\"TCP\",\"www.sysdot3000.000webhostapp.com\",80\r\n");

  if (read_until_ESP(kw_OK, sizeof(kw_OK), 5000, 0)) {
    serial_dump_ESP();              // get rid of whatever else is coming
    Serial.println("CONNECTED");    // yay, connected
    ESP8266.print("AT+CIPSEND=0,"); // send AT+CIPSEND=0, size of payload
    ESP8266.print(payload_size);    // the payload size
    serial_dump_ESP();              // everything is echoed back, so get rid of it
    ESP8266.print("\r\n\r\n");      // cap off that command with a carriage return and new line feed

    if (read_until_ESP(kw_carrot, sizeof(kw_carrot), 5000, 0)) {
      Serial.println("READY TO SEND");
      Serial.println(payload_size);

      /*print the payload to the ESP */
      for (int i = 0; i < payload_size; i++) {
        ESP8266.print(payload[i]);
        Serial.print(payload[i]);
      }

      /*go wait for 'SEND OK' */
      if (read_until_ESP(kw_sendok, sizeof(kw_sendok), 5000, 0)) {
        Serial.println("SENT");
        return 1;
      }
      else {
        Serial.println("FAILED TO SEND");
      }
    }
    else {
      Serial.println("FAILED TO GET >");
    }

  }
  else {
    Serial.println("FAILED TO CONNECT");
    setup_ESP();
  }
}
