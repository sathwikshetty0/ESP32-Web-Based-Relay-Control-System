#include <WiFi.h>
#include <WebServer.h>

// Set to true for Normally Open (NO) relay
#define RELAY_NO    true

// Number of relays
#define NUM_RELAYS  4

// GPIO pins for each relay
int relayGPIOs[NUM_RELAYS] = {12,13,14,27};

// WiFi credentials
const char* ssid     = "ne";
const char* password = "12121212";

// WebServer on port 80
WebServer server(80);

// ─── Relay State Helper ───────────────────────────────────────────────────────
String relayState(int numRelay){
  if(RELAY_NO){
    return digitalRead(relayGPIOs[numRelay - 1]) ? "OFF" : "ON";
  } else {
    return digitalRead(relayGPIOs[numRelay - 1]) ? "ON" : "OFF";
  }
}

bool relayIsOn(int numRelay){
  return relayState(numRelay) == "ON";
}

// ─── Build HTML Page ──────────────────────────────────────────────────────────
String buildPage(){
  // Build relay cards dynamically
  String cards = "";
  for(int i = 1; i <= NUM_RELAYS; i++){
    bool on        = relayIsOn(i);
    String onClass = on ? " on"      : "";
    String stText  = on ? "ON"       : "OFF";
    String checked = on ? " checked" : "";

    cards += "<div class=\"relay-card" + onClass + "\" id=\"card" + String(i) + "\">";
    cards +=   "<div class=\"relay-info\">";
    cards +=     "<div class=\"relay-dot\"></div>";
    cards +=     "<div>";
    cards +=       "<div class=\"relay-name\">Relay " + String(i) + "</div>";
    cards +=       "<div class=\"relay-gpio\">GPIO " + String(relayGPIOs[i-1]) + "</div>";
    cards +=     "</div>";
    cards +=   "</div>";
    cards +=   "<div class=\"controls\">";
    cards +=     "<span class=\"relay-status\" id=\"st" + String(i) + "\">" + stText + "</span>";
    cards +=     "<label class=\"switch-wrap\">";
    cards +=       "<input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\"" + checked + ">";
    cards +=       "<span class=\"track\"></span>";
    cards +=     "</label>";
    cards +=   "</div>";
    cards += "</div>";
  }

  String ip = WiFi.localIP().toString();

  String html = R"rawliteral(<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Relay Control</title>
  <style>
    *{box-sizing:border-box;margin:0;padding:0}
    body{font-family:Arial,sans-serif;background:#f0f2f5;min-height:100vh;display:flex;align-items:flex-start;justify-content:center;padding:2rem 1rem}
    .shell{background:#fff;border-radius:16px;box-shadow:0 4px 24px rgba(0,0,0,0.08);max-width:420px;width:100%;overflow:hidden}
    .header{background:#1a1a2e;padding:1.5rem;text-align:center}
    .header-icon{width:44px;height:44px;background:rgba(255,255,255,0.1);border-radius:50%;display:inline-flex;align-items:center;justify-content:center;margin-bottom:10px;font-size:22px}
    .header h1{color:#fff;font-size:18px;font-weight:600;margin:0}
    .header p{color:rgba(255,255,255,0.5);font-size:12px;margin-top:4px}
    .ip-pill{display:inline-block;background:rgba(255,255,255,0.08);border:1px solid rgba(255,255,255,0.15);border-radius:20px;color:rgba(255,255,255,0.7);font-size:11px;padding:3px 12px;margin-top:10px;font-family:monospace}
    .body{padding:1.25rem}
    .section-label{font-size:11px;font-weight:600;color:#9ca3af;text-transform:uppercase;letter-spacing:0.8px;margin-bottom:10px}
    .relay-card{background:#f9fafb;border:1px solid #e5e7eb;border-radius:10px;padding:1rem 1.25rem;margin-bottom:10px;display:flex;align-items:center;justify-content:space-between;gap:12px;transition:border-color 0.2s,background 0.2s}
    .relay-card.on{border-color:#3b82f6;background:#eff6ff}
    .relay-info{display:flex;align-items:center;gap:10px}
    .relay-dot{width:8px;height:8px;border-radius:50%;background:#d1d5db;flex-shrink:0;transition:background 0.2s,box-shadow 0.2s}
    .relay-card.on .relay-dot{background:#3b82f6;box-shadow:0 0 0 3px rgba(59,130,246,0.2)}
    .relay-name{font-size:14px;font-weight:600;color:#111827}
    .relay-gpio{font-size:11px;color:#6b7280;font-family:monospace;margin-top:2px}
    .controls{display:flex;align-items:center;gap:10px}
    .relay-status{font-size:11px;font-weight:600;color:#9ca3af;transition:color 0.2s;min-width:24px;text-align:right}
    .relay-card.on .relay-status{color:#3b82f6}
    .switch-wrap{position:relative;display:inline-block;width:48px;height:26px;flex-shrink:0}
    .switch-wrap input{opacity:0;width:0;height:0}
    .track{position:absolute;top:0;left:0;right:0;bottom:0;background:#d1d5db;border-radius:13px;cursor:pointer;transition:background 0.25s}
    .track:before{content:"";position:absolute;width:20px;height:20px;left:3px;bottom:3px;background:#fff;border-radius:50%;transition:transform 0.25s;box-shadow:0 1px 3px rgba(0,0,0,0.2)}
    input:checked+.track{background:#3b82f6}
    input:checked+.track:before{transform:translateX(22px)}
    .footer{border-top:1px solid #f3f4f6;padding:0.75rem 1.25rem;display:flex;align-items:center;justify-content:space-between}
    .uptime{font-size:12px;color:#9ca3af}
    .signal{display:flex;align-items:center;gap:5px;font-size:12px;color:#9ca3af}
    .bars{display:flex;align-items:flex-end;gap:2px;height:14px}
    .bars span{display:block;width:3px;border-radius:1px;background:#d1d5db}
    .bars span:nth-child(1){height:4px;background:#3b82f6}
    .bars span:nth-child(2){height:7px;background:#3b82f6}
    .bars span:nth-child(3){height:10px;background:#3b82f6}
    .bars span:nth-child(4){height:13px}
  </style>
</head>
<body>
<div class="shell">
  <div class="header">
    <div class="header-icon">&#9889;</div>
    <h1>ESP32 Relay Control</h1>
    <p>Smart Home Controller</p>
    <div class="ip-pill">)rawliteral";

  html += ip;

  html += R"rawliteral(</div>
  </div>
  <div class="body">
    <div class="section-label">Relay Channels</div>)rawliteral";

  html += cards;

  html += R"rawliteral(  </div>
  <div class="footer">
    <span class="uptime">&#128336; Uptime: <span id="uptime">00:00:00</span></span>
    <span class="signal">
      <div class="bars"><span></span><span></span><span></span><span></span></div>
      )rawliteral";

  html += String(ssid);

  html += R"rawliteral(
    </span>
  </div>
</div>
<script>
  function toggleCheckbox(el){
    var xhr=new XMLHttpRequest();
    xhr.open("GET","/update?relay="+el.id+"&state="+(el.checked?1:0),true);
    xhr.send();
    var card=document.getElementById("card"+el.id);
    var status=document.getElementById("st"+el.id);
    if(el.checked){card.classList.add("on");status.textContent="ON";}
    else{card.classList.remove("on");status.textContent="OFF";}
  }
  var secs=0;
  setInterval(function(){
    secs++;
    var h=String(Math.floor(secs/3600)).padStart(2,"0");
    var m=String(Math.floor((secs%3600)/60)).padStart(2,"0");
    var s=String(secs%60).padStart(2,"0");
    document.getElementById("uptime").textContent=h+":"+m+":"+s;
  },1000);
</script>
</body></html>)rawliteral";

  return html;
}

// ─── Route Handlers ───────────────────────────────────────────────────────────
void handleRoot(){
  server.send(200, "text/html", buildPage());
}

void handleUpdate(){
  if(server.hasArg("relay") && server.hasArg("state")){
    int relayNum = server.arg("relay").toInt();
    int state    = server.arg("state").toInt();

    if(relayNum >= 1 && relayNum <= NUM_RELAYS){
      if(RELAY_NO){
        digitalWrite(relayGPIOs[relayNum - 1], !state); // NO: HIGH=OFF, LOW=ON
      } else {
        digitalWrite(relayGPIOs[relayNum - 1], state);  // NC: LOW=OFF, HIGH=ON
      }
      Serial.printf("Relay %d -> %s\n", relayNum, state ? "ON" : "OFF");
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Relay number out of range");
    }
  } else {
    server.send(400, "text/plain", "Missing parameters");
  }
}

void handleNotFound(){
  server.send(404, "text/plain", "Not found");
}

// ─── Setup ────────────────────────────────────────────────────────────────────
void setup(){
  Serial.begin(115200);

  // Initialise relay pins — all OFF at startup
  for(int i = 1; i <= NUM_RELAYS; i++){
    pinMode(relayGPIOs[i - 1], OUTPUT);
    digitalWrite(relayGPIOs[i - 1], RELAY_NO ? HIGH : LOW);
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  // Register routes
  server.on("/",       HTTP_GET, handleRoot);
  server.on("/update", HTTP_GET, handleUpdate);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Web server started.");
}

// ─── Loop ─────────────────────────────────────────────────────────────────────
void loop(){
  server.handleClient();  // Must be called repeatedly for WebServer to work
}
