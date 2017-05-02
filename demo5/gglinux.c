#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#include "php.h"
 
 
#define phpext_gglinux_ptr &gglinux_module_entry

//http://www.cunmou.com/phpbook/8.1.md

ZEND_FUNCTION(gglinux_hello)
{
    php_printf("Hello World!\n");
}

/*
内存管理

emalloc(size_t size);
 
efree(void *ptr);
 
ecalloc(size_t nmemb, size_t size);
 
erealloc(void *ptr, size_t size);
 
estrdup(const char *s);
 
estrndup(const char *s, unsigned int length);

*/
ZEND_FUNCTION(gglinux_test_hashtable)
{
    HashTable *test_ht;
    int ht_len = 10;
    test_ht = test_hashtable_create(test_ht,ht_len);
    test_hashtable_scan(test_ht);
    //毁尸灭迹
    zend_hash_destroy(test_ht);
 
    FREE_HASHTABLE(test_ht);
    return SUCCESS;

    
}

/*
   新建哈希表
*/
void test_hashtable_create(HashTable *ht, int hashtable_len)
{
        //分配内存
    ALLOC_HASHTABLE(ht);

    //初始化
    if (zend_hash_init(ht, hashtable_len, NULL,ZVAL_PTR_DTOR, 0) == FAILURE) {
        FREE_HASHTABLE(ht);
        return FAILURE;
    }
    int i;

    for (i = 0; i < hashtable_len; i++)
    {
        zval *value;
        MAKE_STD_ZVAL(value);
        ZVAL_LONG(value, i);
        i++;
        //添加数据(不需要索引值参数)
        if(zend_hash_next_index_insert(ht, (void **) &value, sizeof(zval *), NULL) == FAILURE) {
            //更新引用计数
            zval_ptr_dtor(&value);
        }
    }
    return ht;
}

/*
    遍历哈希表 回调方法
*/
int test_print_zval(zval **val TSRMLS_DC)
{
    //重新copy一个zval，防止破坏原数据
    zval tmpcopy = **val;
    zval_copy_ctor(&tmpcopy);
     
    //转换为字符串
    INIT_PZVAL(&tmpcopy);
    convert_to_string(&tmpcopy);
    
    //开始输出
    php_printf("The value is: ");
    PHPWRITE(Z_STRVAL(tmpcopy), Z_STRLEN(tmpcopy));
    php_printf("\n");
     
    //毁尸灭迹
    zval_dtor(&tmpcopy);
     
    //返回，继续遍历下一个
    return ZEND_HASH_APPLY_KEEP;
}

/*
    哈希表遍历
*/
void test_hashtable_scan(HashTable *ht)
{
    zend_hash_apply(ht, test_print_zval TSRMLS_CC);
}






static zend_function_entry gglinux_functions[] = {
    ZEND_FE(gglinux_hello, NULL) 
    ZEND_FE(gglinux_test_hashtable, NULL)     
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

