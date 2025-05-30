<?php

	function rhe_flat_vacancy_list_pdf($flat_type_id = 0, $flat_category_id = 0, $flat_status_id = 0, $file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		
		$flat_type_id = decrypt_url($flat_type_id);
		$flat_category_id = decrypt_url($flat_category_id);
		$flat_status_id = decrypt_url($flat_status_id);
		
		if((is_numeric($flat_type_id) && $flat_type_id > 0) && (is_numeric($flat_category_id) && $flat_category_id > 0) && (is_numeric($flat_status_id) && $flat_status_id > 0)) {
			
			$result1 = rhe_flat_status($flat_status_id);
			$data1 = $result1->fetchObject();
			
			$result = rhe_flat_allotment_list($flat_type_id, $flat_status_id, $flat_category_id);
			
			$result2 = rhe_flat_allotment_list($flat_type_id, $flat_status_id, $flat_category_id);
			$data2 = $result2->fetchObject();
			
			$page_output = '';
			$page_output = '
			<div align="center">
				<img src="'.drupal_get_path('module', 'vacancy_list').'/images/govt_logo1.png" alt="Government Logo">
				<br>
				Housing Department
				<br>
				Government of West Bengal
				<br>
				1, K. S Roy Road, Kolkata - 700001
				<br>
				<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
				<br>
				<font size="5"><b>RHE Flat Vacancy List for New Allotment of Type '.$data2->flat_type.'</b></font>
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
						<th align="left" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>District</b></font></th>
						<th align="center" width="28%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Name of the RHE</b></font></th>
						<th align="center" width="27%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Estate Address</b></font></th>
						<th align="center" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat No.</b></font></th>
						<th align="right" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>No of Vacant Flat</b></font></th>
					</tr>
				</thead>
			';
				while($data = $result->fetchObject()) {
					$page_output .='
				<tbody>
					<tr>
						<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->district_name.'</font></td>
						<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->estate_name.'</font></td>
						<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->estate_address.'</font></td>
						';
						$out = rhe_flat_allotment_list_rst_estate($flat_type_id, $flat_status_id, $data->estate_id, $flat_category_id);
						$page_output .= '
						<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$out[1].'</font></td>
						<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$out[0].'</font></td>
					</tr></tbody>';
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