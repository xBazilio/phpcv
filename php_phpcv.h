#ifndef PHP_PHPCV_H
#define PHP_PHPCV_H

#define PHP_PHPCV_EXTNAME  "phpcv"
#define PHP_PHPCV_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
#include "php.h"
}

PHP_FUNCTION(cv_detect_multicale);

extern zend_module_entry phpcv_module_entry;
#define phpext_phpcv_ptr &phpcv_module_entry

#ifdef ZTS
#include "TSRM.h"
#endif

#endif /* PHP_PHPCV_H */