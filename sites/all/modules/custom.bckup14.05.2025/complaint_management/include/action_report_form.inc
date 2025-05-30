<?php

	function action_report_form($form, &$form_state, $online_complaint_id) {
		global $user;
		global $user_role;
		
		$online_complaint_id = decrypt_url($online_complaint_id);
		
		$action_report_accepted =  isset($form_state['values']['action_report_accepted']) && !empty($form_state['values']['action_report_accepted']) ? $form_state['values']['action_report_accepted'] : '';
		
		$query = db_select('housing_online_complaint', 'hoc');
		$query->innerJoin('housing_flat', 'hf', 'hf.flat_id = hoc.occupant_flat_id');
		$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query->fields('hoc', array());
		$query->fields('hf', array());
		$query->fields('he', array());
		$query->condition('online_complaint_id', $online_complaint_id, '=');
		$result = $query->execute();
		if($result->rowCount() > 0) {
			$data = $result->fetchObject();	
		}
		
		$form['online_complaint_id'] = array(
			'#type' => 'hidden',
			'#default_value' => $online_complaint_id,
	  	);
		
		$form['complaint_date'] = array(
			'#title' => t('Compalint Date'),
			'#type' => 'textfield',
			'#default_value' => implode('/', array_reverse(explode('-', $data->complaint_date))),
			'#attributes' => array('readonly' => 'readonly'),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		
		$form['complaint_no'] = array(
			'#title' => t('Compalint No.'),
			'#type' => 'textfield',
			'#default_value' => $data->complaint_no,
			'#attributes' => array('readonly' => 'readonly'),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		
		$form['rhe_name'] = array(
			'#title' => t('RHE Name'),
			'#type' => 'textfield',
			'#default_value' => $data->estate_name,
			'#attributes' => array('readonly' => 'readonly'),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		
		$form['occupant_flat_no'] = array(
			'#title' => t('Occupant Flat No'),
			'#type' => 'textfield',
			'#default_value' => $data->flat_no,
			'#attributes' => array('readonly' => 'readonly'),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		
		$form['complaint_type'] = array(
			'#title' => t('Compalint Type'),
			'#type' => 'textfield',
			'#default_value' => $data->complaint_type,
			'#attributes' => array('readonly' => 'readonly'),
			'#required' => TRUE,
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
		);
		
		$form['complaints_details'] = array(
			'#title' => t('The specific details of the complaint'),
			'#type' => 'textarea',
			'#default_value' => $data->complaint_details,
			'#attributes' => array('readonly' => 'readonly'),
			'#required' => TRUE,
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
		);
		
		$max_length = 200;
		if($user_role == 7) {
			$form['subdivn_action_report'] = array(
				'#title' => t('Action Report'),
				'#type' => 'textarea',
				'#required' => TRUE,
				/*'#prefix' => '<div class="two-one">',
				'#suffix' => '</div>',*/
				'#element_validate' => array('element_validate_textarea'),
				'#attributes'=>array('onKeyPress' => "return(this.value.length<$max_length);"), 
			);	
		} else if($user_role == 8) {
			
			$query1 = db_select('housing_complaint_action', 'hca');
			$query1->fields('hca', array());
			$query1->condition('online_complaint_id', $online_complaint_id, '=');
			$result1 = $query1->execute();
			if($result1->rowCount() > 0) {
				$data1 = $result1->fetchObject();	
			}
			
			$form['action_report_from_subdivn'] = array(
				'#title' => t('Action Report From Sub-Division'),
				'#type' => 'textarea',
				'#required' => TRUE,
				'#default_value' => $data1->subdivn_action_report,
				'#attributes' => array('readonly' => 'readonly'),
				/*'#prefix' => '<div class="two-one">',
				'#suffix' => '</div>',*/
			);	
			
			$form['action_report_accepted'] = array(
				'#title' => t('Do you want to accept Sub-Division Action Report as Final Action Report?'),
				'#type' => 'radios',
				'#options' => array('Y' => 'YES', 'N' => 'NO'),
				'#prefix' => '<div class="one">',
				'#suffix' => '</div>',
				'#required' => TRUE,
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_divn_action_report',
						   'method' => 'replace',
				),
			);
			
			if(trim($action_report_accepted) == 'N') {
				$form['divn_action_report'] = array(
					'#title' => t('Final Action Report'),
					'#type' => 'textarea',
					'#required' => TRUE,
					/*'#prefix' => '<div class="two-one">',
					'#suffix' => '</div>',*/
					'#prefix' => '<div id="divn_action_report_replace">',
					'#suffix' => '</div>',
					'#element_validate' => array('element_validate_textarea'),
					'#attributes'=>array('onKeyPress' => "return(this.value.length<$max_length);"), 
				);		
			} else {
				$form['divn_action_report'] = array(
					'#prefix' => '<div id="divn_action_report_replace">',
					'#suffix' => '</div>', 
				);	
			}
				
		}
		
		$form['#attributes'] = array('onsubmit' => 'return validate_action_report_form()');
		
		$form['submit_button']=array(
			'#type' => 'submit',
			'#value' => t('Submit'),
		);						
		
		return $form; 
	}
	
	
	function action_report_form_validate($form, &$form_state) {
		
		global $user_role;
		
		if($user_role == 7) {
			if(strlen($form_state['values']['subdivn_action_report']) > 200) {
				form_set_error('subdivn_action_report', t('Action Report contains more than 200 characters.'));
			}
		} else if($user_role == 8) {
			if(strlen($form_state['values']['divn_action_report']) > 200) {
				form_set_error('divn_action_report', t('Action Report contains more than 200 characters.'));
			}
		}
		
	}
	
	
	function action_report_form_submit($form, &$form_state) {
		global $user;
		global $user_role;
		
		
		if($user_role == 7) {
			
			$subdivn_action_report_arr = array();
			
			$subdivn_action_report_arr['online_complaint_id'] = $form_state['values']['online_complaint_id'];
			$subdivn_action_report_arr['subdivn_uid'] = $user->uid;
			$subdivn_action_report_arr['subdivn_action_report'] = ucfirst($form_state['values']['subdivn_action_report']);
					
					
			db_insert('housing_complaint_action')
			->fields($subdivn_action_report_arr)
			->execute();
			
			drupal_set_message('Action Report Submitted to Division.');
			drupal_goto('rhewise_complaint_list');
			
		} else if($user_role == 8) {
			
			$online_complaint_id = $form_state['values']['online_complaint_id'];
			$divn_action_report_arr = array();
			
			$divn_action_report_arr['divn_uid'] = $user->uid;
			$divn_action_report_arr['action_report_accepted'] = $form_state['values']['action_report_accepted'];
			
			if(trim($form_state['values']['action_report_accepted']) == 'Y') {
				$divn_action_report_arr['action_report_to_occupant'] = $form_state['values']['action_report_from_subdivn'];
			} else if(trim($form_state['values']['action_report_accepted']) == 'N') {
				$divn_action_report_arr['action_report_to_occupant'] = ucfirst($form_state['values']['divn_action_report']);	
			}
					
					
			db_update('housing_complaint_action')
			->fields($divn_action_report_arr)
			->condition('online_complaint_id', $online_complaint_id, '=')
			->execute();
			
			db_update('housing_online_complaint')
			->fields(array(
					'complaint_status' => 'Action Taken',
				)
			)
			->condition('online_complaint_id', $online_complaint_id, '=')
			->execute();
			
			drupal_set_message('Action Report Submitted.');
			drupal_goto('rhewise_complaint_list');
			
		}
		
		
		
		
	}
	
	
	function _reload_divn_action_report($form, &$form_state) {
		$commands[] = ajax_command_replace('#divn_action_report_replace', drupal_render($form['divn_action_report']));
		
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}