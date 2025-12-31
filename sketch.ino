#include <DHT.h>

  /* ================= PIN DEFINITIONS ================= */
  #define DHT_PIN           5
  #define DHT_TYPE          DHT22

  #define MQ2_PIN           34
  #define PIR_PIN           13

  #define BUZZER_PIN        4
  #define LED_FIRE          32
  #define LED_MOTION        33
  #define RELAY_FAN         18   // Ventilation / exhaust

  /* ================= THRESHOLDS ================= */
  #define TEMP_THRESHOLD          60.0     // Fire temperature
  #define TEMP_RISE_THRESHOLD     0.12     // °C/sec
  #define SMOKE_THRESHOLD         3757     // MQ-2 calibrated value

  #define SAMPLE_COUNT 5

  /* ================= GLOBAL VARIABLES ================= */
  DHT dht(DHT_PIN, DHT_TYPE);

  float tempSamples[SAMPLE_COUNT];
  int smokeSamples[SAMPLE_COUNT];
  int sampleIndex = 0;

  bool fireDetected = false;
  bool motionDetected = false;

  float lastTemp = 0;
  unsigned long lastTempTime = 0;

  /* ================= HELPER FUNCTIONS ================= */

  float averageTemp() {
    float sum = 0;
    for (int i = 0; i < SAMPLE_COUNT; i++) sum += tempSamples[i];
    return sum / SAMPLE_COUNT;
  }

  int averageSmoke() {
    int sum = 0;
    for (int i = 0; i < SAMPLE_COUNT; i++) sum += smokeSamples[i];
    return sum / SAMPLE_COUNT;
  }

  /* Temperature Rate-of-Rise Detection */
  bool detectRapidTempIncrease(float currentTemp) {
    unsigned long now = millis();

    if (lastTempTime == 0) {
      lastTemp = currentTemp;
      lastTempTime = now;
      return false;
    }

    float deltaTemp = currentTemp - lastTemp;
    float deltaTime = (now - lastTempTime) / 1000.0;

    lastTemp = currentTemp;
    lastTempTime = now;

    if (deltaTime <= 0) return false;

    float rate = deltaTemp / deltaTime;
    Serial.print("Temp Rise Rate: ");
    Serial.println(rate);

    return (rate >= TEMP_RISE_THRESHOLD);
  }

  /* Alarm Sound */
  void fireAlarm() {
    int tones[] = {1200, 1500, 1800};
    for (int i = 0; i < 3; i++) {
      tone(BUZZER_PIN, tones[i]);
      delay(250);
    }
    noTone(BUZZER_PIN);
  }

  /* ================= SETUP ================= */
  void setup() {
    Serial.begin(115200);

    pinMode(MQ2_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_FIRE, OUTPUT);
    pinMode(LED_MOTION, OUTPUT);
    pinMode(RELAY_FAN, OUTPUT);

    digitalWrite(LED_FIRE, LOW);
    digitalWrite(LED_MOTION, LOW);
    digitalWrite(RELAY_FAN, LOW);

    for (int i = 0; i < SAMPLE_COUNT; i++) {
      tempSamples[i] = 0;
      smokeSamples[i] = 0;
    }

    dht.begin();
    Serial.println("Child Safety System Initialized");
  }

  /* ================= MAIN LOOP ================= */
  void loop() {
    float temperature = dht.readTemperature();
    int smoke = analogRead(MQ2_PIN);
    int motion = digitalRead(PIR_PIN);

    /* Update sliding window */
    tempSamples[sampleIndex] = temperature;
    smokeSamples[sampleIndex] = smoke;
    sampleIndex = (sampleIndex + 1) % SAMPLE_COUNT;

    float avgTemp = averageTemp();
    int avgSmoke = averageSmoke();

    /* Fire & Hazard Detection */
    bool highTemp = avgTemp >= TEMP_THRESHOLD;
    bool rapidTempRise = detectRapidTempIncrease(avgTemp);
    bool smokeDetected = avgSmoke >= SMOKE_THRESHOLD;

    fireDetected = highTemp || rapidTempRise || smokeDetected;

    /* Motion Detection (Baby movement) */
    motionDetected = (motion == HIGH);

    /* OUTPUT CONTROL */
    digitalWrite(LED_FIRE, fireDetected);
    digitalWrite(LED_MOTION, motionDetected);
    digitalWrite(RELAY_FAN, smokeDetected);

    if (fireDetected) {
      fireAlarm();
    }

    /* ===== SERIAL MONITOR ===== */
    Serial.println("===== SYSTEM STATUS =====");
    Serial.print("Temperature: "); Serial.println(avgTemp);
    Serial.print("Smoke Level: "); Serial.println(avgSmoke);
    Serial.print("Motion Detected: "); Serial.println(motionDetected);
    Serial.print("Fire Risk: "); Serial.println(fireDetected);
    Serial.println("==========================\n");

    delay(3000);
  }
