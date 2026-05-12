// WebInterface.cpp - Web interface for ESP32 OuroMini (by PardhuVarma, Team Ouroboros)

#include "WebInterface.h"
#include "WebAccessPoint.h"
#include "WebStation.h"
#include "WebProbeReqSsid.h"
#include "Settings.h"
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

WebInterface::WebInterface() {}
WebInterface::~WebInterface() {
    if (webServer) {
        webServer->end();
        delete webServer;
        webServer = nullptr;
    }
    if (ws) {
        delete ws;
        ws = nullptr;
    }
}

extern "C" {
  uint8_t temprature_sens_read(void);
}


// -------------------------------------------------
// Begin Web Interface
// -------------------------------------------------
bool WebInterface::begin(const char* apName) {
    webServer = new AsyncWebServer(80);
    ws = new AsyncWebSocket("/ws");

    ws->onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client,
                       AwsEventType type, void *arg, uint8_t *data, size_t len) {
        if (type == WS_EVT_CONNECT) {
            Serial.println("[WS] Client connected");
            updateClients();
        } 
        else if (type == WS_EVT_DISCONNECT) {
            Serial.println("[WS] Client disconnected");
        } 
        else if (type == WS_EVT_DATA) {
            AwsFrameInfo *info = (AwsFrameInfo*)arg;
            if (info->opcode != WS_TEXT) return;
            String msg = String((char*)data).substring(0, len);
            Serial.printf("[WS RX] %s\n", msg.c_str());

            StaticJsonDocument<512> doc;
            DeserializationError err = deserializeJson(doc, msg);
            if (!err) {
                const char *typeStr = doc["type"];
                if (typeStr && strcmp(typeStr, "exec") == 0 && doc.containsKey("cmd")) {
                    String cmd = doc["cmd"].as<String>();
                    if (onCommand) onCommand(cmd);
                    DynamicJsonDocument ack(128);
                    ack["term"] = String("Cmd Exec: ") + cmd;
                    String out; serializeJson(ack, out);
                    client->text(out);
                } else if (doc.containsKey("raw")) {
                    String raw = doc["raw"].as<String>();
                    if (onCommand) onCommand(raw);
                }
            } else {
                msg.trim();
                if (msg.length() && onCommand) onCommand(msg);
            }
        }
    });

    webServer->addHandler(ws);
    ws->enable(true);

    // ---------------- HTML Dashboard ----------------
    webServer->on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
        const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<meta name="theme-color" content="#0a0a0f">
<title>OuroMini - ESP32 Dashboard</title>

<style>
*{margin:0;padding:0;box-sizing:border-box;}
body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI','Roboto','Oxygen','Ubuntu','Cantarell',sans-serif;background:#0a0a0f;color:#f3f4f6;line-height:1.6;overflow-x:hidden;}
.container{max-width:1400px;margin:0 auto;padding:0 1rem;}

