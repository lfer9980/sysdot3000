/*
  Estructura de la base de datos
  `id` int(5) NOT NULL,
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
#define ESP8266_RX 10
#define ESP8266_TX 11

int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4 = 5;
int LED5 = 6;
int LED_ALARM = 7;

/* datos de conexión */
const char SSID_ESP[] = "IZZI FERNANDEZ"; 
const char SSID_KEY[] = "123498760";
const char *host = "sysdot3000.000webhostapp.com/";
String sysdot_id = "99999";
String sysdot_password = "12345";
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

char sch_data_ESP[20];
char payload[200];
byte payload_size = 0, counter = 0;
char ip_address[16];

/* Variable to SEND to the DATABASE */
bool sent_alarm = 0; /*  alarma estado */
float sent_temp = 0; /* lectura dht11 */

/* Variable RECEIVED from the DATABASE */
bool received_bool_1 = 0; /* switches digitales */
bool received_bool_2 = 0;
bool received_bool_3 = 0;
bool received_bool_4 = 0;
bool received_bool_5 = 0;
int received_cont_temp = 0; /* valor del control alarma */

/* Store received chars in this variables */
char t1_from_ESP[5]; // For time from web
char d1_from_ESP[2]; // For received_bool_1
char d2_from_ESP[2]; // For received_bool_2
char d3_from_ESP[2]; // For received_bool_3
char d4_from_ESP[2]; // For received_bool_4
char d5_from_ESP[2]; // For received_bool_5
char d6_from_ESP[6]; // For received_cont_temp

/* DEFINE KEYWORDS HERE */
const char kw_OK[] = "OK";
const char kw_rn[] = "\r\n";
const char kw_carrot[] = ">";
const char kw_sendok[] = "SEND OK";


const char kw_t1[] = "t1";
const char kw_b1[] = "b1";
const char kw_b2[] = "b2";
const char kw_b3[] = "b3";
const char kw_b4[] = "b4";
const char kw_b5[] = "b5";
const char kw_n1[] = "n1"; // received_cont_temp
const char kw_dh[] = "##";

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

  ESP8266.begin(9600);
  ESP8266.listen();
  Serial.begin(9600);

  delay(2000);
  setup_ESP();
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
  send_to_server_2();

  digitalWrite(LED1, received_bool_1);
  digitalWrite(LED2, received_bool_2);
  digitalWrite(LED3, received_bool_3);
  digitalWrite(LED4, received_bool_4);
  digitalWrite(LED5, received_bool_5);

  delay(500);
}
