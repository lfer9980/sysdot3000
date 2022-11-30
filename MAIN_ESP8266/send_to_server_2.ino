void send_to_server_2() {
  url = location_url;
  url += sysdot_id;
  url += "&un=2";
  url += "&b1=";
  url += String(sent_alarm);

  URL_withPacket = "";
  URL_withPacket = (String("GET ") + url + " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    "Connection: close\r\n\r\n");

  counter = 0;
  payload_size = 0;

  for (int i = 0; i < (URL_withPacket.length()); i++) { 
    payload[payload_size + i] = URL_withPacket[i]; 
    counter++;
  }

  payload_size = counter + payload_size;

  if (connect_ESP()) { 
    if (read_until_ESP(kw_t1, sizeof(kw_t1), 5000, 0)) {
      if (read_until_ESP(kw_dh, sizeof(kw_dh), 5000, 1)) {
        for (int i = 1; i <= (sch_data_ESP[0] - sizeof(kw_dh) + 1); i++) {
          t1_from_ESP[i] = sch_data_ESP[i];
        }
        t1_from_ESP[0] = (sch_data_ESP[0] - sizeof(kw_dh) + 1);

        if (read_until_ESP(kw_b1, sizeof(kw_b1), 5000, 0)) {
          if (read_until_ESP(kw_dh, sizeof(kw_dh), 5000, 1)) {
            for (int i = 1; i <= (sch_data_ESP[0] - sizeof(kw_dh) + 1); i++) {
              d1_from_ESP[i] = sch_data_ESP[i];
            }
            d1_from_ESP[0] = (sch_data_ESP[0] - sizeof(kw_dh) + 1);

            if (read_until_ESP(kw_b2, sizeof(kw_b2), 5000, 0)) {
              if (read_until_ESP(kw_dh, sizeof(kw_dh), 5000, 1)) {
                for (int i = 1; i <= (sch_data_ESP[0] - sizeof(kw_dh) + 1); i++) {
                  d2_from_ESP[i] = sch_data_ESP[i];
                }
                d2_from_ESP[0] = (sch_data_ESP[0] - sizeof(kw_dh) + 1);

                if (read_until_ESP(kw_b3, sizeof(kw_b3), 5000, 0)) {
                  if (read_until_ESP(kw_dh, sizeof(kw_dh), 5000, 1)) { 
                    for (int i = 1; i <= (sch_data_ESP[0] - sizeof(kw_dh) + 1); i++) {
                      d3_from_ESP[i] = sch_data_ESP[i];
                    }
                    d3_from_ESP[0] = (sch_data_ESP[0] - sizeof(kw_dh) + 1);

                    if (read_until_ESP(kw_b4, sizeof(kw_b4), 5000, 0)) {
                      if (read_until_ESP(kw_dh, sizeof(kw_dh), 5000, 1)) {
                        for (int i = 1; i <= (sch_data_ESP[0] - sizeof(kw_dh) + 1); i++) {
                          d4_from_ESP[i] = sch_data_ESP[i];
                        }
                        d4_from_ESP[0] = (sch_data_ESP[0] - sizeof(kw_dh) + 1);

                        if (read_until_ESP(kw_b5, sizeof(kw_b5), 5000, 0)) { 
                          if (read_until_ESP(kw_dh, sizeof(kw_dh), 5000, 1)) {
                            for (int i = 1; i <= (sch_data_ESP[0] - sizeof(kw_dh) + 1); i++) {
                              d5_from_ESP[i] = sch_data_ESP[i];
                            }
                            d5_from_ESP[0] = (sch_data_ESP[0] - sizeof(kw_dh) + 1);

                            if (read_until_ESP(kw_n1, sizeof(kw_n1), 5000, 0)) {
                              if (read_until_ESP(kw_dh, sizeof(kw_dh), 5000, 1)) {
                                for (int i = 1; i <= (sch_data_ESP[0] - sizeof(kw_dh) + 1); i++) { 
                                  d6_from_ESP[i] = sch_data_ESP[i];
                                }
                                d6_from_ESP[0] = (sch_data_ESP[0] - sizeof(kw_dh) + 1);
                                
                                Serial.println("FOUND DATA & DISCONNECTED");
                                serial_dump_ESP();

                                Serial.println("");
                                Serial.print("Time ");

                                if (t1_from_ESP[0] > 3) {
                                  Serial.print(t1_from_ESP[1]);
                                  Serial.print(t1_from_ESP[2]);
                                  Serial.print(":");
                                  Serial.print(t1_from_ESP[3]);
                                  Serial.println(t1_from_ESP[4]);
                                } else {
                                  Serial.print(t1_from_ESP[1]);
                                  Serial.print(":");
                                  Serial.print(t1_from_ESP[2]);
                                  Serial.println(t1_from_ESP[3]);
                                }

                                Serial.print("RECEIVED_BOOL_1 = "); 
                                received_bool_1 = 0;
                                for (int i = 1; i <= d1_from_ESP[0]; i++) {
                                  received_bool_1 = received_bool_1 + ((d1_from_ESP[i] - 48) * multiplier[d1_from_ESP[0] - i]);
                                }
                                Serial.println(received_bool_1);

                                Serial.print("RECEIVED_BOOL_2 = ");
                                received_bool_2 = 0;
                                for (int i = 1; i <= d2_from_ESP[0]; i++) {
                                  received_bool_2 = received_bool_2 + ((d2_from_ESP[i] - 48) * multiplier[d2_from_ESP[0] - i]);
                                }
                                Serial.println(received_bool_2);

                                Serial.print("RECEIVED_BOOL_3 = "); 
                                received_bool_3 = 0;
                                for (int i = 1; i <= d3_from_ESP[0]; i++) {
                                  received_bool_3 = received_bool_3 + ((d3_from_ESP[i] - 48) * multiplier[d3_from_ESP[0] - i]);
                                }
                                Serial.println(received_bool_3);

                                Serial.print("RECEIVED_BOOL_4 = ");
                                received_bool_4 = 0;
                                for (int i = 1; i <= d4_from_ESP[0]; i++) {
                                  received_bool_4 = received_bool_4 + ((d4_from_ESP[i] - 48) * multiplier[d4_from_ESP[0] - i]);
                                }
                                Serial.println(received_bool_4);

                                Serial.print("RECEIVED_BOOL_5 = ");
                                received_bool_5 = 0;
                                for (int i = 1; i <= d5_from_ESP[0]; i++) {
                                  received_bool_5 = received_bool_5 + ((d5_from_ESP[i] - 48) * multiplier[d5_from_ESP[0] - i]);
                                }
                                Serial.println(received_bool_5);

                                Serial.print("RECEIVED_NUMBER_1 = "); 
                                received_cont_temp = 0;
                                for (int i = 1; i <= d6_from_ESP[0]; i++) {
                                  received_cont_temp = received_cont_temp + ((d6_from_ESP[i] - 48) * multiplier[d6_from_ESP[0] - i]);
                                }
                                Serial.println(received_cont_temp);
                                Serial.println("");
                              }
                            }                       // n1
                          }                         //##
                        }                           // b5
                      }                             //##
                    }                               // b4
                  }                                 //##
                }                                   // b3
              }                                     //##
            }                                       // b2
          }                                         //##
        }                                           // b1
      }                                             //##
    }                                               // t1
  }
}
