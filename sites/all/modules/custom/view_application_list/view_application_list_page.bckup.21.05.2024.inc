<?php

function view_app_page($status='', $entity = '') {
	global $user,$user_role;
	//echo $user_role;
	//die;
	//echo $entity;
	$status = decrypt_url($status);
	$entity = decrypt_url($entity);
	//echo $entity;
	$output = '';
	$rows =array();
	$header = array();
	//echo "<pre>";print_r($entity);die;
	
		if($status !== '' && $entity !== '' && preg_match("/^[a-zA-Z\-\_]*$/",$status) && preg_match("/^[a-zA-Z\-\_]*$/",$entity)){
		if($status == 'applied'){
			$statusMsg = 'New ';
		}
		else if($status == 'verified'){
			$statusMsg = 'Verified ';
		}
		else if($status == 'reject'){
			$statusMsg = 'Rejected ';
		}
		
		if($entity == 'new-apply'){
			$entityMsg = 'New Allotment ';
		}
		else if($entity == 'vs'){
			$entityMsg = 'Vertical Shifting ';
		}
		else if($entity == 'cs'){
			$entityMsg = 'Category Shifting ';
		}
		else if($entity == 'new_license'){
			$entityMsg = 'New Licence ';
		}
		
		//new code
		else if($entity == 'vs_licence'){
			$entityMsg = 'VS Licence ';
		}
		else if($entity == 'cs_licence'){
			$entityMsg = 'CS Licence ';
		}
		//
		
		else if($entity == 'renew_license'){
			$entityMsg = 'Renew Licence ';
		}
			
		drupal_set_title($statusMsg.'Application List for '.$entityMsg);
			
		
		$result = fetch_all_application_detail1($entity,$status);
		//echo "<pre>";print_r($result);die;

		$header = array(
			'applicant_name' => array(
				'data' => 'Name'
			) ,
			'application_no' => array(
				'data' => 'Application No.',
				'width'=>'20%'
			) 
		);
		
		
		if($status == 'applied'){
			$header['date_of_application'] = array('data' => 'Date of Application');
		}
		//$header[] = array('data' => 'Time of Application');
		
		if($entity == 'new-apply'){
			$header['flat_type'] = array('data' => 'Flat Type');
			$header['allotment_category'] = array('data' => 'Allotment Reason');
		}
		
		if($status == 'verified'){
			$header['date_of_verified'] = array('data' => 'Verification Date');
		}
		
		if($status == 'verified' && ($entity == 'new-apply')){
			$header['computer_serial_no'] = array('data' => 'Computer Serial No');
		}
		
		else if($status == 'reject'){
			$header[] = array('data' => 'Reject Date');
		}
		$header[] = array('data' => 'View');
		
		if($status == 'applied') {
			$header[] = array('data' => 'Action', 'width'=>'20%');
		}
	
		 while($data = $result->fetchObject()) {

			//echo json_encode($data);
			 $fields = array();
			 
			 //if($entity == 'new_license' || $entity == 'vs_licence' || $entity == 'cs_licence'){
				$fields[] = $data->applicant_name;
			 //}
			 $fields[] = $data->application_no;
			if($status == 'applied'){
				$fields[] = implode('/', array_reverse(explode('-', $data->date_of_application)));
			}
			
			if($entity == 'new-apply'){
				$fields[] = $data->flat_type;
			}
			
			//if($entity == 'new-apply' || $entity == 'vs' || $entity == 'cs'){
			if($entity == 'new-apply'){
				$fields[] = $data->allotment_category;
			}
			//echo $data->date_of_verified;die;
			if($status != 'applied'){
				if(isset($data->date_of_verified))
				$fields[] = implode('/', array_reverse(explode('-', $data->date_of_verified)));
			else
				$fields[] = 'NA';
			} 
			if($status == 'verified' && ($entity == 'new-apply')) {
				//echo "hghg";die;
				/*$c_wait_no = get_individual_waiting_no($data1->application_no);
				$fields[] = $c_wait_no != 0 ? $c_wait_no : '';*/
				
				$fields[] = $data->computer_serial_no;

			}
			
			 global $base_path;
			 $src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
			 $fields[] = l(
							'<img src="'.$src.'" alt="View Icon">',
							'application_detail/'.encrypt_url($data->online_application_id), 
							array(
									'html'=>TRUE,
									'attributes'=> array('target' => '_blank'),
							)
						);
			if($status == 'applied') {
				/* if($data->uploaded_app_form == '') {
					$fields[] = '<b><font color="#FF0000">Signed Application Form upload pending.</font></b>';	
				} else {
					
				} */
				$onclick="return confirm('Are you sure you want to approve?')";
				$onclick1="return confirm('Are you sure you want to reject?')";
				$fields[] = l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'view_application_list').'/images/accept_icon.png" title="Approve" 
					alt="Accept Icon" alt="Accept Icon">Approve' , 'application-approve/'.encrypt_url($data->online_application_id).'/'.encrypt_url('verified').'/'.encrypt_url($status).'/
					'.encrypt_url($entity), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: underline; 
					font-size:14px'))).' &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| <br><br>'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'view_application_list'
					).'/images/reject_icon.png" title="Reject" alt="Reject Icon">Reject' ,  'update_status/'.encrypt_url($data->online_application_id).'/'.encrypt_url('reject').'/'.
					encrypt_url($status).'/'.encrypt_url($entity), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick1, 'style' => 'color: #0090C7;font-weight: 
					400;text-decoration: underline; font-size:14px')));
			}
				
			  $rows[] = $fields;
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
		}else {
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
	
	
	}
	return $output;
}