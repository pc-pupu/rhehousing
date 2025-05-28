<?php

	function subdivn_rhewise_complaint_list_form($form, &$form_state) {
		global $user_role;
		
		$subdiv = !empty($form_state['values']['subdiv']) ? $form_state['values']['subdiv'] : '';
		$rhe_name = !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : '';
		
		if($user_role == 6) {
			$form['subdiv'] = array(
				'#type' => 'select',
				'#title' => 'Select Sub-Division',
				'#options' => subdiv_list(),
				'#default_value' => '',
				'#required' => TRUE,
				'#prefix' => '<div>',
				'#suffix' => '</div>',
				'#ajax' => array(
					'event' => 'change',
					//'wrapper' => 'no_of_vacancy',
					'callback' => '_reload_rhename',
					'method' => 'replace',
				),
				'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				),
			);
			
			if($subdiv != '') {
			
				$form['rhe_name'] = array(
					'#title' => t('Select RHE'),
					'#type' => 'select',
					'#options' => subdivn_wise_rhe_list($subdiv),
					'#required' => TRUE,
					//'#weight' => -10,
					'#prefix' => '<div id="rhe_name_replace">',
					'#suffix' => '</div>',
					'#ajax' => array(
						'event' => 'change',
						//'wrapper' => 'no_of_vacancy',
						'callback' => '_reload_subdivn_rhewise_complaint_list',
						'method' => 'replace',
					),
					'#select2' => array(
						'width' => '500',
						//'placeholder' => '- Select -',
						'allowClear' => TRUE
					),
					//'#attributes' => array('class' => array('update_rhe_selectize')),
				);
			} else {
				$form['rhe_name'] = array(
					'#prefix' => '<div id="rhe_name_replace">',
					'#suffix' => '</div>',
				);	
			}
		
			$form['subdivn_rhewise_complaint_list'] = array(
				'#prefix' => '<div  id="subdivn_rhewise_complaint_list_replace">',
				'#suffix' => '</div>',
			);
			
			if($subdiv != '' && $rhe_name != '') {
				
				$form['subdivn_rhewise_complaint_list'] = array(
					'#type' => 'markup',
					'#markup' => subdivn_rhewise_complaint_list_page($subdiv, $rhe_name),
					'#prefix' => '<div id="subdivn_rhewise_complaint_list_replace">',
					'#suffix' => '</div>',
				);
			 
			}
			
			return $form;
		}
	}
	
	function subdivn_rhewise_complaint_list_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function subdivn_rhewise_complaint_list_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_rhename($form, &$form_state) {
		$commands = array();
		
		$commands[] = ajax_command_replace("#rhe_name_replace", drupal_render($form['rhe_name']));
		$commands[] = ajax_command_replace("#subdivn_rhewise_complaint_list_replace", drupal_render($form['subdivn_rhewise_complaint_list']));
		
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function _reload_subdivn_rhewise_complaint_list($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#subdivn_rhewise_complaint_list_replace", drupal_render($form['subdivn_rhewise_complaint_list']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function subdivn_rhewise_complaint_list_page($subdiv = '', $rhe_name = '') {
		global $base_path;
		global $user_role;
		
		ctools_include('modal');
		ctools_modal_add_js();
		
		global $base_path;
	 	$src = $base_path.drupal_get_path('module', 'complaint_management').'/images/view.png';
		
		$output = '';
		$result = fetch_subdivn_rhe_wise_complaint_list($subdiv, $rhe_name);
		$rows = array();
		$header = array();
		
		$header[] = array('data' => 'Sl. No.');
		$header[] = array('data' => 'Complaint No');
		$header[] = array('data' => 'Date of Complaint');
		$header[] = array('data' => 'Complaint Type');
		$header[] = array('data' => 'Complaint Details');
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
			
			if($result1->rowCount() > 0) {
				$data1 = $result1->fetchObject();
				if($data1->action_report_to_occupant != '') {
					$fields[] = l('<img src="'.$src.'" width="30" height="30">', 'view_action_report_housing/nojs/'.encrypt_url($data->online_complaint_id), array('html'=>TRUE, 'attributes' => array('class' => 'ctools-use-modal')));
				} else {
					$fields[] = 'Action Report not submitted by Division.';
				}
				
			} else {
				$fields[] = 'Action Report not submitted by Sub-Division.';	
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
	
	