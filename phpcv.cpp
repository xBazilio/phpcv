#include "php_phpcv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

const zend_function_entry phpcv_functions[] = {
    PHP_FE(cv_detect_multiscale, NULL)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(phpcv) {
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(phpcv) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION(phpcv) {
    php_info_print_table_start();
    php_info_print_table_header(2, "phpcv support", "enabled");
    php_info_print_table_end();
}

PHP_FUNCTION(cv_detect_multiscale) {
    char *imgPath = NULL, *cascadePath = NULL;
    long imgPathLen, cascadePathLen, minNeighbors;
    double scaleFactor, minWidth, minHeight;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssdl", &imgPath, &imgPathLen, &cascadePath, &cascadePathLen, &scaleFactor, &minNeighbors) == FAILURE) {
        return;
    }

    // Read Image
    Mat image;
    image = imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
    if (image.empty()) {
        RETURN_FALSE;
    }
    equalizeHist(image, image);

    //min size for detected object, discarding objects smaller than this
    minWidth = image.size().width / 10;
    minHeight = image.size().height / 10;

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
        zval face;
        array_init(&face);
        add_assoc_long(&face, "x", faces[i].x);
        add_assoc_long(&face, "y", faces[i].y);
        add_assoc_long(&face, "w", faces[i].width);
        add_assoc_long(&face, "h", faces[i].height);

        add_next_index_zval(return_value, &face);
    }
}

zend_module_entry phpcv_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_PHPCV_EXTNAME,
    phpcv_functions,
    PHP_MINIT(phpcv),
    PHP_MSHUTDOWN(phpcv),
    NULL,
    NULL,
    PHP_MINFO(phpcv),
    PHP_PHPCV_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHPCV
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(phpcv)
#endif
