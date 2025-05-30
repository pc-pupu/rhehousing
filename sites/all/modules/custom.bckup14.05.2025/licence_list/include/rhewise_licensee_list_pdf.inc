<?php

	function rhewise_licensee_list_pdf($rhe_name = '', $file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		
		$rhe_name = decrypt_url($rhe_name);
		
		$result = fetch_rhewise_licensee_list($rhe_name);
		$result1 = fetch_rhewise_licensee_list($rhe_name);
		$data1 = $result1->fetchObject();
		
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
			<font size="5"><b>'.$data1->estate_name.' Licensee List</b></font>
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
					<th align="center" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Licensee Name</b></font></th>
					<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Licence No.</b></font></th>
					<th align="center" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Issue</b></font></th>
					<th align="right" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Expiry</b></font></th>
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
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->license_no.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->license_issue_date))).'</font></td>
					<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->license_expiry_date))).'</font></td>
				</tr></tbody>';
				
				$i++;
			}
			$page_output .='</table>
		</div>';
		//print_r($page_output); die();
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}