#ifndef __Tps65__
#define __Tps65__

#include "GObj.h"
#include "GList.h"

// echo -n "Tps65" | xxd -ps
// 5470733635
#define Tps65_ID 0x54707336

#define Tps65_MEMBERS(Obj, SuperObj) \
    void* i2cPort;\
    uint8_t addr;\
    uint8_t sdaPin;\
    uint8_t sclPin;\
    uint8_t resetPin;\
    int baud;\
    int fingers;\
    int x;\
    int y;\
    int rx;\
    int ry;

#define Tps65_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id, bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr);

#define Tps65_METHODS(Obj, SuperObj) \
    METHOD(void, reset)(void);\
    METHOD(void, release)(void);\
    METHOD(uint8_t, readUByte)(uint16_t reg);\
    METHOD(uint16_t, readUWord)(uint16_t reg);\
    METHOD(int, readByte)(int reg);\
    METHOD(int, readWord)(int reg);\
    METHOD(void, write)(uint16_t reg, uint8_t data[], int nbytes);\
    METHOD(void, status)(void);\
    METHOD(void, getFinger)(void);\
    METHOD(void, _initClass)(void);

CLASS(Tps65, GObj)

extern Tps65* Tps65_new(bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr);

extern void Tps65Reset(Tps65* this);
extern void Tps65Release(Tps65* this);
extern void Tps65Init(Tps65* this, bool isPort0, int baud, int sdaPin, int sclPin, int resetPin, uint8_t addr);
extern void Tps65Write(Tps65* this, uint16_t reg, uint8_t data[], int nbytes);
extern int Tps65ReadByte(Tps65* this, int reg);
extern int Tps65ReadWord(Tps65* this, int reg);
extern uint8_t Tps65ReadUByte(Tps65* this, uint16_t reg);
extern uint16_t Tps65ReadUWord(Tps65* this, uint16_t reg);
extern Tps65* Tps65GetFinger(Tps65* this);
extern void Tps65Debug(Tps65* this);

#endif // __Tps65__
