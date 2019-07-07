#include <Python.h>
#include <iostream>
#include <string>
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))


PyObject* InsertButton(PyObject *button_name_)
{

    PyObject *null_pointer;
//
//    char *value_str = _PyUnicode_AsString(button_name_);
//    if (value_str == NULL)
//    {
//        PyErr_SetString(PyExc_TypeError, "expected a string");
//        return NULL;
//    }
//    std::cout <<"-----------good--------------"<<button_name<<std::endl;
    std::cout <<"-----------good--------------"<<std::endl;


    return null_pointer;
}


static struct PyMethodDef bpy_ops_methods[] = {
        {"InsertButton", (PyCFunction) InsertButton, METH_O, NULL},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef bpy_ops_module = {
        PyModuleDef_HEAD_INIT,
        "_bpy.ops",
        NULL,
        -1, /* multiple "initialization" just copies the module dict. */
        bpy_ops_methods,
        NULL, NULL, NULL, NULL
};

PyObject *BPY_operator_module(void)
{
    PyObject *submodule;

    submodule = PyModule_Create(&bpy_ops_module);

    return submodule;
}


bool InitCrazyPy()
{
    PyObject *mod;
    mod = PyModule_New("_crazy_py");
    /* add the module so we can import it */
    PyDict_SetItemString(PyImport_GetModuleDict(), "_crazy_py", mod);
    Py_DECREF(mod);

    PyModule_AddObject(mod, "ops", BPY_operator_module());

}

int RunPython(std::string python_root_dir,std::string python_script_path,std::string module_name,std::string exe_name)
{

    FILE *pyscript_file;
    wchar_t *program_name = Py_DecodeLocale(exe_name.c_str(), NULL);
    if (program_name == NULL)
    {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        return 1;
    }
    Py_SetProgramName(program_name);  /* optional but recommended */


    wchar_t *python_home = Py_DecodeLocale(python_root_dir.c_str(), NULL);
    Py_SetPythonHome(python_home);

    Py_Initialize();

    InitCrazyPy();


    pyscript_file = _Py_fopen(python_script_path.c_str(),"r");
    if(pyscript_file ==NULL)
    {
        fprintf(stderr, "Fatal error: cannot open script file argv[1]\n");
        return 1;
    }
    PyRun_SimpleFile(pyscript_file,module_name.c_str());

    PyMem_RawFree(program_name);

    return 0;
}

int test2()
{


    std::string python_root_dir="PYTHON_ROOT";
    std::string pyfile_path="PATH_TO_PROJECT/Main.py";
    std::string pyfile_name="Main.py";
    std::string exe_name="Python_Main";

    RunPython(python_root_dir,pyfile_path,pyfile_name,exe_name);

    return 0;
}
int main(int argc, char *argv[])
{

    test2();


}
