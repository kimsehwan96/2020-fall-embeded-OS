#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define LED12 12
#define LED13 13
#define LED14 14
#define DARK 40 //조도센서 값이 20이하일시 매우 어두움
#define LIGHT 60 //조도 센서 값이 60이상일 경우 밝음.
//DARK와 LIGHT 사이는 어두움.

const char* ssid = "511_TEST";
const char* password  = "511511511@";


#define mqtt_server "ihlab.iptime.org"
#define mqtt_port 1883
#define mqtt_topic "2015146007" //topic은 2015146007 로 설정.
#define mqtt_user "IoT"
#define mqtt_password "IoT_Test@"


int light = 0;
int lightPinA = 0; //ADC 핀 설정 
char lightData[50]; //mqtt로 Publish 하기 위해서 만든 문자열 배열  

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  Serial.begin(9600);
  pinMode(LED12, OUTPUT);
  pinMode(LED13, OUTPUT);
  pinMode(LED14 , OUTPUT);
  pinMode(lightPinA, INPUT);

  digitalWrite(LED12, 0);
  digitalWrite(LED13, 0);
  digitalWrite(LED14, 0);

}

void loop() {
    if (!client.connected()) {
    client.connect("ESP8266Client_12345", mqtt_user, mqtt_password);
    client.subscribe(mqtt_topic);
  }
  sprintf(lightData, "%d", analogRead(lightPinA)); //loop logic에서 analog read한 정수 값 을 lightdata라는 문자열에 저장  
  client.publish(mqtt_topic, lightData); //매 1초마다 publish.
  delay(1000);
  client.loop(); //for looping callback. 콜백을 계속해서 호출하기 위한 loop. -> 한번만 loop 호출되면 될 것 같은데.. 
}


void callback(char* topic, byte* payload, unsigned int length) { //콜백 함수. 이벤트가 발생했을 때 처리하는 부분 
  String Msg = "";
  int i = 0;
  int convertData = 0;
  while (i < length) Msg += (char)payload[i++];
  Serial.println(Msg);
  convertData = Msg.toInt(); //Msg는 문자열이므로, 정수형 데이터로 바꿔서 조건처리 하기 위한 용도. 
  controllLED(convertData); //String을 int로 변환한 값을 controllLED 함수의 인자로 전
  
  //loop 블럭에서 publish한 조도 데이터를 그대로 subscribe해서 터미널에 출력해주는 콜백 함
}

void controllLED(int condition) {
  if (condition < DARK) {
    digitalWrite(LED12,0);
    digitalWrite(LED13,1);
    digitalWrite(LED14,1); //LED 1개 점등
  }
  else if ( (condition > DARK) && (condition < LIGHT)){ //20과 90사이 일 경우 2개 점등   
    digitalWrite(LED12,0);
    digitalWrite(LED13,0);
    digitalWrite(LED14,1); //LED 2개 점등
  }

  else { // 그 외 90 이상일 경우 3개 점등 
    digitalWrite(LED12,0);
    digitalWrite(LED13,0);
    digitalWrite(LED14,0); //LED 3개 점등
  }
}