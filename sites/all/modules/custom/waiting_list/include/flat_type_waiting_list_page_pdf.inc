<?php

	function flat_type_waiting_list_page_pdf($flat_type = '', $file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		$flat_type = decrypt_url($flat_type);
		$page_output = '';
		
		if(is_numeric($flat_type)) {
			if($flat_type == 5) {
				$result = db_query("select applicant_name, hoa.online_application_id, status, application_no, flat_type, 	
									allotment_category, computer_serial_no, grade_pay 
									from {housing_applicant} ha
									inner join {housing_applicant_official_detail} haod on haod.uid = ha.uid
									inner join {housing_online_application} hoa 
									on hoa.applicant_official_detail_id = haod.applicant_official_detail_id
									inner join {housing_new_allotment_application} hnaa 
									on hnaa.online_application_id = hoa.online_application_id
									inner join {housing_flat_type} hft on hnaa.flat_type_id = hft.flat_type_id
									where status = :status and hft.flat_type_id = :flat_type_id 
									and substring(application_no,1,2) = :app_no
									order by grade_pay desc, online_application_id asc", 
									//array(':status' => 'verified', ':flat_type_id' => $flat_type, ':app_no' => 'NA'));
									//debaleena start//
									//array(':status' => 'housing_sup_approved_1', ':flat_type_id' => $flat_type, ':app_no' => 'NA'));	
									array(':status' => 'housingapprover_approved_1', ':flat_type_id' => $flat_type, ':app_no' => 'NA'));  //debaleena 04-09-2024
									//end//	
			} else {
				$result = db_query("select applicant_name, hoa.online_application_id, status, application_no, flat_type, 	
									allotment_category, computer_serial_no, grade_pay 
									from {housing_applicant} ha
									inner join {housing_applicant_official_detail} haod on haod.uid = ha.uid
									inner join {housing_online_application} hoa 
									on hoa.applicant_official_detail_id = haod.applicant_official_detail_id
									inner join {housing_new_allotment_application} hnaa 
									on hnaa.online_application_id = hoa.online_application_id
									inner join {housing_flat_type} hft on hnaa.flat_type_id = hft.flat_type_id
									where status = :status and hft.flat_type_id = :flat_type_id 
									and substring(application_no,1,2) = :app_no
									order by online_application_id asc", 
									//array(':status' => 'verified', ':flat_type_id' => $flat_type, ':app_no' => 'NA'));
									//debaleena start//
									//array(':status' => 'housing_sup_approved_1', ':flat_type_id' => $flat_type, ':app_no' => 'NA'));	
									array(':status' => 'housingapprover_approved_1', ':flat_type_id' => $flat_type, ':app_no' => 'NA'));   //debaleena 04-09-2024
									//end//
			}
		//$data1 = $result->fetchObject();					
		
		$page_output = '
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
			<font size="5"><b>Flat Type Wise Waiting List for New Allotment</b></font>
			
		</div>
		<br>
		<div align="right">
			<font size="3"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
		</div>
		<br>
		<div>
			<table style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;" align="center" width="100%">
			<thead>
				<tr bgcolor="#999999">
					<th align="left" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat Type Wise Waiting No</b></font></th>
					<th align="center" width="30%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Applicant Name</b></font></th>
					<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Application No.</b></font></th>'.
					//<th align="center" width="12%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Allotment Category</b></font></th>
					'.
					<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat Type</b></font></th>
					';
					if($flat_type == 5) {
						$page_output .='
						<th align="right" width="13%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Grade Pay</b></font></th>
						<th align="right" width="13%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Computer Serial No</b></font></th>
						';	
					} else {
						$page_output .='
						<th align="right" width="13%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Computer Serial No</b></font></th>
						';	
					}
					$page_output .=';
				</tr>
			</thead>
		';
			$i = 1;
			while($data = $result->fetchObject()) {
				$page_output .='
			<tbody>
				<tr>
					<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->applicant_name.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->application_no.'</font></td>
					'.//<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->allotment_category.'</font></td>
					'.
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_type.'</font></td>
				';
					if($flat_type == 5) {
						$page_output .='
						<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->grade_pay.'</font></td>
						<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->computer_serial_no.'</font></td>
						';	
					} else {
						$page_output .='
						<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->computer_serial_no.'</font></td>
						';	
					}
					$page_output .=';
				</tr></tbody>';
				$i++;
			}
			$page_output .='</table>
		</div>';
		
		}
		else {
			$page_output = 'Invalid Access';	
		}
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}