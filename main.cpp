

const uint8_t pinLeds[3] = {11, 10, 9};   
const uint8_t pinBuzzer = 8;
const uint8_t pinBotones[3] = {4, 3, 2};  

const uint16_t tonosLeds[3] = {262, 330, 392}; 
const uint16_t tonoExito = 523;
const uint16_t tonoError = 130;

const uint8_t MAX_NIVEL = 30;
uint8_t secuencia[MAX_NIVEL];
uint8_t nivelActual = 1;

void setup() {
  for (uint8_t i = 0; i < 3; i++) {
    pinMode(pinLeds[i], OUTPUT);
    pinMode(pinBotones[i], INPUT_PULLUP);
    digitalWrite(pinLeds[i], LOW);
  }
  pinMode(pinBuzzer, OUTPUT);
  noTone(pinBuzzer);
  randomSeed(analogRead(A0));
  delay(1000);
}

void loop() {
  generarSecuencia();
  reproducirSecuencia();

  if (obtenerRespuestaJugador()) {
    secuenciaExito();
    nivelActual++;
    delay(800);
  } else {
    secuenciaError();
    nivelActual = 1;
    delay(1000);
  }
}

void generarSecuencia() {
  secuencia[nivelActual - 1] = random(0, 3);
}

void reproducirSecuencia() {
  delay(500);
  for (uint8_t i = 0; i < nivelActual; i++) {
    uint8_t color = secuencia[i];
    activarSalida(color, 350);
    delay(150);
  }
}

void activarSalida(uint8_t indice, uint16_t duracion) {
  digitalWrite(pinLeds[indice], HIGH);
  tone(pinBuzzer, tonosLeds[indice]);
  delay(duracion);
  noTone(pinBuzzer);
  digitalWrite(pinLeds[indice], LOW);
}

bool obtenerRespuestaJugador() {
  for (uint8_t paso = 0; paso < nivelActual; paso++) {
    int botonPresionado = esperarPulsacion();
    if (botonPresionado != secuencia[paso]) {
      return false;
    }
  }
  return true;
}

int esperarPulsacion() {
  while (true) {
    for (uint8_t i = 0; i < 3; i++) {
      if (digitalRead(pinBotones[i]) == LOW) {
        delay(30); // Antirrebote basico
        if (digitalRead(pinBotones[i]) == LOW) {
          // Enciende luz y sonido mientras se presiona
          digitalWrite(pinLeds[i], HIGH);
          tone(pinBuzzer, tonosLeds[i]);
      
          while (digitalRead(pinBotones[i]) == LOW);
        
          noTone(pinBuzzer);
          digitalWrite(pinLeds[i], LOW);
          delay(50); 
          return i;
        }
      }
    }
  }
}

void secuenciaExito() {
  tone(pinBuzzer, tonoExito);
  delay(200);
  noTone(pinBuzzer);
  delay(50);
  tone(pinBuzzer, (uint16_t)(tonoExito * 1.25));
  delay(300);
  noTone(pinBuzzer);
}

void secuenciaError() {
  tone(pinBuzzer, tonoError);
  for (uint8_t i = 0; i < 3; i++) digitalWrite(pinLeds[i], HIGH);
  delay(600);
  noTone(pinBuzzer);
  for (uint8_t i = 0; i < 3; i++) digitalWrite(pinLeds[i], LOW);
  delay(300);
}
