int analogPin = 0;
int [] moleLEDPins = {2, 3, 4, 5, 6, 7, 8, 9};
int [] moleStates = {0, 0, 0, 0, 0, 0, 0 , 0};
int pause = 1000;
int duration = 2000;
int lastUpdate = 0;
int lives = 5;
int score = 0;

void setup() {
  size(500,500);
  lastUpdate = millis();
}

void draw() {
  background(255);
  setMoleStates();
  updateMoleStates();
  updateLEDStates();
}


void setMoleStates() {
  if(millis() - lastUpdate > pause) {
    int randNum = int(random(8));
    if(moleStates[randNum] == 0) {
      moleStates[randNum] = millis();
      lastUpdate = millis();
      pause-=10;
      duration-=5;
    }
  }
}

void updateMoleStates() {
  for(int i = 0; i < moleStates.length; i++) {
    if(moleStates[i] > 0) {
      if (millis() - moleStates[i] > duration) {
        moleStates[i] = 0;
        lives--;
        if(lives == 0) lostSequence();
      }
    }  
  }
}

void keyPressed() {
  if (key == '1') hit(1);
  else if (key == '2') hit(2);
  else if (key == '3') hit(3);
  else if (key == '4') hit(4);
  else if (key == '5') hit(5);
  else if (key == '6') hit(6);
  else if (key == '7') hit(7);
  else if (key == '8') hit(8);
}

void hit(int num) {
  num = num - 1;
  if(moleStates[num] > 0) {
    score+= 100;
    moleStates[num] = 0;
  }
}

void updateLEDStates() {
  for(int i = 0; i < moleLEDPins.length; i++) {
    if(moleStates[i] > 0) fill(255,0,0);
    else fill(0);
    rect(i*25+10, 100, 18, 18);
  }
}

void lostSequence() {
  exit();
  while(true);
}
