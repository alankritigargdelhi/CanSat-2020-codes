void update_state()
{
  
   if(state==0 && pres_alt==prev_alt && pres_alt<5) //still inside rocket
      state++;                                      //idle
   else if(state==1 && pres_alt>prev_alt && pres_alt>5)           //inside rocket
      state++;                                      //Launch Detect
   else if(state==2 && pres_alt<=725 && pres_alt>=670 && pres_alt > prev_alt)          //LDR shows cansat is outside
      state++;                                      //Cansat Deployement 
   else if(state==3 && analogRead(A1)<100)           //A1 and 100 to be changed
      state++;                                      //Descent
   else if(state==4 && pres_alt<=500 && pres_alt<prev_alt ){              //release the payload
      state++; 
      payload=1;
      }                         //Payload Deployement
   else if(state==5 && pres_alt<=400 && pres_alt<prev_alt )               //release payload parachute
      payload= 2;
   else if(state==5 && pres_alt<=5)
      state++;
}
