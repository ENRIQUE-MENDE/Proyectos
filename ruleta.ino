#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Dirección I2C de la pantalla LCD
#define LCD_ADDRESS 0x27
#define LEFT_PLAYER_SHOOT_PIN 26
#define RIGHT_PLAYER_SHOOT_PIN 27
#define MAX_LIVES 5
#define BUTTON_PRESS_DELAY 300
#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25

// Define la secuencia de pasos para girar 90 grados hacia la izquierda
const int steps_left[][4] = {
  {LOW, HIGH, LOW, LOW},
  {LOW, LOW, HIGH, LOW},
  {LOW, LOW, LOW, HIGH},
  {HIGH, LOW, LOW, LOW}
};
const int stepDelay = 1;

// Define la secuencia de pasos para girar 90 grados hacia la derecha
const int steps_right[][4] = {
  {HIGH, LOW, LOW, LOW},
  {LOW, LOW, LOW, HIGH},
  {LOW, LOW, HIGH, LOW},
  {LOW, HIGH, LOW, LOW}
};

// Inicializar el objeto LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

// Variables para las vidas de los jugadores
int leftPlayerLives = MAX_LIVES;
int rightPlayerLives = MAX_LIVES;

// Función para mostrar el estado de las vidas en la pantalla LCD
void displayLives() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Left Lives: ");
  lcd.print(leftPlayerLives);

  lcd.setCursor(0, 1);
  lcd.print("Right Lives: ");
  lcd.print(rightPlayerLives);
}

void setup() {
  // Inicializar la comunicación serial a 9600 baudios
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Inicializar la pantalla LCD
  lcd.init();
  lcd.backlight();
  // Inicializar pines de disparo como entradas sin pull-up
  pinMode(LEFT_PLAYER_SHOOT_PIN, INPUT);
  pinMode(RIGHT_PLAYER_SHOOT_PIN, INPUT);

  // Limpiar la pantalla LCD y mostrar las vidas iniciales
  displayLives();
}

void loop() {
  // Generar la longitud del código aleatoriamente entre 3 y 7
  int codeLength = random(3, 8);
  int code[codeLength];
  for (int i = 0; i < codeLength; i++) {
    code[i] = random(0, 2);
  }

  Serial.print("[");
  for (int i = 0; i < codeLength; i++) {
    Serial.print(code[i]);
    if (i < codeLength - 1) {
      Serial.print(",");
    }
  }
  Serial.println("]");
  int balaActual=0;
    lcd.clear();

  // Mostrar la información en la pantalla LCD
  int count0 = 0;
  int count1 = 0;
      for (int i = 0; i < codeLength; i++) {
      if (code[i] == 0) {
        count0++;
      } else {
        count1++;
      }
    }

  lcd.setCursor(0, 0);
  lcd.print("Vacios: ");
  lcd.print(count0);

  lcd.setCursor(0, 1);
  lcd.print("Cargados: ");
  lcd.print(count1);
  do{
  
  // Disparo del jugador izquierdo
  if (digitalRead(LEFT_PLAYER_SHOOT_PIN) == HIGH) {
    delay(BUTTON_PRESS_DELAY);
    if (digitalRead(LEFT_PLAYER_SHOOT_PIN) == HIGH) {
          for (int i = 0; i < 512; i++) { // 512 pasos para 90 grados
      for (int j = 0; j < 4; j++) {
        digitalWrite(IN1, steps_left[i % 4][0]);
        digitalWrite(IN2, steps_left[i % 4][1]);
        digitalWrite(IN3, steps_left[i % 4][2]);
        digitalWrite(IN4, steps_left[i % 4][3]);
        delay(stepDelay);
      }
    }
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(500);
      //
      Serial.print(balaActual);
      if (code[balaActual] == 1) {
        // Si el código es 1, el jugador izquierdo pierde una vida
        leftPlayerLives--;
        // Mostrar "BANG" en la pantalla LCD
        lcd.clear();
        lcd.print("BANG!");
        delay(1000);
        // Actualizar el conteo de vidas en la pantalla LCD
        displayLives();
      } else {
        // Mostrar "blank" en la pantalla LCD
        lcd.clear();
        lcd.print("blank");
        delay(1000);
        // Actualizar el conteo de vidas en la pantalla LCD
        displayLives();
      }
      balaActual++;
         for (int i = 0; i < 512; i++) {
          for (int j = 0; j < 4; j++) {
            digitalWrite(IN1, steps_right[i % 4][0]);
            digitalWrite(IN2, steps_right[i % 4][1]);
            digitalWrite(IN3, steps_right[i % 4][2]);
            digitalWrite(IN4, steps_right[i % 4][3]);
            delay(stepDelay);
      }
    } 
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(500);

    }
  }

  // Disparo del jugador derecho
  if (digitalRead(RIGHT_PLAYER_SHOOT_PIN) == HIGH) {
    delay(BUTTON_PRESS_DELAY);
    if (digitalRead(RIGHT_PLAYER_SHOOT_PIN) == HIGH) {
      Serial.print(balaActual);
          // Girar 90 grados hacia la derecha
    for (int i = 0; i < 512; i++) { // 512 pasos para 90 grados
      for (int j = 0; j < 4; j++) {
        digitalWrite(IN1, steps_right[i % 4][0]);
        digitalWrite(IN2, steps_right[i % 4][1]);
        digitalWrite(IN3, steps_right[i % 4][2]);
        digitalWrite(IN4, steps_right[i % 4][3]);
        delay(stepDelay);
      }
    }
    // Detener el motor después de girar 90 grados
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

      if (code[balaActual]==1) {
        // Si el código es 0, el jugador derecho pierde una vida
        rightPlayerLives--;
        // Mostrar "BANG" en la pantalla LCD
        lcd.clear();
        lcd.print("BANG!");
        delay(1000);
        // Actualizar el conteo de vidas en la pantalla LCD
        displayLives();
      } else {
        // Mostrar "blank" en la pantalla LCD
        lcd.clear();
        lcd.print("*blank*");
        delay(1000);
        // Actualizar el conteo de vidas en la pantalla LCD
        displayLives();
      }
          // Girar 90 grados hacia la izquierda para volver a la posición inicial
    for (int i = 0; i < 512; i++) {
      for (int j = 0; j < 4; j++) {
        digitalWrite(IN1, steps_left[i % 4][0]);
        digitalWrite(IN2, steps_left[i % 4][1]);
        digitalWrite(IN3, steps_left[i % 4][2]);
        digitalWrite(IN4, steps_left[i % 4][3]);
        delay(stepDelay);
      }
    }
    // Detener el motor después de girar 90 grados hacia la izquierda
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(500);
      balaActual++;
    }
  }

  // Verificar si alguno de los jugadores se quedó sin vidas
  if (leftPlayerLives <= 0 || rightPlayerLives <= 0) {
    lcd.clear();
    if (leftPlayerLives <= 0) {
      lcd.print("Right Player Wins!");
    } else {
      lcd.print("Left Player Wins!");
    }
    // Bucle infinito para detener el juego
    
    while (true) {
      // No hacer nada
    }
  }

  // Pequeña pausa antes de iniciar la siguiente ronda
  delay(100);
  }while(balaActual+1<=codeLength);
}