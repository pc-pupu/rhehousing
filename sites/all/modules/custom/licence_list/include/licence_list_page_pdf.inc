<?php

	function licence_list_page_pdf($licensee_type = '', $file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		
		$licensee_type = decrypt_url($licensee_type);
		$result = fetch_licence_list($licensee_type);
		
		$result1 = fetch_licence_list($licensee_type);
		$data1 = $result1->fetchObject();
		
		if($data1->type_of_application == 'new') {
			$type_of_licence = 'New Allotment';	
		} else if($data1->type_of_application == 'vs') {
			$type_of_licence = 'Floor Shifting';	
		} else if($data1->type_of_application == 'cs') {
			$type_of_licence = 'Category Shifting';	
		}
		
		$page_output = '';
		
		$page_output = '
		
		<div align="center">
			<img src="'.drupal_get_path('module', 'licence_list').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Housing Department
			<br>
			Government of West Bengal
			<br>
			1, K. S Roy Road, Kolkata - 700001
			<br>
			<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
			<br>
			<font size="5"><b>'.$type_of_licence.' Licensee List</b></font>
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
					<th align="left" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Licensee Name</b></font></th>
					<th align="center" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Licence No.</b></font></th>
					<th align="center" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Issue</b></font></th>
					<th align="right" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Expiry</b></font></th>
				</tr>
			</thead>
		';
		
			while($data = $result->fetchObject()) {
				$page_output .='
			<tbody>
				<tr>
					<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->applicant_name.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->license_no.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->license_issue_date))).'</font></td>
					<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->license_expiry_date))).'</font></td>
				</tr></tbody>';
			}
			$page_output .='</table>
		</div>';
		//print_r($page_output); die();
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}