<?php

	function new_complaint_form($form, &$form_state) {
		
		$complaint_type =  isset($form_state['values']['complaint_type']) && !empty($form_state['values']['complaint_type']) ? $form_state['values']['complaint_type'] : '';
		
		$form['complaint_type'] = array(
			'#title' => t('Complaint Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select Complaint Type --', 'Civil Work' => 'Civil Work', 'Electrical Work' => 'Electrical Work', 'Other' => 'Other'),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_other_complaint_type',
					   'method' => 'replace',
			),
		);
		
		$form['adjust_div1'] = array(
			'#type' => 'hidden',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		
		if(trim($complaint_type) == 'Other') {
			
			$form['complaint_other_type'] = array(
				'#title' => t('Compalint Other Type'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#prefix' => '<div id="complaint_other_type_replace" class="one">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'),
			);
			
		} else {
			
			$form['complaint_other_type'] = array(
				'#prefix' => '<div id="complaint_other_type_replace">',
				'#suffix' => '</div>',
			);
		}
		
		
		$max_length = 200;
		$form['complaints_details'] = array(
			'#title' => t('The specific details of the complaint'),
			'#type' => 'textarea',
			'#required' => TRUE,
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_textarea'),
			'#attributes'=>array('onKeyPress' => "return(this.value.length<$max_length);"), 
		);
		
		
		$form['#attributes'] = array('onsubmit' => 'return validate_new_complaint_form()');
		
		$form['submit_button']=array(
			'#type' => 'submit',
			'#value' => t('Submit'),
		);						
		
		return $form; 
	}
	
	
	function new_complaint_form_validate($form, &$form_state) {
		
		if(strlen($form_state['values']['complaints_details']) > 200) {
			form_set_error('complaints_details', t('Complaints details contains more than 200 characters.'));
		}
		
		$result = fetch_flat_occupant_list();
		if($result->rowCount() <= 0) {
			form_set_error('occupant_error', t('You are not Occupant. You can\'t submit a complaint.'));	
		}
		
	}
	
	
	function new_complaint_form_submit($form, &$form_state) {
		global $user;
		
		$result = fetch_flat_occupant_list();
		$data = $result->fetchObject();
		
		$query1 = db_select('housing_online_complaint', 'hoc');
		$query1->fields('hoc', array());
		$result1 = $query1->execute();
		$no_of_rows = $result1->rowCount();
		if($no_of_rows <= 0) {
			$online_complaint_id = '01';	
		} else {
			$result2 = db_query("select max(online_complaint_id) as online_complaint_id from {housing_online_complaint}");
			$data2 = $result2->fetchObject();
			$x = $data2->online_complaint_id;
			if($x < 9) {
				$x = $x + 1;
				$online_complaint_id = '0'.$x;
			}
			else {
				$x = $x + 1;
				$online_complaint_id = $x;
			}		
		}
		
		$online_complaint_arr = array();
		$online_complaint_arr['uid'] = $user->uid;
		$online_complaint_arr['complaint_no'] = implode('/', array_reverse(explode('-', date('Y-m-d')))).'-'.$data->flat_no.'-'.$online_complaint_id;
		$online_complaint_arr['complaint_date'] = date('Y-m-d');
		$online_complaint_arr['complaint_submission_time'] = time();
		$online_complaint_arr['occupant_flat_id'] = $data->occupant_flat_id;
		
		if($form_state['values']['complaint_type'] == 'Other') {
			$online_complaint_arr['complaint_type'] = ucwords($form_state['values']['complaint_other_type']);	
		} else {
			$online_complaint_arr['complaint_type'] = $form_state['values']['complaint_type'];		
		}
		
		$online_complaint_arr['complaint_details'] = ucfirst($form_state['values']['complaints_details']);
		$online_complaint_arr['flat_occupant_id'] = $data->flat_occupant_id;
		$online_complaint_arr['complaint_status'] = 'Submitted';
		
		/*echo '<pre>';
		print_r($online_complaint_arr);
		die();*/		
				
		db_insert('housing_online_complaint')
		->fields($online_complaint_arr)
		->execute();
		
		drupal_set_message('Thank You!<br>Your complaint has been received.');
	}
	
	
	function _reload_other_complaint_type($form, &$form_state) {
		$commands[] = ajax_command_replace('#complaint_other_type_replace', drupal_render($form['complaint_other_type']));
		
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}