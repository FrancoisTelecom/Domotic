#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX_TIME 85
#define DHT11PIN 7
int dht11_val[5]={0,0,0,0,0};

void write(int a,int b,int c,int d){
  FILE* fichier = NULL;
  fichier = fopen("test290720171716.txt", "a+");
  if (fichier != NULL)
  {
    fputs ("Humidity: ",fichier);
    fputc(a, fichier);
    fputc(a, fichier);
    fputs("\n",fichier);
    fputs ("Temperature: ",fichier);
    fputc(c, fichier);
    fputc(d, fichier);
    fclose(fichier);
  }
  else printf("Impossible d'ouvrir le fichier test.txt");
}

void dht11_read_val()
{
  uint8_t lststate=HIGH;
  uint8_t counter=0;
  uint8_t j=0,i;
  float farenheit;
  int dht11_val[5]={0,0,0,0,0};

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
    farenheit=dht11_val[2]*9./5.+32;

    //printf("H = %d.%d\nT = %d.%d\n",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3]);
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

    printf("digitalRead= %d\n", digitalRead(DHT11PIN));
    printf("H = %d.%d\nT = %d.%d\n",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3]);
    /*while ( b < 6 ){
      ("H = %d.%d\nT = %d.%d\n",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3]);

      delay(1000);
      b++;
    }*/
     dht11_read_val();
     delay(1500);
  }
  return 0;
}
