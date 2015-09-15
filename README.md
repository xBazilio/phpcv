# phpcv
PHP extension for face detection

# Installing from sources

    1. Install OpenCV libraries (>=2.3.1)
    2. Unpack phpcv source package
    3. Go to phpcv folder and type "phpize && ./configure && make && make install"
    4. Make sure you have extension=phpcv.so in your php.ini

# Functions

```php
/**
 * @see cv::CascadeClassifier::detectMultiScale
 * @param string $imgPath
 * @param string $cascadePath
 * @param double $scaleFactor
 * @param int $minNeighbors
 *
 * @return array
 */
function cv_detect_multiscale($imgPath, $cascadePath, $scaleFactor, $minNeighbors) {
}
```
# Usage example

```php
$cascade = '/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml';
$img = __DIR__ . '/img.jpg';
$faces = cv_detect_multiscale($img, $cascade, 1.1, 5);
var_export($faces);
/**
 * will output something like this:
 * array (
 *   0 =>
 *   array (
 *     'x' => 313,
 *     'y' => 41,
 *     'w' => 74,
 *     'h' => 74,
 *   ),
 *   1 =>
 *   array (
 *     'x' => 121,
 *     'y' => 43,
 *     'w' => 75,
 *     'h' => 75,
 *   ),
 *   2 =>
 *   array (
 *     'x' => 470,
 *     'y' => 46,
 *     'w' => 72,
 *     'h' => 72,
 *   ),
 * )
 */
```
