#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#include "php.h"
 
 
#define phpext_gglinux_ptr &gglinux_module_entry

ZEND_FUNCTION(gglinux_hello)
{
    php_printf("Hello World!");
}

static zend_function_entry gglinux_functions[] = {
    ZEND_FE(gglinux_hello, NULL)
    {
        NULL,
        NULL,
        NULL
    }
};

zend_module_entry gglinux_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
     STANDARD_MODULE_HEADER,
#endif
    "gglinux", 
    gglinux_functions, /* Functions */
    NULL, /* MINIT */
    NULL, /* MSHUTDOWN */
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    "2.1",
#endif
    STANDARD_MODULE_PROPERTIES
};
 
#ifdef COMPILE_DL_GGLINUX
ZEND_GET_MODULE(gglinux)
#endif

