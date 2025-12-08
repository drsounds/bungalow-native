//
// Created by Alexander Forselius on 2025-12-08.
//

#include "SPNavigateEventArgs.h"

#include "SPObject.h"

namespace space
{
    SPNavigateEventArgs::SPNavigateEventArgs(string url)
    {
        this->url = url;
    }

    SPNavigateEventArgs::~SPNavigateEventArgs()
    {
    }
} // space