<?php

	function cs_allottee_list_page_pdf($cs_allotment_process_date = '', $cs_allotment_process_no = '', $file_name = '') {
		$cs_allotment_process_date = decrypt_url($cs_allotment_process_date);
		$cs_allotment_process_no = decrypt_url($cs_allotment_process_no);
		date_default_timezone_set("Asia/Kolkata");
		$result = fetch_all_cs_allottee_details($cs_allotment_process_date, $cs_allotment_process_no);
		
		$page_output = '';
		
		$page_output = '
		
		<div align="center">
			<img src="'.drupal_get_path('module', 'shifting_allotment_list').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Housing Department
			<br>
			Government of West Bengal
			<br>
			1, K. S Roy Road, Kolkata - 700001
			<br>
			<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
			<br>
			<font size="5"><b>Allottee List of Category Shifting Allotment of Date - '.implode('/', array_reverse(explode('-', $cs_allotment_process_date))).'</b></font>
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
					<th align="left" width="7%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Sl. No.</b></font></th>
					<th align="center" width="8%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat Type</b></font></th>
					<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Application</b></font></th>
					<th align="center" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Application No</b></font></th>
					<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Date of Allotment</b></font></th>
					<th align="right" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Allotment No.</b></font></th>
				</tr>
			<thead>
		';
			$i = 1;
			while($data = $result->fetchObject()) {
				$page_output .='
			<tbody>
				<tr>
					<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_type.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->date_of_application))).'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->application_no.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.implode('/', array_reverse(explode('-', $data->allotment_date))).'</font></td>
					<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->allotment_no.'</font></td>
				</tr><tbody>';
				$i++;
			}
			$page_output .='</table>
		</div>';
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}