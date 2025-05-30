<?php

	function application_pdf_gen($app_id = '', $file_name = '') {

		date_default_timezone_set("Asia/Kolkata");
		//module_load_include('php', 'user_sso_login', 'composer/vendor/autoload');
		$fileLogo = drupal_get_path('module', 'application_list').'/images/govt_logo1.png';

		global $user;
		$app_id = decrypt_url($app_id);

		if(is_numeric($app_id) && $app_id > 0) {
			$app_details = fetch_application_detail($app_id);
			
			$app_details1 = fetch_application_detail($app_id);
			$app_data = $app_details1->fetchObject();
			$output = array();
			
			if($app_data->uid == $user->uid) {
				/*if($app_id !== '' && (!is_numeric($app_id) || $app_id <= 0)) {
					$output[] = false;
				}
				else*/ 
				if($app_details->rowCount() == 0){
					$output[] = false;
				}
				else{	
					$output[] = true;
					$output[] = $app_details->fetchObject();
					$output[] = check_application_entity(0,$app_id);
					$output[] = applicant_personal_info()->fetchObject();
				}
			}
		}
		
		//  *** generate content
		
		$isVal = $output[0];
		if($isVal){

			$application_arr = $output[2];
			$entityList = $application_arr[0];
			$fields = $entityList['fields'];
			$expressions = $entityList['expressions'];
			$entityType = $entityList['type'];
			$application_data = $application_arr[1];
			$common_data = $output[1];
			$applicant_data = $output[3];
			
			if($common_data->status == 'allotted') {
				$status = 'Allotted Offer';
			}
			else {
				$status = $common_data->status;
			}
			
			if(trim($entityType) == 'New Licence') {
				$rhe_details_result = fetch_allotment_details();
				$rhe_details_data = $rhe_details_result->fetchObject();
			} else if(trim($entityType) == 'VS Licence') {
				$rhe_details_result = fetch_vs_allotment_details();
				$rhe_details_data = $rhe_details_result->fetchObject();
			} else if(trim($entityType) == 'CS Licence') {
				$rhe_details_result = fetch_cs_allotment_details();
				$rhe_details_data = $rhe_details_result->fetchObject();
			}
			
			$page_output = '';
			$page_output .='
			<div align="center">
				<img src="'.drupal_get_path('module', 'application_list').'/images/govt_logo1.png" alt="Government Logo">
				<br>
				Housing Department
				<br>
				Government of West Bengal
				<br>
				1, K. S Roy Road, Kolkata - 700001
				<br>
				<font style="font-size:18px;"><b>e-Allotment of Rental Housing Estate</b></font>
			</div>
			<br>
			<div style="font-size:14px;" align="center">
			<b>Form of Application for grant of licence for occupation of Government Premises</b>
			</div>
			<br>
			<div align="right">
				<font style="font-size:12px;"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
			</div>
			<br>
			<div align="left" style="font-size:12px;">
			To<br>
			The Competent Authority under the<br>
			West Bengal Government Premises<br>
			(Regulation of Occupancy)Act, 1984 in respect of RHEs in Kolkata under the Housing Department.<br><br>
			Sir,<br><br>';
		if(trim($entityType) == 'New Allotment' || trim($entityType) == 'Vertical Shifting' || trim($entityType) == 'Category Shifting') {
			$page_output .='
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I am in the employment of the Government of West Bengal and I hold a specified post under it. I pray that a licence under section 4 of the West Bengal Government Premises (Regulation of Occupancy)Act, 1984 may kindly be granted in my favour for the occupation of the Government premises in Kolkata.<br><br>';
		} else if(trim($entityType) == 'New Licence' || trim($entityType) == 'VS Licence' || trim($entityType) == 'CS Licence' || trim($entityType) == 'Renew Licence') {
			$page_output .='
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I am in the employment of the Government of West Bengal and I hold a specified post under it. I pray that a licence under section 4 of the West Bengal Government Premises (Regulation of Occupancy)Act, 1984 may kindly be granted in my favour for the occupation of the Government premises at <b>'.$rhe_details_data->estate_name.', '.$rhe_details_data->estate_address.'</b>.<br><br>';
		}
		$page_output .='
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I have read and understood the provisions of the aforesaid Act and I know that I shall have to abide by the terms and conditions mentioned in Schedule I to the Act and such other terms and conditions as may be stipulated by the Competent Authority.<br><br>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I hereby declare that I do not possess any house/flat/residential accommodation either in my own name or in the name of my spouse or any of the Dependent members of my family within the local limits of Kolkata Corporation within twenty kilometers from my office.<br><br>';
		if(trim($entityType) == 'New Allotment' || trim($entityType) == 'Vertical Shifting' || trim($entityType) == 'Category Shifting') {
			$page_output .='
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I undertake to declare that I shall vacate the flat if allotted to me, in the event of my transfer from service from Kolkata or suburbs or retirement from service, acquiring a house/flat etc. in my name or in the name of my spouse, whichever is earlier.<br><br>
			';
		}
		$page_output .='
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I furnish all relevant particulars below for consideration of my application:<br><br>
			</div>';
			$page_output .='
			<div align="center"><font style="font-size:16px;"><b>Application Details</b></font></div>
			<br>
			<div>	
				<table align="center" width="100%" style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;">
					<tr bgcolor="#CCCCCC">
  						<th colspan="2" style="text-align: center;font-size: 16px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Application Information</th>
  					</tr>
    				<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Application Type</th>
						<td style="border: 1px solid black; border-collapse: collapse;">Application for '.$entityType.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Application No.</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->application_no.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Date of Application</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.implode('/', array_reverse(explode('-', $common_data->date_of_application))).'</td>
					</tr>
					
					';
					
					$headArr = array();
	 				$valArr = array();
					$l = 0;
					if(count($expressions) != 0){
					foreach($expressions as $entityAlias => $columnHeadFieldSet ){
						foreach($columnHeadFieldSet as $columnHead => $expression){
							$headArr[$l] = $columnHead;
							$valArr[$l] = $application_data->$expression[1];
							$l++;
					}}} 
					if(count($fields) != 0){
					foreach($fields as $entityAlias => $columnHeadFieldSet ){
						foreach($columnHeadFieldSet as $columnHead => $field){
							$headArr[$l] = $columnHead;
							$valArr[$l] = $application_data;
							$l++;
						}
					}
					} 
					$l = 0;
					
					if(trim($entityType) == 'New Allotment') {
						$heading = 'Information for Allotment';
					}
					else if(trim($entityType) == 'Vertical Shifting' || trim($entityType) == 'Category Shifting') {	
						$heading = 'Possession Details';
					}
					else if(trim($entityType) == 'New Licence' || trim($entityType) == 'VS Licence' || trim($entityType) == 'CS Licence' || trim($entityType) == 'Renew Licence') {
						$heading = 'Allotment Details';	
					}
					//echo "<pre>";print_r($applicant_data);die;
				//permanent and present address
					$result_permanent = particular_district_list($applicant_data->permanent_district);
					$data_permanent = $result_permanent->fetchObject();
					
					$permanent_address = $applicant_data->permanent_street.', P.O - '.$applicant_data->permanent_post_office.', '.$applicant_data->permanent_city_town_village.', '.$data_permanent->district_name.' - '.$applicant_data->permanent_pincode;
					
					if($applicant_data->permanent_present_same == 1) {
						$present_address = $permanent_address;
					} else {
						$result_present = particular_district_list($applicant_data->present_district);
						$data_present = $result_present->fetchObject();
						
						$present_address = $applicant_data->present_street.', P.O - '.$applicant_data->present_post_office.', '.$applicant_data->present_city_town_village.', '.$data_present->district_name.' - '.$applicant_data->present_pincode;	
					}
					
				//office address
					$result_office = particular_district_list($common_data->office_district);
					$data_office = $result_office->fetchObject();
					
					$office_address = $common_data->office_street.', P.O - '.$common_data->office_post_office.', '.$common_data->office_city_town_village.', '.$data_office->district_name.' - '.$common_data->office_pin_code;
					
			$page_output .='
					<tr bgcolor="#CCCCCC">
  						<th colspan="2" style="text-align: center;font-size: 16px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Applicant Personal Information(According to Service Book)</th>
  					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Applicant\'s Name</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$applicant_data->applicant_name.'</td>
					</tr>
					<tr style="font-size:14px;">
					  	<th style="border: 1px solid black; border-collapse: collapse;">Father\'s / Husband\'s Name</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$applicant_data->guardian_name.'</td>
					</tr>
					<tr style="font-size:14px;">
					  	<th style="border: 1px solid black; border-collapse: collapse;">Permanent Address</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$permanent_address.'</td>
					</tr>
					<tr style="font-size:14px;">
					  	<th style="border: 1px solid black; border-collapse: collapse;">Present Address</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$present_address.'</td>
					</tr>
					<tr style="font-size:14px;">
					  	<th style="border: 1px solid black; border-collapse: collapse;">Gender</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.($applicant_data->gender == 'M'?'Male':'Female').'</td>
					</tr>
					<tr style="font-size:14px;">
					  	<th style="border: 1px solid black; border-collapse: collapse;">Date of Birth(According to Service Book)</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.implode('/', array_reverse(explode('-', $applicant_data->date_of_birth))).'</td>
					</tr>
					<tr style="font-size:14px;">
					  	<th style="border: 1px solid black; border-collapse: collapse;">Mobile No</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$applicant_data->mobile_no.'</td>
					</tr>
					<tr style="font-size:14px;">
					  	<th style="border: 1px solid black; border-collapse: collapse;">Email ID</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$applicant_data->mail.'</td>
					</tr>
				</table>';
				$page_output .='<pagebreak>';
				$page_output .='
				<table align="center" width="100%" style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;">
					<tr bgcolor="#CCCCCC">
  						<th colspan="2" style="text-align: center;font-size: 16px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Applicant Official Information</th>
  					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Employee HRMS ID</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->hrms_id.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Designation</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->applicant_designation.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Office Headquarter</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->applicant_headquarter.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Place of Posting</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->applicant_posting_place.'</td>
					</tr>
					<tr style="font-size:14px;">
					';
					//echo "<pre>";print_r($common_data);die;
						$page_output .= '<th style="border: 1px solid black; border-collapse: collapse;">Pay Band</th>';
						if($common_data->scale_from == 0 && $common_data->scale_to != 0){
								//$str =  $common_data->scale_to.' (Below Rs '.$common_data->scale_to.'/-)';
								$str =  $common_data->flat_type.' (Below Rs '.$common_data->scale_to.'/-)';
						}
						else if($common_data->scale_from != 0 && $common_data->scale_to == 0){
								//$str =  $common_data->scale_from.' (Rs '.$common_data->scale_from.'/- and above)';
								$str =  $common_data->flat_type.' (Rs '.$common_data->scale_from.'/- and above)';
						}
						else{
								//$str = $common_data->scale_from.' (Rs '.$common_data->scale_from.'/- to Rs '.$common_data->scale_to.'/-)';
							$str = $common_data->flat_type.' (Rs '.$common_data->scale_from.'/- to Rs '.$common_data->scale_to.'/-)';
						}
						$page_output .= '<td style="border: 1px solid black; border-collapse: collapse;">'.$str.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Basic Pay</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->pay_in_the_pay_band.'</td>
					</tr>
					 
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Date of Joining</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.implode('/', array_reverse(explode('-', $common_data->date_of_joining))).'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Date of Retirement(According to Service Book)</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.implode('/', array_reverse(explode('-', $common_data->date_of_retirement))).'</td>
					</tr>
					<tr bgcolor="#CCCCCC">
  						<th colspan="2" style="text-align: center;font-size: 16px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Applicant Office Name and Address</th>
  					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Office Name</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->office_name.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Office Address</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$office_address.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">Office Phone No.</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->office_phone_no.'</td>
					</tr>
					<tr bgcolor="#CCCCCC">
  						<th colspan="2" style="text-align: center;font-size: 16px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">DDO Information</th>
  					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">DDO District</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->district_name.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">DDO Designation</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->ddo_designation.'</td>
					</tr>
					<tr style="font-size:14px;">
						<th style="border: 1px solid black; border-collapse: collapse;">DDO Address</th>
						<td style="border: 1px solid black; border-collapse: collapse;">'.$common_data->ddo_address.'</td>
					</tr>
					<tr bgcolor="#CCCCCC">
  						<th colspan="2" style="text-align: center;font-size: 16px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">'.$heading.'</th>
					</tr>
					';
					//echo "<pre>";print_r($l);die;
					if(trim($entityType) == 'New Allotment') { 
						$page_output .='
						<tr style="font-size:14px;">
								<th style="border: 1px solid black; border-collapse: collapse;" width="46%">'.$headArr[0].'</th>
	      						<td style="border: 1px solid black; border-collapse: collapse;" width="54%">'
	      						.$application_data->allotment_category
	      						.'</td>
						</tr>
						<tr style="font-size:14px;">
								<th style="border: 1px solid black; border-collapse: collapse;" width="46%">'.$headArr[1].'</th>
	      						<td style="border: 1px solid black; border-collapse: collapse;" width="54%">'
	      						.$application_data->flat_type
	      						.'</td>
						</tr>';


					}else if(trim($entityType) == 'Vertical Shifting'){
						$page_output .='
						<tr style="font-size:14px;">
								<th style="border: 1px solid black; border-collapse: collapse;" width="46%">'.$headArr[0].'</th>
	      						<td style="border: 1px solid black; border-collapse: collapse;" width="54%">'
	      						.$application_data->possession_date
	      						.'</td>
						</tr>
						<tr style="font-size:14px;">
								<th style="border: 1px solid black; border-collapse: collapse;" width="46%">'.$headArr[1].'</th>
	      						<td style="border: 1px solid black; border-collapse: collapse;" width="54%">'
	      						.$application_data->estate_name
	      						.'</td>
						</tr>
						<tr style="font-size:14px;">
								<th style="border: 1px solid black; border-collapse: collapse;" width="46%">'.$headArr[2].'</th>
	      						<td style="border: 1px solid black; border-collapse: collapse;" width="54%">'
	      						.$application_data->block_name
	      						.'</td>
						</tr>
						<tr style="font-size:14px;">
								<th style="border: 1px solid black; border-collapse: collapse;" width="46%">'.$headArr[3].'</th>
	      						<td style="border: 1px solid black; border-collapse: collapse;" width="54%">'
	      						.$application_data->flat_no
	      						.'</td>
						</tr>';

					}else{
						while($l < count($headArr)) {
							$page_output .='
						<tr style="font-size:14px;">
							<th style="border: 1px solid black; border-collapse: collapse;" width="46%">'.$headArr[$l].'</th>
      						<td style="border: 1px solid black; border-collapse: collapse;" width="54%">'
      						//.$valArr[$l]
      						.'</td>
						</tr>';
							$l++;
						}
						$l = 0;
					}
      					
				$page_output .='
			  	</table>';
			  	
				$result_scanned_sign = fetch_applicant_scanned_sign();
				if($result_scanned_sign->rowCount() > 0) {
					$data_scanned_sign = $result_scanned_sign->fetchObject();
					if($data_scanned_sign->uri_scaned_sign != '') {
						$file_path = "sites/default/files/";
						$path = substr($data_scanned_sign->uri_scaned_sign, 9);
					}
				}
			 //echo $path;die; 
			if(trim($entityType) == 'New Allotment' || trim($entityType) == 'Vertical Shifting' || trim($entityType) == 'Category Shifting') {
				$page_output .='
				<table>
					<tr>
						<td>
							<b><br><br><br><br><br><br><br><br>Recommended & forwarded by <br>Drawing and Disbursing Officer/Head <br>of Department/Head of Office with <br>official seal.<br><br>or<br><br>Digital Signature by <br>Drawing and Disbursing Officer/<br>Head of Department/Head of Office</b>
						</td>
					</tr>
			  	</table>
			  	<table align="right">
					<tr>
						<td align="center">
							<br><br><br>Yours faithfully,
							<br><br><img src="'.$file_path.$path.'" alt="Scaned Signature" width="140" height="60">
							<br><br>Signature
						</td>
					</tr>
			  	</table>';
				
			} else if(trim($entityType) == 'New Licence' || trim($entityType) == 'VS Licence' || trim($entityType) == 'CS Licence' || trim($entityType) == 'Renew Licence') {
				$page_output .='
				<table align="right">
					<tr>
						<td align="center">
							<br><br><br><br>Yours faithfully,
							<br><br><img src="'.$file_path.$path.'" alt="Scaned Signature" width="140" height="60">
							<br><br>Signature
						</td>
					</tr>
				</table>
				<table>
					<tr>
						<td>
							<br><br><br><br><br><b>Counter Signature of Drawing and Disbursing Officer/<br>Head of Department/Head of Office with office seal.<br><br>or<br><br>Digital Signature by <br>Drawing and Disbursing Officer/<br>Head of Department/Head of Office</b>
						</td>
					</tr>
			  	</table>';
				$page_output .='<pagebreak>';
				$page_output .='
				<div align="center">
					<font style="font-family: Arial, sans-serif; font-size: 18px;"><b>DECLARATION BEFORE COMPETENT AUTHORITY</b></font>
				</div>
				<br>
				<div style="font-size: 13px">
				I, '.($applicant_data->gender == 'M'?'Sri':'Smt.').' <b>'.$applicant_data->applicant_name.'</b> '.($applicant_data->gender == 'M'?'son of':'daughter/wife of').' Sri 
				<b>'.$applicant_data->guardian_name.'</b>, resident of <b>'.$permanent_address.'</b> presently working as <b>'.$common_data->applicant_designation.'</b> in the 
				Office/Department of <b>'.$common_data->office_name.'</b> hereby declare and affirm.
				<br><br>
				1.	That I have no house/flat in my name, in my name spouse’s name or in the name of and dependent member of my family within Kolkata municipal Corporation area 
				of Howrah Municipal Corporation area of within 20 KM from the Rental Housing Estate allotted to me.
				<br>
				2.	That I shall use the flat for the purpose for which it has been allotted to me and shall not use it for any other purpose.
				<br>
				3.	That I shall not let any other person to reside in the flat issued in favour of me or keep it vacant for more than six months.
				<br>
				4.	I shall not assign or transfer the premises in any way to any person or put any person in possession of the premises.
				<br>
				5.	I shall not add to, or alter any fixtures of the premises or make any structural alterations in the flat without the express permission in writing of the 
				Competent Authority.
				<br>
				6.	I shall not cause, or suffer to be caused, any damage to the premises beyond the normal wear and tear through the proper use and occupation of the premises.
				<br>
				7.	I shall allow any officers duly authorized in this behalf by the competent Authority to inspect the flat as and when necessary.
				<br>
				8.	I shall pay such licence fee for the flat as may be determined from time by the Competent Authority.
				<br>
				9.	I shall inform the Competent Authority in Writing about every change in my post on place of posting and every change in my position by reason of going to leave 
				or being placed under suspension or by any other reason within a week of the change taking place.
				<br>
				10.	That further i do hereby undertake that I shall not violate any of the terms and conditions as laid down in the licence issued in my favour. If I violate any of 
				the terms and conditions of licence the Competent Authority shall be free to terminate my licence.
				<br>
				11.	I further undertake that upon the expire of term of licence of upon termination or licence . I shall deliver vacant possession of the flat to the Competent 
				Authority or to any other person authorised by the Competent Authority in this behalf, in the same condition in which i took possession of the premises.
				<br> 
				12.	I further undertake that I will vacate the flat within 30 days from the date of my transfer (beyond 20 kms . from the concerned RHE) / retirement / resignation 
				of dismissal / removal from service. I shall be liable to pay whatever occupational charge will be fixed for the said period.
				<br><br><br>
				<b>Mobile No: '.$applicant_data->mobile_no.'
				<br><br><br>
				*Pay Slip
				<br><br><br>
				Date: '.date('d/m/Y').'</b>
				<br><br><br>
				<table align="left">
					<tr>
						<td align="left"><b>Place: '.$applicant_data->permanent_city_town_village.'</b></td>
					</tr>
				</table>
				<table align="right">
					<tr>
						<td align="center">
							<img src="'.$file_path.$path.'" alt="Scaned Signature" width="140" height="60">
							<br><b>
							............................................
							<br>
							Signature of the Declarant</b>
						</td>
					</tr>
				</table>
				</div>';
				
			}
			
			$page_output .='
			</div>';
		
		}
		
		ob_end_clean();
		$mpdf = new \Mpdf\Mpdf(['mode' => 'utf-8', 'format' => 'A4-L','tempDir' =>'sites/default/files',
	        'margin_top' => 12,
	        'margin_header' => 5,
	        'margin_footer' => 5,
	        'margin_right' => 5,
	        'margin_bottom' => 10,
	        'margin_left' => 5
	        //'pdf_filename' => 'AI-Worker-LIC-Details('.date("d/m/Y").')'
	    ]);
	     //$fileName = 'Districtwise-Pranimitra-AI-Worker('.date("d/m/Y").')';
        $mpdf->SetWatermarkImage($fileLogo);
        $mpdf->showWatermarkImage = true;
        $mpdf->setFooter('{PAGENO} / {nb}');
        $mpdf->SetTitle($common_data->application_no);

        $mpdf->WriteHTML($page_output);
        //$mpdf->Output('r.pdf', 'D');
        return $mpdf->Output($file_name,"I");
		//return pdf_using_mpdf_api($page_output, $file_name);
		
	}