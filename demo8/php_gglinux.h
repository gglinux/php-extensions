#ifndef GGLINUX_H
#define GGLINUX_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#include "php.h"
 
 
#define phpext_gglinux_ptr &gglinux_module_entry

ZEND_BEGIN_MODULE_GLOBALS(gglinux)
    unsigned long global_counter;
ZEND_END_MODULE_GLOBALS(gglinux)

/*
 这个是做什么用的？？？？？
*/
#ifdef ZTS
#define GGLINUX_G(v) TSRMG(gglinux_globals_id,zend_gglinux_globals *, v)

#else
#define GGLINUX_G(v) (gglinux_globals.v)
#endif

#endif