/* Navbar */
nav{background:rgba(17,24,39,0.5);border-bottom:1px solid rgba(75,85,99,0.5);backdrop-filter:blur(12px);position:sticky;top:0;z-index:50;}
.nav-content{display:flex;align-items:center;justify-content:space-between;height:64px;}
.logo-section{display:flex;align-items:center;gap:12px;}
.logo{width:40px;height:40px;border-radius:12px;background:linear-gradient(135deg,#00E5FF 0%,#00A8CC 100%);display:flex;align-items:center;justify-content:center;font-size:24px;color:white;}
.logo-text{font-size:20px;font-weight:700;color:#00ffff;text-shadow:0 0 8px rgba(0,255,255,0.8),0 0 20px rgba(0,255,255,0.5);}
.status-indicator{display:flex;align-items:center;gap:8px;}
.status-dot{width:8px;height:8px;border-radius:50%;background:#00E5FF;animation:pulse 2s ease-in-out infinite;}
@keyframes pulse{0%,100%{opacity:1;}50%{opacity:0.5;}}
.status-text{font-size:14px;color:#9ca3af;}

/* App Title */
.app-title{
  color:#00ffff;
  font-weight:700;
  text-shadow:0 0 8px rgba(0,255,255,0.8);
  text-align:center;
  font-size:1.8rem;
  margin:1.5rem 0;
  letter-spacing:1px;
}

main{padding:1.5rem 0;}
.section{margin-bottom:1.5rem;}

/* Card styling */
.card{background:linear-gradient(135deg,rgba(17,24,39,0.9) 0%,rgba(17,24,39,0.5) 100%);border:1px solid rgba(75,85,99,0.5);border-radius:16px;padding:24px;backdrop-filter:blur(12px);}
.card-header-flex{display:flex;align-items:center;justify-content:space-between;margin-bottom:24px;}

/* Card headings (glowing cyan bold) */
.card-title{
  font-size:24px;
  margin-bottom:4px;
  color:#00ffff;
  font-weight:700;
  text-shadow:0 0 8px rgba(0,255,255,0.8),0 0 20px rgba(0,255,255,0.5);
}
.card-subtitle{font-size:14px;color:#9ca3af;}

/* Badge */
.badge{display:inline-flex;align-items:center;padding:6px 16px;border-radius:9999px;font-size:14px;background:rgba(0,229,255,0.2);color:#00E5FF;border:1px solid rgba(0,229,255,0.3);}
.badge-dot{width:8px;height:8px;border-radius:50%;background:#00E5FF;margin-right:8px;}

/* Status grid */
.status-grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(200px,1fr));gap:16px;}
.status-item{display:flex;align-items:flex-start;gap:12px;padding:16px;border-radius:12px;background:rgba(31,41,55,0.3);border:1px solid rgba(55,65,81,0.3);}
.status-label{font-size:12px;color:#9ca3af;margin-bottom:4px;}
.status-value{font-size:14px;color:#fff;}

/* Info Card (separate card under main section) */
.info-card {
  background: linear-gradient(135deg, rgba(17,24,39,0.9), rgba(17,24,39,0.5));
  border: 1px solid rgba(75,85,99,0.4);
  border-radius: 16px;
  padding: 24px;
  color: #9ca3af;
  backdrop-filter: blur(10px);
  box-shadow: inset 0 0 12px rgba(0,229,255,0.08);
  transition: 0.3s ease-in-out;
}
.info-card:hover {box-shadow: inset 0 0 18px rgba(0,229,255,0.15), 0 0 8px rgba(0,229,255,0.1);}
.info-title {text-align: center;color: #00ffff;font-weight:700;text-shadow:0 0 8px rgba(0,255,255,0.8);font-size: 1.2rem;text-transform: uppercase;letter-spacing: 1px;margin-bottom: 1rem;}
.info-list {list-style-type: disc;padding-left: 1.5rem;color: #9ca3af;font-size: 0.95rem;line-height: 1.6;}
.info-list li {margin-bottom: 0.6rem;}

/* Glowing strong text */
strong {
  color: #00E5FF;
  font-weight: 700;
  text-shadow: 0 0 8px rgba(0,255,255,0.8), 0 0 20px rgba(0,255,255,0.5), 0 0 35px rgba(0,255,255,0.3);
  animation: glowPulse 3s ease-in-out infinite;
}
@keyframes glowPulse {
  0%,100%{text-shadow:0 0 6px rgba(0,255,255,0.6),0 0 14px rgba(0,255,255,0.4),0 0 24px rgba(0,255,255,0.2);}
  50%{text-shadow:0 0 10px rgba(0,255,255,0.9),0 0 26px rgba(0,255,255,0.7),0 0 40px rgba(0,255,255,0.4);}
}

/* Tables */
table{width:100%;border-collapse:collapse;margin-top:10px;font-size:13px;}
th,td{border:1px solid rgba(55,65,81,0.4);padding:6px 8px;text-align:left;}
th{background:rgba(0,229,255,0.15);color:#00E5FF;}
td{color:#e5e7eb;}

/* Terminal */
.terminal{height:420px;background:rgba(0,0,0,0.6);border:1px solid rgba(0,229,255,0.3);border-radius:12px;padding:16px;overflow-y:auto;font-family:'Courier New',monospace;font-size:13px;}
.terminal-line{margin-bottom:4px;word-wrap:break-word;color:#fff;}
.terminal-line.system{color:#9ca3af;}
.terminal-line.success{color:#10b981;}
.terminal-line.error{color:#ef4444;}
.terminal-line.info{color:#00E5FF;}
.terminal-input-wrapper{display:flex;align-items:center;gap:8px;margin-top:8px;}
.terminal-prompt{color:#00E5FF;font-weight:bold;}
.terminal-input{flex:1;background:rgba(31,41,55,0.5);border:1px solid rgba(0,229,255,0.3);border-radius:8px;padding:8px 12px;color:#fff;font-family:'Courier New',monospace;font-size:13px;outline:none;}
.terminal-send-btn{padding:8px 16px;background:linear-gradient(90deg,#00E5FF 0%,#00A8CC 100%);color:white;border:none;border-radius:8px;font-size:13px;font-weight:500;cursor:pointer;}
.terminal-send-btn:hover{opacity:0.9;}

/* Footer */
.footer-card{margin-top:2rem;text-align:center;background:linear-gradient(135deg,rgba(17,24,39,0.9),rgba(17,24,39,0.5));border:1px solid rgba(75,85,99,0.4);border-radius:16px;padding:24px;color:#9ca3af;backdrop-filter:blur(10px);box-shadow:inset 0 0 12px rgba(0,229,255,0.08);}
.footer-card p{margin:6px 0;font-size:13px;}

@media(max-width:768px){.status-grid{grid-template-columns:1fr;}}
</style>
</head>

<body>

<nav>
  <div class="container">
    <div class="nav-content">
      <div class="logo-section">
        <span class="logo-text">OuroMini Control Dashboard v1.4</span>
      </div>
      <div class="status-indicator">
        <div class="status-dot"></div><span class="status-text">Live</span>
      </div>
    </div>
  </div>
</nav>
<main>
<div class="container">

<section class="section">
  <div class="card">
    <div class="card-header-flex">
      <div><h2 class="card-title">ESP32-WROOM-32</h2><p class="card-subtitle">Device Information</p></div>
      <div class="badge"><span class="badge-dot"></span><span id="connectionStatus">Online</span></div>
    </div>

    <div class="status-grid">
      <div class="status-item"><div><div class="status-label">WiFi SSID</div><div class="status-value" id="wifiSSID">OuroMini</div></div></div>
      <div class="status-item"><div><div class="status-label">IP Address</div><div class="status-value" id="ipAddress">192.168.4.1</div></div></div>
      <div class="status-item"><div><div class="status-label">Uptime</div><div class="status-value" id="uptime">0h 0m 0s</div></div></div>
      <div class="status-item"><div><div class="status-label">Firmware</div><div class="status-value" id="firmware">v1.4.0</div></div></div>
    </div>
  </div>
</section>

<section class="section">
  <div class="info-card">
    <h3 class="info-title">Device Usage & Access Information</h3>
    <ul class="info-list">
      <li>Commands are executed in the context of the <strong>OuroMini</strong> device and can be used to control its behavior, retrieve information, and manage settings.</li>
      <li>Connect to the OuroMini Wi-Fi Access Point "SSID: <strong>OuroMini</strong>, Password: <strong>ASK ADMINISTRATOR</strong>" to access this dashboard and manage your device.</li>
      <li>Use the terminal below to execute commands directly on the <strong>OuroMini</strong> device.</li>
      <li>Team: <strong>OuroMini Firmware & Web Design Development Team</strong></li>
      <li>Version: <strong>1.4</strong></li>
      <li>License: <strong>AGPL-3.0</strong></li>
    </ul>
  </div>
</section>

<section class="section">
  <div class="card">
    <div class="card-header"><h2 class="card-title">OuroSpy Live Wi-Fi Data</h2><p class="card-subtitle">Access Points, Stations, and Probe Requests</p></div>
    <h3>Access Points</h3>
    <table id="aps"><thead><tr><th>SSID</th><th>Ch</th><th>Enc</th><th>RSSI</th><th>MAC</th></tr></thead><tbody></tbody></table>
    <h3>Stations</h3>
    <table id="stations"><thead><tr><th>MAC</th><th>RSSI</th></tr></thead><tbody></tbody></table>
    <h3>Probe Requests</h3>
    <table id="probes"><thead><tr><th>SSID</th><th>Requests</th></tr></thead><tbody></tbody></table>
  </div>
</section>

<section class="section">
  <div class="card">
    <div class="card-header"><h2 class="card-title">OuroMini Terminal Konsole</h2><p class="card-subtitle">OuroMini Web Terminal Konsole</p></div>
    <div class="terminal" id="terminal">
      <div id="terminalOutput" class="terminal-output">
        <div class="terminal-line info">OuroMini Web Command-Line Interface</div>
        <div class="terminal-line system">Type 'help' for command list.</div>
        <div class="terminal-line system">---</div>
      </div>
    </div>
    <div class="terminal-input-wrapper">
      <span class="terminal-prompt">$</span>
      <input id="terminalInput" class="terminal-input" placeholder="Enter command..." autocomplete="off" spellcheck="false">
      <button class="terminal-send-btn" id="sendBtn">Send</button>
    </div>
  </div>
</section>

<section class="section">
  <div class="footer-card">
    <p>© 2025 <strong>Project OuroMini</strong> | Built with ❤️ by <strong>OuroMini Firmware Team</strong></p>
    <p>Firmware v1.4 | Licensed under <strong>AGPL-3.0</strong></p>
    <p>OuroMini Framework | Part of <strong>The Ouroboros Series</strong></p>
  </div>
</section>

</div>
</main>

<script>
let ws; let uptime=0;
const term=document.getElementById('terminal');
const termOut=document.getElementById('terminalOutput');
const cmdInput=document.getElementById('terminalInput');
const sendBtn=document.getElementById('sendBtn');

function addTerminalLine(t,c=''){const l=document.createElement('div');l.className='terminal-line '+c;l.innerHTML=t;termOut.appendChild(l);term.scrollTop=term.scrollHeight;}
function updateTableData(items,id){const tbody=document.querySelector(`#${id} tbody`);if(!tbody)return;tbody.innerHTML='';items.forEach(it=>{const tr=document.createElement('tr');for(const k in it){const td=document.createElement('td');td.textContent=it[k];tr.appendChild(td);}tbody.appendChild(tr);});}

function initWebSocket(){
 ws=new WebSocket(`ws://${window.location.hostname}/ws`);
 ws.onopen=()=>{addTerminalLine('✅ Connected to ESP32 WebSocket','success');fetch('/aps').then(r=>r.json()).then(d=>updateTableData(d,'aps')).catch(()=>{});};
 ws.onclose=()=>addTerminalLine('❌ WebSocket Disconnected','error');
 ws.onmessage=(e)=>{try{const d=JSON.parse(e.data);
   if(d.term)addTerminalLine(d.term,'system');
   if(d.aps)updateTableData(d.aps,'aps');
   if(d.stations)updateTableData(d.stations,'stations');
   if(d.probes)updateTableData(d.probes,'probes');
 }catch(err){console.error('Invalid data:',e.data,err);}}; }

function sendCommand(){
 const cmd=cmdInput.value.trim();if(!cmd)return;
 addTerminalLine(`<span class='terminal-prompt'>$</span> ${cmd}`,'system');
 if(ws&&ws.readyState===1){ws.send(JSON.stringify({type:'exec',cmd}));}
 else addTerminalLine('⚠️ Not connected.','warning');
 cmdInput.value='';
}

setInterval(()=>{uptime++;const h=Math.floor(uptime/3600),m=Math.floor((uptime%3600)/60),s=uptime%60;document.getElementById('uptime').textContent=`${h}h ${m}m ${s}s`;},1000);
sendBtn.onclick=sendCommand;
cmdInput.addEventListener('keydown',e=>{if(e.key==='Enter')sendCommand();});
window.onload=initWebSocket;
</script>

</body>
</html>
)rawliteral";
        req->send(200, "text/html", html);
    });

    webServer->on("/aps", HTTP_GET, [this](AsyncWebServerRequest *req) {
        req->send(200, "application/json", serializeAPs());
    });
    webServer->on("/stations", HTTP_GET, [this](AsyncWebServerRequest *req) {
        req->send(200, "application/json", serializeStations());
    });
    webServer->on("/probes", HTTP_GET, [this](AsyncWebServerRequest *req) {
        req->send(200, "application/json", serializeProbeReqSSIDs());
    });

    webServer->on("/exec", HTTP_POST, [this](AsyncWebServerRequest *req) {
        if (!req->hasArg("plain")) { req->send(400, "application/json", "{\"error\":\"empty body\"}"); return; }
        String body = req->arg("plain");
        StaticJsonDocument<512> doc;
        if (deserializeJson(doc, body)) { req->send(400, "application/json", "{\"error\":\"invalid json\"}"); return; }
        if (!doc.containsKey("cmd")) { req->send(400, "application/json", "{\"error\":\"no cmd\"}"); return; }
        String cmd = doc["cmd"].as<String>();
        Serial.printf("[HTTP exec] %s\n", cmd.c_str());
        if (onCommand) onCommand(cmd);
        req->send(200, "application/json", "{\"status\":\"ok\"}");
    });

    webServer->begin();

    // --- Initial clean startup messages ---
    pushTerminalLine("> CLI Ready");
    pushTerminalLine("✅ Wi-Fi driver initialized");
    pushTerminalLine("✅ SoftAP + STA mode active");
    pushTerminalLine("[WebInterface] Server started on port 80");
    // pushTerminalLine("🌐 WebInterface started on http://192.168.4.1");
    float tempC = (temprature_sens_read() - 32) / 1.8;
    pushTerminalLine("[OuroMini] ESP Temp: " + String(tempC) + " °C");
    return true;
}

// -------------------------------------------------
// JSON serialization
// -------------------------------------------------
String WebInterface::serializeAPs() {
    StaticJsonDocument<8192> doc;
    JsonArray arr = doc.to<JsonArray>();
    if (access_points) {
        for (int i = 0; i < access_points->size(); i++) {
            WebAccessPoint ap = access_points->get(i);
            JsonObject o = arr.createNestedObject();
            o["SSID"] = ap.ssid;
            o["Ch"] = ap.channel;
            o["Enc"] = ap.encryption;
            o["RSSI"] = ap.rssi;
            o["MAC"] = ap.mac;
        }
    }
    String out; serializeJson(doc, out);
    return out;
}

String WebInterface::serializeStations() {
    StaticJsonDocument<4096> doc;
    JsonArray arr = doc.to<JsonArray>();
    if (WebStations) {
        for (int i = 0; i < WebStations->size(); i++) {
            WebStation s = WebStations->get(i);
            JsonObject o = arr.createNestedObject();
            o["MAC"] = s.mac;
            o["RSSI"] = s.rssi;
        }
    }
    String out; serializeJson(doc, out);
    return out;
}

String WebInterface::serializeProbeReqSSIDs() {
    StaticJsonDocument<4096> doc;
    JsonArray arr = doc.to<JsonArray>();
    if (probe_req_ssids) {
        for (int i = 0; i < probe_req_ssids->size(); i++) {
            WebProbeReqSsid p = probe_req_ssids->get(i);
            JsonObject o = arr.createNestedObject();
            o["SSID"] = p.ssid;
            o["Requests"] = p.requests;
        }
    }
    String out; serializeJson(doc, out);
    return out;
}

// -------------------------------------------------
// Push updates
// -------------------------------------------------
void WebInterface::updateClients() {
    if (!ws) return;
    StaticJsonDocument<12288> root;
    JsonArray aps = root.createNestedArray("aps");

    if (access_points) {
        for (int i = 0; i < access_points->size(); i++) {
            WebAccessPoint ap = access_points->get(i);
            JsonObject o = aps.createNestedObject();
            o["SSID"] = ap.ssid;
            o["Ch"] = ap.channel;
            o["Enc"] = ap.encryption;
            o["RSSI"] = ap.rssi;
            o["MAC"] = ap.mac;
        }
    }

    JsonArray stations = root.createNestedArray("stations");
    if (WebStations) {
        for (int i = 0; i < WebStations->size(); i++) {
            WebStation s = WebStations->get(i);
            JsonObject o = stations.createNestedObject();
            o["MAC"] = s.mac;
            o["RSSI"] = s.rssi;
        }
    }

    JsonArray probes = root.createNestedArray("probes");
    if (probe_req_ssids) {
        for (int i = 0; i < probe_req_ssids->size(); i++) {
            WebProbeReqSsid p = probe_req_ssids->get(i);
            JsonObject o = probes.createNestedObject();
            o["SSID"] = p.ssid;
            o["Requests"] = p.requests;
        }
    }

    String json; serializeJson(root, json);
    ws->textAll(json);

    static bool announced = false;
    if (!announced) {
        Serial.println("[WebInterface] Live update pushed...");
        announced = true;
    }
}

// -------------------------------------------------
// Helpers
// -------------------------------------------------
String WebInterface::macToString(const uint8_t *mac) {
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}

void WebInterface::pushTerminalLine(const String &line) {
    if (!ws) return;

    // Skip repetitive logs (scan spam)
    static const char* ignoreList[] = {
        "📡 Scan started", "✅ Scan done", "📋 Populated accessPoints",
        "[WebInterface] Live update pushed", "number=", "scan_id="
    };
    for (auto &pat : ignoreList) if (line.indexOf(pat) >= 0) return;

    DynamicJsonDocument d(256);
    d["term"] = line;
    String out;
    serializeJson(d, out);
    ws->textAll(out);
    Serial.println(line);
}
