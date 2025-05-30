<?php

	function rhe_flat_vacancy_list_pdf($district_id = 0, $flat_type_id = 0, $flat_status_id = 0, $file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		
		$district_id = decrypt_url($district_id);
		$flat_type_id = decrypt_url($flat_type_id);
		$flat_status_id = decrypt_url($flat_status_id);
		
		if((is_numeric($district_id) && $district_id != 0) && (is_numeric($flat_type_id) && $flat_type_id != 0) && (is_numeric($flat_status_id) && $flat_status_id != 0)) {
			
			$result1 = rhe_flat_status($flat_status_id);
			$data1 = $result1->fetchObject();
			
			$result = rhe_flat_allotment_list($district_id, $flat_type_id, $flat_status_id);
			
			$result2 = rhe_flat_allotment_list($district_id, $flat_type_id, $flat_status_id);
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
				<font size="5"><b>RHE Flat Vacancy List of '.$data2->flat_type.' Type</b></font>
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
						<th align="left" width="5%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Sl. No.</b></font></th>
						<th align="center" width="14%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>District</b></font></th>
						<th align="center" width="23%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Name of the RHE</b></font></th>
						<th align="center" width="23%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Estate Address</b></font></th>
						<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat No.</b></font></th>
						<th align="right" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>No of Vacant Flat</b></font></th>
					</tr>
				</thead>
			';
				$i = 1;
				while($data = $result->fetchObject()) {
					$page_output .='
				<tbody>
					<tr>
						<td align="left" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
						<td align="center" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data->district_name.'</font></td>
						<td align="center" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data->estate_name.'</font></td>
						<td align="center" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$data->estate_address.'</font></td>
						';
						$out = rhe_flat_allotment_list_rst_estate($flat_type_id, $flat_status_id, $data->estate_id);
						$page_output .= '
						<td align="center" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$out[1].'</font></td>
						<td align="right" style="border: 0.5px solid black; border-collapse: collapse;"><font size="4">'.$out[0].'</font></td>
					</tr>';
					
					$i++;
					$total_no_flat = $total_no_flat + $out[0];
				}
				$page_output .='
					<tr>
						<td colspan="5" align="center" style="border: 0.5px solid black; border-collapse: collapse;"><b>Total No. of Vacant Flat</b></td>
						<td align="right" style="border: 0.5px solid black; border-collapse: collapse;"><b>'.$total_no_flat.'</b></td>
					</tr>
				</tbody></table>
			</div>';
		
		}
		else {
			$page_output = 'Invalid Access';	
		}
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}