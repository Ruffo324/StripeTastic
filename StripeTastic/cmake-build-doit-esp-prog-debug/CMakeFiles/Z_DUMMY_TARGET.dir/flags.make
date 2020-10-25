# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# compile C with C:\Users\ruffo/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-gcc.exe
# compile CXX with C:\Users\ruffo/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-g++.exe
C_FLAGS = -std=gnu99 -Wno-old-style-declaration -Wall -nostdlib -Wpointer-arith -Wno-error=unused-but-set-variable -Wno-error=unused-variable -mlongcalls -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -Wno-error=deprecated-declarations -Wno-error=unused-function -Wno-unused-parameter -Wno-sign-compare -fstack-protector -fexceptions -Werror=reorder -Og -g2 -ggdb2   -D'PLATFORMIO=50001' -D'ARDUINO_ESP32_DEV' -D'ESP32' -D'ESP_PLATFORM' -D'F_CPU=240000000L' -D'HAVE_CONFIG_H' -D'MBEDTLS_CONFIG_FILE="mbedtls/esp_config.h"' -D'ARDUINO=10805' -D'ARDUINO_ARCH_ESP32' -D'ARDUINO_VARIANT="doitESP32devkitV1"' -D'ARDUINO_BOARD="DOIT ESP32 DEVKIT V1"' -D'__PLATFORMIO_BUILD_DEBUG__' -std=gnu99

C_DEFINES = 

C_INCLUDES = -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\include -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\lib\StripeBridge\include -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\lib\StripeBridge\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\lib\Services -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\DNSServer\src -IC:\_Files\1_PROG~1\3_GitHub\STRIPE~1\STRIPE~1\PIO~1\libdeps\DOIT-E~1\ESPASY~1\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\WiFi\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\.pio\libdeps\doit-esp-prog-debug\AsyncTCP\src -IC:\Users\ruffo\.platformio\lib\CppLinq\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SPIFFS\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\FS\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\lib\Configuration -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\.pio\libdeps\doit-esp-prog-debug\NeoPixelBus\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SPI\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\.pio\libdeps\doit-esp-prog-debug\ArduinoJson\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\config -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\app_trace -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\app_update -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\asio -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\bootloader_support -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\bt -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\coap -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\console -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\driver -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp-tls -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp32 -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_adc_cal -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_event -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_http_client -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_http_server -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_https_ota -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_ringbuf -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\ethernet -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\expat -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\fatfs -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\freemodbus -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\freertos -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\heap -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\idf_test -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\jsmn -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\json -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\libsodium -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\log -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\lwip -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\mbedtls -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\mdns -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\micro-ecc -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\mqtt -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\newlib -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\nghttp -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\nvs_flash -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\openssl -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\protobuf-c -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\protocomm -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\pthread -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\sdmmc -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\smartconfig_ack -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\soc -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\spi_flash -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\spiffs -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\tcp_transport -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\tcpip_adapter -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\ulp -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\vfs -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\wear_levelling -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\wifi_provisioning -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\wpa_supplicant -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\xtensa-debug-module -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp-face -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp32-camera -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\fb_gfx -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\cores\esp32 -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\variants\doitESP32devkitV1 -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\.pio\libdeps\doit-esp-prog-debug\arduinoFFT\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\ArduinoOTA\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\AsyncUDP\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\AzureIoT\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\BLE\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\BluetoothSerial\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\EEPROM\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\ESP32\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\ESPmDNS\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\FFat\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\HTTPClient\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\HTTPUpdate\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\NetBIOS\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\Preferences\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SD\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SD_MMC\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SimpleBLE\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\Ticker\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\Update\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\WebServer\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\WiFiClientSecure\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\Wire\src -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\xtensa-esp32-elf\include\c++\5.2.0 -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\xtensa-esp32-elf\include\c++\5.2.0\xtensa-esp32-elf -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\lib\gcc\xtensa-esp32-elf\5.2.0\include -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\lib\gcc\xtensa-esp32-elf\5.2.0\include-fixed -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\xtensa-esp32-elf\include -IC:\Users\ruffo\.platformio\packages\tool-unity 

