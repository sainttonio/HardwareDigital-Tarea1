// Pines de componentes
const int pinLEDs[3] = {11, 10, 9};       // Rojo, Verde, Azul
const int pinBotones[3] = {4, 3, 2};      // Rojo, Verde, Azul
const int tonos[3] = {261, 329, 392};     
const int pinBuzzer = 8;

int secuencia[100];
int nivel = 0;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(pinLEDs[i], OUTPUT);
    pinMode(pinBotones[i], INPUT_PULLUP);
  }
  pinMode(pinBuzzer, OUTPUT);
  randomSeed(analogRead(A0));
}

void loop() {
  
  secuencia[nivel] = random(0, 3);
  nivel++;


  for (int i = 0; i < nivel; i++) {
    int color = secuencia[i];
    digitalWrite(pinLEDs[color], HIGH);
    tone(pinBuzzer, tonos[color], 300);
    delay(400);
    digitalWrite(pinLEDs[color], LOW);
    delay(200);
  }


  for (int i = 0; i < nivel; i++) {
    int botonPresionado = esperarBoton();

   
    if (botonPresionado != secuencia[i]) {
      secuenciaError();
      nivel = 0; // Reinicia el juego
      delay(1000);
      return;
    }
  }


  delay(800);
}

int esperarBoton() {
  while (true) {
    for (int i = 0; i < 3; i++) {
      if (digitalRead(pinBotones[i]) == LOW) { 
        digitalWrite(pinLEDs[i], HIGH);
        tone(pinBuzzer, tonos[i], 200);
        delay(250);
        digitalWrite(pinLEDs[i], LOW);

       
        while (digitalRead(pinBotones[i]) == LOW);
        delay(50);
        return i;
      }
    }
  }
}

void secuenciaError() {
  tone(pinBuzzer, 130, 600); // Tono grave de error
  for (int i = 0; i < 3; i++) digitalWrite(pinLEDs[i], HIGH);
  delay(600);
  for (int i = 0; i < 3; i++) digitalWrite(pinLEDs[i], LOW);
}
