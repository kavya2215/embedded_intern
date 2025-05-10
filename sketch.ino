  #include <DHT.h>

  #define DHTPIN 15
  #define DHTTYPE DHT22
  #define HEATER_LED 16
  #define STABILIZE_LED 17
  #define BUZZER 18

  DHT dht(DHTPIN, DHTTYPE);

  void setup() {
    Serial.begin(115200);
    dht.begin();
    pinMode(HEATER_LED, OUTPUT);
    pinMode(STABILIZE_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
  }

  void loop() {
    float temp = dht.readTemperature();

    if (isnan(temp)) {
      Serial.println("Idle: Sensor not responding.");
      return;
    }

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C → ");

    // Reset all indicators
    digitalWrite(HEATER_LED, LOW);
    digitalWrite(STABILIZE_LED, LOW);
    digitalWrite(BUZZER, LOW);

    if (temp < 28) {
      digitalWrite(HEATER_LED, HIGH);
      Serial.println("Heating");
    } 
    else if (temp < 30) {
      digitalWrite(STABILIZE_LED, HIGH);
      Serial.println("Stabilizing");
    } 
    else if (temp <= 35) {
      Serial.println("Target Reached");
    } 
    else {
      digitalWrite(BUZZER, HIGH);
      Serial.println("Overheat!");
    }

    delay(2000); // 2 seconds interval
  }
