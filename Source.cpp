#include "PythonH.h"


int main()
{
        ppython pInstance;
        opython p = PyUnicode_FromString("This is a string");
        //long cl = callSpecificFunctionLong("getInteger1", "ttyon", NULL);

        const char* ci = callSpecificFunctionChar("getInteger1", "ttyon", p);
        std::cout << ci << std::endl;

    return 0;
}

