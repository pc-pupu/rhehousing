<?php

	function view_waiting_list_page_pdf($file_name = '') {
		
		date_default_timezone_set("Asia/Kolkata");
		//$result = db_query("select online_application_id, status, application_no from housing_online_application where status='verified' and substring(application_no,1,2) = 'NA' order by online_application_id asc");
		
		$result = db_query("select applicant_name, hoa.online_application_id, status, application_no, flat_type, 	
							computer_serial_no 
							from {housing_applicant} ha
							inner join {housing_applicant_official_detail} haod on haod.uid = ha.uid
							inner join {housing_online_application} hoa 
							on hoa.applicant_official_detail_id = haod.applicant_official_detail_id
							inner join {housing_new_allotment_application} hnaa 
							on hnaa.online_application_id = hoa.online_application_id
							inner join {housing_flat_type} hft on hnaa.flat_type_id = hft.flat_type_id
							where status = :status and substring(application_no,1,2) = :app_no
							order by to_number(hoa.computer_serial_no, text(9999999999)) asc, hoa.computer_serial_no asc", 
							array(':status' => 'verified', ':app_no' => 'NA'));
		
		$page_output = '';
		
		$page_output = '
		<div align="center">
			<img src="'.drupal_get_path('module', 'waiting_list').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Housing Department
			<br>
			Government of West Bengal
			<br>
			1, K. S Roy Road, Kolkata - 700001
			<br>
			<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
			<br>
			<font size="5"><b>Combined Waiting List for New Allotment</b></font>
		</div>
		<br>
		<div align="right">
			<font size="3"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
		</div>
		<br>
		<div>
			<table style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;" align="center" width="100%">
			<thead>
				<tr bgcolor="#CCCCCC">
					<th align="left" width="25%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Applicant Name</b></font></th>
					<th align="center" width="30%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Application No.</b></font></th>
					<th align="center" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat Type</b></font></th>
					<th align="right" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Computer Serial No.</b></font></th>
				</tr>
			</thead>
		';
			$i = 1;
			while($data = $result->fetchObject()) {
				$page_output .='
			<tbody>
				<tr>
					<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->applicant_name.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->application_no.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->flat_type.'</font></td>
					<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->computer_serial_no.'</font></td>
				</tr></tbody>';
				$i++;
			}
			$page_output .='
			</table>
		</div>';
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}