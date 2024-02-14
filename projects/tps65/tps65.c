#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

static uint8_t addr = 0x74;

#define DEBUG quiet

void quiet()
{
}

typedef struct _TPS65
{
    void *i2cPort;
    uint8_t addr;
    uint8_t sdaPin;
    uint8_t sclPin;
    int baud;
} TPS65;

void TPS65Debug(TPS65 *this)
{
    DEBUG("TPS65: i2cPort=%08x, addr=%02x, sdaPin=%02x, sclPin=%02x, baud=%d\n", this->i2cPort, this->addr, this->sdaPin, this->sclPin, this->baud);
}

void TPS65Init(TPS65 *this, bool isPort0, int baud, int sdaPin, int sclPin, uint8_t addr)
{
    if (isPort0)
        this->i2cPort = i2c0;
    else
        this->i2cPort = i2c1;
    this->addr = addr;
    this->sdaPin = sdaPin;
    this->sclPin = sclPin;
    this->baud = baud;
    i2c_init(this->i2cPort, baud);
    gpio_set_function(sdaPin, GPIO_FUNC_I2C);
    gpio_set_function(sclPin, GPIO_FUNC_I2C);
    gpio_pull_up(sdaPin);
    gpio_pull_up(sclPin);
}

uint8_t TPS65ReadByte(TPS65 *this, uint16_t reg)
{
    uint8_t buf[2] = {reg >> 8, reg & 0xFF};
    uint8_t data;
    TPS65Debug(this);
    DEBUG("addressing... %02x, reg=%02x %02x\n", this->addr, buf[0], buf[1]);
    i2c_write_blocking(this->i2cPort, this->addr, buf, 2, true);
    DEBUG("reading... %02x\n", this->addr);
    i2c_read_blocking(this->i2cPort, this->addr, &data, 1, false);
    DEBUG("Got... %02x\n", data);
    return data;
}

uint16_t TPS65ReadWord(TPS65 *this, uint16_t reg)
{
    uint8_t hi = TPS65ReadByte(this, reg);
    uint8_t lo = TPS65ReadByte(this, reg + 1);
    return (hi << 8) | lo;
}

void TPS65Write(TPS65 *this, uint16_t reg, uint8_t data[], int nbytes)
{
    uint8_t buf[nbytes + 2];
    buf[0] = reg >> 8;
    buf[1] = reg & 0xFF;
    for (int i = 0; i < nbytes; i++)
        buf[i + 2] = data[i];
    i2c_write_blocking(this->i2cPort, this->addr, buf, nbytes + 2, false);
}

void TPS65Release(TPS65 *this)
{
    // TODO: release I2C and GPIO Pins
    free(this);
}

TPS65 *newTPS65(bool isPort0, int baud, int sdaPin, int sclPin, uint8_t addr)
{
    TPS65 *obj = (TPS65 *)malloc(sizeof(TPS65));
    TPS65Init(obj, isPort0, baud, sdaPin, sclPin, addr);
    return obj;
}
int blink(int onms, int offms)
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    sleep_ms(onms);
    gpio_put(LED_PIN, 0);
    sleep_ms(offms);
}

// Initialise Accelerometer Function
// void glsTPS65Init(void)
// {
//     // Check to see if connection is correct
//     sleep_ms(1000); // Add a short delay to help BNO005 boot up
//     uint8_t reg[2] = {0x00, 0x00};
//     uint8_t chipID[2] = {0x00, 0x00};

//     while (1)
//     {
//         blink(75, 75);
//         i2c_write_blocking(I2C_PORT, addr, reg, 2, true);
//         i2c_read_blocking(I2C_PORT, addr, chipID, 1, false);
//         printf("\nAddr: 0x%02x%02x... Chip ID: 0x%02x%02x", reg[0], reg[1], chipID[0], chipID[1]);
//         reg[1]++;
//         if (reg[1] == 0x00)
//             reg[0]++;
//     }
// }

// void glsI2CInit(uint kbaud, uint sda, uint scl)
// {
//     i2c_init(I2C_PORT, kbaud * 1000);
//     printf("70\n");
//     gpio_set_function(sda, GPIO_FUNC_I2C);
//     printf("72\n");
//     gpio_set_function(scl, GPIO_FUNC_I2C);
//     printf("74\n");
//     gpio_pull_up(sda);
//     printf("76\n");
//     gpio_pull_up(scl);
//     printf("78\n");
// }
int main(void)
{
    stdio_init_all(); // Initialise STD I/O for printing over serial
    blink(75, 500);
    printf("\nTPS65 for Raspberry Pi Pico (c) 2024 Agile Frontiers\n");
    blink(75, 500);
    TPS65 *tps65 = newTPS65(false, 400, 2, 3, 0x74);
    blink(75, 500);
    printf("\nGot the tps65 object %08x\n", tps65);
    for(int i=0; i<16; i++)
    {
        blink(75, 75);
        printf("Addr: 0x%04x, Value: 0x%02x\n", i, TPS65ReadByte(tps65, i));
    }
    int cnt = 0;
    while(true) {
        cnt++;
        blink(75, 75);
        int nfingers = TPS65ReadByte(tps65, 0x11);
        int x = TPS65ReadWord(tps65, 0x12);
        int y = TPS65ReadWord(tps65, 0x14);
        if (nfingers) printf("CNT: %d, Fingers: %d, X: %d, Y: %d\n", cnt, nfingers, x, y);
    }
}
