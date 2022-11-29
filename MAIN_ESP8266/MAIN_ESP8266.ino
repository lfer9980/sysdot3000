/*
  Estructura de la base de datos
  `id` int(5) NOT NULL,
  `PASSWORD` int(5) NOT NULL,
  `RECEIVED_BOOL1` int(1) NOT NULL,
  `RECEIVED_BOOL2` int(1) NOT NULL,
  `RECEIVED_BOOL3` int(1) NOT NULL,
  `RECEIVED_BOOL4` int(1) NOT NULL,
  `RECEIVED_BOOL5` int(1) NOT NULL,
  `SENT_TEMP` int(5) NOT NULL,
  `SENT_ALARM` int(1) NOT NULL,
  `RECEIVED_CONT_TEMP` int(5) NOT NULL
 */

#include <SoftwareSerial.h>
#include <avr/power.h>
#include <dht.h>

dht DHT;
#define DHT11_PIN 9
/* Conecta el pin TX del ESP a este pin RX del Arduino */
#define ESP8266_RX 10
/* Conecta el pin TX del Arduino al pin RX del ESP */
#define ESP8266_TX 11

int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4 = 5;
int LED5 = 6;
int LED_ALARM = 7;
int pin_dht = A0;

/* datos de conexión */

const char SSID_ESP[] = "MiFibra-4132"; // Give EXACT name of your WIFI
const char SSID_KEY[] = "vzP5anY5";     // Add the password of that WIFI connection
const char *host = "sysdot3000.000webhostapp.com/";
String NOOBIX_id = "99999";
String NOOBIX_password = "12345";
String location_url = "/TX.php?id=";

/* variables usadas en el codigo */
String url = "";
String URL_withPacket = "";
unsigned long multiplier[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

/* modos del ESP */
const char CWMODE = '1'; // CWMODE 1=STATION, 2=APMODE, 3=BOTH
const char CIPMUX = '1'; // CWMODE 0=Single Connection, 1=Multiple Connections

/* variables para conexión con el ESP */
boolean setup_ESP();
boolean read_until_ESP(const char keyword1[], int key_size, int timeout_val, byte mode);

void timeout_start();
boolean timeout_check(int timeout_ms);

void serial_dump_ESP();
boolean connect_ESP();

void connect_webhost();
unsigned long timeout_start_val;

char scratch_data_from_ESP[20]; // first byte is the length of bytes
char payload[200];
byte payload_size = 0, counter = 0;
char ip_address[16];

/* Variable to SEND to the DATABASE */
bool sent_alarm = 0; /*  alarma estado */
float sent_temp = 0; /* lectura dht11 */

/* Variable RECEIVED from the DATABASE */
bool received_bool_1 = 0; /* switches digitales */
bool received_bool_2 = 0;
bool received_bool_4 = 0;
bool received_bool_3 = 0;
bool received_bool_5 = 0;
int received_cont_temp = 0; /* valor del control alarma */

/* Store received chars in this variables */
char t1_from_ESP[5]; // For time from web
char d1_from_ESP[2]; // For received_bool_1
char d2_from_ESP[2]; // For received_bool_2
char d3_from_ESP[2]; // For received_bool_3
char d4_from_ESP[2]; // For received_bool_4
char d5_from_ESP[2]; // For received_bool_5
char d9_from_ESP[6]; // For received_cont_temp

/* DEFINE KEYWORDS HERE */
const char keyword_OK[] = "OK";
const char keyword_Ready[] = "Ready";
const char keyword_no_change[] = "no change";
const char keyword_blank[] = "#&";
const char keyword_ip[] = "192.";
const char keyword_rn[] = "\r\n";
const char keyword_quote[] = "\"";
const char keyword_carrot[] = ">";
const char keyword_sendok[] = "SEND OK";
const char keyword_linkdisc[] = "Unlink";

const char keyword_b1[] = "b1";
const char keyword_n1[] = "n1";
const char keyword_doublehash[] = "##";

SoftwareSerial ESP8266(ESP8266_RX, ESP8266_TX);

void setup() {
  // Pin Modes for ESP TX/RX
  pinMode(ESP8266_RX, INPUT);
  pinMode(ESP8266_TX, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);

  ESP8266.begin(9600); // default baudrate for ESP
  ESP8266.listen();    // not needed unless using other software serial instances
  Serial.begin(9600);  // for status and debug

  delay(2000); // delay before kicking things off
  setup_ESP(); // go setup the ESP
}

void loop() {
  /* leer temperatura del sensor */
  int readData = DHT.read11(DHT11_PIN);
  sent_temp = DHT.temperature;

  /* si la temperatura es mayor a la del control, enviar un true a web */
  if (sent_temp > received_cont_temp) {
    sent_alarm = 1;
  }
  else {
    sent_alarm = 0;
  }

  send_to_server_1();
  /* prendemos / apagamos de acuerdo a datos del servidor*/
  digitalWrite(LED1, received_bool_1);
  digitalWrite(LED2, received_bool_2);
  digitalWrite(LED3, received_bool_3);
  digitalWrite(LED4, received_bool_4);
  digitalWrite(LED5, received_bool_5);
  digitalWrite(LED_ALARM, sent_alarm);

  delay(500);
  send_to_server_5();

  digitalWrite(LED1, received_bool_1);
  digitalWrite(LED2, received_bool_2);
  digitalWrite(LED3, received_bool_3);
  digitalWrite(LED4, received_bool_4);
  digitalWrite(LED5, received_bool_5);

  delay(500);
}
