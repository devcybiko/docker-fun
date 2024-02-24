#include "GCronEntry.h"
#include "GTimer.h"

// constructor
GCronEntry::GCronEntry(std::string name, int msRepeat, int (*callback)(GCronEntry *self), void *context) : GObj(name)
{
    this->msRepeat = msRepeat;
    this->msLast = GTimer.mSecs();
    this->callback = callback;
    this->context = context;
}

// destructor
GCronEntry::~GCronEntry()
{
}

// basic class function to convert "name" to string
std::string GCronEntry::toString()
{
    return this->name;
}

void GCronEntry::debug(std::string message)
{
    GObj::debug(message);
    std::cout << "msRepeat: " << this->msRepeat << std::endl;
    std::cout << "msLast: " << this->msLast << std::endl;
    std::cout << "flags: " << this->flags << std::endl;
    std::cout << "context: " << this->context << std::endl;
}
