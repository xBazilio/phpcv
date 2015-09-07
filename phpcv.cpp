#include "php_phpcv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

static zend_function_entry phpcv_functions[] = {
    PHP_FE(cv_detect_multiscale, NULL)

    {NULL, NULL, NULL}
};

PHP_FUNCTION(cv_detect_multiscale) {
    char *imgPath = NULL, *cascadePath = NULL;
    long imgPathLen, cascadePathLen, minNeighbors;
    double scaleFactor, minWidth, minHeight;
    zval *minSize = NULL, **zminWidth, **zminHeight;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssdla", &imgPath, &imgPathLen, &cascadePath, &cascadePathLen, &scaleFactor, &minNeighbors, &minSize) == FAILURE) {
        RETURN_NULL();
    }

    if (zend_hash_index_find(Z_ARRVAL_P(minSize), 0, (void**)&zminWidth) == FAILURE) {
        RETURN_NULL();
    }
    minWidth = Z_DVAL_PP(zminWidth);
    if (zend_hash_index_find(Z_ARRVAL_P(minSize), 1, (void**)&zminHeight) == FAILURE) {
        RETURN_NULL();
    }
    minHeight = Z_DVAL_PP(zminHeight);

    // Read Image
    Mat image;
    image = imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
    if (image.empty()) {
        RETURN_FALSE;
    }

    // Load Face cascade (.xml file)
    CascadeClassifier faceCascade;
    if (!faceCascade.load(cascadePath)) {
        RETURN_FALSE;
    }

    // Detect faces
    std::vector<Rect> faces;
    faceCascade.detectMultiScale(image, faces, scaleFactor, minNeighbors, 0, Size(minWidth, minHeight));

    array_init(return_value);

    // Build array to return
    for ( int i = 0; i < faces.size(); i++ ) {
        // Now we have: faces[i].x faces[i].y faces[i].width faces[i].height
        zval *face;
        ALLOC_INIT_ZVAL(face);
        array_init(face);
        add_assoc_long(face, "x", faces[i].x);
        add_assoc_long(face, "y", faces[i].y);
        add_assoc_long(face, "w", faces[i].width);
        add_assoc_long(face, "h", faces[i].height);

        add_next_index_zval(return_value, face);
    }
}

zend_module_entry phpcv_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_PHPCV_EXTNAME,
    phpcv_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_PHPCV_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHPCV
extern "C" {
ZEND_GET_MODULE(phpcv)
}
#endif