CXX_FLAGS = -fno-rtti -fno-exceptions -std=gnu++11 -Wall -nostdlib -Wpointer-arith -Wno-error=unused-but-set-variable -Wno-error=unused-variable -mlongcalls -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -Wno-error=deprecated-declarations -Wno-error=unused-function -Wno-unused-parameter -Wno-sign-compare -fstack-protector -fexceptions -Werror=reorder -Og -g2 -ggdb2   -D'PLATFORMIO=50001' -D'ARDUINO_ESP32_DEV' -D'ESP32' -D'ESP_PLATFORM' -D'F_CPU=240000000L' -D'HAVE_CONFIG_H' -D'MBEDTLS_CONFIG_FILE="mbedtls/esp_config.h"' -D'ARDUINO=10805' -D'ARDUINO_ARCH_ESP32' -D'ARDUINO_VARIANT="doitESP32devkitV1"' -D'ARDUINO_BOARD="DOIT ESP32 DEVKIT V1"' -D'__PLATFORMIO_BUILD_DEBUG__' -std=gnu++11

CXX_DEFINES = 

CXX_INCLUDES = -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\include -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\lib\StripeBridge\include -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\lib\StripeBridge\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\lib\Services -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\DNSServer\src -IC:\_Files\1_PROG~1\3_GitHub\STRIPE~1\STRIPE~1\PIO~1\libdeps\DOIT-E~1\ESPASY~1\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\WiFi\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\.pio\libdeps\doit-esp-prog-debug\AsyncTCP\src -IC:\Users\ruffo\.platformio\lib\CppLinq\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SPIFFS\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\FS\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\lib\Configuration -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\.pio\libdeps\doit-esp-prog-debug\NeoPixelBus\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SPI\src -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\.pio\libdeps\doit-esp-prog-debug\ArduinoJson\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\config -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\app_trace -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\app_update -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\asio -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\bootloader_support -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\bt -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\coap -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\console -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\driver -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp-tls -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp32 -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_adc_cal -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_event -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_http_client -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_http_server -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_https_ota -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp_ringbuf -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\ethernet -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\expat -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\fatfs -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\freemodbus -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\freertos -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\heap -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\idf_test -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\jsmn -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\json -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\libsodium -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\log -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\lwip -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\mbedtls -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\mdns -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\micro-ecc -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\mqtt -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\newlib -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\nghttp -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\nvs_flash -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\openssl -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\protobuf-c -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\protocomm -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\pthread -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\sdmmc -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\smartconfig_ack -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\soc -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\spi_flash -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\spiffs -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\tcp_transport -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\tcpip_adapter -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\ulp -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\vfs -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\wear_levelling -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\wifi_provisioning -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\wpa_supplicant -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\xtensa-debug-module -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp-face -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\esp32-camera -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\tools\sdk\include\fb_gfx -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\cores\esp32 -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\variants\doitESP32devkitV1 -IC:\_Files\1_Programming\3_GitHub\StripeTastic\StripeTastic\.pio\libdeps\doit-esp-prog-debug\arduinoFFT\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\ArduinoOTA\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\AsyncUDP\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\AzureIoT\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\BLE\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\BluetoothSerial\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\EEPROM\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\ESP32\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\ESPmDNS\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\FFat\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\HTTPClient\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\HTTPUpdate\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\NetBIOS\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\Preferences\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SD\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SD_MMC\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\SimpleBLE\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\Ticker\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\Update\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\WebServer\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\WiFiClientSecure\src -IC:\Users\ruffo\.platformio\packages\framework-arduinoespressif32\libraries\Wire\src -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\xtensa-esp32-elf\include\c++\5.2.0 -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\xtensa-esp32-elf\include\c++\5.2.0\xtensa-esp32-elf -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\lib\gcc\xtensa-esp32-elf\5.2.0\include -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\lib\gcc\xtensa-esp32-elf\5.2.0\include-fixed -IC:\Users\ruffo\.platformio\packages\toolchain-xtensa32\xtensa-esp32-elf\include -IC:\Users\ruffo\.platformio\packages\tool-unity 

