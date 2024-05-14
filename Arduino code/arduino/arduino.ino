#include <Servo.h>
#include <WiFiNINA.h>

const int sensorTempPin = 1;
const int servo1Pin = 2;
const int ledPin = 3;
const int sensorUltrasonicoTrigPin = 4;
const int sensorUltrasonicoEchoPin = 6;
const int servo2Pin = 5;
const int fotorresistenciaPin = A0;

Servo servo1;
Servo servo2;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;
WiFiClient client;

char server[] = "192.168.0.176";
int port = 5000;

void setup() {
  Serial.begin(9600);
  
  pinMode(sensorTempPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorUltrasonicoTrigPin, OUTPUT);
  pinMode(sensorUltrasonicoEchoPin, INPUT);
  
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  
  while (status != WL_CONNECTED) {
    Serial.print("Conectando a la red WiFi...");
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("Conexión WiFi establecida");
}

void loop() {
  int temperatura = analogRead(sensorTempPin);
  
  if (temperatura > 500) {
    servo1.write(90);
    enviarDatos("servo1=activado");
    delay(1000);
    servo1.write(0);
  }
  
  int luz = analogRead(fotorresistenciaPin);
  
  if (luz < 100) {
    digitalWrite(ledPin, HIGH);
    enviarDatos("led=encendido");
  } else {
    digitalWrite(ledPin, LOW);
    enviarDatos("led=apagado");
  }
  
  if (detectaMovimiento()) {
    servo2.write(90);
    enviarDatos("servo2=activado");
    delay(1000);
    servo2.write(0);
  }
}

bool detectaMovimiento() {
  digitalWrite(sensorUltrasonicoTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorUltrasonicoTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorUltrasonicoTrigPin, LOW);
  
  long duracionEco = pulseIn(sensorUltrasonicoEchoPin, HIGH);
  
  int distancia = duracionEco * 0.034 / 2;

  if (distancia <= 50) {
    Serial.print("Movimiento detectado a ");
    Serial.print(distancia);
    Serial.println(" cm");
    return true;
  } else {
    return false;
  }
}

void enviarDatos(String datos) {
  if (client.connect(server, port)) {
    Serial.println("Conectado al servidor");
    client.print("GET /datos?");
    client.print(datos);
    client.println(" HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Error al conectarse al servidor");
  }
}
