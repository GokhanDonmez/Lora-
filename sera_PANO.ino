#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>
#include <PWM.h>
#include <avr/wdt.h>
#include <TimerOne.h>

SoftwareSerial Ekran(4, 5);
//#define Ekran Serial

SoftwareSerial mySerial(10, 11);
LoRa_E32 e32ttl(&mySerial);

String sHacim1; //data String
String sPpm1;
String sHacim2; //data String
String sPpm2;
String sHacim3; //data String
String sPpm3;
String sHacim4; //data String
String sPpm4;
String sHacim5; //data String
String sPpm5;
String sHacim6; //data String
String sPpm6;
String sHacim7; //data String
String sPpm7;
String sHacim8; //data String
String sPpm8;
String sHacim9; //data String
String sPpm9;

int ind1; // , locations
int ind2;
int ind3;
int ind4;
int ind5;
int ind6;
int ind7;
int ind8;
int ind9;
int ind10;
int ind11;
int ind12;
int ind13;
int ind14;
int ind15;
int ind16;
int ind17;
int ind18;


typedef struct {
  int durum;
} Vana;
Vana vana;
enum States {LORABIR, LORAIKI, LORAUC, LORADORT, LORABES, LORAALTI, LORAYEDI, LORASEKIZ, LORADOKUZ, STOP};
enum States state = LORABIR;
bool guncellensinMi = false;
bool vanaKapat = false;
int hacim = 0;
int vanaBirHacim;
int vanaIkiHacim = 3;
int vanaUcHacim = 2;
int vanaDortHacim = 3;
int vanaBesHacim = 5;
int vanaAltiHacim = 2;
int vanaYediHacim = 4;
int vanaSekizHacim = 1;
int vanaDokuzHacim = 3;

int vanaBirPpm = 400;
int vanaIkiPpm = 30;
int vanaUcPpm = 20;
int vanaDortPpm = 30;
int vanaBesPpm = 5;
int vanaAltiPpm = 2;
int vanaYediPpm = 4;
int vanaSekizPpm = 1;
int vanaDokuzPpm = 3;

