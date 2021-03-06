/*
 * mp3 player by module esp8266 and xy-v17b
 * Mar 20 2019
 * by ZHAO
 */


#include "Arduino.h"
#include "SoftwareSerial.h"


// Play selected track examples
byte playXX[] =     {0xAA, 0x07, 0x02, 0x00, 0x02, 0xB5};
byte play01[] =     {0xAA, 0x07, 0x02, 0x00, 0x01, 0xB4};
byte play02[] =     {0xAA, 0x07, 0x02, 0x00, 0x02, 0xB5};
byte play03[] =     {0xAA, 0x07, 0x02, 0x00, 0x03, 0xB6};

// Control Commands
byte play[] =     {0xAA, 0x02, 0x00, 0xAC};
byte pause[] =    {0xAA, 0x03, 0x00, 0xAD};
byte stop[] =     {0xAA, 0x04, 0x00, 0xAE};
byte previous[] = {0xAA, 0x05, 0x00, 0xAF};
byte next[] =     {0xAA, 0x06, 0x00, 0xB0};
byte volPlus[] =  {0xAA, 0x14, 0x00, 0xBE};
byte volMinus[] = {0xAA, 0x15, 0x00, 0xBF};
byte prevFile[] = {0xAA, 0x0E, 0x00, 0xB8};
byte nextFile[] = {0xAA, 0x0F, 0x00, 0xB9};
byte stopPlay[] = {0xAA, 0x10, 0x00, 0xBA};

// Setting Commands
byte setVol[] =               {0xAA, 0x13, 0x01};     // {0xAA, 0x13, 0x01, VOL, SM}            VOL:    0x00-0xFF (0-30)
byte setLoopMode[] =          {0xAA, 0x18, 0x01};     // {0xAA, 0x18, 0x01, LM, SM}             LM:     0x00-0x07
byte setCycleTimes[] =        {0xAA, 0x19, 0x02};     // {0xAA, 0x19, 0x02, H, L, SM}           L&H:    0x00-0xFF
byte setEQ[] =                {0xAA, 0x1A, 0x01};     // {0xAA, 0x1A, 0x01, EQ, SM}             EQ:     0x00-0x04
byte specifySong[] =          {0xAA, 0x07, 0x02};     // {0xAA, 0x07, 0x02, H, L, SM}           L&H:    0x00-0xFF
byte specifyPath[] =          {0xAA, 0x08};           // {0xAA, 0x08, Length, Drive, Path, SM}  L,D&P:  0x00-0xFF
byte switchDrive[] =          {0xAA, 0x0B, 0x01};     // {0xAA, 0x0B, 0x01, Drive, SM}          L&H:    0x00-0xFF
byte specifySongInterplay[] = {0xAA, 0x16, 0x03};     // {0xAA, 0x16, 0x03, H, L, SM}           L&H:    0x00-0xFF
byte specifyPathInterplay[] = {0xAA, 0x17};           // {0xAA, 0x17, Length, Drive, Path, SM}  L,D&P:  0x00-0xFF
byte selectSong[] =           {0xAA, 0x1F, 0x02};     // {0xAA, 0x1F, 0x02, H, L, SM}           L&H:    0x00-0xFF (Don't play)

// Query Commands
// Command                  // Command Code           // Return
byte playStatus[] =          {0xAA, 0x01, 0x00, 0xAB};  // AA, 01 01, play status, SM
byte currentOnlineDrive[] =  {0xAA, 0x09, 0x00, 0xB3};  // AA, 09 01, drive, SM
byte currentPlayDrive[] =    {0xAA, 0x0A, 0x00, 0xB4};  // AA, 0A 01, drive, SM
byte NumberOfSongs[] =       {0xAA, 0x0C, 0x00, 0xB6};  // AA, 0C 02, S.N.H S.N.L SM
byte currentSong[] =         {0xAA, 0x0D, 0x00, 0xB7};  // AA, 0D 02, S.N.H S.N.L SM
byte folderDirectorySong[] = {0xAA, 0x11, 0x00, 0xBB};  // AA, 11 02, S.N.H S.N.L SM
byte folderNumberOfSongs[] = {0xAA, 0x12, 0x00, 0xBC};  // AA, 12 02, S.N.H S.N.L SM


