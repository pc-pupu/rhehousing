<?php
		
	function rhewise_complaint_list_form($form, &$form_state) {
		global $user_role;
		
		$rhe_name =  !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : 0;
		
		if($user_role == 7 || $user_role == 8) {
			$form['rhe_name'] = array(
				'#title' => t('Name of the RHE'),
				'#type' => 'select',
				'#options' => rhe_list_specific(),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div>',
				'#suffix' => '</div>',
				'#ajax' => array(
					'event' => 'change',
					//'wrapper' => 'no_of_vacancy',
					'callback' => '_reload_rhewise_complaint_list',
					'method' => 'replace',
				),
				'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				),
				//'#attributes' => array('class' => array('update_rhe_selectize')),
			);
		}
		
		$form['rhewise_complaint_list'] = array(
			'#prefix' => '<div  id="rhewise_complaint_list">',
			'#suffix' => '</div>',
		);
		
		if($rhe_name != 0) {
			
			$form['rhewise_complaint_list'] = array(
				'#type' => 'markup',
				'#markup' => rhewise_complaint_list_page($rhe_name),
				'#prefix' => '<div id="rhewise_complaint_list">',
				'#suffix' => '</div>',
			);
		 
	  	}
		
		return $form;
	}
	
	function rhewise_complaint_list_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function rhewise_complaint_list_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_rhewise_complaint_list($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#rhewise_complaint_list", drupal_render($form['rhewise_complaint_list']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function rhewise_complaint_list_page($rhe_name = '') {
		global $base_path;
		global $user_role;
		
		ctools_include('modal');
		ctools_modal_add_js();
		
		global $base_path;
	 	$src = $base_path.drupal_get_path('module', 'complaint_management').'/images/view.png';
		
		$output = '';
		$result = fetch_rhewise_complaint_list($rhe_name);
		$rows = array();
		$header = array();
		
		$header[] = array('data' => 'Sl. No.');
		$header[] = array('data' => 'Complaint No');
		$header[] = array('data' => 'Date of Complaint');
		$header[] = array('data' => 'Complaint Type');
		$header[] = array('data' => 'Complaint Details');
		$header[] = array('data' => 'Action');
		$header[] = array('data' => 'Action Report Details');
		
		$i = 1;
		while($data = $result->fetchObject()) {
			
			$fields = array();
			
			$fields[] = $i;
			$fields[] = $data->complaint_no;
			$fields[] = implode('/', array_reverse(explode('-', $data->complaint_date)));
			$fields[] = $data->complaint_type;
			$fields[] = $data->complaint_details;
			
			if($user_role == 7) {
				$result1 = check_subdivn_action_report($data->online_complaint_id);
				if($result1->rowCount() > 0) {
					$fields[] = 'Action Report Submitted to Division';
					$fields[] = l('<img src="'.$src.'" width="30" height="30">', 'view_action_report_divn_subdivn/nojs/'.encrypt_url($data->online_complaint_id), array('html'=>TRUE, 'attributes' => array('class' => 'ctools-use-modal')));	
				} else {
					$fields[] = l('Submit Action Report to Division' , 'action_report/'.encrypt_url($data->online_complaint_id), array('html'=>TRUE, 'attributes' => array('style' => 'color: #0090C7; font-weight: 400; text-decoration: underline; font-size: 14px')));
					$fields[] = 'Action not taken till now.';
				}
				
			} else if($user_role == 8) {
				$result1 = check_divn_action_report($data->online_complaint_id);
				if($result1->rowCount() > 0) {
					$fields[] = 'Action Report Submitted';
					$fields[] = l('<img src="'.$src.'" width="30" height="30">', 'view_action_report_divn_subdivn/nojs/'.encrypt_url($data->online_complaint_id), array('html'=>TRUE, 'attributes' => array('class' => 'ctools-use-modal')));	
				} else {
					$result2 = fetch_action_report($data->online_complaint_id);
					if($result2->rowCount() > 0) {
						$fields[] = l('Submit Action Report' , 'action_report/'.encrypt_url($data->online_complaint_id), array('html'=>TRUE, 'attributes' => array('style' => 'color: #0090C7; font-weight: 400; text-decoration: underline; font-size: 14px')));
					} else {
						$fields[] = 'Action Report not Submitted by Sub-Division';	
					}
					$fields[] = 'Action not taken till now.';
				}
				
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
		
		if($result->rowCount() > 0) {
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