byte loraArrayBir[3] = {0x00, 0x10, 0x11};
byte loraArrayIki[3] = {0x00, 0x10, 0x11};
byte loraArrayUc[3] = {0x00, 0x10, 0x11};
byte loraArrayDort[3] = {0x00, 0x10, 0x11};
byte loraArrayBes[3] = {0x00, 0x10, 0x11};
byte loraArrayAlti[3] = {0x00, 0x10, 0x11};
byte loraArrayYedi[3] = {0x00, 0x10, 0x11};
byte loraArraySekiz[3] = {0x00, 0x10, 0x11};
byte loraArrayDokuz[3] = {0x00, 0x10, 0x11};
int i = 0;
uint32_t timer = 0;
uint32_t frekans = 0;
float pSure[1];
void setup() {
  Serial.begin(9600);
  Ekran.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2, INPUT_PULLUP);
  digitalWrite(13, LOW);
  InitTimersSafe();
  Serial.println("Baslangic");
  while (!Ekran.available());
  degerAl();

  vanaBirHacim = sHacim1.toInt();
  vanaIkiHacim = sHacim2.toInt();
  vanaUcHacim = sHacim3.toInt();
  vanaDortHacim = sHacim4.toInt();
  vanaBesHacim = sHacim5.toInt();
  vanaAltiHacim = sHacim6.toInt();
  vanaYediHacim = sHacim7.toInt();
  vanaSekizHacim = sHacim8.toInt();
  vanaDokuzHacim = sHacim9.toInt();

  hacim = vanaBirHacim;

  vanaBirPpm = sPpm1.toInt();
  vanaIkiPpm = sPpm2.toInt();
  vanaUcPpm = sPpm3.toInt();
  vanaDortPpm = sPpm4.toInt();
  vanaBesPpm = sPpm5.toInt();
  vanaAltiPpm = sPpm6.toInt();
  vanaYediPpm = sPpm7.toInt();
  vanaSekizPpm = sPpm8.toInt();
  vanaDokuzPpm = sPpm9.toInt();

  pSure[0] = 1000;

  e32ttl.begin();

  delay(500);
 // Timer1.initialize(1000000);
 // Timer1.attachInterrupt(pompa);
  attachInterrupt(digitalPinToInterrupt(2),pompa,RISING);
}
int j = 0;
void loop() {

  switch (state)
  {

    case LORABIR: loraAc(loraArrayBir); Serial.println("vana1");Serial.println(vanaBirPpm);frekansGuncelle(vanaBirPpm); Serial.print("hacim:"); Serial.println(hacim); Serial.print("frekans"); Serial.println(frekans);
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {

          frekansGuncelle(vanaBirPpm);
          //SetPinFrequency(3, frekans);
          //pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(0);
          guncellensinMi = false;
        }
      } Serial.println("Vana1cikis"); vanaKapat = false; loraKapat(loraArrayBir); state = LORAIKI; break;

    case LORAIKI: loraAc(loraArrayIki); Serial.println("vana2"); Serial.println(vanaIkiPpm); Serial.print("pSure=");Serial.println(pSure[0]);
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {
          frekansGuncelle(vanaIkiPpm);
          //SetPinFrequency(3, frekans);
          //pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(0);
          guncellensinMi = false;
        }
      } Serial.println("Vana2cikis"); Serial.print("hacim:"); Serial.println(hacim);vanaKapat = false; loraKapat(loraArrayIki); state = LORAUC; break;

    case LORAUC: loraAc(loraArrayUc); Serial.println("vana3");Serial.println(vanaUcPpm); Serial.print("pSure=");Serial.println(pSure[0]);  Serial.print("hacim:"); Serial.println(hacim); 
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {
          frekansGuncelle(vanaUcPpm);
         // SetPinFrequency(3, frekans);
         // pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(frekans);
          guncellensinMi = false;
        }
      } Serial.println("Vana3cikis"); Serial.print("hacim:"); Serial.println(hacim);vanaKapat = false; loraKapat(loraArrayUc); state = LORADORT; break;

    case LORADORT: loraAc(loraArrayDort); Serial.println("vana4");Serial.println(vanaDortPpm); Serial.print("pSure=");Serial.println(pSure[0]); Serial.print("hacim:"); Serial.println(hacim); 
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {
          frekansGuncelle(vanaDortPpm);
          SetPinFrequency(3, frekans);
          pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(frekans);
          guncellensinMi = false;
        }
      } Serial.println("Vana4cikis");Serial.print("hacim:");Serial.println(hacim); vanaKapat = false; loraKapat(loraArrayDort); state = LORABES; break;

    case LORABES: loraAc(loraArrayBes); Serial.println("vana5");Serial.println(vanaBesPpm); Serial.print("pSure=");Serial.println(pSure[0]); Serial.print("hacim:"); Serial.println(hacim); 
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {
          frekansGuncelle(vanaBesPpm);
          SetPinFrequency(3, frekans);
          pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(frekans);
          guncellensinMi = false;
        }
      } Serial.println("Vana5cikis");Serial.print("hacim:");Serial.println(hacim); vanaKapat = false; loraKapat(loraArrayBes); state = LORAALTI; break;

    case LORAALTI: loraAc(loraArrayAlti); Serial.println("vana6"); Serial.println(vanaAltiPpm); Serial.print("pSure=");Serial.println(pSure[0]); Serial.print("hacim:"); Serial.println(hacim);
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {
          frekansGuncelle(vanaAltiPpm);
          SetPinFrequency(3, frekans);
          pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(frekans);
          guncellensinMi = false;
        }
      } Serial.println("Vana6cikis"); Serial.print("hacim:"); Serial.println(hacim);vanaKapat = false; loraKapat(loraArrayAlti); state = LORAYEDI; break;

    case LORAYEDI: loraAc(loraArrayYedi); Serial.println("vana7"); Serial.println(vanaYediPpm); Serial.print("pSure=");Serial.println(pSure[0]); Serial.print("hacim:"); Serial.println(hacim); Serial.print("frekans"); Serial.println(frekans);
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {
          frekansGuncelle(vanaYediPpm);
          SetPinFrequency(3, frekans);
          pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(frekans);
          guncellensinMi = false;
        }
      } Serial.println("Vana7cikis");Serial.print("hacim:"); Serial.println(hacim); vanaKapat = false; loraKapat(loraArrayYedi); state = LORASEKIZ; break;

    case LORASEKIZ: loraAc(loraArraySekiz); Serial.println("vana8");Serial.println(vanaSekizPpm); Serial.print("pSure=");Serial.println(pSure[0]);Serial.print("hacim:"); Serial.println(hacim); Serial.print("frekans"); Serial.println(frekans);
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {
          frekansGuncelle(vanaSekizPpm);
          SetPinFrequency(3, frekans);
          pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(frekans);
          guncellensinMi = false;
        }
      } Serial.println("Vana8cikis");Serial.print("hacim:"); Serial.println(hacim); vanaKapat = false; loraKapat(loraArraySekiz); state = LORADOKUZ; break;

    case LORADOKUZ: loraAc(loraArrayDokuz); Serial.println("vana9");Serial.println(vanaDokuzPpm); Serial.print("pSure=");Serial.println(pSure[0]);  Serial.print("hacim:"); Serial.println(hacim); Serial.print("frekans"); Serial.println(frekans);
      while (!vanaKapat)
      {

        delay(10);
        if (guncellensinMi == true)
        {
          frekansGuncelle(vanaDokuzPpm);
          SetPinFrequency(3, frekans);
          pwmWrite(3, 127);
          Serial.print("hacim:"); Serial.println(hacim);
          Serial.print("frekans"); Serial.println(frekans);
          guncellensinMi = false;
        }
      } Serial.println("Vana9cikis"); vanaKapat = false; loraKapat(loraArrayDokuz); state = STOP; break;


    case STOP: reboot();


  }



}
void pompa()
{
  /*
  if(i==0){
    
    timer=millis();
  }
  if(i==10){
    i=-1;
    timer = millis() - timer;
    pSure[0] = timer;
    frekans=(1*10)/(float)(pSure[0]/1000);
  }
  i++;
  */
  
  if (i == 0) {
    timer = millis();
  }
  if (i == 10) {
    i = -1;
    timer = millis() - timer;
    pSure[0] = timer;

    guncellensinMi = true;
    hacim--;

    if (hacim == 0) {
      switch (state) {
        case LORABIR: hacim = vanaIkiHacim; break;
        case LORAIKI: hacim = vanaUcHacim; break;
        case LORAUC: hacim = vanaDortHacim; break;
        case LORADORT: hacim = vanaBesHacim; break;
        case LORABES: hacim = vanaAltiHacim; break;
        case LORAALTI: hacim = vanaYediHacim; break;
        case LORAYEDI: hacim = vanaSekizHacim; break;
        case LORASEKIZ: hacim = vanaDokuzHacim; break;
      }
      vanaKapat = true;
    }
  }
  i++;
  
}
void loraAc(byte loraArray[])
{
  vana.durum = 100;
  delay(5);
  ResponseStatus rs = e32ttl.sendFixedMessage(loraArray[0], loraArray[1], loraArray[2], &vana, sizeof(Vana));
  delay(100);

}
void loraKapat(byte loraArray[])
{
  vana.durum = 200;
  ResponseStatus rs = e32ttl.sendFixedMessage(loraArray[0], loraArray[1], loraArray[2], &vana, sizeof(Vana));
}
void frekansGuncelle(int ppm)
{
  //frekans = 10 * ppm / (float)(pSure[0] / 1000);
  frekans= (ppm*10)/(float)(pSure[0]/1000);
 // Serial.println(frekans);
  

}

