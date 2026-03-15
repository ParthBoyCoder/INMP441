#include <driver/i2s.h>

#define I2S_SAMPLE_RATE 16000

#define I2S_BCLK 26
#define I2S_LRCL 25
#define I2S_DIN  22

void setup() {
  Serial.begin(115200);

  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 256,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRCL,
    .data_out_num = -1,
    .data_in_num = I2S_DIN
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);

  Serial.println("INMP441 READY — TALK! 🎤🔥");
}

void loop() {
  int32_t buffer[256];
  size_t bytes_read;

  i2s_read(I2S_NUM_0, buffer, sizeof(buffer), &bytes_read, portMAX_DELAY);

  for (int i = 0; i < 10; i++) {
    Serial.println(buffer[i] >> 14);
  }

  delay(100);
}
