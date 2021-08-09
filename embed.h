#pragma once

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include <iostream>

class pysonI {
public:
    pysonI() {
        Py_Initialize();
        std::cout << "Python embedder initialized" << std::endl;
    }
    ~pysonI() {
        if (Py_FinalizeEx() < 0) {
            exit(120);
        }
        else
        std::cout << "Python embedder de-initialized" << std::endl;

    }
};
class pysonO {
    PyObject* ob;
public:
    pysonO() : ob(NULL) {}
    pysonO(PyObject* _ob) : ob(_ob) {}
    ~pysonO() {
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

long NUMERATOREX(const char* funcName, const char* fileNameWithoutPy,opython param) {

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

 const char* stringEX(const char* funcName, const char* fileNameWithoutPy, opython param) {

    pysonO pName = PyUnicode_DecodeFSDefault(fileNameWithoutPy);
    pysonO pModule = PyImport_Import(pName);
    pysonO pArgs = PyTuple_New(1);

    if (param == NULL)
        pArgs = NULL;
    else
    {
    PyTuple_SetItem(pArgs, 0, param);
    }


    if (pModule) {
        pysonO fFunc = PyObject_GetAttrString(pModule, funcName);
        if (fFunc && PyCallable_Check(fFunc))
        {
             pysonO pValue = PyObject_CallObject(fFunc, pArgs);


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
