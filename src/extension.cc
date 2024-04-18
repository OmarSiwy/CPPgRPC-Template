#include <Python.h>

// Function to be called from Python
static PyObject* crunch(PyObject *self, PyObject *args) {
    int a, b;
    // Parse a tuple of two integers from Python to C++
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL;  // Return NULL if parsing fails
    }
    int result = a * b;  // Perform the multiplication (or any other complex operation)
    // Convert the C++ int result back to Python integer and return
    return PyLong_FromLong(result);
}

static PyObject* bin_exp(PyObject *self, PyObject *args) {
    long long a, b;
    // Parse a tuple of two integers from Python to C++
    if (!PyArg_ParseTuple(args, "LL", &a, &b)) {
        return NULL;  // Return NULL if parsing fails
    }

    long long result = 1;  // Initialize result
    while (b > 0) {
        if (b & 1)  // If b is odd, multiply the base with result
            result = result * a;
        a = a * a;  // Square the base
        b >>= 1;  // Right shift the exponent
    }

    // Convert the C++ long long result back to Python integer and return
    return PyLong_FromLongLong(result);
}


// PYTHON INTERFACE ____________________________________________________________________________________


/*
  * This Initializes the Module that will be passed onto Python
  * parameters: { "function_name", function_pointer, METH_VARARGS, "function_description"}
  */
PyMethodDef gRPCNvidia_methods[] = {
  { "crunch", crunch, METH_VARARGS, "A number-crunching function." },
  { "bin_exp", bin_exp, METH_VARARGS, "Binary exponentiation function." },
};


/*
  * This is the Module Definition that will be passed onto Python
  * parameters: { "module_name", method_table }
  */
struct PyModuleDef gRPCNvidia_module = {
  PyModuleDef_HEAD_INIT,
  "gRPCNvidia",
  nullptr,
  -1,
  gRPCNvidia_methods
};


// Initialization Functions
PyMODINIT_FUNC PyInit_gRPCNvidia(void) {
  return PyModule_Create(&gRPCNvidia_module);
}
