byte SimWiFi[] = { 0xCC, 0x01, 0x00, 0x32 };
byte SimPower[]= { 0xCC, 0x01, 0x01, 0xE7 };
byte Mode[]    = { 0xCC, 0x01, 0x02, 0x4D };
byte StartRec[]= { 0xCC, 0x01, 0x03, 0x98 };
byte stopRec[]=  { 0xCC, 0x01, 0x04, 0xCC };

#define EnableCam

const int Rc1 = 2;
volatile const int Rc2 = 3;
//const int led = 4;
//Serial.write(message, sizeof(message));
int Rc1Value;
volatile int Rc2Value;

bool sPower = false;

int i;

void setup() {

	attachInterrupt(digitalPinToInterrupt(2), TriggISR, CHANGE);
	Serial.begin(115200);

}
void loop() {
	Rc1Value = pulseIn(Rc1, HIGH);//get the pwm value
	
	if(Rc1Value >= 970 && Rc1Value <= 980) {
		
		i++;
		//when the switch goes to this posision 
		//the i counter starts 
   
     return;
	}
	if (Rc1Value >= 1480 && Rc1Value <= 1490) {
	//mid
		//when the switch is back at center detarmine
		//the time that it spent on lower pos
		
		if (i >=20) {
				#ifdef EnableCam
					Serial.write(SimWiFi, sizeof(SimWiFi));
				#endif // EnableCam
				
				#ifndef EnableCam
					Serial.println("simWiFi");
				#endif // !EnableCam
		}
		if (i <= 19 && i>0) {
			//then send the command 
				#ifdef EnableCam
					Serial.write(Mode, sizeof(Mode));
				#endif // EnableCam

				#ifndef EnableCam
					Serial.println("Mode");
				#endif // !EnableCam
		}

		if (sPower == true) {
			//read the flag , if true perform the actio n only once 
				#ifdef EnableCam
					Serial.write(Mode, sizeof(SimPower));
				#endif // EnableCam

				#ifndef EnableCam
					Serial.println("simPower");
				#endif // !EnableCam			
		}
	     sPower = false;
	     i = 0;
         return;//finaly reset the timer and flag and return
	}
	if(Rc1Value >= 1990 && Rc1Value <= 2000) {       
	
	 //top
	 // single action
		sPower = true;//set a flag ,when on mid  the right action will take place 
#ifndef EnableCam
		Serial.println("simPower");
#endif // !EnableCam
     return;
    }
	delay(800); 
}

void TriggISR() {
	Rc2Value = pulseIn(Rc2, HIGH);
	if (Rc2Value >= 2000) {
		#ifdef EnableCam
			Serial.write(Mode, sizeof(SimPower));
		#endif // EnableCam

		#ifndef EnableCam
			Serial.println("simPower");
		#endif // !EnableCam			
	}
}