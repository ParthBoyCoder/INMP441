#include <WiFi.h>
#include <WebSocketsServer.h>
#include <driver/i2s.h>

#define WIFI_SSID "PRADIP -2.4Ghz"
#define WIFI_PASS "Pradip@123"

#define I2S_SAMPLE_RATE 16000
#define I2S_BCLK 26
#define I2S_LRCL 25
#define I2S_DIN  22

WebSocketsServer wsServer(81);

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  Serial.println(WiFi.localIP());

  wsServer.begin();

  i2s_config_t config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 1024,
    .use_apll = false
  };

  i2s_pin_config_t pins = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRCL,
    .data_out_num = -1,
    .data_in_num = I2S_DIN
  };

  i2s_driver_install(I2S_NUM_0, &config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pins);
  i2s_zero_dma_buffer(I2S_NUM_0);
}

void loop() {
  wsServer.loop();

  const int samples = 512;
  int32_t buffer32[samples];
  int16_t buffer16[samples];

  size_t bytesRead;
  i2s_read(I2S_NUM_0, buffer32, sizeof(buffer32), &bytesRead, portMAX_DELAY);

  for (int i = 0; i < samples; i++) {
    buffer16[i] = buffer32[i] >> 16;  // convert 32 → 16 bit cleanly
  }

  wsServer.broadcastBIN((uint8_t*)buffer16, samples * 2);
  
  delay(16);  // send frames at correct timing (~60fps audio chunks)
}
