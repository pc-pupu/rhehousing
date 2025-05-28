<?php

	function occupied_flat_details_page_pdf($flat_id = '', $file_name = '') {
		date_default_timezone_set("Asia/Kolkata");
		
		$flat_id = decrypt_url($flat_id);
		
		if(is_numeric($flat_id) && $flat_id > 0) {
			
			$flat_details = fetch_u_o_flat_detail($flat_id);
			$data = $flat_details->fetchObject();
			
			$page_output = '';
			$page_output .='
			<div align="center">
				<img src="'.drupal_get_path('module', 'application_list').'/images/govt_logo1.png" alt="Government Logo">
				<br>
				Housing Department
				<br>
				Government of West Bengal
				<br>
				1, K. S Roy Road, Kolkata - 700001
				<br>
				<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
				<br>
				<font size="5"><b>Unauthorized Occupant Flat Details</b></font>
			</div>
			<br>
			<div align="right">
				<font size="3"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
			</div>
			<br>
			
			<div>
				<table align="center" width="60%" style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;">
					<tr bgcolor="#CCCCCC">
  						<th colspan="2" style="text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: "Dosis",Arial,Verdana,serif; border: 1px solid black; border-collapse: collapse;">Occupied Flat Information</th>
  					</tr>
					
					<tr>
						<th style="border: 1px solid black; border-collapse: collapse;">Flat Type</th>
						<td style="border: 1px solid black; border-collapse: collapse; text-align: center;">'.$data->flat_type.'</td>
					</tr>
					<tr>
						<th style="border: 1px solid black; border-collapse: collapse;">District Name</th>
						<td style="border: 1px solid black; border-collapse: collapse; text-align: center;">'.$data->district_name.'</td>
					</tr>
					<tr>
						<th style="border: 1px solid black; border-collapse: collapse;">Estate Name</th>
						<td style="border: 1px solid black; border-collapse: collapse; text-align: center;">'.$data->estate_name.'</td>
					</tr>
					<tr>
						<th style="border: 1px solid black; border-collapse: collapse;">Estate Address</th>
						<td style="border: 1px solid black; border-collapse: collapse; text-align: center;">'.$data->estate_address.'</td>
					</tr>
					<tr>
						<th style="border: 1px solid black; border-collapse: collapse;">Block</th>
						<td style="border: 1px solid black; border-collapse: collapse; text-align: center;">'.$data->block_name.'</td>
					</tr>
					<tr>
						<th style="border: 1px solid black; border-collapse: collapse;">Flat No.</th>
						<td style="border: 1px solid black; border-collapse: collapse; text-align: center;">'.$data->flat_no.'</td>
					</tr>
				</table>
			</div>
			';
		
		}
		else {
			$page_output = 'Invalid Access';	
		}
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}