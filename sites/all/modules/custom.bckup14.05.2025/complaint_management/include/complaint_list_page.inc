<?php

	function complaint_list_page() {
		global $base_path;
		global $user;
		
		ctools_include('modal');
		ctools_modal_add_js();
		
		global $base_path;
	 	$src = $base_path.drupal_get_path('module', 'complaint_management').'/images/view.png';
		
		$output = '';
		$result = fetch_complaint_list($user->uid);
		$rows = array();
		$header = array();
		
		$header[] = array('data' => 'Sl. No.');
		$header[] = array('data' => 'Complaint No.');
		$header[] = array('data' => 'Date of Complaint');
		$header[] = array('data' => 'Complaint Type');
		$header[] = array('data' => 'Complaint Details');
		$header[] = array('data' => 'Complaint Status');
		$header[] = array('data' => 'Action Report Details');
		
		$i = 1;
		while($data = $result->fetchObject()) {
			
			$result1 = fetch_action_report($data->online_complaint_id);
			 
			$fields = array();
			
			$fields[] = $i;
			$fields[] = $data->complaint_no;
			$fields[] = implode('/', array_reverse(explode('-', $data->complaint_date)));
			$fields[] = $data->complaint_type;
			$fields[] = $data->complaint_details;
			$fields[] = $data->complaint_status;
			
			if($result1->rowCount() > 0) {
				$data1 = $result1->fetchObject();
				if($data1->action_report_to_occupant != '') {
					//$fields[] = $data1->action_report_to_occupant;
					$fields[] = l('<img src="'.$src.'" width="30" height="30">', 'view_action_report/nojs/'.encrypt_url($data->online_complaint_id), array('html'=>TRUE, 'attributes' => array('class' => 'ctools-use-modal')));
				} else {
					$fields[] = 'Action not taken till now.';		
				}
			} else {
				$fields[] = 'Action not taken till now.';
			}
			
			$i++;
			
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
