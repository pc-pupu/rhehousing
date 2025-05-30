<?php
	
	/*<tr><td>'.$data->license_no.'</td></tr>
	<tr><td>'.$data->license_issue_date.'</td></tr>
	<tr><td>'.$data->applicant_name.'</td></tr>
	<tr><td>'.$data->applicant_designation.'</td></tr>
	<tr><td>'.$data->allotment_district.'</td></tr>
	<tr><td>'.$data->allotment_estate.'</td></tr>
	
	<tr><td>'.$data->allotment_address.'</td></tr>
	<tr><td>'.$data->flat_no.'</td></tr>
	<tr><td>'.$data->license_expiry_date.'</td></tr>
	<tr><td>'.$data->date_of_retirement.'</td></tr>*/
	
	function license_pdf_gen_page($app_id = '', $flat_occupant_id = '', $license_application_id = '', $file_name = '') {
		$online_application_id = decrypt_url($app_id);
		$flat_occupant_id = decrypt_url($flat_occupant_id);
		$license_application_id = decrypt_url($license_application_id);
		
		if((is_numeric($online_application_id) && $online_application_id > 0) && (is_numeric($flat_occupant_id) && $flat_occupant_id > 0) && (is_numeric($license_application_id) && $license_application_id > 0)) {
			
			$result = licence_details($online_application_id, $flat_occupant_id, $license_application_id);
			$data = $result->fetchObject();
			
			if($data->gender == 'M')
				$str = 'Sri.';
			else if($data->gender == 'F')
				$str = 'Smt.';
		
			$page_output = '';
			$page_output = '
			<div>
				<table align="center" width="100%">
					<tr>
						<td align="center" colspan="2">
							<font style="font-size: 18px;"><b>GOVERNMENT OF WEST BENGAL</b></font>
							<br>
							<font style="font-size: 16px;"><b>HOUSING DEPARTMENT</b></font>
							<br>
							<font style="font-size: 16px;"><b>Licence for the Occupation of Government Premises</b></font>
						</td>
					</tr>
					<br>
					<tr>
						<td style="font-size: 12px;">No. '.$data->license_no.'</td>
						<td align="right" style="font-size: 12px;">Date : '.implode('/', array_reverse(explode('-', $data->license_issue_date))).'</td>
					</tr>
					<br><br>
					<tr>
						<td colspan="2" style="font-size: 12px;">
							Licence under section 4 of the West Bengal Government Premises (Regulation of Occupancy ) Act, 1984 is hereby granted to '.$str.' <b>'.$data->applicant_name.', '.$data->applicant_designation.'</b> for the occupation of flat no. <b>'.$data->flat_no.', '.$data->allotment_estate.', '.$data->allotment_address.', '.$data->allotment_district.'</b> subject to the provisions of the said Act and to the additional terms and conditions mentioned below.<br><br>
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.	The validity of this licence will expire on <b>'.implode('/', array_reverse(explode('-', $data->license_expiry_date))).'.</b><br>
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.	Date of Retirement <b>'.implode('/', array_reverse(explode('-', $data->date_of_retirement))).'.</b>
						</td>
					</tr>
					<br><br><br>
					<tr>
						<td align="right" colspan="2" style="font-size: 14px;">
							<table>
								<tr>
									<td align="center">
										Competent Authority under the West Bengal<br> 
										Government Premises (Regulation of Occupancy)<br>
										Act, 1984
									</td>>
								</tr>
							</table>
						</td>
					</tr>
					<br>
					<tr>
						<td colspan="2" align="center" style="font-size: 14px;">
							<font size="4">ADDITIONAL TERMS AND CONDITIONS</font>
						</td>
					</tr>
					<br><br>
					<tr>
						<td colspan="2" style="font-size: 12px;">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.	He/She will not draw H. R. A.<br>
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.	He/She is requested to intimate this Department the date of possession of the flat.
						</td>
					</tr>
					<br><br><br>
					<tr>
						<td align="right" colspan="2" style="font-size: 14px;">
							<table>
								<tr>
									<td align="center">
										Competent Authority under the West Bengal<br> 
										Government Premises (Regulation of Occupancy)<br>
										Act, 1984
									</td>>
								</tr>
							</table>
						</td>
					</tr>
					<br>
					<tr>
						<td style="font-size: 12px;">No. '.$data->license_no.'</td>
						<td align="right" style="font-size: 12px;">Date : '.implode('/', array_reverse(explode('-', $data->license_issue_date))).'</td>
					</tr>
					<tr>
						<td colspan="2" style="font-size: 12px;">
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Copy forwarded, for information and necessary action to :</p><br>
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i) '.$str.' <b>'.$data->applicant_name.'</b></p><br>																										
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ii) <b>'.$data->office_name.'</b></p><br>
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(iii) <b>'.$data->ddo_designation.', '.$data->ddo_address.'</b><br>
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;He is requested to intimate this office regarding transfer/retirement of the licensee from the present posting.<br>
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(iv) The Executive Engineer, Housing Construction Division No. .................................................</p><br>	
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(v)	The Executive Engineer, Electrical Division No. ......................................................................</p><br>
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(vi) The Pay and Accounts Officer, Kolkata Pay and Accounts Office,81/2/2, Phears Lane, Kolkata -12</p><br>
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;or Treasury Officer .......................................................................................................................</p><br>
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(vii) The Work Assistant .................................................................................................................</p><br>	
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;It may be noted that the retirement of the licensee is on ............................................................</p><br> 	
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(viii)	The Assistant Engineer, Housing Construction Sub-Division No. .........................................</p><br> 	
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ix) The Computer Cell</p><br><br>
						</td>
					</tr>';
							
							$page_output .='
					<tr>
						<td colspan="2" style="font-size: 12px;">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.	Special attention is invited to clauses 10 and 11 of the terms and conditions mentioned overleaf. Pending receipt of roll for licence fee from the Executive Engineer, licence fee at the rate indicated under additional terms and conditions should be realised from the salary of the licensee and credited to the head "0216-Housing-02-Urban Housing-105-Receipts from Rental Housing Scheme--001 collection for RHS-05-Rent". Code No. [0216-02-105-001-05]
						</td>
					</tr>
					<br><br><br><br>
					<tr>
						<td align="right" colspan="2" style="font-size: 14px;">
							<table>
								<tr>
									<td align="center">
										Competent Authority under the West Bengal<br> 
										Government Premises (Regulation of Occupancy)<br>
										Act, 1984
									</td>>
								</tr>
							</table>
						</td>
					</tr>
					<br><br>
					<tr>
						<td colspan="2" style="font-size: 14px;">
							<b>Terms and conditions applicable to all licensees in respect of Government Premises</b>
						</td>
					</tr>
					<br><br>
					<tr>
						<td colspan="2">
						<font style="font-size:12px">
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. Subject to the provisions of item 2 and section 11, a license shall remain valid for the specified period and such period may be renewed from time to time by the Competent Authority. For this purpose specified period shall mean - </p><br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i) the period specified in the license or, where nothing is specified in the license, a period of three years from the date of issue of license and such date, in the case of anything deemed to be a license under section 9, shall be the appointed day ; or </p><br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(ii) any period for which the license is renewed by the Competent Authority.</p><br>
							<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2. An application for the renewal of a license shall be made to the Competent Authority in the prescribed manner. No such application shall be refused by the Competent Authority if the licensee continues to be eligible to hold the license in accordance with the provisions of this Act. A license-shall remain valid during the pendency of an application for its renewal.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3. An application for the renewal of a license shall state inter alia the licensee\'s post and place of posting.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4. A license shall cease to be valid if the licensee fails to take possession of the premises covered by it (hereinafter referred to as the premises) within fifteen days of its issue or within such period as the Competent Authority may grant, upon an application by the licensee.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5. The licensee shall use the premises for the purpose for which they have been allotted to him and shall not use them for any other purpose.</p><br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Example- Where a flat is allotted to any person for the purpose of his residence there will be a violation of this condition if he dose not himself ordinarily, reside in it and allows his dependents or any other person to reside in it or keeps it vacant.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6. The licensee shall not assign or transfer the premises in any way to any person or put any person in possession of the premises.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7. The licensee shall not add to, or alter, any fixtures of the premises or make any structural alterations in the premises without the express permission in writing of the Competent Authority.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8. The licensee shall not cause, or suffer to be caused, any damage to the premises beyond the normal wear and tear through the proper use and occupation of the premises.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;9. The licensee shall allow any officer duly authorised in this behalf by the Competent Authority to inspect the premises as and when necessary.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10. The licensee shall pay such license fee for the premises as may be determined from time to time by the Competent Authority.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11. The license fee in respect of each month shall be payable by the first week of the following month in such manner as may be stipulated by the Competent Authority. The licensee shall send to the Competent Authority as and when required by it a statement showing the details of the license fee paid by the licensee, and such statement shall be in such form, and shall be authenticated in such manner, as may be stipulated by the Competent Authority.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12. The licensee, if he is in occupation of Government premises on the appointed day, shall inform the Competent Authority in writing within one month from that day about the post held by him, the headquarters of his post and the date of his retirement on superannuation based upon the entries contained in his Service Book.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13. The licensee shall inform the Competent Authority in writing about every change in his post or place of posting and every change in his is by reason of his going on leave, or being placed under suspension or by any other reason within a week of the change taking place.</p> <br>
							</font>
							</td>
						</tr>
						<tr>
							<td colspan="2">
							<font style="font-size:12px">
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14. A license may be terminated upon--</p><br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(a)	the acquisition of a licensee of any other premises by way of ownership, tenancy or otherwise either in his own name or in the name of any member of family dependent on him.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b)	the violation by the licensee of any of the terms and conditions of the license;</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(c)	the licensee being placed under suspension, or upon proceeding on leave of any kind, for a period exceeding six months:</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Provided that where, by reason of any declaration made under section 5, that post from which the licensee has proceeded on leave is a specified post in respect of the premises occupied by him and the authority granting the leave has not certified that upon the expiry of the leave the licensee is likely to return to that post, the license may be terminated at any time after the commencement of the leave;</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(d)	the expiry of one calendar month\'s notice given by the Competent Authority to the licensee.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15. Upon the expiry or termination of any license, the licensee shall deliver vacant possession of the premises to the Competent Authority, or to any other person authorised by the Competent Authority in this behalf, in the same condition in which the licensee took possession of the premises.</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;16. The license shall automatically terminated upon :</p> <br>
								<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i)	The death of the licensee or (ii) the expiry of the period of validity of the license or (iii) the cessation of the licensee’s employment under the state Government by reason of his retirement, resignation, discharge or dismissal or by any other reason, or (iv) the licensee ceasing to hold any specified post under the state Government by reason of his transfer from any such post on any other reason.</p><br><br>
	SPL/12-13
	
	
						</font>
						</td>
					</tr>
				</table>
			</div>';
		
		}
		else {
			$page_output = 'Invalid Access';	
		}
		
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
		
	}