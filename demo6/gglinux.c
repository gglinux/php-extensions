#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#include "php.h"
 
 
#define phpext_gglinux_ptr &gglinux_module_entry

//http://www.cunmou.com/phpbook/7.1.md

ZEND_FUNCTION(gglinux_hello)
{
    php_printf("Hello World!\n");
}

ZEND_FUNCTION(gglinux_test_array)
{
    zval *subarray;
    array_init(return_value);

    // ["life"]=> int(42)
    add_assoc_string(return_value, "name", "gglinux",1);
    // [123]=> bool(true)
    add_index_bool(return_value, 123, 1);
    //[124]=> float(3.1415926535)
    add_next_index_double(return_value, 3.1415926535);
    // [125]=> string(3) "Foo"
    add_next_index_string(return_value, "Foo", 1);
    
    //[126]=> string(3) "Bar"
    add_next_index_string(return_value, estrdup("Bar"), 0);

    //子数组
    MAKE_STD_ZVAL(subarray);
    array_init(subarray);

    //添加值
    add_next_index_long(subarray, 1);
    add_next_index_long(subarray, 20);
    add_next_index_long(subarray, 300);

    //添加到父串中
    add_index_zval(return_value, 444, subarray);
}



static zend_function_entry gglinux_functions[] = {
    ZEND_FE(gglinux_hello, NULL) 
    ZEND_FE(gglinux_test_array, NULL)     
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

