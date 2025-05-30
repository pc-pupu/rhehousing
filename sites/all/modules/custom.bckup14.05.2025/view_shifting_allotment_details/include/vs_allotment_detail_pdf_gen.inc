<?php

function vs_allotment_detail_pdf_gen($app_id='', $file_name = '') {
	
	$online_application_id = decrypt_url($app_id);
	
	$result = fetch_vs_allotment_details();
	$data = $result->fetchObject();
	
	$page_output = '';
	$page_output = '
	<div>
		<table style="font-family: Arial, sans-serif;">
			<tr><td align="center" colspan="2"><font size="6"><b>GOVERNMENT OF WEST BENGAL</b></font></td></tr>
			<tr><td align="center" colspan="2"><font size="4">DEPARTMENT OF HOUSING : Allotment Branch</font></td></tr>
			<tr><td align="center" colspan="2"><font size="5"><u>1, K.S. Roy Road , N.S. Building, A Block, 1st Floor, Kolkata-1</u></font></td></tr>
			<br><br><br>
			<tr>
				<td>No. '.$data->allotment_no.'</td>
				<td align="center">Date : '.implode('/', array_reverse(explode('-', $data->allotment_date))).'</td>
			</tr>
			<br><br><br>
			<tr>
				<td colspan="2">
					From: The Commissioner<br>
						  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Housing Department<br>
						  		   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;and<br>
						  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The Competent Authority under the West Bengal<br>
						  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Govt. Premises (Regulation of Occupancy) Act, 1984
				</td>
			</tr>
			<br><br><br><br>
			<tr>
				<td colspan="2">
					To &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>'.$data->applicant_name.'</b><br><br>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;C/O&nbsp;<b>'.$data->guardian_name.'</b><br><br>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Sub. : </b>Allotment of flat at <b>'.$data->estate_name.'</b>,<br><br> 
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>'.$data->estate_address.'</b> housing estate located in <b>'.$data->district_name.'</b>.
				</td>
			</tr>
			<br><br><br><br>
			<tr>
				<td colspan="2">
					Madam/Sir,<br>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I am directed to inform you that this Department has been considering to allot you one R.H.E. Flat by 
					way of floor shifting at the above mentioned Housing Estate subject to your eligibility for the same. You are, therefore, requested to 
					download this offer letter and to fill up the prescribed Form for application for Licence for floor shifting within 7(Seven) days from 
					the date of receipt of this letter failing which the offer will be treated as cancelled.<br>
					<br>
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Please note that this letter does not entitle you to the grant of a licence.
				</td>
			</tr>
			<br><br><br><br>
			<tr>
				<td>
				</td>
				<td align="center">
					Yours faithfully,<br><br><br><br>
					COMMISSIONER<br>
					&<br>
					COMPETENT AUTHORITY UNDER<br>
					THE WEST BENGAL GOVT. PREMISES<br>
					(REGULATION OF OCCUPANCY) ACT, 1984
					
					
				</td>
			</tr>
		</table>
	</div>';
	
	ob_end_clean();
	return pdf_using_mpdf_api($page_output, $file_name);
	
	

}