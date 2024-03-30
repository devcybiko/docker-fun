#define TRACE_OFF

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/time.h"
#include "Tps65.h"

Tps65* Tps65_new(bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr)
{
    if (Tps65$.id == 0) _initClass();
    Tps65 *this = NEW(Tps65);
    this->class = &Tps65$;
    _(this).init(Tps65_ID, isPort0,  baud,  sdaPin,  sclPin,  resetPin,  addr);
    return this;
}

static void delete()
{
    Tps65 *this = THIS(Tps65, "Tps65.delete");
    Tps65Release(this);
    __(this).delete();
}

void Tps65Debug(Tps65* this)
{
    printf("Tps65: i2cPort=%08x, addr=%02x, sdaPin=%02x, sclPin=%02x, baud=%d\n", this->i2cPort, this->addr, this->sdaPin, this->sclPin, this->baud);
}

static void debug(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Tps65 *this = THIS(Tps65, "Tps65.debug");
    __(this).debug(fmt, args);
    Tps65Debug(this);
}

void Tps65Release(Tps65* this)
{
    // release the gpio and uart pins
}

static void release() {
    Tps65 *this = THIS(Tps65, "Tps65.release");
    Tps65Release(this);
}

void Tps65Reset(Tps65* this)
{
    gpio_put(this->resetPin, 0);
    sleep_ms(200);
    gpio_put(this->resetPin, 1);
    sleep_ms(2000);
}

static void reset() {
    Tps65 *this = THIS(Tps65, "Tps65.reset");
    Tps65Reset(this);
}

void Tps65Init(Tps65* this, bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr)
{
    if (isPort0)
        this->i2cPort = i2c0;
    else
        this->i2cPort = i2c1;
    this->addr = addr;
    this->sdaPin = sdaPin;
    this->sclPin = sclPin;
    this->resetPin = resetPin;
    this->baud = baud;
    i2c_init(this->i2cPort, baud);
    gpio_set_function(sdaPin, GPIO_FUNC_I2C);
    gpio_set_function(sclPin, GPIO_FUNC_I2C);
    gpio_init(resetPin);
    gpio_set_dir(resetPin, GPIO_OUT);
    gpio_pull_up(resetPin);
    gpio_pull_up(sdaPin);
    gpio_pull_up(sclPin);
    Tps65Reset(this);
}

static void init(int id, bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr)
{
    Tps65 *this = _THIS_; // special case for init
    __(this).init(Tps65_ID); // parent init
    Tps65Init(this, isPort0, baud, sdaPin, sclPin, resetPin, addr);
}

uint8_t Tps65ReadUByte(Tps65* this, uint16_t reg)
{
    uint8_t buf[2] = { reg >> 8, reg & 0xFF };
    uint8_t data;
    Tps65Debug(this);
    i2c_write_blocking(this->i2cPort, this->addr, buf, 2, true);
    i2c_read_blocking(this->i2cPort, this->addr, &data, 1, false);
    return data;
}

static uint8_t readUByte(uint16_t reg)
{
    Tps65 *this = THIS(Tps65, "Tps65.readUByte");
    return Tps65ReadUByte(this, reg);
}

uint16_t Tps65ReadUWord(Tps65* this, uint16_t reg)
{
    uint8_t hi = Tps65ReadUByte(this, reg);
    uint8_t lo = Tps65ReadUByte(this, reg + 1);
    return (hi << 8) | lo;
}
static uint16_t readUWord(uint16_t reg)
{
    Tps65 *this = THIS(Tps65, "Tps65.readUWord");
    return Tps65ReadUWord(this, reg);
}

int Tps65ReadByte(Tps65* this, int reg)
{
    int value = Tps65ReadUByte(this, reg);
    // if (value & 0x80)
    //     value = 256 - value;
    return (int8_t)value;
}
static int readByte(int reg)
{
    Tps65 *this = THIS(Tps65, "Tps65.readByte");
    return Tps65ReadByte(this, reg);
}

