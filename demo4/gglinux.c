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

/*
 zend_parse_parameters 解析参数
    b   Boolean
    l   Integer 整型
    d   Floating point 浮点型
    s   String 字符串
    r   Resource 资源
    a   Array 数组
    o   Object instance 对象
    O   Object instance of a specified type 特定类型的对象
    z   Non-specific zval 任意类型～
    Z   zval**类型
*/

ZEND_FUNCTION(gglinux_get_long)
{
    long foo;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &foo) == FAILURE) {
        RETURN_NULL();
    }
    php_printf("Parameter value:%ld\n", foo);
    RETURN_TRUE;
}

/*
 定义string，需要定义长度和具体的值
 多个参数，依次获取
*/
ZEND_FUNCTION(gglinux_get_str)
{
    char *name;
    int name_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&name, &name_len) == FAILURE)
    {
        RETURN_NULL();
    }
    php_printf("Hello ");
    PHPWRITE(name, name_len);
    php_printf("!\n");
}


/*
 获取默认值
    |       它之前的参数都是必须的，之后的都是非必须的，也就是有默认值的。
    !       如果接收了一个PHP语言里的null变量，则直接把其转成C语言里的NULL，而不是封装成IS_NULL类型的zval。
    /       如果传递过来的变量与别的变量共用一个zval，而且不是引用，则进行强制分离，新的zval的is_ref__gc==0, and refcount__gc==1.
*/
ZEND_FUNCTION(gglinux_get_defalut)
{
    char *name = "gglinux";
    int name_len = sizeof("gglinux") - 1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s",&name, &name_len) == FAILURE)
    {
        RETURN_NULL();
    }
    php_printf("Hello ");
    PHPWRITE(name, name_len);
    php_printf("!\n");

}


static zend_function_entry gglinux_functions[] = {
    ZEND_FE(gglinux_hello, NULL)
    ZEND_FE(gglinux_get_long, NULL)
    ZEND_FE(gglinux_get_str, NULL)
    ZEND_FE(gglinux_get_defalut, NULL)    
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

