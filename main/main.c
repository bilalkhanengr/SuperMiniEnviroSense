#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"   // declares esp_lcd_new_panel_ssd1306()
#include "esp_lcd_types.h"

#define I2C_PORT        I2C_NUM_0
#define PIN_I2C_SDA     8           // Super‑Mini default
#define PIN_I2C_SCL     9           // Super‑Mini default
#define OLED_ADDR       0x3C        // most 0.96‑inch modules
#define OLED_WIDTH      128
#define OLED_HEIGHT     64

static void i2c_master_init(void)
{
    i2c_config_t cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = PIN_I2C_SDA,
        .scl_io_num = PIN_I2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master = { .clk_speed = 400000 }
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_PORT, &cfg));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_PORT, cfg.mode, 0, 0, 0));
}

void app_main(void)
{
    i2c_master_init();

    /* -------- I²C “panel‑io” object -------- */
    esp_lcd_panel_io_handle_t io_handle;
    const esp_lcd_panel_io_i2c_config_t io_cfg = {
        .dev_addr            = OLED_ADDR,
        .control_phase_bytes = 1,    // new name in IDF v5.x
        .lcd_cmd_bits        = 8,
        .lcd_param_bits      = 8,
        .dc_bit_offset       = 6,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(I2C_PORT, &io_cfg, &io_handle));

    /* -------- SSD1306 panel driver -------- */
    esp_lcd_panel_handle_t panel_handle;
    const esp_lcd_panel_dev_config_t panel_cfg = {
        .reset_gpio_num = -1,                         // no reset pin on most breakout boards
        .color_space    = ESP_LCD_COLOR_SPACE_MONOCHROME,
        .bits_per_pixel = 1,
        .vendor_config  = NULL                       // no extra cfg struct needed now
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io_handle, &panel_cfg, &panel_handle));

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    /* -------- clear screen once -------- */
    static uint8_t blank[OLED_WIDTH * (OLED_HEIGHT / 8)] = {0};
    ESP_ERROR_CHECK(
        esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, OLED_WIDTH, OLED_HEIGHT, blank)
    );

    /* -------- demo loop: invert every second -------- */
    bool invert = false;
    while (true) {
        invert = !invert;
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, invert));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
