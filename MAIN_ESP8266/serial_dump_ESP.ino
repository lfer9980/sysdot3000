
/* leer todo lo que sale del búfer de serie y lo que viene y deshacerse de él */
void serial_dump_ESP()
{
  char temp;
  while (ESP8266.available())
  {
    temp = ESP8266.read();
    delay(1);
  }
}
