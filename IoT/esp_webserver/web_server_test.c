#include <ESP8266WiFi.h>
#include <Wire.h>

#define LED14 14
#define LED13 13


const char* ssid ="511_TEST";
const char* password  = "511511511@";

WiFiServer server(80);



void setup(){


Serial.begin(115200);

//prepare LED

pinMode(LED14, OUTPUT);
digitalWrite(LED14, 0);
pinMode(LED13, OUTPUT);
digitalWrite(LED13, 0);

// connect wifi
Serial.println();
Serial.println();
Serial.print(F("connection to "));
Serial.println(ssid);

WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);

while(WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(F("."));
}

Serial.println();
Serial.println(F("WiFi connected"));

server.begin();
Serial.println(F("Server started"));

Serial.println(WiFi.localIP());

}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    return ;
  }

  Serial.println(F("new client"));

  client.setTimeout(5000);

  String req = client.readStringUntil('\r');
  Serial.println(F("request :"));
  Serial.println(req);

  int val1, val2;

  //일종의 rest api같은 느낌?
  if (req.indexOf(F("/gpio14/0")) != -1) {
    val1 = 0;
  } else if (req.indexOf(F("/gpio14/1")) != -1) {
    val1 = 1;
  } else {
    val1 = digitalRead(LED14);
  }

    if (req.indexOf(F("/gpio13/0")) != -1) {
    val2 = 0;
  } else if (req.indexOf(F("/gpio13/1")) != -1) {
    val2 = 1;
  } else {
    val2 = digitalRead(LED13);
  }

  if (req.indexOf(F("/test")) != -1) {
    Serial.println(F("test destination"));
  }

  digitalWrite(LED14, val1);
  digitalWrite(LED13, val2);

  while(client.available()) {
    client.read();
  }

  client.print(F("HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<H1 style='text-align: center;' >This is Test Page</H1>\r\nGPIO 14 is now"));
  client.print((val1) ? F("high, LED off") : F("low, LED on"));
  client.print(F("<br><br>click <a href = 'http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio14/14'>here</a> to switch LED GPIO14 on, or <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio14/0'>here</a> to switch LED GPIO14 off."));

  client.print(F("<br><br>GPIO13 is now "));
client.print((val2) ? F("high, LED off") : F("low, LED On"));
client.print(F("<br><br>Click <a href='http://"));
client.print(WiFi.localIP());
client.print(F("/gpio13/1'>here</a> to switch LED GPIO13 on, or <a href='http://"));
client.print(WiFi.localIP());
client.print(F("/gpio13/0'>here</a> to switch LED GPIO13 off.\r\n"));
client.print(F("<H2 id = 'date' style='text-align: center;'></H2>\r\n"));
client.print(F("<script>"));
client.print(F("setInterval( function() { printDate();},1000); \r\n"));
client.print(F("function printDate() { document.getElementById('date').innerHTML = Date(); }\r\n"));
client.print(F("</script>\r\n"));
client.print(F("<script src='https://cdn.jsdelivr.net/npm/moment@2.24.0/min/moment.min.js'></script>"));
client.print(F("<script src='https://cdn.jsdelivr.net/npm/chart.js@2.8.0'></script>"));
client.print(F("<script src='https://cdn.jsdelivr.net/npm/chartjs-plugin-streaming@1.8.0'></script>"));
client.print(F("<div style='width:800px'><canvas id = 'myChart'></canvas></div>\r\n"));
client.print(F("<script> var ctx = document.getElementById('myChart').getContext('2d');"));
client.print(F("var myChart = new Chart(ctx, { type : 'line', data: { datasets: [ { data:[]} ] }, options: { scales: { xAxses: [{ type: 'realtime'}] } }    });</script>\r\n"));


client.print(F("</html>"));
Serial.println(F("Disconnecting from client"));
}

//TODO: 보니까 html + js 코드를 하드 코딩해야 하는듯.