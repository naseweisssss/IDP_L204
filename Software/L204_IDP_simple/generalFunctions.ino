void ledBlink(void)
{
   for (int i = 0; i<4; i++)
   { 
      digitalWrite (OrangeLED, HIGH);
      delay (1000);
      digitalWrite (OrangeLED, LOW);
      delay (1000);
   } 
}


// TODO - make all the LED commands work
