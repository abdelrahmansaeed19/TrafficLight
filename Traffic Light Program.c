//char segment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

 # define displayWest portb
 # define displaySouth portc
 # define red1 portd.b0
 # define yellow1 portd.b1
 # define green1 portd.b2
 # define red2 portd.b3
 # define yellow2 portd.b4
 # define green2 portd.b5
 # define powerLeft porta.b2
 # define powerRight porta.b3
 # define auto_manual porta.b0
 # define west_south porta.b1
 
int street, counter = 0, counter1 = 0, i;

void displayOnLcd(int num, int street)
 {
      int rightNum = num % 10;
      if(street == 1)
      {
          displayWest = rightNum;
          if(num >= 20)
                displayWest.b5 = 1;
          if(num >= 10 && num < 20)
                displayWest.b4 = 1;
      }
      else
      {
          displaySouth = rightNum;
          if(num >= 20)
                displaySouth.b5 = 1;
          if(num >= 10 && num < 20)
                displaySouth.b4 = 1;
      }
 }
 void downCount1(int from, int to)
 {
      for(i = from; i >= to; i--)
      {
            displayOnLcd(i, 1);
            displayOnLcd(i + 3, 2);
            delay_ms(1000);
            if(auto_manual == 0)
                break;
      }
 }
 
  void downCount2(int from, int to)
 {
      for(i = from; i >= to; i--)
      {
            displayOnLcd(i + 12, 1);
            displayOnLcd(i, 2);
            delay_ms(1000);
            if(auto_manual == 0)
                break;
      }
 }

void downCount3(int from, int to)
 {
      for(i = from; i >= to; i--)
      {
            displayOnLcd(i + 3, 1);
            displayOnLcd(i + 3, 2);
            delay_ms(1000);
            if(auto_manual == 0)
               break;
      }
 }
void downCount4(int from, int to)
 {
      for(i = from; i >= to; i--)
      {
            displayOnLcd(i, 1);
            displayOnLcd(i, 2);
            delay_ms(1000);
            if(auto_manual == 0)
               break;
      }
 }
 void displayAuto()
 {
      while(1)
      {
         green1 = 1; yellow1 = 0; red1 = 0;
         red2 = 1; yellow2 = 0; green2 = 0;
         downCount1(20, 1);
         if(auto_manual == 0)
             break;
         green1 = 0; red1 = 1;
         yellow2 = 1;
         downCount2(3, 1);
         if(auto_manual == 0)
             break;
         green2 = 1; yellow2 = 0; red2 = 0;
         downCount3(9, 1);
          if(auto_manual == 0)
             break;
         yellow1 = 1;
         downCount4(3, 1);
         if(auto_manual == 0)
             break;
      }
 }
 
void downCount5(int from, int to, int street)
 {
      for(i = from; i >= to; i--)
      {
            displayOnLcd(i, street);
            delay_ms(1000);
            if(auto_manual == 1)
                break;
            if(west_south == 0)
                break;
      }
 }
 
 void downCount6(int from, int to, int street)
 {
      for(i = from; i >= to; i--)
      {
            displayOnLcd(i, street);
            delay_ms(1000);
            if(auto_manual == 1)
                break;
            if(west_south == 1)
                break;
      }
 }
void displayManual()
 {
       while(1)
       {
            if(west_south == 1)
            {
                  red1 = 1; yellow1 = 1; green1 = 0;
                  red2 = 1; yellow2 = 0; green2 = 0;
                  displaySouth = 0;
                  downCount5(3, 0, 1);
                  while(west_south == 1 && auto_manual == 0)
                  {red1 = 0; yellow1 = 0; green1 = 1;}
                  if(auto_manual == 1)
                       break;
                  if(west_south == 0)
                       break;
            }
            else
            {
                  red1 = 1; yellow1 = 0; green1 = 0;
                  red2 = 1; yellow2 = 1; green2 = 0;
                  displayWest = 0;
                  downCount6(3, 0, 2);
                  while(west_south == 0 && auto_manual == 0)
                  {red2 = 0; yellow2 = 0; green2 = 1;}
                  if(auto_manual == 1)
                       break;
                  if(west_south == 0)
                       break;
            }
       }
 }
void main() 
{    
     ADCON1 = 0x07;   // digital pins
     trisb = 0b00000000;
     trisc = 0b00000000;
     trisd = 0b00000000;
     porte.b0 = 1;
     porte.b1 = 1;
     trisa.b2 = 0;
     trisa.b3 = 0;
     powerLeft = 1;
     powerRight = 1;
     trisa.b0 = 1;
     trisa.b1 = 1;
     trisa.b4 = 1;
     displayWest = 0;
     displaySouth = 0;
     while(porta.b4 == 1);
     while(1)
     {
         if(auto_manual == 1)
             displayAuto();
         else
             displayManual();
         displayWest = 0;
         displaySouth = 0;
     }
}