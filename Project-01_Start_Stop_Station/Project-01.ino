const int MOTOR = 5; //led hijau yang pura-pura jadi motor
const int PBputihStart = 22;
const int PBkuningStop = 23;

bool motorON = false;

void setup() {
Serial.begin(115200);
pinMode(MOTOR, OUTPUT);

pinMode(PBputihStart, INPUT_PULLDOWN);
pinMode(PBkuningStop, INPUT_PULLDOWN);
}

void loop() {
  //jika PB putih ditekan maka MOTOR akan menyala
  if (digitalRead(PBputihStart) == HIGH){
    motorON = true;
  }
 
   //jika PB kuning ditekan maka motor akan mati
  else if (digitalRead(PBkuningStop) == HIGH){
    motorON = false;
  }

  if(motorON){
    digitalWrite(MOTOR, HIGH);
  } else {
    digitalWrite(MOTOR, LOW);
  }
  
  }
