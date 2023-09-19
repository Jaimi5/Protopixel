# Protopixel
Protopixel Technical Task Firmware Engineer

## [Task description](https://protopixel.notion.site/Technical-Task-Firmware-Engineer-41d9b9e8c44248c7967ae2ce0ed0c2be)

## Task steps

1. Add Led state
2. Add button interrupt that toggles the led
3. Add a solution for the button bouncing
4. Add a WiFi connection
5. Add a MQTT connection
6. Add a MQTT/LED state synchronization
 
## Pre-requisites

- [VSCode](https://code.visualstudio.com/download)
- [PlatformIO](https://platformio.org/install/ide?install=vscode)
- [Docker](https://docs.docker.com/get-docker/)
- [MQTT Broker](https://www.emqx.io/downloads)

## Configuration

- Connect to a WiFi network
- Execute the MQTT broker using docker

```bash
docker run -d --name emqx -p 1883:1883 -p 8083:8083 -p 8084:8084 -p 8883:8883 -p 18083:18083 emqx/emqx:5.2.0
```

- Found the IP address of the MQTT broker

- In the src/config.h file, change the following values:

Define the type of board, choose between LAMP or CONTROLLER

```c
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"
#define MQTT_BROKER_IP "YOUR_MQTT_BROKER_IP"
```