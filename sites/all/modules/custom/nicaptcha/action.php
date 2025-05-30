<?php
session_start();
if(isset($_POST['submit']) && $_POST['submit'] == 'Check') {

if($_POST['security_code'] == $_SESSION['captcha']['code'])
echo 'valid'.$_POST['security_code'].'##'.$_SESSION['captcha']['code'];
else 
echo 'invalid'.$_POST['security_code'].'##'.$_SESSION['captcha']['code'];
	
}

?>