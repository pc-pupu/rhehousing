<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Test Captcha</title>
</head>

<body>
<?php
session_start();
$_SESSION = array();
include("simple-php-captcha.php");

$_SESSION['captcha'] = simple_php_captcha();

#print_r($_SESSION['captcha']);




?>

<form method="post" action="action.php">
Enter Captcha
<input type="text" name="security_code" /> <br />

<img src="<?php echo $_SESSION['captcha']['image_src']; ?>" alt="Captcha Code"/>

<input type="submit" name="submit" value="Check" />
</form>






</body>
</html>