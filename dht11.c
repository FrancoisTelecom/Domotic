#include <wiringPi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX_TIME 85
#define DHT11PIN 7
int dht11_val[5]={0,0,0,0,0};

void date(){
  char format[128];
  time_t temps;
  struct tm date;

  time(&temps);
  date=*localtime(&temps);
  strftime(format, 128, "%d%m%Y%H%M", &date);
  FILE* fichier = NULL;
  fichier = fopen("30072017.log", "a+");
  if (fichier != NULL)  {
    fprintf(fichier, "%s\n",format );
    fclose(fichier);
  }
}

void write(int a,int b,int c,int d){
  date();
  FILE* fichier = NULL;
  fichier = fopen("30072017.log", "a+");
  if (fichier != NULL) {
    //fputs ("Humidity: ",fichier);
    fprintf(fichier, "H: %d.%d %\n", a,b);
    //fputs(".",fichier);
    //fprintf(fichier, "%d", b);
    //fputs(" %\n",fichier);
    //fputs ("Temperature: ",fichier);
    fprintf(fichier, "T: %d.%d°C\n", c,d);
    //fputs(".",fichier);
    //fprintf(fichier, "%d", d);
    //fputs("°C\n\n",fichier);
    fclose(fichier);
  }
  else printf("Impossible d'ouvrir le fichier 30072017.log");
}

void dht11_read_val()
{
  uint8_t lststate=HIGH;
  uint8_t counter=0;
  uint8_t j=0,i;

  for(i=0;i<5;i++) dht11_val[i]=0; //init 0
  /*init pin rasp*/
  pinMode(DHT11PIN,OUTPUT);
  digitalWrite(DHT11PIN,LOW);
  delay(18);
  digitalWrite(DHT11PIN,HIGH);
  delayMicroseconds(40);
  pinMode(DHT11PIN,INPUT);

  for(i=0;i<MAX_TIME;i++)
  {
    counter=0;
    while(digitalRead(DHT11PIN)==lststate){
      counter++;
      delayMicroseconds(1);
      if(counter==255)
        break;
    }
    lststate=digitalRead(DHT11PIN);
    if(counter==255)
       break;
    // top 3 transistions are ignored
    if((i>=4)&&(i%2==0)){
      dht11_val[j/8]<<=1;
      if(counter>16)
        dht11_val[j/8]|=1;
      j++;
    }
  }
  // verify cheksum and print the verified data
  if((j>=40)&&(dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF)))
  {
    printf("H = %d.%d\nT = %d.%d\n",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3]);
    /*écrit dans le fichier*/
    write(dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3]);
  }
  else
    printf("Invalid Data!!\n");
}


int main(void)
{
  printf("Interfacing Temperature and Humidity Sensor (DHT11) With Raspberry Pi\n");
  if(wiringPiSetup()==-1) exit(1);
  while(1) {
     dht11_read_val();
     delay(600000);
  }
  return 0;
}
