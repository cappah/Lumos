#include "LM.h"
#include "Core/OS.h"

namespace Lumos
{
    class UnixOS : public OS
    {
    public:
        UnixOS() {}
        ~UnixOS() {}

        void Run() override {}
    };
}