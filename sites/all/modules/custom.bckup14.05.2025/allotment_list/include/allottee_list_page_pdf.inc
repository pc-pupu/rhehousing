<?php

	function allottee_list_page_pdf($allotment_process_date = '', $allotment_process_no = '', $allotment_process_type = '', $file_name = '') {
		$allotment_process_date = decrypt_url($allotment_process_date);
		$allotment_process_no = decrypt_url($allotment_process_no);
		$allotment_process_type = decrypt_url($allotment_process_type);
		
		date_default_timezone_set("Asia/Kolkata");
		
		$result1 = fetch_allotment_process_detail($allotment_process_no);
		
		if($result1->rowCount() > 0) {
			$data1 = $result1->fetchObject();
			
		}
		
		if($allotment_process_type != 'NAL') {
			$result_rhe = fetch_shifting_allotment_rhe_detail($allotment_process_date, $allotment_process_no, $allotment_process_type);
		}
		
		$page_output = '';
		
		$page_output = '<!doctype html>
		<html>
		<head>
		<meta charset="utf-8">
		<link rel="shortcut icon" href="http://localhost/rhewbhousing/misc/favicon.ico" type="image/vnd.microsoft.icon" />
		<title>Allotees List</title>
		</head>	
		<body>	
		<div align="center">
			<img src="'.drupal_get_path('module', 'allotment_list').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Government of West Bengal
			<br>
			Housing Department : Allotment Branch
			<br>
			1, K. S Roy Road, N.S. Building, 1st Floor, Kolkata - 700001
			<br><br>
			<font style="font-size: 14px;"><b>e-Allotment of Rental Housing Estate</b></font>
			<br><br>
		</div>';
		if($allotment_process_type == 'NAL') {
			$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type);
			
			$page_output .= '<div align="left"><font style="font-size: 16px;">Proposal for allotment of flats at Government Rental Housing Estate at Different R.H.E. of Flat Type - \''.trim($data1->flat_type).'\' (New Allotment)</font></div>';
			
			$page_output .= '<br>
			<div align="center">
				<font style="font-size: 14px;"><b>Date of Allotment - '.implode('/', array_reverse(explode('-', $allotment_process_date))).'</b></font>
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
					<th align="left" width="4%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Sl. No.</b></font></th>
					<th align="center" width="18%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Name and designation</b></font></th>
					<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>1. Application No.<br>2. Place of Posting<br>3. Date of Application</b></font></th>
					<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat Allotted</b></font></th>
					<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Floor</b></font></th>
					<th align="center" width="12%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Name of R.H.E.</b></font></th>
					<th align="center" width="12%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Retirement</b></font></th>
					<th align="right" width="16%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Remarks</b></font></th>
					<th align="right" width="16%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Allotment Approval Status</b></font></th>
					<th align="right" width="16%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Application Status</b></font></th>
				</tr>
			</thead>
			';
		
			// $result_roaster = db_query("(SELECT flat_occupant_id, allotment_process_no, roaster_vacancy_position, allotment_reason FROM {housing_allotment_roaster_details} hard 	
			// where hard.allotment_process_no = :allotment_process_no_hard)
			// UNION ALL 
			// (SELECT flat_occupant_id, allotment_process_no, roaster_vacancy_position, allotment_reason FROM {housing_flat_occupant} hfo
			// where hfo.allotment_date = :allotment_date AND hfo.allotment_process_no = :allotment_process_no AND substring(hfo.allotment_no, '\w+') = :allotment_no_type AND 
			// hfo.roaster_vacancy_position IS :roaster_vacancy_position)", array(':allotment_date' => $allotment_process_date, ':allotment_process_no' => $allotment_process_no, 
			// ':allotment_no_type' => 'NAL', ':roaster_vacancy_position' => NULL, ':allotment_process_no_hard' => $allotment_process_no));

			//////start 05-07-2024///
			$result_roaster = db_query("select hard.flat_occupant_id, hard.allotment_process_no, hard.roaster_vacancy_position, hard.allotment_reason from {housing_allotment_roaster_details} hard INNER JOIN {housing_flat_occupant} hfo ON hard.flat_occupant_id = hfo.flat_occupant_id
			where hfo.allotment_date = :allotment_date AND hfo.allotment_process_no = :allotment_process_no AND substring(hfo.allotment_no, '\w+') = :allotment_no_type AND hard.allotment_process_no = :allotment_process_no_hard AND
			hfo.roaster_vacancy_position IS :roaster_vacancy_position",array(':allotment_date' => $allotment_process_date, ':allotment_process_no' => $allotment_process_no, 
			':allotment_no_type' => 'NAL', ':roaster_vacancy_position' => NULL, ':allotment_process_no_hard' => $allotment_process_no));
			////end/////
				
			$i = 1;
			while($data_roaster = $result_roaster->fetchObject()) {
				
				if($data_roaster->flat_occupant_id != '') {
			
					if($data = $result->fetchObject()) {
						// print_r($data);die;
						if(trim($data->floor) == 'F') {
							$floor = '1st';	
						} else if(trim($data->floor) == 'S') {
							$floor = '2nd';	
						} else {
							$floor = $data->floor;	
						}
						
						if($data->allowed_for_floor_shifting != '' && $data->allowed_for_floor_shifting == 'N') {
							$allowed_for_fs = 'No Floor Shifting Henceforth';		
						} else {
							$allowed_for_fs = '';	
						}

						//if($data->roaster_vacancy_position != '') {   ==========off  and change $data_roaster instead of $data at 05-07-2024======
						if($data_roaster->roaster_vacancy_position == 1 || $data_roaster->roaster_vacancy_position == 21) {
							$remarks = $data_roaster->roaster_vacancy_position.'st Vacancy<br><br>'.$data_roaster->allotment_reason.'<br>'.$allowed_for_fs;	
						} else if($data_roaster->roaster_vacancy_position == 2 || $data_roaster->roaster_vacancy_position == 22) {
							$remarks = $data_roaster->roaster_vacancy_position.'nd Vacancy<br><br>'.$data_roaster->allotment_reason.'<br>'.$allowed_for_fs;	
						} else if($data_roaster->roaster_vacancy_position == 3 || $data_roaster->roaster_vacancy_position == 23) {
							$remarks = $data_roaster->roaster_vacancy_position.'rd Vacancy<br><br>'.$data_roaster->allotment_reason.'<br>'.$allowed_for_fs;	
						} else {
							$remarks = $data_roaster->roaster_vacancy_position.'th Vacancy<br><br>'.$data_roaster->allotment_reason.'<br>'.$allowed_for_fs;
						}
						//} else {
						//	$remarks = $allowed_for_fs;		==========off at 05-07-2024===========
						//}
						
						// if($data->roaster_vacancy_position != '') {
						// 	if($data->roaster_vacancy_position == 1 || $data->roaster_vacancy_position == 21) {
						// 		$remarks = $data->roaster_vacancy_position.'st Vacancy<br><br>'.$data->allotment_reason.'<br>'.$allowed_for_fs;	
						// 	} else if($data->roaster_vacancy_position == 2 || $data->roaster_vacancy_position == 22) {
						// 		$remarks = $data->roaster_vacancy_position.'nd Vacancy<br><br>'.$data->allotment_reason.'<br>'.$allowed_for_fs;	
						// 	} else if($data->roaster_vacancy_position == 3 || $data->roaster_vacancy_position == 23) {
						// 		$remarks = $data->roaster_vacancy_position.'rd Vacancy<br><br>'.$data->allotment_reason.'<br>'.$allowed_for_fs;	
						// 	} else {
						// 		$remarks = $data->roaster_vacancy_position.'th Vacancy<br><br>'.$data->allotment_reason.'<br>'.$allowed_for_fs;
						// 	}
						// } else {
						// 	$remarks = $allowed_for_fs;		
						// }

						////////////added by dg 06-12-2024//////
						if($data->status == 'offer_letter_cancel'){
							$application_status = 'Offer Letter Cancel';
						}else if($data->status == 'license_cancel'){
							$application_status = 'License Cancel';
						}else{
							$application_status = 'N/A';
						}
						$allotment_status=fetchAllotmentStatus($data->online_application_id);
						///////end////////////
						
						$page_output .='
					<tbody>
						<tr>
							<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
							<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->applicant_name.'<br>'.$data->applicant_designation.'</font></td>
							<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.'1. '.$data->application_no.'<br>'.'2. '.$data->applicant_posting_place.'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_application))).'</font></td>
							<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_no.'</font></td>
							<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$floor.'</font></td>
							<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->estate_name.'</font></td>
							<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->date_of_retirement))).'</font></td>
							<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$remarks.'</font></td>
							<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$allotment_status.'</font></td>
							<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->status_description.'</font></td>
						</tr></tbody>';
						$i++;
					}
			
				} else {
						if($data_roaster->roaster_vacancy_position == 1 || $data_roaster->roaster_vacancy_position == 21) {
							$remarks = $data_roaster->roaster_vacancy_position.'st Vacancy<br><br>'.$data_roaster->allotment_reason;	
						} else if($data_roaster->roaster_vacancy_position == 2 || $data_roaster->roaster_vacancy_position == 22) {
							$remarks = $data_roaster->roaster_vacancy_position.'nd Vacancy<br><br>'.$data_roaster->allotment_reason;	
						} else if($data_roaster->roaster_vacancy_position == 3 || $data_roaster->roaster_vacancy_position == 23) {
							$remarks = $data_roaster->roaster_vacancy_position.'rd Vacancy<br><br>'.$data_roaster->allotment_reason;	
						} else {
							$remarks = $data_roaster->roaster_vacancy_position.'th Vacancy<br><br>'.$data_roaster->allotment_reason;
						}
						$page_output .='
						<tbody>
							<tr>
								<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4"><b>Not Available</b></font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4"></font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4"></font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4"></font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4"></font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4"></font></td>
								<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$remarks.'</font></td>
							</tr>
						</tbody>';
						$i++;	
				}
			}
			$page_output .='</table>
			<br><br><br><br><br><br>
			<table width="100%" align="center">
				<tr>
					<td align="center" width="35%">
						<b>Competent Authority &<br>
						Commissioner<br>
						Housing Department</b>
					</td>
					<td width="25%"></td>
					<td align="center" width="40%">
						<b>Secretary<br>
						Housing Department</b>
					</td>
				</tr>
			</table>
		</div>';
			} else if($allotment_process_type == 'VSAL') {
				$page_output .= '
		<div align="center">
			<font style="font-size: 14px;"><b>Date of Allotment - '.implode('/', array_reverse(explode('-', $allotment_process_date))).'</b></font>
		</div>
		<br>
		<div align="right">
			<font size="3"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
		</div><br>';
		
				while($data_rhe = $result_rhe->fetchObject()) {
					$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type, $data_rhe->estate_id);
					$page_output .= '<br><div align="center"><font style="font-size: 16px;">Proposal for allotment of \''.trim($data1->flat_type).'\' Type flats at '.$data_rhe->estate_name.'
					<br><br>
					<b>(Floor Shifting '.trim($data_rhe->from_flat_type).' type to '.trim($data_rhe->to_flat_type).' type)</b>
					</font></div><br>
					
					<div>
						<table style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;" align="center" width="100%">
						<thead>
							<tr bgcolor="#999999">
								<th align="left" width="4%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Sl. No.</b></font></th>
								<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Name</b></font></th>
								<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>1. Date of Possession<br>2. Date of Application<br>3. Date of Retirement</b></font></th>
								<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Allotted Flat No.</b></font></th>
								<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Type of Flat</b></font></th>
								<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Floor</b></font></th>
								<th align="center" width="16%" style="border: 1px solid black; border-collapse: collapse;" colspan="2"><font size="5"><b>By way of shifting</b></font></th>
								<th align="right" width="14%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Remarks</b></font></th>
							</tr>
							<tr bgcolor="#999999">
								<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>From</b></font></th>
								<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>To</b></font></th>	
							</tr>
						</thead>
					';
					$i = 1;
					if($result->rowCount() > 0) {
						while($data = $result->fetchObject()) {
							if(trim($data->floor) == 'F') {
								$floor = '1st';	
							} else if(trim($data->floor) == 'S') {
								$floor = '2nd';	
							} else {
								$floor = $data->floor;	
							}
						
						$page_output .='
						<tbody>
							<tr>
								<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->applicant_name.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.'1. '.implode('/', array_reverse(explode('-', $data->possession_date))).'<br>'.'2. '.implode('/', array_reverse(explode('-', $data->date_of_application))).'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_retirement))).'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_no.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_type.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$floor.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->occupied_flat_vs.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_no.'</font></td>
								<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.'Floor Shifting'.'</font></td>
							</tr>
						</tbody>';
						$i++;
						}
					}
					$page_output .='</table>
				</div>';
			
				}
				$page_output .='<div>
				<br><br><br><br><br><br>
				<table width="100%" align="center">
					<tr>
						<td align="center" width="35%">
							<b>Competent Authority &<br>
							Commissioner<br>
							Housing Department</b>
						</td>
						<td width="25%"></td>
						<td align="center" width="40%">
							<b>Secretary<br>
							Housing Department</b>
						</td>
					</tr>
				</table>
				</div>';
				
			} else if($allotment_process_type == 'CSAL') {
				$page_output .= '
		<div align="center">
			<font style="font-size: 14px;"><b>Date of Allotment - '.implode('/', array_reverse(explode('-', $allotment_process_date))).'</b></font>
		</div>
		<br>
		<div align="right">
			<font size="3"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
		</div><br>';
		
				while($data_rhe = $result_rhe->fetchObject()) {
					$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type, $data_rhe->estate_id);
					$page_output .= '<br><div align="center"><font style="font-size: 16px;">Proposal for allotment of \''.trim($data1->flat_type).'\' Type flats at '.$data_rhe->estate_name.'
					<br><br>
					<b>(Category Shifting '.trim($data_rhe->from_flat_type).' type to '.trim($data_rhe->to_flat_type).' type)</b>
					</font></div><br>
					
					<div>
						<table style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;" align="center" width="100%">
						<thead>
							<tr bgcolor="#999999">
								<th align="left" width="4%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Sl. No.</b></font></th>
								<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Name</b></font></th>
								<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>1. Date of Possession<br>2. Date of Application<br>3. Date of Retirement</b></font></th>
								<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Allotted Flat No.</b></font></th>
								<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Type of Flat</b></font></th>
								<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Floor</b></font></th>
								<th align="center" width="16%" style="border: 1px solid black; border-collapse: collapse;" colspan="2"><font size="5"><b>By way of shifting</b></font></th>
								<th align="right" width="14%" style="border: 1px solid black; border-collapse: collapse;" rowspan="2"><font size="5"><b>Remarks</b></font></th>
							</tr>
							<tr bgcolor="#999999">
								<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>From</b></font></th>
								<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>To</b></font></th>	
							</tr>
						</thead>
					';
					$i = 1;
					if($result->rowCount() > 0) {
						while($data = $result->fetchObject()) {
							if(trim($data->floor) == 'F') {
								$floor = '1st';	
							} else if(trim($data->floor) == 'S') {
								$floor = '2nd';	
							} else {
								$floor = $data->floor;	
							}
						
						$page_output .='
						<tbody>
							<tr>
								<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->applicant_name.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.'1. '.implode('/', array_reverse(explode('-', $data->possession_date))).'<br>'.'2. '.implode('/', array_reverse(explode('-', $data->date_of_application))).'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_retirement))).'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_no.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_type.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$floor.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->occupied_flat_cs.'</font></td>
								<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_no.'</font></td>
								<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.'Category Shifting'.'</font></td>
							</tr>
						</tbody>';
						$i++;
						}
					}
					$page_output .='</table>
				</div>';
			
				}
				$page_output .='<div>
				<br><br><br><br><br><br>
				<table width="100%" align="center">
					<tr>
						<td align="center" width="35%">
							<b>Competent Authority &<br>
							Commissioner<br>
							Housing Department</b>
						</td>
						<td width="25%"></td>
						<td align="center" width="40%">
							<b>Secretary<br>
							Housing Department</b>
						</td>
					</tr>
				</table>
				</div>';
				
			}
	$page_output .='</body>
</html>';		
			
		//echo $page_output;
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}