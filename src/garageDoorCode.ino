#include <HomeSpan.h>
#include <ESP32Servo.h>

#define SERVO_PIN 26  // Pin D26

Servo myservo;

// Define the Servo Control service
class ServoControl : public Service::Switch {
public:
  // Constructor
  ServoControl() : Service::Switch() {
    // Add On characteristic
    new Characteristic::On();
  }

  // Update method
  boolean update() override {
    // Access the "On" characteristic value
    bool buttonState = ((Characteristic::On*)getCharacteristic(0))->getValue();

    // Control the servo based on the button state
    if (buttonState) {
      // Rotate servo to 90 degrees
      myservo.write(90);
    } else {
      // Rotate servo to 0 degrees
      myservo.write(0);
    }

    return true;
  }
};

void setup() {
  Serial.begin(115200);
  myservo.attach(SERVO_PIN);  // Attach the servo to the designated pin

  // Initialize HomeSpan
  homeSpan.begin(Category::Bridges, "ESP32 Servo Control");

  // Create an Accessory
  new SpanAccessory();

  // Create Accessory Information
  new Service::AccessoryInformation();

  // Create Identify characteristic
  new Characteristic::Identify();

  // Create Servo Control service
  new ServoControl();
}

void loop() {
  homeSpan.poll();  // Keep HomeSpan responsive
}