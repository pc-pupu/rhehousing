<?php
phpinfo();


echo PHP_VERSION;
echo "<br/>";
if(function_exists('mcrypt_encrypt')) {
    echo "mcrypt is loaded!";
} else {
    echo "mcrypt isn't loaded!";
}
echo "<br/>";
if(extension_loaded('mcrypt')) {
    echo "mcrypt is loaded!";
} else {
    echo "mcrypt isn't loaded!";
}

echo "<br/>";
if(extension_loaded('mbstring')) {
    echo "mbstring is loaded!";
} else {
    echo "mbstring isn't loaded!";
}

?>