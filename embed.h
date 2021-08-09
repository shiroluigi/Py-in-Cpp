#pragma once

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include <iostream>

class ppython {
public:
    ppython() {
        Py_Initialize();
        std::cout << "Python interpreter initialized" << std::endl;
    }
    ~ppython() {
        if (Py_FinalizeEx() < 0) {
            exit(120);
        }
        else
        std::cout << "Python interpreter de-initialized" << std::endl;

    }
};
class opython {
    PyObject* ob;
public:
    opython() : ob(NULL) {}
    opython(PyObject* _ob) : ob(_ob) {}
    ~opython() {
        if (ob) {
            Py_DECREF(ob);
        }
        ob = NULL;
    }


    PyObject* AddRef()
    {
        if (ob)
        {
            Py_INCREF(ob);
        }
        return ob;
    }
 
    operator PyObject* ()
    {
        return ob;
    }

    PyObject* operator = (PyObject* pp)
    {
        ob = pp;
        return ob;
    }

    PyObject* operator ->()
    {
        return ob;
    }
    PyObject* getValue() {
        return ob;
    }
};

void RunPythonScript(const char* Location,const char* fileName) {
    FILE* PythonFile = fopen(Location, "r");
    if (PythonFile) {
        PyRun_SimpleFile(PythonFile, fileName);
        fclose(PythonFile);
    }
}

long callSpecificFunctionLong(const char* funcName, const char* fileNameWithoutPy,opython param) {

    opython pName = PyUnicode_FromString(fileNameWithoutPy);
    opython pModule = PyImport_Import(pName);

    if (pModule) {
        opython fFunc = PyObject_GetAttrString(pModule, funcName);
        if (fFunc && PyCallable_Check(fFunc))
        {
            opython pValue = PyObject_CallObject(fFunc, param);

            std::cout << "result = " << PyLong_AsLong(pValue) << std::endl;;
            return PyLong_AsLong(pValue);
        }
        else
        {
            std::cout << "ERROR: function " << std::endl;
            return 0;
        }
    }
    else
    {
        fprintf(stderr,"ERROR: Module not imported");
        return 0;
    }

    
}

 const char* callSpecificFunctionChar(const char* funcName, const char* fileNameWithoutPy, opython param) {

    opython pName = PyUnicode_DecodeFSDefault(fileNameWithoutPy);
    opython pModule = PyImport_Import(pName);
    opython pArgs = PyTuple_New(1);

    //checking if the parameters are NULL (0)
    //if not then setting up a Tuple to store thhe valus
    if (param == NULL)
        pArgs = NULL;
    else
    {
    PyTuple_SetItem(pArgs, 0, param);
    }


    if (pModule) {
        opython fFunc = PyObject_GetAttrString(pModule, funcName);
        if (fFunc && PyCallable_Check(fFunc))
        {
             opython pValue = PyObject_CallObject(fFunc, pArgs);

             //dont start this faking debug sentance without knowing tje working!
             //std::cout << PyUnicode_AsUTF8(param) << std::endl;

             return PyUnicode_AsUTF8(pValue);
            
        }
        else
        {
            std::cout << "ERROR: function " << std::endl;
            return 0;
        }
    }
    else
    {
        std::cout << "ERROR: Module not imported" << std::endl;
        return 0;
    }

    std::cout << "Program end" << std::endl;

}
