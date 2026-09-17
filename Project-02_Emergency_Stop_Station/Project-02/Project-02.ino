const int LED_HIJAU = 23; //HIJAU ARTINYA RUNNING
const int LED_MERAH = 22; //MERAH ARTINYA STOPPU  

const int PB1_Start = 18; //START HANYA BISA MERUBAH READY KE RUNNING
const int PB2_Stop = 19;  //STOP MERUBAH RUNNING KE READY
const int PB3_Estop = 21; //EMERGENCY BISA MENGUBAH READY DAN RUNNING MENJADI EMERGENCY
const int PB4_Reset = 4; //RESET MENGUBAH EMERGENCY MENJADI READY

int state = 0;//READY(0), RUNNING(1), EMERGENCY(2)

void setup() {
  Serial.begin(115200);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);

  pinMode(PB1_Start, INPUT_PULLDOWN);
  pinMode(PB2_Stop, INPUT_PULLDOWN);
  pinMode(PB3_Estop, INPUT_PULLDOWN);
  pinMode(PB4_Reset, INPUT_PULLDOWN);

}

void loop() {
  
  if(digitalRead(PB3_Estop) == HIGH && (state == 0 || state == 1)){
    state = 2;
  } else if(digitalRead(PB1_Start) == HIGH && state == 0){
    state = 1;
  } else if(digitalRead(PB2_Stop) == HIGH && state == 1){
    state = 0;
  } else if(digitalRead(PB4_Reset) == HIGH && state == 2){
    state = 0;
  }

  if(state == 0){
    digitalWrite(LED_HIJAU, LOW);
    digitalWrite(LED_MERAH, LOW);
  } 
  if(state == 1){
    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(LED_MERAH, LOW);
  }
  if(state == 2){
    digitalWrite(LED_HIJAU, LOW);
    digitalWrite(LED_MERAH, HIGH);
  }

}
