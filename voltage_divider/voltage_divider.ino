#define pin 7

void voltage()
{
  float cap = analogRead(pin);
  float vol = (cap/1024) * 3.7 * (11/21);
  String vol1= String(vol);
  Serial.println(vol);
}
