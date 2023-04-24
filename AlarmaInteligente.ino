#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>  
#include <ArduinoJson.h>

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client2(espClient);


const int pinBuzzer = 15;
const int smokeA0 = 32;
const int sensorPIR = 34; // Pin donde está conectada la entrada del sensor PIR
const int luz = 13;// Pin para luz de 110 o 220 V( Con módulo relay)
const int botonPin = 5;  // El número de pin del botón

#define DHTPIN 14


//Declaramos el tipo de sensor (DHT11)
#define DHTTYPE DHT11
//Inicializamos el sensor
DHT dht(DHTPIN, DHTTYPE);
// Inicializamos el display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Replace with your network credentials
const char* ssid = "JMSAXD";
const char* password = "linux123";

// Initialize Telegram BOT
#define BOTtoken "5908628911:AAF4oOIzh-T7Yc7ALCNUWzXOPVnHNwTZXNc"  
#define CHAT_ID "6060843959"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int conteo = 0;
String mensaje = "";
String conteoString = "";
int PIR = 0;
int estadoBoton = 0;
bool alarma = false;

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int ledPin = 2;
bool ledState = LOW;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Usuario no Autorizado!!!", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Bienvenido, " + from_name + ".\n";
      welcome += "Usa los siguientes comandos para controlar tu microcontrolador.\n\n";
      welcome += "/activate Activará la alarma \n";
      welcome += "/deactivate Desactivará la alarma \n";
      welcome += "/on Encenderá la alarma \n";
      welcome += "/off Apagará la alarma \n";
      welcome += "/state Muestra el estado del LED\n";
      bot.sendMessage(chat_id, welcome, "");
    }
    if (text == "/activate") {
      alarma = true;
      bot.sendMessage(chat_id, "Alarma activada!!!", "");
    }
    if (text == "/deactivate") {
      alarma = false;
      bot.sendMessage(chat_id, "Alarma desactivada!!!", "");
    }
    if (text == "/on") {
      bot.sendMessage(chat_id, "Alarma Encendida", "");
      ledState = HIGH;
      digitalWrite(luz, HIGH);//Encendemos la luz
      digitalWrite(pinBuzzer, HIGH); // Encendemos el buzzer
      digitalWrite(ledPin, ledState);
    }
    
    if (text == "/off") {
      bot.sendMessage(chat_id, "Alarma Apagada", "");
      ledState = LOW;
      digitalWrite(luz, LOW);//Encendemos la luz
      digitalWrite(pinBuzzer, LOW); // Encendemos el buzzer
      digitalWrite(ledPin, ledState);
    }
    
    if (text == "/state") {
      if (digitalRead(ledPin)){
        bot.sendMessage(chat_id, "La alarma esta encendida", "");
      }
      else{
        bot.sendMessage(chat_id, "La alarma esta apagada", "");
      }
    }
  }
}

void setup() {

  Serial.begin(9600);
  dht.begin();
   // Inicializamos la comunicación con el display OLED
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Dirección del dispositivo OLED: 0x3C

  // Borramos el contenido anterior del display OLED
  display.clearDisplay();

  // Establecemos el tamaño del texto y el color
  display.setTextSize(1.9);
  display.setTextColor(WHITE);

  // Escribimos un mensaje en el display OLED
  display.setCursor(0, 0);
  display.println("Hola, mundo!");
  display.display();

  // Activamos el resistor de PULLUP para la entrada sensor PIR
  pinMode(sensorPIR, INPUT_PULLUP);
  pinMode(luz, OUTPUT);
  pinMode(smokeA0, INPUT);
  
  // Configuramos el pin del buzzer como salida
  pinMode(pinBuzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  pinMode(botonPin, INPUT); // Configuramos el pin del botón como entrada
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wifi..");
  }
  Serial.print("Dirección ip: ");
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  client2.setServer("192.168.0.64",1883);
  client2.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length]='\0';
  String val = String((char*)payload);
  Serial.println(val);
}

void loop() {

     if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

 if (!client2.connected()) {
    if (client2.connect("ESP32")) {
      Serial.println("Conexión exitosa!!!");
    }
  }
  estadoBoton = digitalRead(botonPin);  // Leemos el estado del botón
  int analogSensor = analogRead(smokeA0);
  PIR = digitalRead(sensorPIR);//Leemos el estado del del sensor PIR
  int tem = dht.readTemperature(); // Leemos el estado del sensor de temperatura
  int hum = dht.readHumidity(); // // Leemos el estado del sensor de humedad

   Serial.print("MQ-2: ");
  Serial.println(analogSensor);
  Serial.print("PIR: ");
  Serial.println(PIR);
  Serial.print("Boton: ");
  Serial.println(estadoBoton);
  if(alarma){
    if(PIR == 1 || analogSensor>500 || estadoBoton == LOW){
      digitalWrite(luz, HIGH);//Encendemos la luz
      digitalWrite(pinBuzzer, HIGH); // Encendemos el buzzer
      Serial.println("Alarma Encendida!");
      conteo = conteo + 1;//Incremento en el contador de movimientos detectados
      conteoString = String(conteo);//Lo convertimos a una cadena
      String pirString = String(PIR);//Lo convertimos a una cadena
      String mq2String = String(analogSensor);//Lo convertimos a una cadena
      String btnString = String(estadoBoton);//Lo convertimos a una cadena
      mensaje = "Cantidad de veces que se ha activado el alarma: " + conteoString + "\n" +
      "PIR: " + pirString + "\n" +
      "Boton: " + btnString + "\n" +
      "MQ-2: " + mq2String;//Concatenamos ambas cadenas
   
      bot.sendMessage(CHAT_ID, mensaje, "");
      delay(10000);//mantensmos la luz encendida este tiempo
     digitalWrite(luz, LOW);//Luego la apagamos
    
      digitalWrite(pinBuzzer, LOW);  // Apagamos el buzzer
      Serial.println("Luz apagada!");
      PIR = 0;//Asignamos el valor "0" a la variable PIR para que deje de cumplirse la condición
    }
  }

//Variables char para poder enviar los datos
  char tem_str[10]; 
  char hum_str[10]; 
  char btn_str[10];
  char mq2_str[10];
  char pir_str[10];

// Convertir las variables de tipo int a char utilizando sprintf()
  sprintf(tem_str, "%d", tem);
  sprintf(hum_str, "%d", hum);
  sprintf(btn_str, "%d", estadoBoton);
  sprintf(mq2_str, "%d", analogSensor);
  sprintf(pir_str, "%d", PIR);
  
// Publicar las variables en MQTT
client2.publish("tem", tem_str);
client2.publish("hum", hum_str);
client2.publish("btn", btn_str);
client2.publish("mq2", mq2_str);
client2.publish("pir", pir_str);
delay(1000);

  // Leemos la humedad relativa
  float humedad = dht.readHumidity();
  // Leemos la temperatura en grados Celsius
  float temperatura = dht.readTemperature();

  // Si no se puede leer la temperatura o la humedad, mostramos un mensaje de error
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error al leer el sensor DHT11");
    return;
  }
    // Mostramos los valores de la temperatura y la humedad en la consola
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Humedad:");
  display.println(humedad);
  display.setCursor(0, 30);
  display.println("Temperatura:");
  display.println(temperatura);
  display.display();
}
