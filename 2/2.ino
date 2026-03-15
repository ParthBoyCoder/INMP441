#include <WiFi.h>
#include <WebSocketsServer.h>
#include <driver/i2s.h>

#define WIFI_SSID "UR SSID"
#define WIFI_PASS "UR PASS"

#define I2S_BCLK 26
#define I2S_LRCL 25
#define I2S_DIN  22

#define SAMPLE_RATE 16000

WebSocketsServer webSocket = WebSocketsServer(81);

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(300);
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent([](uint8_t num, WStype_t type, uint8_t * payload, size_t length){});

  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 4,
    .dma_buf_len = 256,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pins = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRCL,
    .data_out_num = -1,
    .data_in_num = I2S_DIN
  };

  i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pins);
  i2s_zero_dma_buffer(I2S_NUM_0);
}

void loop() {
  webSocket.loop();

  static int32_t buf[256];
  size_t bytesRead;

  i2s_read(I2S_NUM_0, buf, sizeof(buf), &bytesRead, portMAX_DELAY);

  int samples = bytesRead / 4;
  int16_t out[256];

  for (int i = 0; i < samples; i++)
    out[i] = buf[i] >> 14;

  webSocket.broadcastBIN((uint8_t*)out, samples * 2);
}
