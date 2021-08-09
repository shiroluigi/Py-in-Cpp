#include "embed.h"


int main()
{
        pysonI pInstance;
        pysonO p = PyUnicode_FromString("This is a string");

        const char* s = stringEX("getInteger1", "pyson", p);
        std::cout << s << std::endl;

    return 0;
}

