
<?php
$url="https://uat.wbifms.gov.in/hrms-External/housing/fetchEmployeeDetails";
//$url="https://uat.wbifms.gov.in/hrms-External/housing/fetchEmployeeDetails";
$fp = fopen("example_homepage1.txt", "w");

$data = array("req" => array ("hrmsId" => '1999002754'));
$postdata = json_encode($data);
        
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $url);
//curl_setopt($ch, CURLOPT_HEADER, 0);
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_POSTFIELDS, $postdata);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));
//curl_setopt($ch,CURLOPT_CAINFO,'D:\xampp-subham\cacert.pem');
//curl_setopt($ch, CURLOPT_SSL_VERIFYPEER,false);
//curl_setopt($ch, CURLOPT_SSL_VERIFYHOST,2);
$op=curl_exec($ch);
if (curl_error($ch)) {
    fwrite($fp, curl_error($ch));
    //echo 'Curl error: ' . curl_error($ch);
    //return false;
}
else {
    fwrite($fp, $op);
    //$curl_output =curl_exec($ch);
}
curl_close($ch);
fclose($fp);
?>