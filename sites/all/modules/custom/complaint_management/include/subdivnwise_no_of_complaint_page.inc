<?php

	function subdivnwise_no_of_complaint_form($form, &$form_state) {
		global $user_role;
		
		$subdiv = !empty($form_state['values']['subdiv']) ? $form_state['values']['subdiv'] : '';
		
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
					'callback' => '_reload_subdivnwise_no_of_complaints',
					'method' => 'replace',
				),
				'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				),
			);
		
			$form['subdivn_wise_no_of_complaint'] = array(
				'#prefix' => '<div  id="subdivn_wise_no_of_complaint_replace">',
				'#suffix' => '</div>',
			);
			
			if($subdiv != '') {
				
				$form['subdivn_wise_no_of_complaint'] = array(
					'#type' => 'markup',
					'#markup' => subdivn_wise_no_of_complaint_page($subdiv),
					'#prefix' => '<div id="subdivn_wise_no_of_complaint_replace">',
					'#suffix' => '</div>',
				);
			 
			}
			
			return $form;
		}
	}
	
	function subdivnwise_no_of_complaint_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function subdivnwise_no_of_complaint_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_subdivnwise_no_of_complaints($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#subdivn_wise_no_of_complaint_replace", drupal_render($form['subdivn_wise_no_of_complaint']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function subdivn_wise_no_of_complaint_page($subdiv = '') {
		global $base_path;
		global $user_role;
		
		$output = '';
		$result = fetch_subdivn_wise_no_of_complaint($subdiv);
		$rows = array();
		$header = array();
		
		$header[] = array('data' => 'Sl. No.');
		$header[] = array('data' => 'Sub-Division Name');
		$header[] = array('data' => 'Total No. of Complaints');
		$header[] = array('data' => 'No. of Pending Complaints');
		$header[] = array('data' => 'No. of Action Taken Complaints');
		
		$i = 1;
		if($result->rowCount() > 0) {
			$data = $result->fetchObject();
			$tot_no_of_complaints = $result->rowCount();
			$fields = array();
			
			$fields[] = $i;
			$fields[] = $data->subdiv_name;
			$fields[] = $tot_no_of_complaints;
			
			//for pending
			$result_pending = fetch_subdivn_wise_no_of_pending_complaint($subdiv);
			if($result_pending->rowCount() > 0) {
				$tot_no_of_pending_complaints = $result_pending->rowCount();
				$fields[] = $tot_no_of_pending_complaints;
			} else {
				$fields[] = 0;	
			}
			
			//for action taken
			$result_action = fetch_subdivn_wise_no_of_action_complaint($subdiv);
			if($result_pending->rowCount() > 0) {
				$tot_no_of_action_complaints = $result_action->rowCount();
				$fields[] = $tot_no_of_action_complaints;
			} else {
				$fields[] = 0;	
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
			
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'complaint_management').'/images/pdf_icon.png" 
						title="Download All Sub-Divisions No. of Complaints List" alt="PDF Icon">Download All Sub-Divisions No. of Complaints List', 
						'all_subdivn_no_of_complaint/all_subdivn_no_of_complaint_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => 	
						'_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: 	none; font-size:14px'))).$output;
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