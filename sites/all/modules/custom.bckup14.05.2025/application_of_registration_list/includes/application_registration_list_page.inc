<?php

	function application_registration_list() {
		global $base_path;
		$output = '';
		
		$header = array();
		$header[] = array('data' => 'NAME');
		$header[] = array('data' => 'DATE OF BIRTH');
		$header[] = array('data' => 'GENDER');
		$header[] = array('data' => 'MOBILE NO.');
		$header[] = array('data' => 'EMAIL ID');
		$header[] = array('data' => 'UPLOADED DOCUMENT');
		$header[] = array('data' => 'VIEW DETAILS');
		
		$rows = array();
			
		$query = db_select('users', 'u');
		$query->innerJoin('users_roles', 'ur', 'ur.uid = u.uid');
		$query->innerJoin('housing_applicant', 'ha', 'ha.uid = u.uid');	
		$query->addField('u', 'uid');
		$query->addField('u', 'mail');
		$query->addField('ha', 'applicant_name');
		$query->addField('ha', 'gender');
		$query->addField('ha', 'mobile_no');
		$query->addField('ha', 'date_of_birth');
		$db_and = db_and();
		$db_and->condition('u.status', 0, '=');
		$db_and->condition('ur.rid', 4, '=');
		$query->condition($db_and);
		$query->orderBy('u.uid', 'ASC');
		$result = $query->execute();
		
		if($result->rowCount() > 0){
		
			while($data = $result->fetchObject()) {
				if(trim($data->gender) == 'M')
					$gender = 'Male';
				elseif(trim($data->gender) == 'F')
					$gender = 'Female';
				
				$query1 = db_select('users', 'u');
				$query1->innerJoin('housing_applicant', 'ha', 'ha.uid = u.uid');
				$query1->innerJoin('file_managed', 'fm', 'u.uid = fm.uid');
				$query1->innerJoin('file_usage', 'fu', 'fm.fid = fu.fid');
				$query1->fields('fm');
				$query1->fields('fu');
				$db_and1 = db_and();
				$db_and1->condition('u.status', 0, '=');
				$db_and1->condition('fm.status', 1, '=');
				$db_and1->condition('u.uid', $data->uid, '=');
				$db_and1->condition('module', 'user_registration', '=');
				$db_and1->condition('type', 'Applicant User Reg Form', '=');
				$query1->condition($db_and1);
				$result1 = $query1->execute();
				
				
				$fields = array();
				$fields[] = trim($data->applicant_name);
				$fields[] = trim( implode('/', array_reverse(explode('-', $data->date_of_birth))));
				$fields[] = $gender;
				$fields[] = trim($data->mobile_no);
				$fields[] = trim($data->mail);
				
				if($result1->rowCount() > 0){
					if($data1 = $result1->fetchObject()) {
						if($data1->uri != '') {
							$download_path = "sites/default/files/";
							$path = substr($data1->uri, 9);
							$filename = str_replace(' ', '', $data->applicant_name).'_'.trim($data->uid).'_DigiSigned';
							
							$fields[] = l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'application_of_registration_list').'/images/download_icon.png" title="Download Applicant Registration Form" alt="Applicant Registration Form">Download Applicant Registration Form', $download_path.$path, array('html'=>TRUE, 'attributes' => array('download' => $filename, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px')));
						}
					}
				} else {
					$fields[] = 'Not Available';	
				}
				
				global $base_path;
				
				$onclick="return confirm('Are you sure you want to activate?')";
				$onclick1="return confirm('Are you sure you want to reject?')";
				$fields[] = l('<img height="16" width="16" src="'.$base_path.drupal_get_path('module', 	
				'application_of_registration_list').'/images/accept_icon.png" title="Activate" alt="Activate Icon">Activate' , 
				'update_registration_status/'.encrypt_url($data->uid).'/'.encrypt_url('activate'), array('html'=>TRUE, 
				'attributes' => array('onclick' => $onclick, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: 
				underline; font-size:12px'))).' &nbsp;&nbsp;&nbsp;| <br>'.l('<img height="16" width="16" src="'.$base_path.
				drupal_get_path('module', 'application_of_registration_list').'/images/reject_icon.png" title="Reject" alt="Reject Icon">
				Reject' , 'update_registration_status/'.encrypt_url($data->uid).'/'.encrypt_url('reject'), array('html'=>
				TRUE, 'attributes' => array('onclick' => $onclick1, 'style' => 'color: #0090C7;font-weight: 
				400;text-decoration: underline; font-size:12px')));
				
				$rows[] = $fields;
				  
			}
		}
		
		/*$output = theme_table(
			array(
			  'header' => $header,
			  'rows' => $rows,
			  'attributes' => array(),
			  'sticky' => true,
			  'caption' => '',
			  'colgroups' => array(),
			  'empty' => t("No data found!") // The message to be displayed if table is empty
			)
		).theme('pager');*/
	  
		if(count($rows) > 0) {
		// Render using Drupal's render API.
			$build['datatable'] = array(
			  '#theme' => 'datatable',
			  '#header' => $header,
			  '#rows' => $rows,
			  '#attributes' => array(),
			);
			
			// Or, render using a theme function.
			$variables = array(
			  'attributes' => array(),
			  'header' => $header,
			  'rows' => $rows,
			);
			
			$output = theme('datatable', $variables);
		}
		else {
			
			$output = '<div>
							<table class="datatable_no_data_found">
								<tr class="tr_no_data_found">
									<th class="th_no_data_found"></th>
								</tr>
								<tr class="tr_no_data_found">
									<td class="td_no_data_found">No data found!</td>
								</tr>
							</table>
						</div>';
		}
		
		return $output;	
	}