<?php
#$to = "seca1.shq.wb@nic.in";
//$to = "snehasish.das@nic.in";
//$to = "dipankar.develop@gmail.com";
$to = "snehasish.das@nic.in";

$subject = "URGENT!!. This is from wbard.gov.in and file name testmail.php ";
$txt = "Hello world!";
$headers = "From:snehasish.das@nic.in" . "\r\n";

if(mail($to,$subject,$txt,$headers))
echo "sent";
else
echo "not sent";
?>