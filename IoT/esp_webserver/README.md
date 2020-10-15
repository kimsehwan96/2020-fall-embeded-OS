# 아두이노로 간단한 웹서버 구축

* HTPP 요청이 들어오면 request 정보를 구분하여 처리한다.

실제 Http Request는 요청라인 + 헤더 + 공백 + 바디.
이때 공백을 \r을 잘라서 확인한다.

```C
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
  ```

  