// globals
#define busyPin         2       // YOUR "busy" pin
#define randomSeedPin   0       // YOUR random seed ANALOG INPUT *Do not connect to anything*

uint8_t noOfTracks    = 0;      // Number of tracks
uint8_t count         = 1;      // Count songs played once (before playing all)
uint8_t playedAll     = 0;      // played all tracks flag
uint8_t lastTrackAll  = 0;      // last track played in random group (== noOfTracks)
uint8_t randTrack     = 0;      // random track to be played
uint8_t busy          = 0;
bool played[256]      = {LOW};  // keeps track of tracks played

// soft serial
SoftwareSerial soft_serial(D5, D6);    // RX, TX

void setup() {
  uint8_t noTracks[6]   = {0};    // used to build Number of tracks (noOfTracks)
  uint8_t indx          = 0;      // used to read Serial noOfTracks
  

  pinMode(busyPin, INPUT);        // sets the "busy" pin as INPUT
  pinMode(randomSeedPin, INPUT);  // sets the "randomSeedPin" pin as INPUT
  randomSeed(analogRead(randomSeedPin));

  Serial.begin(115200);
  soft_serial.begin(9600);
  //Serial1.begin(9600);
  Serial.println("STARTING...");

  // Detect & print number of tracks ///////////////////////////
//  soft_serial.write(NumberOfSongs, sizeof(NumberOfSongs));
//  soft_serial.flush();
//  while (!soft_serial.available())  {
//    Serial.print('.');
//    delay(500);
//  }
//  Serial.println("");
//  while (soft_serial.available()) {
//    noTracks[indx] = soft_serial.read();
//    Serial.println(noTracks[indx++], HEX);
//    indx++;
//  }
//  Serial.print("No. of songs: ");
//  noOfTracks = ((256*noTracks[3]) + (noTracks[4]));
//  Serial.println(noOfTracks);
//
//  for (uint8_t initial=0; initial<noOfTracks; initial++) {
//    played[initial] = LOW;
//  }

 // Play //////////////////////////////////////////////////////
//  Serial1.write(play, sizeof(play));

  soft_serial.write(play02, sizeof(play02));
  soft_serial.flush();
//  delay(3000);
//  Serial1.write(play02, sizeof(play02));
//  Serial1.flush(); 
}


void loop() {

  // Play random track (if not busy) //////////////////////////////////////////////////
  busy = (digitalRead(busyPin));
  if (busy == LOW) { // !busy
//    Serial.println("!busy");

  // Check if played all tracks. //////////////////////////////////////////////////////
    playedAll = HIGH;
    for (int8_t chck=0; chck<noOfTracks; chck++) {
//      Serial.print("played[");
//      Serial.print(chck);
//      Serial.print("]: ");
//      Serial.print(played[chck]);
//      Serial.print(", ");
      if (played[chck] == LOW)  {
        playedAll = LOW;
      }
    }
//    Serial.print("\n");

  // Reset if played all. /////////////////////////////////////////////////////////////
    if (playedAll == HIGH)  {
      Serial.println("Played all\n\t");
      count = 1;
      for (uint8_t initial=0; initial<noOfTracks; initial++) {
//      for (uint8_t initial=0; initial<sizeof(played); initial++) {
        played[initial] = LOW;
      }
    }
    
  // Pick random track (not already played) ///////////////////////////////////////////
    randTrack = random(1, noOfTracks+1);
    while ( (played[randTrack-1]==HIGH) || (randTrack==lastTrackAll) ) {
      randTrack = random(1, noOfTracks+1);
    }
    lastTrackAll = randTrack;

  // Play chosen track ////////////////////////////////////////////////////////////////
    Serial.print("Playing track[");
    Serial.print(count++);
    Serial.print("]: ");
    Serial.println(randTrack);
    playXX[4] = randTrack;                                                      // playXX[4] set to 0
    playXX[5] = ( playXX[0] + playXX[1] + playXX[2] + playXX[3] + playXX[4] );  // Should be "low 8 bits" only!
    soft_serial.write(playXX, sizeof(playXX));
    played[randTrack-1] = HIGH;          
    
    delay(500);
  }
}
