<?php

	function flat_list_page_pdf($file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		
		$result = rhe_flat_list();
		
		$page_output = '';
		
		$page_output = '
		
		<div align="center">
			<img src="'.drupal_get_path('module', 'update_flat').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Housing Department
			<br>
			Government of West Bengal
			<br>
			1, K. S Roy Road, Kolkata - 700001
			<br>
			<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
			<br>
			<font size="5"><b>Rental Housing Estate Flat List</b></font>
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
					<th align="center" width="12%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>District</b></font></th>
					<th align="center" width="7%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat Type</b></font></th>
					<th align="center" width="16%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Name of the RHE</b></font></th>
					<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Estate Address</b></font></th>
					<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Block</b></font></th>
					<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Floor</b></font></th>
					<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat No</b></font></th>
					<th align="right" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat Status</b></font></th>
				</tr>
			</thead>
		';
			$i = 1;
			while($data = $result->fetchObject()) {
				$page_output .='
			<tbody>
				<tr>
					<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->district_name.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_type.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->estate_name.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->estate_address.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->block_name.' Block</font></td>';
					 if($data->floor == 'G')
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">Ground Floor</font></td>';
					 else if($data->floor == 'F')
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">First Floor</font></td>';
					 else if($data->floor == 'S')
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">Second Floor</font></td>';
					 else if($data->floor == 'T')
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">Third Floor</font></td>';
					 else if($data->floor == '') {
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4"></font></td>';
					 }
					$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_no.'</font></td>
					<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_status.'</font></td>
				</tr></tbody>';
				
				$i++;
			}
			$page_output .='</table>
		</div>';
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
		
	}