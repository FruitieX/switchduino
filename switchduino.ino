/*
 * switchduino v1.0
 *
 * Used to control relays for home automation
 
 * Pins:
 * D2: disable
 * D3: enable
 * D4: switch A
 * D5: switch B
 * D6: switch C
 */

#define OUTPUTS 3

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  for (int i = 0; i < OUTPUTS; i++) {
    pinMode(i + 4, OUTPUT);
  }

  Serial.begin(9600);
  Serial.println("switchduino-v1.0");
}

void loop() {
  if (Serial.available() > 0) {
    char in = Serial.read();
    int output;
    boolean enable;
    
    if (in < 'A') {
      Serial.println("ERROR: invalid input");
      return;
    } else if (in < 'a') {
      // upper-case letter: turn switch on
      output = in - 'A';
      enable = true;
      if (output >= OUTPUTS) {
        Serial.println("ERROR: invalid switch id");
        return;
      }
    } else {
      // lower-case letter: turn switch off
      output = in - 'a';
      enable = false;
      if (output >= OUTPUTS) {
        Serial.println("ERROR: invalid switch id");
        return;
      }
    }

    Serial.println("OK: " + String(enable ? "enabled" : "disabled") + " relay " + String(output));

    digitalWrite(enable ? 3 : 2, HIGH);

    digitalWrite(output + 4, HIGH);
    delay(500);
    digitalWrite(output + 4, LOW);

    digitalWrite(enable ? 3 : 2, LOW);
  }
}

