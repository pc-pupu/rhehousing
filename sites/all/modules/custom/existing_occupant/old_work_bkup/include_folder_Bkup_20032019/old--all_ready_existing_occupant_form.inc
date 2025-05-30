<?php

	function all_ready_existing_occupant_form($form, &$form_state, $param) {
		
		$computer_serial_no = decrypt_url($param);
		
		$occupied_estate_default = isset($form['occupied_estate']['#default_value']) && !empty($form['occupied_estate']['#default_value']) ? $form['occupied_estate']['#default_value'] : '';
	
		$occupied_block_default = isset($form['occupied_block']['#default_value']) && !empty($form['occupied_block']['#default_value']) ? $form['occupied_block']['#default_value'] : '';
	
		$occupied_estate = isset($form_state['values']['occupied_estate']) && !empty($form_state['values']['occupied_estate']) ? $form_state['values']['occupied_estate'] : $occupied_estate_default;
	
		$occupied_block = isset($form_state['values']['occupied_block']) && !empty($form_state['values']['occupied_block']) ? $form_state['values']['occupied_block'] : $occupied_block_default;
		
		$form['computer_serial_no'] = array(
			'#type' => 'hidden',
			'#default_value' => $computer_serial_no,
			'#weight' => 2
	  	);
		
		$form['allotment_no'] = array(
			'#title' => t('Allotment No.'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#required' => TRUE,
			'#weight' => 3
	  	);
		
		$form['allotment_date'] = array(
			'#title' => t('Allotment Date'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'allotment-date'),
			'#default_value' => '',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#required' => TRUE,
			'#weight' => 4
	  	);
		
		$form['occupied_estate'] = array(
			'#title' => t('Housing'),
			'#type' => 'select',
			'#options' => get_housing_estate(),
			//'#default_value' => '',
			'#required' => TRUE,
			'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_occupied_flat_no',
						   'effect' => 'fade',
						   'progress' => array(
							  'type' => '',
							  'message' => '',
							),
				),
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#validated' => TRUE,
			'#weight' => 5
		);
		
		$form['occupied_block'] = array(
			'#title' => t('Block'),
			'#type' => 'select',
			'#options' => get_housing_block(),
			//'#default_value' => '',
			'#required' => TRUE,
			'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_occupied_flat_no',
						   'effect' => 'fade',
						   'progress' => array(
							  'type' => '',
							  'message' => '',
							),
				),
			'#prefix' => '<div class="three" id="occupied_block_replace">',
			'#suffix' => '</div>',
			'#validated' => TRUE,
			'#weight' => 6
		);
		
		$form['occupied_flat'] = array(
			'#title' => t('Flat No.'),
			'#type' => 'select',
			'#options' => get_housing_flat1($occupied_estate, $occupied_block),
			'#required' => TRUE,
			'#prefix' => '<div class="three" id="occupied_flat_no_replace">',
			'#suffix' => '</div>',
			'#validated' => TRUE,
			'#weight' => 7
		);
		
		$form['submit'] = array(
			'#value' => t('Submit'),
			'#type' => 'submit',
			'#weight' => 8
	  	);
		
		$form['back-btn'] = array(
			'#type' => 'button',
			'#value' => t('Back'),
			'#attributes' => array('onclick' => 'window.history.back();'),
			'#weight' => 9
		);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_all_ready_existing_occupant_form()');
		
		return $form;
	}
	
	function all_ready_existing_occupant_form_validate($form, &$form_state) {
		
		if($form_state['values']['occupied_estate'] == '') {
			form_set_error('occupied_estate', t('Please select the housing'));
		}
		  
		if($form_state['values']['occupied_block'] == '') {
			form_set_error('occupied_block', t('Please select the block'));
		}
		  
		if($form_state['values']['occupied_flat'] == '') {
			form_set_error('occupied_flat', t('Please select the flat no.'));
		}	
	}
	
	
	function all_ready_existing_occupant_form_submit($form, &$form_state) {
		
		$computer_serial_no = $form_state['values']['computer_serial_no'];
		
		if($computer_serial_no != '') {
		
			$query = db_select('housing_online_application', 'hoa');
			$query->addField('hoa', 'online_application_id');
			$query->addField('hoa', 'computer_serial_no');
			$query->condition('hoa.computer_serial_no', $computer_serial_no, '=');
			$result = $query->execute();
			
			if($result->rowCount() > 0) {
				if($data = $result->fetchObject()) {
					if($data->computer_serial_no == $computer_serial_no) {
						
						//die(print_r($form_state['values']).'<br>'.$data->online_application_id.'<br>'.$computer_serial_no);
						echo '<pre>';
						print_r($form_state['values']);
						print_r($data->online_application_id);
						exit;
						/*db_update('housing_online_application')
						->fields()
						->condition('online_application_id', $data->online_application_id, '=')
						->execute();*/
					}
				}
			}
		}
	}
	
	
	function _reload_occupied_flat_no($form, &$form_state) {
	
		$commands[] = ajax_command_replace('#occupied_block_replace', drupal_render($form['occupied_block']));
		$commands[] = ajax_command_replace('#occupied_flat_no_replace', drupal_render($form['occupied_flat']));
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}
	
	