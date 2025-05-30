<?php

	function existing_occupant_search_form($form, &$form_state) {
		
		$computer_serial_no = isset($form_state['values']['computer_serial_no']) && !empty($form_state['values']['computer_serial_no']) ? $form_state['values']['computer_serial_no'] : '';
		
		
		$form['computer_serial_no']=array(
			'#title' => t('Computer Serial No.'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#attributes' => array('placeholder' => 'Enter Computer Serial No.'),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphanumeric'),
			'#weight' =>2
		);
		$form['search'] = array(
			'#value' => t('Search'),
			'#type' => 'submit',
			'#prefix' => '<div class="two" style="margin-top:43px;height: 30px;">',
			'#suffix' => '</div>',
			'#weight' =>3
	  	);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_computer_serial_no_search_form()');
		
		return $form;
	}
	
	
	function existing_occupant_search_form_validate($form, &$form_state) {
		
	}
	
	
	function existing_occupant_search_form_submit($form, &$form_state) {
		
		$computer_serial_no = $form_state['values']['computer_serial_no'];
		
		if($computer_serial_no != '') {
			
			$query = db_select('housing_online_application', 'hoa');
			$query->addField('hoa', 'computer_serial_no');
			$query->condition('hoa.computer_serial_no', $computer_serial_no, '=');
			$result = $query->execute();
			
			if($result->rowCount() > 0) {
				$form_state['redirect'] = 'all_ready_existing_occupant/'.encrypt_url($computer_serial_no);
			}
			else {
				$form_state['redirect'] = 'existing_occupant';
				
				/*$form_state['rebuild'] = TRUE;
				drupal_set_message('Computer Serial No. not in the database.', 'error');*/	
			}
		}
		else {
			drupal_set_message('Computer Serial No. can not be blank.', 'error');	
		}
	}