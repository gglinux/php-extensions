#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#include "php.h"
 
 
#define phpext_gglinux_ptr &gglinux_module_entry

//http://www.laruence.com/2009/04/28/719.html


static  ulong le_sample_descriptor;

/*
 资源释放时调用的函数
*/
static void myfile_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC){
     FILE *fp = (FILE *) rsrc->ptr;
     fclose(fp);
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
ZEND_MINIT_FUNCTION(gglinux_file)
{
    //module_number 已经被定义好
    le_sample_descriptor = zend_register_list_destructors_ex(myfile_dtor, NULL, "gglinux file resource", module_number);
    return SUCCESS;
}

//http://www.cunmou.com/phpbook/9.1.md

ZEND_FUNCTION(gglinux_hello)
{
    php_printf("Hello World!\n");
}

PHP_FUNCTION(gglinux_fopen)
{
     char *filename = NULL;
     char *mode = NULL;
     int argc = ZEND_NUM_ARGS();
     int filename_len;
     int mode_len;
     FILE *fp;
 
     if (zend_parse_parameters(argc TSRMLS_CC, "ss", &filename,&filename_len, &mode, &mode_len) == FAILURE) {
          RETURN_NULL();
     }
     // 虚拟当前工作目录 完成文件打开
     fp = VCWD_FOPEN(filename, mode);
 
     if (fp == NULL) {
          RETURN_FALSE;
     }
 
     /*
         宏参数	参数类型
        rsrc_result	zval *, 设置为已注册资源信息
        rsrc_pointer 资源数据指针
        rsrc_type 注册资源类型时获得的资源id
     */
     ZEND_REGISTER_RESOURCE(return_value, fp, le_sample_descriptor);
}

PHP_FUNCTION(gglinux_fclose)
{
     int argc = ZEND_NUM_ARGS();
     zval *filehandle = NULL;
 
     if (zend_parse_parameters(argc TSRMLS_CC, "r", &filehandle) == FAILURE) {
          return;
     }
     
     //判断是否是资源类型，如果为资源类型，则删除
     if (zend_list_delete(Z_RESVAL_P(filehandle)) == FAILURE) {
          RETURN_FALSE;
     }
 
     RETURN_TRUE;
}

//判断文件是否结束
PHP_FUNCTION(gglinux_eof)
{
     int argc = ZEND_NUM_ARGS();
     zval *filehandle = NULL;
     FILE *fp;
 
     if (zend_parse_parameters(argc TSRMLS_CC, "r", &filehandle) ==FAILURE) {
          return;
     }
     /* 
        参数	含义
        rsrc	资源值保存到的变量名。它应该和资源有相同类型。
        rsrc_type	rsrc的类型，用于在内部把资源转换成正确的类型
        passed_id	寻找的资源值(例如zval **)
        default_id	如果该值不为-1，就使用这个id。用于实现资源的默认值。
        resource_type_name	资源的一个简短名称，用于错误信息。
        resource_type	注册资源的资源类型id
     */
     ZEND_FETCH_RESOURCE(fp, FILE *, &filehandle, -1, "gglinux file resource",le_sample_descriptor);
 
     if (fp == NULL){
          RETURN_FALSE;
     } 
 
     if (feof(fp)) {
        /* Return eof also if there was an error */
          RETURN_TRUE;
     }
 
     RETURN_FALSE;
}

//文件写入
PHP_FUNCTION(gglinux_fwrite)
{
     char *buffer = NULL;
     int argc = ZEND_NUM_ARGS();
     int buffer_len;
     zval *filehandle = NULL;
     FILE *fp;
 
     if (zend_parse_parameters(argc TSRMLS_CC, "rs", &filehandle,&buffer, &buffer_len) == FAILURE) {
          return;
     }
      /* 
        参数	含义
        rsrc	资源值保存到的变量名。它应该和资源有相同类型。
        rsrc_type	rsrc的类型，用于在内部把资源转换成正确的类型
        passed_id	寻找的资源值(例如zval **)
        default_id	如果该值不为-1，就使用这个id。用于实现资源的默认值。
        resource_type_name	资源的一个简短名称，用于错误信息。
        resource_type	注册资源的资源类型id
     */
     ZEND_FETCH_RESOURCE(fp, FILE *, &filehandle, -1, "gglinux file resource", le_sample_descriptor);
 
     if (fwrite(buffer, 1, buffer_len, fp) != buffer_len) {
          RETURN_FALSE;
     }
 
     RETURN_TRUE;
}

//文件读取
PHP_FUNCTION(gglinux_fread)
{
     int argc = ZEND_NUM_ARGS();
     long size;
     zval *filehandle = NULL;
     FILE *fp;
     char *result;
     size_t bytes_read;
 
     if (zend_parse_parameters(argc TSRMLS_CC, "rl", &filehandle,&size) == FAILURE) {
          return;
     }
 
     ZEND_FETCH_RESOURCE(fp, FILE *, &filehandle, -1, "gglinux file resource", le_sample_descriptor);
 
     result = (char *) emalloc(size+1);
 
     bytes_read = fread(result, 1, size, fp);
 
     result[bytes_read] = '\0';
 
     RETURN_STRING(result, 0);
}




static zend_function_entry gglinux_functions[] = {
    ZEND_FE(gglinux_hello, NULL) 
    ZEND_FE(gglinux_fopen, NULL) 
    ZEND_FE(gglinux_fread, NULL) 
    ZEND_FE(gglinux_fwrite, NULL) 
    ZEND_FE(gglinux_eof, NULL) 
    ZEND_FE(gglinux_fclose, NULL)     
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
    ZEND_MINIT(gglinux_file),/* MINIT php装载阶段*/
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

