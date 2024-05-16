
String readStringFromSerial()
{
  String str;
  while (Serial.available())
  {
    char c = Serial.read();
    str += c;
  }
  return str;
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{ 
  if (Serial.available())
  {
    Serial.println(readStringFromSerial());
  }
  delay(100);
}
