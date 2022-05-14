#define GREEN 5
#define A 2

enum States {OFF, ON} state;

void setup() {
  // put your setup code here, to run once:

  // LED Setup
  pinMode(GREEN, OUTPUT);

  digitalWrite(GREEN, LOW);
  // BUTTON SETUP
  pinMode(A, INPUT_PULLUP);


}


void loop() {
  // put your main code here, to run repeatedly:
  Tick();
  delay(500);
}

void Tick()
{
  switch (state) { // Transition States
    case ON:
      if (digitalRead(A) == HIGH)
      {
        state = OFF;
      }
      break;

    case OFF:
      if (digitalRead(A) == LOW)
      {
        state = ON;
      }
      break;

    default:
      break;
  }


  switch (state) { // Action States
    case ON:
      digitalWrite(GREEN, HIGH);
      break;

    case OFF:
      digitalWrite(GREEN, LOW);
      break;

    default:
      break;
  }
}
