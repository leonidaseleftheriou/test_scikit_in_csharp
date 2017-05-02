#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <python2.7/Python.h>
#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>
#include "python2.7/numpy/arrayobject.h"


void * initialize_classifier(char *script, char *function) {
	printf("entered INITIALIZATION c-library \n");
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue, *pValue2;
	int i;
	
	dlopen("libpython2.7.so.1", RTLD_LAZY | RTLD_GLOBAL);
	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\".\")");
	pName = PyString_FromString(script);

	pModule = PyImport_Import(pName);
	if (pModule == NULL) {
		printf(" PMODULE IS NULL!!!!! \n");
	}
	Py_DECREF(pName);
	import_array();
	if (pModule != NULL) {
		pDict = PyModule_GetDict(pModule);
		pFunc = PyDict_GetItemString(pDict, function);

		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(1);
			int dims[1] = { 4000 };
			int args2[4] = {1,2,3,4};
			int a_useless = 1; // just to pass something to the python script
			int paok = PyTuple_SetItem(pArgs, 0, PyInt_FromLong(a_useless));
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL) {
				return (void *)pValue;	
				 //Py_DECREF(pValue);
			}
			else {
					 Py_DECREF(pModule);
					 PyErr_Print();
					 fprintf(stderr,"Call failed\n");
			}
            /* pDict and pFunc are borrowed and must not be Py_DECREF-ed */
       		}
       		 else {
           		 if (PyErr_Occurred())
                		PyErr_Print();
           		 fprintf(stderr, "Cannot find function \"%s\"\n", function);
       		}
       		 Py_DECREF(pModule);
   	 }
   	else {
       		PyErr_Print();
       		fprintf(stderr, "Failed to load \"%s\"\n", script);
       		 //return 1;
    }
	printf("Check exception 111\n");
	//Py_Finalize();
	printf("Check exception 2\n");
	
}


void * train(char *script, char *function, double args[], int totalsize, int numOfArgs, PyObject* classifier, PyObject* coeff_ptr) {
	printf("entered TRAIN c-library \n");
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue, *pValue2;
	int i;
	
	dlopen("libpython2.7.so.1", RTLD_LAZY | RTLD_GLOBAL);
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\".\")");
	pName = PyString_FromString(script);
	pModule = PyImport_Import(pName);
	
		
	if (pModule == NULL) {
		printf(" PMODULE IS NULL!!!!! \n");
	}
	Py_DECREF(pName);
	
	import_array();
	
	if (pModule != NULL) {
		PyErr_Print();
		pDict = PyModule_GetDict(pModule);
		PyErr_Print();
		pFunc = PyDict_GetItemString(pDict, function);
		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(4);
			npy_intp dim = totalsize;
			pValue = PyArray_SimpleNewFromData(1, &dim, NPY_DOUBLE, args);
			if (!pValue) {
				Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert argument\n");
				//return 1;
			}
			// pValue reference stolen here: //
			int paok = PyTuple_SetItem(pArgs, 0, pValue);
			paok = PyTuple_SetItem(pArgs, 1, PyInt_FromLong(numOfArgs));			
			paok = PyTuple_SetItem(pArgs, 2, classifier);
			paok = PyTuple_SetItem(pArgs, 3, coeff_ptr);

			 PyObject* pValue4 = PyObject_CallObject(pFunc, pArgs);
			 //PyObject_CallObject(pFunc, pArgs);
			 Py_DECREF(pArgs);
			 if (pValue != NULL) {
				 PyObject *pValue0, *pValue1;

			 }
			 else {
				 Py_DECREF(pModule);
				 PyErr_Print();
				 fprintf(stderr,"Call failed\n");
					 //return 1;
			 }
            /* pDict and pFunc are borrowed and must not be Py_DECREF-ed */
       		 }
       		 else {
           		 if (PyErr_Occurred())
                		PyErr_Print();
           		 fprintf(stderr, "Cannot find function \"%s\"\n", function);
       		 }
       		 Py_DECREF(pModule);
   	 }
   	 else {
       		 PyErr_Print();
       		 fprintf(stderr, "Failed to load \"%s\"\n", script);
       		 //return 1;
      }
	//Py_Finalize();
	//return (void *)pValue4;
	//return 0;
}




void * return_results(char *script, char *function, PyObject* classifier) {
	printf("entered RETURN_RESULTS c-library \n");
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue, *pValue2;
	int i;
	double *temp;
	dlopen("libpython2.7.so.1", RTLD_LAZY | RTLD_GLOBAL);
	//Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\".\")");
	pName = PyString_FromString(script);
	pModule = PyImport_Import(pName);
	if (pModule == NULL) {
		printf(" PMODULE IS NULL!!!!! \n");
	}
	Py_DECREF(pName);
	import_array();
	if (pModule != NULL) {
		pDict = PyModule_GetDict(pModule);
		pFunc = PyDict_GetItemString(pDict, function);

		if (pFunc && PyCallable_Check(pFunc)) {
			//pArgs = PyTuple_New(numOfArgs);
			pArgs = PyTuple_New(1);
			//npy_intp dims[1] = { 2 };
			int dims[1] = { 4000 };
			int args2[4] = {1,2,3,4};	
			if (!pValue) {
				Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert argument\n");
				//return 1;
				}

			int paok = PyTuple_SetItem(pArgs, 0, classifier);
			pValue = PyObject_CallObject(pFunc, pArgs);
			//PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL) {
				 PyObject *pValue0, *pValue1;
				 //pValue0 = PyList_GetItem(pValue,0);
				 printf("Result of call: %d\n", PyList_Check(pValue));
				 int count = (int) PyList_Size(pValue);
				 temp = (double *) malloc(count*sizeof(double));
				 PyObject *ptemp, *objectsRepresentation ;
				 char* a11;

				 for (i = 0 ; i < count ; i++ )
				 {
					 ptemp = PyList_GetItem(pValue,i);
					 objectsRepresentation = PyObject_Repr(ptemp);
					 a11 = PyString_AsString(objectsRepresentation);
					 temp[i] = (double)strtod(a11,NULL);

				 }

					Py_DECREF(pValue);
			}
			else {
					 Py_DECREF(pModule);
					 PyErr_Print();
					 fprintf(stderr,"Call failed\n");
					 //return 1;
			}
            /* pDict and pFunc are borrowed and must not be Py_DECREF-ed */
		 }
		 else {
			 if (PyErr_Occurred())
					PyErr_Print();
			 fprintf(stderr, "Cannot find function \"%s\"\n", function);
		 }
		 Py_DECREF(pModule);
   	 }
   	 else {
       		 PyErr_Print();
       		 fprintf(stderr, "Failed to load \"%s\"\n", script);
       		 //return 1;
     }
	//Py_Finalize();
	return (void *)temp;
	//return 0;
}
