#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "MecanumCar";
const char* password = "12345678";

WebServer server(80);

// Motor pins
int IN1 = 13, IN2 = 12;   // Front Left
int IN3 = 14, IN4 = 27;   // Front Right
int IN5 = 26, IN6 = 25;   // Back Left
int IN7 = 33, IN8 = 32;   // Back Right

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT); pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT); pinMode(IN8, OUTPUT);

  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/cmd", handleCommand);
  server.begin();
}

void loop() {
  server.handleClient();
}

// ===== HTML PAGE =====
void handleRoot() {
  String html = R"rawliteral(
  <html>
  <head>
  <title>Mecanum Car</title>
  <style>
    button {width:100px;height:60px;font-size:16px;margin:5px;}
  </style>
  <script>
    function sendCmd(cmd){fetch(`/cmd?move=${cmd}`);}
    function hold(btn,cmd){
      btn.addEventListener('mousedown',()=>sendCmd(cmd));
      btn.addEventListener('mouseup',()=>sendCmd('S'));
      btn.addEventListener('touchstart',()=>sendCmd(cmd));
      btn.addEventListener('touchend',()=>sendCmd('S'));
    }
    window.onload=()=>{
      ['F','B','SL','SR','RL','RR','FL','FR','BL','BR'].forEach(id=>{
        hold(document.getElementById(id),id);
      });
    }
  </script>
  </head>
  <body style='text-align:center;'>
    <h2>Mecanum Wheel Robot Car</h2>
    <div>
      <button id='FL'>F-L</button>
      <button id='F'>F</button>
      <button id='FR'>F-R</button>
    </div>
    <div>
      <button id='SL'>S-L</button>
      <button id='SR'>S-R</button>
    </div>
    <div>
      <button id='BL'>B-L</button>
      <button id='B'>B</button>
      <button id='BR'>B-R</button>
    </div>
    <div>
      <button id='RL'>R-L</button>
      <button id='RR'>R-R</button>
    </div>
    <br>
    <button onclick="sendCmd('S')">STOP</button>
  </body></html>
  )rawliteral";
  server.send(200, "text/html", html);
}

// ===== Handle Commands =====
void handleCommand() {
  String move = server.arg("move");
  if (move == "F") forward();
  else if (move == "B") backward();
  else if (move == "SL") strafeLeft();
  else if (move == "SR") strafeRight();
  else if (move == "RL") rotateLeft();
  else if (move == "RR") rotateRight();
  else if (move == "FL") forwardLeft();
  else if (move == "FR") forwardRight();
  else if (move == "BL") backLeft();
  else if (move == "BR") backRight();
  else stopCar();

  server.send(200, "text/plain", "OK");
}

// ===== Motor Control Logic =====
void stopCar(){
  digitalWrite(IN1,LOW); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,LOW);
  digitalWrite(IN5,LOW); digitalWrite(IN6,LOW);
  digitalWrite(IN7,LOW); digitalWrite(IN8,LOW);
}

void forward(){
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
  digitalWrite(IN5,HIGH); digitalWrite(IN6,LOW);
  digitalWrite(IN7,HIGH); digitalWrite(IN8,LOW);
}

void backward(){
  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
  digitalWrite(IN5,LOW); digitalWrite(IN6,HIGH);
  digitalWrite(IN7,LOW); digitalWrite(IN8,HIGH);
}

void strafeRight(){
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);  // FL
  digitalWrite(IN3,LOW);  digitalWrite(IN4,HIGH); // FR
  digitalWrite(IN5,LOW);  digitalWrite(IN6,HIGH); // BL
  digitalWrite(IN7,HIGH); digitalWrite(IN8,LOW);  // BR
}

void strafeLeft(){
  digitalWrite(IN1,LOW);  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
  digitalWrite(IN5,HIGH); digitalWrite(IN6,LOW);
  digitalWrite(IN7,LOW);  digitalWrite(IN8,HIGH);
}

void rotateRight(){
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);  digitalWrite(IN4,HIGH);
  digitalWrite(IN5,HIGH); digitalWrite(IN6,LOW);
  digitalWrite(IN7,LOW);  digitalWrite(IN8,HIGH);
}

void rotateLeft(){
  digitalWrite(IN1,LOW);  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
  digitalWrite(IN5,LOW);  digitalWrite(IN6,HIGH);
  digitalWrite(IN7,HIGH); digitalWrite(IN8,LOW);
}

void forwardLeft(){
  digitalWrite(IN1,LOW); digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);  digitalWrite(IN4,LOW);
  digitalWrite(IN5,HIGH);  digitalWrite(IN6,LOW);
  digitalWrite(IN7,LOW); digitalWrite(IN8,LOW);
}

void forwardRight(){
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);  digitalWrite(IN4,LOW);
  digitalWrite(IN5,LOW);  digitalWrite(IN6,LOW);
  digitalWrite(IN7,HIGH); digitalWrite(IN8,LOW);
}

void backLeft(){
  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);  digitalWrite(IN4,LOW);
  digitalWrite(IN5,LOW);  digitalWrite(IN6,LOW);
  digitalWrite(IN7,LOW); digitalWrite(IN8,HIGH);
}

void backRight(){
  digitalWrite(IN1,LOW);  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
  digitalWrite(IN5,LOW); digitalWrite(IN6,HIGH);
  digitalWrite(IN7,LOW);  digitalWrite(IN8,LOW);
}
