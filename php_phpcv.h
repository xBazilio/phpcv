#ifndef PHP_PHPCV_H
#define PHP_PHPCV_H

#define PHP_PHPCV_EXTNAME "phpcv"
#define PHP_PHPCV_VERSION "0.2.0"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
#include "php.h"
#include "ext/standard/info.h"
}

PHP_FUNCTION(cv_detect_multiscale);

extern zend_module_entry phpcv_module_entry;
#define phpext_phpcv_ptr &phpcv_module_entry

#ifdef ZTS
#include "TSRM.h"
#endif

#if defined(ZTS) && defined(COMPILE_DL_PHPCV)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_PHPCV_H */