//
// MATLAB Compiler: 23.2 (R2023b)
// Date: Fri May 10 21:12:03 2024
// Arguments:
// "-B""macro_default""-W""cpplib:UsbConnect""-T""link:lib""connectVisa.m""disco
// nnectVisa.m"
//

#ifndef UsbConnect_h
#define UsbConnect_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_UsbConnect_C_API 
#define LIB_UsbConnect_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_UsbConnect_C_API 
bool MW_CALL_CONV UsbConnectInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_UsbConnect_C_API 
bool MW_CALL_CONV UsbConnectInitialize(void);
extern LIB_UsbConnect_C_API 
void MW_CALL_CONV UsbConnectTerminate(void);

extern LIB_UsbConnect_C_API 
void MW_CALL_CONV UsbConnectPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_UsbConnect_C_API 
bool MW_CALL_CONV mlxConnectVisa(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_UsbConnect_C_API 
bool MW_CALL_CONV mlxDisconnectVisa(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_UsbConnect
#define PUBLIC_UsbConnect_CPP_API __declspec(dllexport)
#else
#define PUBLIC_UsbConnect_CPP_API __declspec(dllimport)
#endif

#define LIB_UsbConnect_CPP_API PUBLIC_UsbConnect_CPP_API

#else

#if !defined(LIB_UsbConnect_CPP_API)
#if defined(LIB_UsbConnect_C_API)
#define LIB_UsbConnect_CPP_API LIB_UsbConnect_C_API
#else
#define LIB_UsbConnect_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_UsbConnect_CPP_API void MW_CALL_CONV connectVisa(int nargout, mwArray& isConnected);

extern LIB_UsbConnect_CPP_API void MW_CALL_CONV disconnectVisa(int nargout, mwArray& isConnected);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