int Tps65ReadWord(Tps65* this, int reg)
{
    int value = Tps65ReadUWord(this, reg);
    // if (value & 0x8000)
    //     value = 65536 - value;
    return (int16_t)value;
}
static int readWord(int reg)
{
    Tps65 *this = THIS(Tps65, "Tps65.readWord");
    return Tps65ReadWord(this, reg);
}

void Tps65Write(Tps65* this, uint16_t reg, uint8_t data[], int nbytes)
{
    uint8_t buf[nbytes + 2];
    buf[0] = reg >> 8;
    buf[1] = reg & 0xFF;
    for (int i = 0; i < nbytes; i++)
        buf[i + 2] = data[i];
    i2c_write_blocking(this->i2cPort, this->addr, buf, nbytes + 2, false);
}
static void write(uint16_t reg, uint8_t data[], int nbytes)
{
    Tps65 *this = THIS(Tps65, "Tps65.write");
    Tps65Write(this, reg, data, nbytes);
}

void TPS65Status(Tps65* this)
{
    int productNumber = Tps65ReadUWord(this, 0x00);
    int projectNumber = Tps65ReadUWord(this, 0x02);
    int version = Tps65ReadUWord(this, 0x04);
    int bootloaderStatus = Tps65ReadUByte(this, 0x06);
    int maxTouch = Tps65ReadUByte(this, 0x0b);
    int prevCycleTime = Tps65ReadUByte(this, 0x0c);
    int gestureEvents0 = Tps65ReadUByte(this, 0x0d);
    int gestureEvents1 = Tps65ReadUByte(this, 0x0e);
    int systemInfo0 = Tps65ReadUByte(this, 0x0f);
    int systemInfo1 = Tps65ReadUByte(this, 0x10);

    printf("Product Number: %04x\n", productNumber);
    printf("Project Number: %04x\n", projectNumber);
    printf("Version: %04x\n", version);
    printf("Bootloader Status: %02x\n", bootloaderStatus);
    printf("Max Touch: %02x\n", maxTouch);
    printf("Prev Cycle Time: %02x\n", prevCycleTime);
    printf("Gesture Events 0: %02x\n", gestureEvents0);
    printf("Gesture Events 1: %02x\n", gestureEvents1);
    printf("System Info 0: %02x\n", systemInfo0);
    printf("System Info 1: %02x\n", systemInfo1);
    printf("\n");
}
static void status()
{
    Tps65 *this = THIS(Tps65, "Tps65.status");
    TPS65Status(this);
}

Tps65* Tps65GetFinger(Tps65* this)
{
    int lastFingers = this->fingers;
    int lastX = this->x;
    int lastY = this->y;
    int fingers = Tps65ReadUByte(this, 0x11);
    int rx = Tps65ReadWord(this, 0x12);
    int ry = Tps65ReadWord(this, 0x14);
    int x = Tps65ReadUWord(this, 0x16);
    int y = Tps65ReadUWord(this, 0x18);
    if (fingers != lastFingers || x != lastX|| y != lastY || rx != this->rx || ry != this->ry) {
        this->fingers = fingers;
        this->x = x;
        this->y = y;
        this->rx = rx;
        this->ry = ry;
        return this;
    }
    return NULL;
}
static void getFinger()
{
    Tps65 *this = THIS(Tps65, "Tps65.getFinger");
    Tps65GetFinger(this);
}

Tps65Class Tps65$;
static void _initClass() {
    memcpy(&Tps65$, &GObj$, sizeof(GObj$));
    Tps65$.name = "Tps65";
    Tps65$.id = Tps65_ID;
    Tps65$.super = &GObj$;
    Tps65$.init = init;
    Tps65$.delete = delete;
    Tps65$.debug = debug;
    Tps65$.reset = reset;
    Tps65$.release = release;
    Tps65$.readUByte = readUByte;
    Tps65$.readUWord = readUWord;
    Tps65$.readByte = readByte;
    Tps65$.readWord = readWord;
    Tps65$.write = write;
    Tps65$.status = status;
    Tps65$.getFinger = getFinger;
}
