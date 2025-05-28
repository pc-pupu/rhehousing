<?php

	function application_registration_pdf($usrid = '', $file_name = '') {
		
		$page_output = '';
		$uid = decrypt_url($usrid);
		
		if(is_numeric($uid)) {
		
			$query1 = db_select('users', 'u');
			$query1->addField('u', 'uid');
			$query1->condition('u.uid', $uid, '=');
			$result1 = $query1->execute();
			
			if($result1->rowcount() > 0){
				
				$query = db_select('users', 'u');
				$query->innerJoin('housing_applicant', 'ha', 'ha.uid = u.uid');
				$query->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
				$query->addField('u', 'mail');
				$query->addField('u', 'created');
				$query->addField('ha', 'applicant_name');
				$query->addField('ha', 'gender');
				$query->addField('ha', 'mobile_no');
				$query->addField('ha', 'date_of_birth');
				$query->addField('haod', 'applicant_designation');
				$query->addField('haod', 'office_name');
				$query->addField('haod', 'hrms_id');
				$query->condition('u.uid', $uid, '=');
				$result = $query->execute();
				
				if($result->rowcount() > 0){
					$data = $result->fetchObject();
					
					if(trim($data->gender) == 'M')
						$gender = 'Male';
					elseif(trim($data->gender) == 'F')
						$gender = 'Female';
		
					$page_output = '<!doctype html>
					<html>
					<head>
					<meta charset="utf-8">
					<link rel="shortcut icon" href="http://localhost/eallotment/misc/favicon.ico" 
					type="image/vnd.microsoft.icon" />
					<title>Applicant Registration Form</title>
					</head>	<body>	
					<div align="center">
						<img src="'.drupal_get_path('module', 'user_registration').'/images/govt_logo1.png" alt="Government Logo">
						<br>
						Housing Department
						<br>
						Government of West Bengal
						<br>
						1, K. S Roy Road, Kolkata - 700001
						<br>
						<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
						<br>
						<font size="5"><b>Applicant Registration Form</b></font>
					</div>
					<br>
					<div align="right">
						<font size="3"><b>Registration Date & Time : </b>'.date('l d-m-Y h:i:s A', $data->created).'</font>
					</div>
					<br>
					<div>
						<table style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;" align="center" width="80%">
							<tr bgcolor="#CCCCCC">
  								<th colspan="2" style="text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Applicant Registration Details</th>
  							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">REGISTRATION ID</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.trim($uid).'</td>
							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">NAME</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.trim($data->applicant_name).'</td>
							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">DATE OF BIRTH</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.trim( implode('/', array_reverse(explode('-', $data->date_of_birth)))).'</td>
							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">GENDER</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.$gender.'</td>
							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">MOBILE NO.</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.trim($data->mobile_no).'</td>
							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">EMAIL ID</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.trim($data->mail).'</td>
							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">Employee HRMS ID</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.trim($data->hrms_id).'</td>
							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">Designation</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.trim($data->applicant_designation).'</td>
							</tr>
							<tr>
								<th style="border: 1px solid black; border-collapse: collapse;">Name of the Office</th>
								<td style="border: 1px solid black; border-collapse: collapse;">'.trim($data->office_name).'</td>
							</tr>
						</table>
						
					</div></body>
					</html>';
					
					ob_end_clean();
					return pdf_using_mpdf_api($page_output, $file_name);
				}
			}
		}
	}