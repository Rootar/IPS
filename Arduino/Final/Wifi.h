String Send(String, const int);

void Wifi(){
  Send("AT+RST\r\n", 2000); // reset modułu
  Send("AT+CWMODE=2\r\n", 1000); // ustawienie w trybie Access Point
  Send("AT+CIFSR\r\n", 1000); // Uzyskanie adresu IP (domyślnie 192.168.4.1)
  Send("AT+CIPMUX=1\r\n", 1000); // Tryb połączeń wielokrotnych
  Send("AT+CWSAP=\"" + WIFI_SSID + "\",\"" + WIFI_PSWD + "\"," + WIFI_CHL + "," + WIFI_ENC + "\r\n", 2000);
  Send("AT+CIPSERVER=1,80\r\n", 1000); // Ustawienie serwera na porcie 80
}


String Send(String command, const int timeout)
{
  String response = "";

  Serial2.print(command); // wysłanie polecenia do ESP01
//  Serial.print(command);
  
  long int time = millis();

  while ((time + timeout) > millis())
  {
    while (Serial2.available()) //jeśli są jakieś dane z modułu, wtedy następuje ich odczyt
    {
      char c = Serial2.read(); // odczyt kolejnego znaku
      response += c;
    }
  }
  Serial.print(response);
  return response;
}
