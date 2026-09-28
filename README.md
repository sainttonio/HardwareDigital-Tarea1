# HardwareDigital-Tarea1

# Tarea 1: Entradas y Salidas Digitales 

**Asignatura:** Hardware Digital (CIN-212 / ISF-215)  
**Institución:** Universidad de Valparaíso  
**Profesor:** Prof. Jhon Pilataxi  
**Autor:** Sebastián Valenzuela  

---

## 📋 Descripción del Proyecto

Este proyecto consiste en la implementación y simulación de un juego interactivo de memoria utilizando la plataforma **Arduino UNO R3**. 

El sistema genera secuencias aleatorias de luces y tonos sonoros mediante LEDs y un zumbador piezoeléctrico. El jugador debe memorizar y replicar la secuencia utilizando tres pulsadores configurados con resistencia interna de pull-up (`INPUT_PULLUP`) y filtrado por software contra rebotes de contactos (*debouncing*).

---

## 🛠️ Componentes y Mapeo de Hardware

El proyecto utiliza los siguientes componentes y distribución de pines en el Arduino UNO R3:

| Componente | Cantidad | Pin en Arduino | Función / Notas |
| :--- | :---: | :---: | :--- |
| **Arduino UNO R3** | 1 | — | Microcontrolador principal |
| **LED Rojo** | 1 | `Pin 11` | Salida digital + Resistencia $220\,\Omega$ |
| **LED Verde** | 1 | `Pin 10` | Salida digital + Resistencia $220\,\Omega$ |
| **LED Azul** | 1 | `Pin 9` | Salida digital + Resistencia $220\,\Omega$ |
| **Piezo Buzzer** | 1 | `Pin 8` | Salida PWM/Tone para tonos musicales |
| **Pulsador Rojo** | 1 | `Pin 4` | Entrada con `INPUT_PULLUP` (Activo en `LOW`) |
| **Pulsador Verde** | 1 | `Pin 3` | Entrada con `INPUT_PULLUP` (Activo en `LOW`) |
| **Pulsador Azul** | 1 | `Pin 2` | Entrada con `INPUT_PULLUP` (Activo en `LOW`) |
| **Pin Analógico** | 1 | `Pin A0` | Flotante (Semilla para `randomSeed`) |

---

## ⚡ Justificación Técnica del Hardware

### Cálculo de Resistencia para LEDs (Ley de Ohm)
Para garantizar la protección de los LEDs y operar dentro del límite de corriente del microcontrolador ($I_D \approx 13.6\,\text{mA}$), se calcula el valor de la resistencia de protección mediante la Ley de Ohm:

$$R = \frac{V_{CC} - V_D}{I_D} = \frac{5.0\,\text{V} - 2.0\,\text{V}}{0.0136\,\text{A}} \approx 220.5\,\Omega \quad \longrightarrow \quad \mathbf{220\,\Omega\text{ (Comercial)}}$$

---

## 🕹️ Lógica de Funcionamiento (FSM)

El programa se estructura mediante un modelo de **Máquina de Estados Finitos (FSM)**:

1. **Inicio / Generación:** El sistema genera una posición aleatoria ($0, 1, 2$) mediante `random()` usando lecturas del pin flotante `A0` como semilla.
2. **Reproducción:** Se reproduce la secuencia acumulada encendiendo los LEDs y emitiendo los tonos asociados.
3. **Lectura del Jugador:** El programa espera la entrada del usuario con filtrado antirrebote de $50\,\text{ms}$.
4. **Evaluación:**
   * **Éxito:** Si el usuario acierta toda la secuencia, emite un tono de victoria, incrementa el nivel y añade un paso más a la secuencia.
   * **Error:** Si el usuario se equivoca, emite un tono grave de error, parpadea todos los LEDs y reinicia el juego al Nivel 1.

---

## 💻 Instrucciones para Simulación en Tinkercad

1. Abrir el proyecto en **Tinkercad Circuits**.
2. Cargar el código ubicado en `main.cpp` dentro del editor de código en modo **Texto**.
3. Presionar **Iniciar simulación**.
4. Observar la secuencia reproducida por los LEDs/Buzzer y presionar los botones correspondientes en el orden correcto usando el ratón.

---

## 📁 Estructura del Repositorio

* `README.md`: Documentación principal del proyecto.
* `main.cpp`: Código fuente estructurado en C++ para Arduino.
* `/docs`: Capturas del circuito en Tinkercad e imágenes de respaldo.
