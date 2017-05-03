 #include "php_gglinux.h"

//http://www.laruence.com/2009/04/28/719.html

//申明全局变量
ZEND_DECLARE_MODULE_GLOBALS(gglinux);   



/*
 zend_gglinux_globals 定义好后，自动生成
*/
static void php_gglinux_globals_ctor(zend_gglinux_globals *gglinux_globals TSRMLS_DC)
{
    //初始化全局变量
     gglinux_globals->global_counter = 0;
}
 

/*
函数声明宏	语义
PHP_MINIT_FUNCTION()	当PHP被装载时，模块启动函数即被引擎调用。这使得引擎做一些例如资源类型，注册INI变量等的一次初始化。
PHP_MSHUTDOWN_FUNCTION()	当PHP完全关闭时，模块关闭函数即被引擎调用。通常用于注销INI条目
PHP_RINIT_FUNCTION()	在每次PHP请求开始，请求前启动函数被调用。通常用于管理请求前逻辑。
PHP_RSHUTDOWN_FUNCTION()	在每次PHP请求结束后，请求前关闭函数被调用。经常应用在清理请求前启动函数的逻辑。
PHP_MINFO_FUNCTION()	调用phpinfo()时模块信息函数被呼叫，从而打印出模块信息。
*/
//PHP 装载即被加载
PHP_MINIT_FUNCTION(gglinux)
{
    //装载阶段 初始化全局变量
     ZEND_INIT_MODULE_GLOBALS(gglinux, php_gglinux_globals_ctor, NULL);

    return SUCCESS;
}

//http://www.cunmou.com/phpbook/9.1.md

ZEND_FUNCTION(gglinux_hello)
{
    php_printf("Hello World!\n");
}

// 增加测试函数
PHP_FUNCTION(gglinux_global_value)
{

    GGLINUX_G(global_counter)++;
    RETURN_LONG(GGLINUX_G(global_counter));

}


static zend_function_entry gglinux_functions[] = {
    ZEND_FE(gglinux_hello, NULL) 
    ZEND_FE(gglinux_global_value, NULL)  
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
    ZEND_MINIT(gglinux),/* MINIT php装载阶段*/
    NULL, /* MSHUTDOWN 当PHP完全关闭 */
    NULL, /* RINIT 每次PHP请求开始 */
    NULL, /* RSHUTDOWN 在每次PHP请求结束后*/
    NULL, /* MINFO 调用phpinfo()时模块 */
#if ZEND_MODULE_API_NO >= 20010901
    "2.1",
#endif
    STANDARD_MODULE_PROPERTIES
};
 
#ifdef COMPILE_DL_GGLINUX
ZEND_GET_MODULE(gglinux)
#endif

