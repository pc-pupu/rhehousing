<?php

	function retirement_list_page_pdf($file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		$date1 = date('Y-m-d');
		
		$result = fetch_retirement_list();
		
		$page_output = '';
		
		$page_output = '
		
		<div align="center">
			<img src="'.drupal_get_path('module', 'retirement_list').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Housing Department
			<br>
			Government of West Bengal
			<br>
			1, K. S Roy Road, Kolkata - 700001
			<br>
			<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
			<br>
			<font size="5"><b>Upcoming Retirement List</b></font>
		</div>
		<br>
		<div align="right">
			<font size="3"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
		</div>
		<br>
		<div>
			<table style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;" align="center" width="80%">
			<thead>
				<tr bgcolor="#999999">
					<th align="left" width="45%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Application No.</b></font></th>
					<th align="right" width="35%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Retirement</b></font></th>
				</tr>
			</thead>
		';
			$flag = 0;
			while($data = $result->fetchObject()) {
				$date2 = $data->date_of_retirement;
				$diff = abs(strtotime($date2) - strtotime($date1));

				$years = floor($diff / (365*60*60*24));
				$months = floor(($diff - $years * 365*60*60*24) / (30*60*60*24));
				$days = floor(($diff - $years * 365*60*60*24 - $months*30*60*60*24)/ (60*60*24));
				
				if($date2 >= $date1) {
					if($years < 1 && $months < 6) {
						$flag = 1;
						$page_output .='
					<tbody>
						<tr>
							<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->application_no.'</font></td>
							<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->date_of_retirement))).'</font></td>
						</tr></tbody>';
					}
				}
			}
			if($flag == 0){
				$page_output .=' 
				<tr>
					<td align="center" colspan="2" style="border: 1px solid black; border-collapse: collapse;"><font size="4">No Data Found</font></td>
				</tr>';
			}
			$page_output .='</table>
		</div>';
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}