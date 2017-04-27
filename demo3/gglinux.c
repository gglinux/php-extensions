#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#include "php.h"
 
 
#define phpext_gglinux_ptr &gglinux_module_entry

ZEND_FUNCTION(gglinux_hello)
{
    php_printf("Hello World!\n");
}

/*
 返回long类型
  等效于 ZVAL_LONG(return_value, 42);
  
  zend_API.h:610 定义所有类型
*/
ZEND_FUNCTION(gglinux_long_42) 
{
    RETVAL_LONG(42);
    return;
}

/**
 返回string类型
 等效于 ZVAL_STRING(return_value, 'hello');
*/
ZEND_FUNCTION(gglinux_str_hello)
{
    RETVAL_STRING("Hello,gglinux!\n", 1);
    return;
}

/*
 返回未被使用
 return_value_used
*/
ZEND_FUNCTION(gglinux_no_return)
{
    if(return_value_used) {
        ZVAL_STRING(return_value, "hello,hello,hello\n", 1);
    } else {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE,"Warning!gglinux");
        RETURN_NULL();
    }
}

static zend_function_entry gglinux_functions[] = {
    ZEND_FE(gglinux_hello, NULL)
    ZEND_FE(gglinux_long_42, NULL)
    ZEND_FE(gglinux_str_hello, NULL)
    ZEND_FE(gglinux_no_return, NULL)
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

