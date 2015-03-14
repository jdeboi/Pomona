//Jenna deBoisblanc, 2011
//Code adapted from:
//Mark Demers' code, Copywrite 2009 (http://spikenzielabs.com/SpikenzieLabs/DrumKitKit.html)
//Georg Mill's YAAMIDrum (www.georgmill.de/)
//Arduino on the 4051 (http://www.arduino.cc/playground/Learning/4051)

#define midichannel 0;
int speakerPin = 3;
unsigned char PadNote[8] = {60,62,64,65,67,69,71,72};	    //array containing MIDI note values, 
                                                            
unsigned char status;
int PadCutOff[8] = {80,110,110,110,80,110,110,110};	    //array containing "threshold" values; 
                                                            //increase (up to 1023) in order to make piezos less sensitive  
int MaxPlayTime[8] = {90,90,90,90,90,90,90,90};		    //time each note remains on after being hit				
									
boolean activePad[8] = {0,0,0,0,0,0,0,0};                   // array of flags of pad currently playing
int PinPlayTime[8] = {0,0,0,0,0,0,0,0};                     // counter since pad started to play
boolean VelocityFlag = false;				    // set this variable to true if you'd like the volume                                          
int analogPin = A0;                                         //to correspond to force of hit
int hitavg = 0;
int pad = 0;

byte byte1;
byte byte2;
byte byte3;

int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int r2 = 0;      //value of select pin at the 4051 (s2)
int count = 0;   //which y pin we are selecting

int multiplex[8];

//*******************************************************************************************************************
// Setup   
//*******************************************************************************************************************

void setup()
{
  pinMode(2, OUTPUT);    // s0
  pinMode(3, OUTPUT);    // s1
  pinMode(4, OUTPUT);    // s2
  Serial.begin(57600);     
}

//*******************************************************************************************************************
// Main Program   
//*******************************************************************************************************************

void loop (){
  readSensors();
  checkSensors();
}

void readSensors () {
  for (count=0; count<=7; count++) {
  
    /////////// select the bit for digital out sent to multiplexer to cycle through 8 inputs /////////////////// 
    r2 = bitRead(count,0);    	        // code that assigns values to digital pins
    r1 = bitRead(count,1);     
    r0 = bitRead(count,2);      

    digitalWrite(2, r0);		//sets the digital output pins to high or low (from values above)
    digitalWrite(3, r1);
    digitalWrite(4, r2);
  
    
    multiplex[count] = analogRead(analogPin);	  //each element of array "multiplex" corresponds to the  
                                                  //voltage read at a particular piezo

    /*Serial.print(count);		          //use these functions to test/print out count (effectively piezo number) 
    Serial.print(" ");                            //and voltage (0-1023) of each piezo
    Serial.println(multiplex[count]);
    */ 
  }
}



void checkSensors() {		//function to get values of each piezo; only checking a single analog input pin

  for(int pin=0; pin <=7; pin++){
    hitavg = multiplex[pin];			//variable hitavg equals the voltage (0-1023) of the piezo
    pad=pin;
    
    if((hitavg > PadCutOff[pin])){		//if the voltage of the piezo is higher than the value of the 
                                                //"threshold" element in array PadCutOff, then:
      if((activePad[pad] == false)){	        //and if the pad wasn't already on or "active"  
      
        if(VelocityFlag == true){
          hitavg = (hitavg / 8) -1;		//and if you want force to correspond to volume (VelocityFlag=true), 
        }					//set voltage of piezo into volume (or "velocity") range of MIDI note (0-127)
        else{
          hitavg = 127;				//if you don't care, set velocity to max value (127)
        }
    
        playKey(144, PadNote[pad],hitavg);       //put together MIDI message; see - http://spikenzielabs.com/SpikenzieLabs/Serial_MIDI_files/Midi%20Message%20Ill2.png
        PinPlayTime[pad] = 0;			//reset the pin play time
        activePad[pad] = true;			//make the pin active (was inactive)
      }
      
      else {					//if the pad was already active when it was hit, increment its play time
         PinPlayTime[pad] = PinPlayTime[pad] + 1;
      }
    }
  
    else if((activePad[pad] == true)){ 	//the pad is active, but it is not greater than cutoff, increment play time
      PinPlayTime[pad] = PinPlayTime[pad] + 1;
    
      if(PinPlayTime[pad] > MaxPlayTime[pad]){	//but if it's already been on for the amount set in the MaxPlayTime array, 
        activePad[pad] = false;                 //turn it off		
        playKey(128, PadNote[pad],127);  //128 is the "status" value which corresponds to an OFF state ()
      }
    }
  }
}



void playKey(unsigned char MESSAGE, unsigned char PITCH, unsigned char VELOCITY) {
  // MIDI_TX(MESSAGE,PITCH,VELOCITY);
  noTone(speakerPin);
  int duration = map(VELOCITY, 0, 127, 0, 1500); 
  tone(speakerPin, PITCH, duration);
}

///////////////////////////
// If we get MIDI working...
///////////////////////////
void MIDI_TX(unsigned char MESSAGE, unsigned char PITCH, unsigned char VELOCITY) {
  status = MESSAGE + midichannel;
  Serial.print(status);
  Serial.print(PITCH);
  Serial.print(VELOCITY);
}
