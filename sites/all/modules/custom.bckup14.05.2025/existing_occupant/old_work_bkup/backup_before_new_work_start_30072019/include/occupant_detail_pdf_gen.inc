<?php

function occupant_detail_pdf_gen($online_app_id = '', $file_name = '') {
	//date_default_timezone_set("Asia/Kolkata");
	
	$online_app_id = decrypt_url($online_app_id);
	$output = array();
	if(is_numeric($online_app_id) && $online_app_id > 0) {	
		$output[] = true;
		$output[] = $online_app_id;
	}
	
	
	//  *** generate content
	
	
	$isVal = $output[0];
	if($isVal) {
		$online_application_id = $output[1];
		$result = fetch_occupant_details($online_application_id);

		$page_output = '';
		
		while($data = $result->fetchObject()) {
			$page_output .='
			<!doctype html>
			<html>
			<head>
			<meta charset="utf-8">
			<link rel="shortcut icon" href="http://tempallotment.nic.in/misc/favicon.ico" type="image/vnd.microsoft.icon" />
			<title>Occupant Details</title>
			</head>	<body>
			<div align="center">
				<img src="'.drupal_get_path('module', 'waiting_list').'/images/govt_logo1.png" alt="Government Logo">
				<br>
				Housing Department
				<br>
				Government of West Bengal
				<br>
				1, K. S Roy Road, Kolkata - 700001
				<br>
				<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
				<br>
				<font size="5"><b>Occupant Details</b></font>
			</div>
			<br>
			<div align="right">
				<font size="3"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
			</div>
			<br>
			<div>
			<table align="center" width="80%" style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;">
				<tr bgcolor="#CCCCCC">
			  		<th colspan="2" style="text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Occupant Personal Information</th>
			  	</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant Name</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->applicant_name.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Father\'s / Husband Name</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->guardian_name.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Gender</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.($data->gender == 'M' ? 'Male' : 'Female').'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Date of Birth(dd/mm/yyyy)</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.implode('/', array_reverse(explode('-', $data->date_of_birth))).'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Mobile No</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->mobile_no.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Email ID</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->mail.'</td>
				</tr>
			<tr bgcolor="#CCCCCC">
			  <th colspan="2" style="text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Occupant Official Information</th>
			  </tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Designation</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->applicant_designation.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Office Headquarter</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->applicant_headquarter.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Posting Place</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->applicant_posting_place.'</td>
				</tr>
				<tr>';
			
			
				$page_output .= '<th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Pay Band</th>';
						 if($data->scale_from == 0 && $data->scale_to != 0){
							$str =  $data->payband.' (Below Rs '.$data->scale_to.'/-)';
						}else if($data->scale_from != 0 && $data->scale_to == 0){
							$str =  $data->payband.' (Rs '.$data->scale_from.'/- and above)';
						}else{
							$str = $data->payband.' (Rs '.$data->scale_from.'/- to Rs '.$data->scale_to.'/-)';
						}
				  $page_output .= '<td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$str.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Pay in Pay Band</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->pay_in_the_pay_band.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Grade Pay</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->grade_pay.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s GPF No.</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->gpf_no.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Date of Joining(dd/mm/yyyy)</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.implode('/', array_reverse(explode('-', $data->date_of_joining))).'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Date of Retirement(dd/mm/yyyy)</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.implode('/', array_reverse(explode('-', $data->date_of_retirement))).'</td>
				</tr>
				<tr bgcolor="#CCCCCC">
						<th colspan="2" style="text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Occupant Office Address</th>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Office Name</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->office_name.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Office Address</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->office_street.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Office City/ Town/ Village</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->office_city_town_village.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Office Post Office</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->office_post_office.'</td>
				</tr>
				<tr>
				  <th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s Office Pin Code</th>
				  <td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->office_pin_code.'</td>
				</tr>
				<tr bgcolor="#CCCCCC">
					<th colspan="2" style="text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">DDO Information</th>
								</tr>
								<tr>
									<th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s DDO District</th>
									<td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->district_name.'</td>
								</tr>
								<tr>
									<th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s DDO Designation</th>
									<td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->ddo_designation.'</td>
								</tr>
								<tr>
									<th style="border: 1px solid black; border-collapse: collapse;">Occupant\'s DDO Address</th>
									<td style="border: 1px solid black; border-collapse: collapse;">&nbsp;'.$data->ddo_address.'</td>
								</tr>
			  </table>
			</div></body>
			</html>';
			  
		}
	} else {
		$page_output = '';
		$page_output = 'No data found.';	
	}
	
	ob_end_clean();
	return pdf_using_mpdf_api($page_output, $file_name);
	
}