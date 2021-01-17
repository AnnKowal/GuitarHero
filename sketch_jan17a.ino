#define pin 3
unsigned char temp2=0;
int temp4=0;
char zmienna='8';
int wypelnienie=0;




 void setup(){
    pinMode(pin, OUTPUT);
    Serial.begin(28800);
    
  }

void loop(){
   Serial.println(zmienna); 

   for (int k=0; k<=12000; k++){  
     if(Serial.available() > 0)
    {
      temp2=Serial.read();
     if (k%4==3)
   {
      if (temp2=='a' || temp2=='b' || temp2=='c' || temp2=='d' || temp2 == 'e' || temp2=='f')
      {
        temp4=temp4*16+(temp2-87);
      }
      else{
        temp4=temp4*16+(temp2-48);
      }
  
   analogWrite(pin, temp4);   
    }
    else if(k%4==2)
    {
      if (temp2=='a' || temp2=='b' || temp2=='c' || temp2=='d' || temp2 == 'e' || temp2=='f')
      {
        temp4=temp4+(temp2-87);
      }
      else
        {
        temp4=temp4+(temp2-48);
        }
    }
    else
    {
      temp4=0;
    } 
   
    }
     
  }
  analogWrite(pin, LOW);  
}



      
     
   
  
