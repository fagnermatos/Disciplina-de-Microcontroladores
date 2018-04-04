
# include  <ESP8266WiFi.h>
# include  <ESP8266Ping.h>

    const char* ssid     = "xxxxxxx"; // Nome da rede
    const char* password = "xxxxxxx"; // Senha da rede    
 
    int wifiStatus;
    bool ret;
 
void setup() {
 
      Serial.begin(115200);
      delay(200);
 
      pinMode(14, OUTPUT);
      digitalWrite(14, 0);
      // Iniciar ligação à rede
 
      Serial.println();
      Serial.println();
      Serial.print("A ligar à rede ");
      Serial.println(ssid);
 
      WiFi.begin(ssid, password);
 
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
 
 }   
 
void loop() {
      ret = Ping.ping("www.siteaqui.com",3); // Coloque o site que você pingará
      int val;
      if(ret == true){
         Serial.println("");
         Serial.println("O seu nodeMCU está ligado!");  
         Serial.print("Endereço IP: ");
         Serial.println(WiFi.localIP()); 
         delay(30000);
        }  
      else{
        Serial.println("");
        Serial.println("Upsss...o seu nodeMCU não se consegue ligar...");
        digitalWrite(14, 1);
        delay(10000); 
        digitalWrite(14, 0);
        delay(20000); 
        
      }

}

