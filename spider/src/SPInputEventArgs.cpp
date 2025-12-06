#include "SPInputEventArgs.h"
namespace spider {
SPInputEventArgs::SPInputEventArgs(string text)
    : EventArgs()
{
    //ctor
    this->text = text;
}

SPInputEventArgs::~SPInputEventArgs()
{
    //dtor
}
}
