String command;
 
void setup() {
    Serial.begin(9600); 
}
 
void loop() {
    if(Serial.available()){
        command = Serial.readStringUntil('\n');
        Serial.println(command);
         
        if(command.equals("ST")){
            Serial.println("starting telemetry");
        }
        else if(command.equals("CXON")){
            Serial.println("turning container ON");
        }
        else if(command.equals("SP1")){
          Serial.println("turning SP1 ON");
        }
        else if(command.equals("SP2")){
             Serial.println("turning SP2 ON");
        }
        else{
            Serial.println("Invalid command");
        }
    }
}
