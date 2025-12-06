#include "SPInputEventArgs.h"
namespace spider {
SPInputEventArgs::SPInputEventArgs(string text)
    : SPEventArgs()
{
    //ctor
    this->text = text;
}

SPInputEventArgs::~SPInputEventArgs()
{
    //dtor
}
}
