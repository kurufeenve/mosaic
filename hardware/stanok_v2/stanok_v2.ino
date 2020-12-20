#define FORWARD 0
#define BACK 1

enum  Opts
{
  Place_Holder,
  Calibration,
  Init_Seq
};

void  Move(uint32_t steps, int8_t Direction)
{
  for (uint32_t i = 0; i < steps; i++)
  {
    digitalWrite(8, LOW);
    digitalWrite(7, Direction);
    digitalWrite(4, HIGH);
    //delay(1);
    delayMicroseconds(500);
    digitalWrite(4, LOW);
    delayMicroseconds(500);
  }
}

void  Main_Belt_Calibration(void)
{
  Serial.println("Main Belt Calibration:");
  /*Serial.println(analogRead(A8));
  while (analogRead(A8) > 300) {
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, HIGH);
    //delay(1);
    delayMicroseconds(500);
    digitalWrite(4, LOW);
    delayMicroseconds(500);
  }*/
}

void  Calibrate(void)
{
  Main_Belt_Calibration();
}

void  Init_Sequence(void)
{
  Move(2500, FORWARD);
}

void  Options(uint8_t option)
{
  switch (option)
  {
    case Place_Holder:
    case Calibration:
      Calibrate();
      break ;
    case Init_Seq:
      Init_Sequence();
  }
}

void setup() {
  //pinMode(A8, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  digitalWrite(8, LOW);

  Serial.begin(9600);
  //Options(Calibration);
  //Options(Init_Seq);
}
int i = 0;
// the loop function runs over and over again forever
void loop() {
  char      steps[5];
  uint32_t  number_of_steps;

  //  memset((void *)steps, 0, 5);
  String a = "";
  //Serial.println(Serial.available());
  if (Serial.available())
  {
    while (Serial.available()) {
      a += (char)Serial.read();
    }
    Serial.print("|");
    Serial.println(a);
  }
  //Serial.println(steps);
  number_of_steps = atoi(steps);
  if (number_of_steps)
  {
    Serial.println(steps);
    Serial.println(number_of_steps);
  }
  //Move()
  //digitalWrite(8, HIGH);
  //delay(500);
}
