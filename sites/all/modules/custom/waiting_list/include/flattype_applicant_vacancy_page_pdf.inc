<?php

	function flattype_applicant_vacancy_page_pdf($district_id = '', $flat_type_id = '', $file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		
		$district_id = decrypt_url($district_id);
		$flat_type_id = decrypt_url($flat_type_id);
		
		$flat_status_id = fetch_flat_status_id('vacant');
		
		$result_waiting_app = db_query("select count(*) as tot_no_applicant
									from {housing_applicant} ha
									inner join {housing_applicant_official_detail} haod on haod.uid = ha.uid
									inner join {housing_online_application} hoa 
									on hoa.applicant_official_detail_id = haod.applicant_official_detail_id
									inner join {housing_new_allotment_application} hnaa 
									on hnaa.online_application_id = hoa.online_application_id
									inner join {housing_flat_type} hft on hnaa.flat_type_id = hft.flat_type_id
									where status = :status and hft.flat_type_id = :flat_type_id 
									and substring(application_no,1,2) = :app_no", 
									array(':status' => 'verified', ':flat_type_id' => $flat_type_id, ':app_no' => 'NA'));
		$data_waiting_app = $result_waiting_app->fetchObject();
		
		$result_flat_vacancy = rhe_flat_allotment_list($district_id, $flat_type_id, $flat_status_id);
		$tot_noestate = $result_flat_vacancy->rowCount();
		
		$result2 = fetch_rhe_flat_type($flat_type_id);
		$data2 = $result2->fetchObject();
		
		$result3 = particular_district_list($district_id);
		$data3 = $result3->fetchObject();
		
		
		$page_output = '';
		
		if(is_numeric($flat_type_id)) {				
		
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
				<font size="5"><b>'.$data2->flat_type.' Flat Type Wise Waiting Applicant and Flat Vacancy</b></font>
				
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
						<th align="left" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>District</b></font></th>
						<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Total No. of Applicant</b></font></th>
						<th align="center" width="40%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Name of the RHE</b></font></th>
						<th align="right" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>No of Vacant Flat</b></font></th>
					</tr>
				</thead>
			';
			if($tot_noestate > 0) {
				$i = 1;
				while($data_flat_vacancy = $result_flat_vacancy->fetchObject()) {
					
					$page_output .='
					<tbody>';
					if($i == 1) {
						$page_output .='
						<tr>
							<td align="left" rowspan="'.$tot_noestate.'" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data_flat_vacancy->district_name.'</font></td>
							<td align="center" rowspan="'.$tot_noestate.'" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data_waiting_app->tot_no_applicant.'</font></td>
							<td align="center" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data_flat_vacancy->estate_name.'</font></td>
							';
							$out = rhe_flat_allotment_list_rst_estate($flat_type_id, $flat_status_id, $data_flat_vacancy->estate_id);
							$page_output .= '
							<td align="right" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$out[0].'</font></td>
						</tr>';	
					} else {
						$page_output .='
						<tr>
							<td align="center" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data_flat_vacancy->estate_name.'</font></td>
							';
							$out = rhe_flat_allotment_list_rst_estate($flat_type_id, $flat_status_id, $data_flat_vacancy->estate_id);
							$page_output .= '
							<td align="right" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$out[0].'</font></td>
						</tr>';	
					}
					$page_output .='	
					</tbody>';
					
					$i++;
				}
			} else {
				$page_output .='
				<tbody>
					<tr>
						<td align="left" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data3->district_name.'</font></td>
						<td align="center" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data_waiting_app->tot_no_applicant.'</font></td>
						<td align="center" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">NILL</font></td>
						<td align="right" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">NILL</font></td>
					</tr>
				</tbody>';
			}
			$page_output .='
			</table>
			</div>';
		
		}
		else {
			$page_output = 'Invalid Access';	
		}
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}