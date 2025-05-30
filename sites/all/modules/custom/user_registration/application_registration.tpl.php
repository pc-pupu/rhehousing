<?php

	$isVal = $output[0];
	if($isVal){
		$usrid = $output[1];
		$data = $output[2];
		
		if(trim($data->gender) == 'M')
			$gender = 'Male';
		elseif(trim($data->gender) == 'F')
			$gender = 'Female';
?>

<div class="table-bottom">
	
<?php
	$filename = str_replace(' ', '', $data->applicant_name).'_'.decrypt_url(trim($usrid));
	
	echo l('<img height="18" width="18" src="'.file_create_url(drupal_get_path('module', 'user_registration') .  
			'/images/pdf_icon.png').'" title="Download Application of Registration" alt="PDF Icon">Download Application of 
			Registration', 'application_of_registration_pdf/'.$usrid.'/'.$filename, array(
			'html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 
			400;text-decoration: none; font-size:14px')));
?>
           
</div>
<div class="table-bottom">
  <table>
  	<tr>
  		<th colspan="2" style="background: none repeat scroll 0 0 #5996d9;text-align: center;font-size: 18px;line-height: 24px;font-weight: bold;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Applicant Registration Details</th>
  	</tr>
  	<tr>
      <th style="background-color:#a1baef" width="50%">REGISTRATION ID</th>
      <td width="50%"><?php echo decrypt_url(trim($usrid));?></td>
    </tr>
    <tr>
      <th style="background-color:#a1baef">NAME</th>
      <td><?php echo trim($data->applicant_name);?></td>
    </tr>
    <tr>
      <th style="background-color:#a1baef">DATE OF BIRTH</th>
      <td><?php echo trim( implode('/', array_reverse(explode('-', $data->date_of_birth))));?></td>
    </tr>
    <tr>
      <th style="background-color:#a1baef">GENDER</th>
      <td><?php echo $gender;?></td>
    </tr>
    <tr>
      <th style="background-color:#a1baef">MOBILE NO.</th>
      <td><?php echo trim($data->mobile_no);?></td>
    </tr>
    <tr>
      <th style="background-color:#a1baef">EMAIL ID</th>
      <td><?php echo trim($data->mail);?></td>
    </tr>
    <tr>
      <th style="background-color:#a1baef">Employee HRMS ID</th>
      <td><?php echo trim($data->hrms_id);?></td>
    </tr>
    <tr>
      <th style="background-color:#a1baef">Designation</th>
      <td><?php echo trim($data->applicant_designation);?></td>
    </tr>
    <tr>
      <th style="background-color:#a1baef">Name of the Office</th>
      <td><?php echo trim($data->office_name);?></td>
    </tr>
  </table>
</div>

<?php }else { ?>

	Invalid Access

<?php } ?>