void degerAl()
{
  while (1) {
    if (Ekran.available()) {
      String s = Ekran.readStringUntil('\n');  //gets one byte from Next buffer
      if (s.endsWith("*")) {

        

        ind1 = s.indexOf('-');  //finds location of first ,
        sHacim1 = s.substring(0, ind1);   //captures first data String
        ind2 = s.indexOf('-', ind1 + 1 ); //finds location of second ,
        sPpm1 = s.substring(ind1 + 1, ind2); //captures second data String
        ind3 = s.indexOf('-', ind2 + 1 ); //finds location of second ,
        sHacim2 = s.substring(ind2 + 1, ind3);
        ind4 = s.indexOf('-', ind3 + 1);
        sPpm2 = s.substring(ind3 + 1, ind4);
        ind5 = s.indexOf('-', ind4 + 1);
        sHacim3 = s.substring(ind4 + 1, ind5);
        ind6 = s.indexOf('-', ind5 + 1);
        sPpm3 = s.substring(ind5 + 1, ind6);
        ind7 = s.indexOf('-', ind6 + 1);
        sHacim4 = s.substring(ind6 + 1, ind7);
        ind8 = s.indexOf('-', ind7 + 1);
        sPpm4 = s.substring(ind7 + 1, ind8);
        ind9 = s.indexOf('-', ind8 + 1);
        sHacim5 = s.substring(ind8 + 1, ind9);
        ind10 = s.indexOf('-', ind9 + 1);
        sPpm5 = s.substring(ind9 + 1, ind10);
        ind11 = s.indexOf('-', ind10 + 1);
        sHacim6 = s.substring(ind10 + 1, ind11);
        ind12 = s.indexOf('-', ind11 + 1);
        sPpm6 = s.substring(ind11 + 1, ind12);
        ind13 = s.indexOf('-', ind12 + 1);
        sHacim7 = s.substring(ind12 + 1, ind13);
        ind14 = s.indexOf('-', ind13 + 1);
        sPpm7 = s.substring(ind13 + 1, ind14);
        ind15 = s.indexOf('-', ind14 + 1);
        sHacim8 = s.substring(ind14 + 1, ind15);
        ind16 = s.indexOf('-', ind15 + 1);
        sPpm8 = s.substring(ind15 + 1, ind16);
        ind17 = s.indexOf('-', ind16 + 1);
        sHacim9 = s.substring(ind16 + 1, ind17);
        ind18 = s.indexOf('-', ind17 + 1);
        sPpm9 = s.substring(ind17 + 1, s.length() - 1);

        


 
break;

        }


      }


    }

  }


