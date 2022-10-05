/**
 * Configure the sample frequency. This is the frequency used to send the data
 * to the studio regardless of the frequency used to sample the data from the
 * sensor. This differs per sensors, and can be modified in the API of the sensor
 */
#define FREQUENCY_HZ        10

/* Include ----------------------------------------------------------------- */
#include "Arduino_BHY2.h"

/* Constants --------------------------------------------------------------- */
#define INTERVAL_MS         (1000 / FREQUENCY_HZ)
#define CONVERT_G_TO_MS2    9.80665f

/* Forward declerations ---------------------------------------------------- */
void ei_printf(const char *format, ...);

/* Private variables ------------------------------------------------------- */
static unsigned long last_interval_ms = 0;

Sensor gas(SENSOR_ID_GAS);

void setup() {
    /* Init serial */
    Serial.begin(115200);
    Serial.println("Edge Impulse sensor data ingestion\r\n");

    /* Init & start gas sensor */
    BHY2.begin(NICLA_I2C);
    gas.begin();
}

void loop() {

    BHY2.update();
    delay(INTERVAL_MS);

    ei_printf("%.2f", gas.value());
    ei_printf("\r\n");
}

/**
* @brief      Printf function uses vsnprintf and output using Arduino Serial
*
* @param[in]  format     Variable argument list
*/
void ei_printf(const char *format, ...)
{
    static char print_buf[1024] = { 0 };

    va_list args;
    va_start(args, format);
    int r = vsnprintf(print_buf, sizeof(print_buf), format, args);
    va_end(args);

    if (r > 0) {
        Serial.write(print_buf);
    }
}
