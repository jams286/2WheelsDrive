// Codigo generado por ChatGPT en su mayoria, con algunos ajustes acordes a conexiones fisicas. 
#include <Arduino.h>
#include <PS4Controller.h>


// Pines L298N conectados al ESP32
#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25
#define ENA 13  // PWM para motor A
#define ENB 12  // PWM para motor B

// Canales PWM (de 0 a 15 en ESP32)
// Revisar en documentacion a que canal pertenece el pin
#define ENA_CH 4 
#define ENB_CH 5

// Metodos para mostrar mensaje cuando DS4 se conecta o se desconecta
void onConnect();
void onDisConnect();

void setup() {
  Serial.begin(115200);    
  // Configuración de pines digitales
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configuración PWM
  ledcSetup(ENA_CH, 1000, 8);  // canal, frecuencia (Hz), resolución (bits)
  ledcSetup(ENB_CH, 1000, 8);
  ledcAttachPin(ENA, ENA_CH);
  ledcAttachPin(ENB, ENB_CH);

  PS4.attachOnConnect(onConnect);  
  PS4.attachOnDisconnect(onDisConnect);   
  PS4.begin();
  Serial.println("Esperando conexión del control PS4...");
}

void loop() {
  if (PS4.isConnected()) {
    // Leer joysticks
    int throttle = -PS4.LStickY(); // Velocidad (adelante/atrás)
    int turn     = PS4.RStickX();  // Giro (izquierda/derecha)

    // Mapear valores de -128~127 a -255~255
    throttle = map(throttle, -128, 127, -255, 255);
    turn     = map(turn,     -128, 127, -255, 255);

    int leftPWM, rightPWM;

    if (abs(throttle) < 20) {
      // Giro en el lugar (detenido)
      leftPWM  = -turn;
      rightPWM = turn;
    } else {
      // Movimiento con giro suave
      float turnScale = 1.0 - (abs(throttle) / 255.0) * 0.6;
      turn = -turn * turnScale; // Invertimos giro aquí
      leftPWM  = throttle - turn;
      rightPWM = throttle + turn;
    }

    // Limitar valores entre -255 y 255
    leftPWM  = constrain(leftPWM,  -255, 255);
    rightPWM = constrain(rightPWM, -255, 255);

    // MOTOR IZQUIERDO
    if (leftPWM >= 0) {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }

    // MOTOR DERECHO
    if (rightPWM >= 0) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    } else {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }

    // Aplicar PWM absoluto
    ledcWrite(ENA_CH, abs(leftPWM));
    ledcWrite(ENB_CH, abs(rightPWM));

    // Debug
    Serial.printf("Throttle: %d | Turn: %d | L: %d | R: %d\n", throttle, turn, leftPWM, rightPWM);
  }
}
void onConnect()
  {    
    Serial.println("Connected!.");
  }
 
  void onDisConnect() 
  {    
    Serial.println("Disconnected!.");    
  } 