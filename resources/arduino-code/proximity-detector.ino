// Define 74HC595 chip pins
#define LATCH 6
#define CLOCK 5
#define DATA 7
// Define HC-SR04 ultrasonic sensor pins
#define TRIG 9
#define ECHO 8
// Define passive buzzer pin
#define BUZZ 2

// Define buzzer notes
#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880
#define B5 988
#define C6 1047

int leds = 0; // 8-bit int represeting LED array
int duration; // Time until echo returns
float distance; // Distance from object
int ledsLit;  // How many LEDs to light

void setup() {
  // Identify input/output pins
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);  // Set trigger pin to low voltage
  delayMicroseconds(2);
  pinMode(ECHO, INPUT);
}

void update() {
  // Copy shift register values to latch register
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, leds);
  digitalWrite(LATCH, HIGH);
}

void loop() {
  leds = 0; // Reset LEDs
  digitalWrite(TRIG, HIGH); // Broadcast noise
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH); // Record time before echo

  if (duration < 38000) { // Ensure object is within reasonable range
    distance = duration / 58; // Calculate distance to object
    
    if (distance <= 100) {  // Check that object is within one meter of sensor
      ledsLit = 8 - (distance / 12.5);  // Calculate how many LEDs to light
      if (ledsLit > 8) ledsLit = 8;

      for (int i = 0; i <= ledsLit; i++) { // Set values for LEDs
        leds = leds + (1 << i);
      }

      // update(); // Update the LEDs
      
      // Pick buzzer note based on LEDs
      switch (leds) {
        case 1:
          tone(BUZZ, C5, 100);
          break;
        case 3:
          tone(BUZZ, D5, 100);
          break;
        case 7:
          tone(BUZZ, E5, 100);
          break;
        case 15:
          tone(BUZZ, F5, 100);
          break;
        case 31:
          tone(BUZZ, G5, 100);
          break;
        case 63:
          tone(BUZZ, A5, 100);
          break;
        case 127:
          tone(BUZZ, B5, 100);
          break;
        case 255:
          tone(BUZZ, C6, 100);
          break;
        default:
          break;
      }
    }
  } else {
    // leds = 0;
    // update();
  }

  update();
  delay(100);
}