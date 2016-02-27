PHP_ARG_ENABLE(phpcv,
    [Whether to enable the "phpcv" extension],
    [  --enable-phpcv      Enable "phpcv" extension support])

if test $PHP_PHPCV != "no"; then
    PHP_REQUIRE_CXX()

    SEARCH_PATH="/usr/local /usr /opt/local"
    SEARCH_FOR="/include/opencv2/opencv.hpp"

    if test -r $PHP_PHPCV/$SEARCH_FOR; then
        CV_DIR=$PHP_PHPCV
    else
        AC_MSG_CHECKING([for opencv in default path])
        for i in $SEARCH_PATH ; do
            if test -r $i/$SEARCH_FOR; then
                CV_DIR=$i
                AC_MSG_RESULT(found in $i)
                break
            fi
        done
    fi

    if test -z "$CV_DIR"; then
        AC_MSG_RESULT([not found])
        AC_MSG_ERROR([Please reinstall the OpenCV distribution])
    fi

    PHP_ADD_INCLUDE($CV_DIR/include)

    AC_CHECK_HEADER([$CV_DIR/include/opencv2/objdetect/objdetect.hpp], [], AC_MSG_ERROR('opencv2/objdetect/objdetect.hpp' header not found))
    AC_CHECK_HEADER([$CV_DIR/include/opencv2/highgui/highgui.hpp], [], AC_MSG_ERROR('opencv2/highgui/highgui.hpp' header not found))

    PHP_ADD_LIBRARY_WITH_PATH(opencv_core, $CV_DIR/lib, PHPCV_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(opencv_objdetect, $CV_DIR/lib, PHPCV_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(opencv_highgui, $CV_DIR/lib, PHPCV_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(opencv_imgproc, $CV_DIR/lib, PHPCV_SHARED_LIBADD)

    PHP_ADD_LIBRARY(stdc++, 1, PHPCV_SHARED_LIBADD)

    PHP_SUBST(PHPCV_SHARED_LIBADD)
    PHP_NEW_EXTENSION(phpcv, phpcv.cpp, $ext_shared)
fi