/*
void degerAl()
{
  while (1) {
    if (Next.available()) {
      String s = Next.readStringUntil('\n');  //gets one byte from Next buffer
      if (s.endsWith("*")) {



        ind1 = s.indexOf('-');  //finds location of first ,
        sHacim1 = s.substring(0, ind1);   //captures first data String
        ind2 = s.indexOf('-', ind1 + 1 ); //finds location of second ,
        sPpm1 = s.substring(ind1 + 1, ind2); //captures second data String
        ind3 = s.indexOf('-', ind2 + 1 ); //finds location of second ,
        sHacim2 = s.substring(ind2 + 1, ind3);
        ind4 = s.indexOf('-', ind3 + 1);
        sPpm2 = s.substring(ind3 + 1, ind4);
        ind5 = s.indexOf('-', ind4 + 1);
        sHacim3 = s.substring(ind4 + 1, ind5);
        ind6 = s.indexOf('-', ind5 + 1);
        sPpm3 = s.substring(ind5 + 1, ind6);
        ind7 = s.indexOf('-', ind6 + 1);
        sHacim4 = s.substring(ind6 + 1, ind7);
        ind8 = s.indexOf('-', ind7 + 1);
        sPpm4 = s.substring(ind7 + 1, ind8);
        ind9 = s.indexOf('-', ind8 + 1);
        sHacim5 = s.substring(ind8 + 1, ind9);
        ind10 = s.indexOf('-', ind9 + 1);
        sPpm5 = s.substring(ind9 + 1, ind10);
        ind11 = s.indexOf('-', ind10 + 1);
        sHacim6 = s.substring(ind10 + 1, ind11);
        ind12 = s.indexOf('-', ind11 + 1);
        sPpm6 = s.substring(ind11 + 1, ind12);
        ind13 = s.indexOf('-', ind12 + 1);
        sHacim7 = s.substring(ind12 + 1, ind13);
        ind14 = s.indexOf('-', ind13 + 1);
        sPpm7 = s.substring(ind13 + 1, ind14);
        ind15 = s.indexOf('-', ind14 + 1);
        sHacim8 = s.substring(ind14 + 1, ind15);
        ind16 = s.indexOf('-', ind15 + 1);
        sPpm8 = s.substring(ind15 + 1, ind16);
        ind17 = s.indexOf('-', ind16 + 1);
        sHacim9 = s.substring(ind16 + 1, ind17);
        ind18 = s.indexOf('-', ind17 + 1);
        sPpm9 = s.substring(ind17 + 1, s.length() - 1);

        Next.print("n0.val=");
        Next.print(sHacim1);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n2.val=");
        Next.print(sHacim2);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n4.val=");
        Next.print(sHacim3);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n6.val=");
        Next.print(sHacim4);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n8.val=");
        Next.print(sHacim5);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n10.val=");
        Next.print(sHacim6);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n12.val=");
        Next.print(sHacim7);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n14.val=");
        Next.print(sHacim8);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n16.val=");
        Next.print(sHacim9);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);

        Next.print("n1.val=");
        Next.print(sPpm1);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n3.val=");
        Next.print(sPpm2);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n5.val=");
        Next.print(sPpm3);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n7.val=");
        Next.print(sPpm4);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n9.val=");
        Next.print(sPpm5);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n11.val=");
        Next.print(sPpm6);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n13.val=");
        Next.print(sPpm7);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n15.val=");
        Next.print(sPpm8);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);
        Next.print("n17.val=");
        Next.print(sPpm9);
        Next.write(0xff);
        Next.write(0xff);
        Next.write(0xff);


        while (!Next.available());
        if (Next.available()) {
          String cevap = Next.readStringUntil('\n');
          if (cevap == "ok") {

            break;
          }

        }


      }


    }

  }
}
*/
void reboot()
{
  
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {};
}
