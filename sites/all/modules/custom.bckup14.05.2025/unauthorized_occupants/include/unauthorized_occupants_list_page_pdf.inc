<?php

	function unauthorized_occupants_list_page_pdf($file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		$date1 = date('Y-m-d');
		
		$result = fetch_unauthorized_occupants();
		
		$page_output = '';
		
		$page_output = '
		
		<div align="center">
			<img src="'.drupal_get_path('module', 'unauthorized_occupants').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Housing Department
			<br>
			Government of West Bengal
			<br>
			1, K. S Roy Road, Kolkata - 700001
			<br>
			<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
			<br>
			<font size="5"><b>Unauthorized Occupants List</b></font>
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
					<th align="left" width="35%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Application No.</b></font></th>
					<th align="center" width="35%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Licence No.</b></font></th>
					<th align="right" width="30%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Retirement</b></font></th>
				</tr>
			</thead>
		';
			$flag = 0;
			while($data = $result->fetchObject()) {
				$date2 = $data->date_of_retirement;
				if($date2 < $date1) {
					$flag = 1;
					$page_output .='
				<tbody>
					<tr>
						<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->application_no.'</font></td>
						<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->license_no.'</font></td>
						<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->date_of_retirement))).'</font></td>
					</tr></tbody>';
				}
			}
			if($flag == 0){
				$page_output .=' 
				<tr>
					<td align="center" colspan="3" style="border: 1px solid black; border-collapse: collapse;"><font size="4">No Data Found</font></td>
				</tr>';
			}
			$page_output .='</table>
		</div>';
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}