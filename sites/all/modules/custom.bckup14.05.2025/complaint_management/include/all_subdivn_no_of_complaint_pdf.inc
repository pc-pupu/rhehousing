<?php

	function all_subdivn_no_of_complaint_pdf($file_name = '') {
		
		date_default_timezone_set("Asia/Kolkata");
		
		$result = fetch_all_subdivn_no_of_complaint();
		
		$page_output = '';
		
		$page_output = '
		<div align="center">
			<img src="'.drupal_get_path('module', 'complaint_management').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Housing Department
			<br>
			Government of West Bengal
			<br>
			1, K. S Roy Road, Kolkata - 700001
			<br>
			<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
			<br>
			<font size="5"><b>All Sub Divisions No. of Complaints</b></font>
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
					<th align="left" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Sl. No.</b></font></th>
					<th align="center" width="30%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Sub-Division Name</b></font></th>
					<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Total No. of Complaints</b></font></th>
					<th align="center" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>No. of Pending Complaints</b></font></th>
					<th align="right" width="20%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>No. of Action Taken Complaints</b></font></th>
				</tr>
			</thead>
		';
			$i = 1;
			while($data = $result->fetchObject()) {
				$subdiv = $data->subdiv_id;
				//for pending
				$result_pending = fetch_subdivn_wise_no_of_pending_complaint($subdiv);
				if($result_pending->rowCount() > 0) {
					$tot_no_of_pending_complaints = $result_pending->rowCount();
				} else {
					$tot_no_of_pending_complaints = 0;	
				}
				
				//for action taken
				$result_action = fetch_subdivn_wise_no_of_action_complaint($subdiv);
				if($result_pending->rowCount() > 0) {
					$tot_no_of_action_complaints = $result_action->rowCount();
				} else {
					$tot_no_of_action_complaints = 0;	
				}
			
				$page_output .='
			<tbody>
				<tr>
					<td align="left" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$i.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->subdiv_name.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$data->tot_no_of_complaints.'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$tot_no_of_pending_complaints.'</font></td>
					<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$tot_no_of_action_complaints.'</font></td>
				</tr></tbody>';
				$i++;
			}
			$page_output .='
			</table>
		</div>';
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
	}