<?php

	function view_action_report_divn_subdivn_page($ajax, $online_complaint_id) {
		$online_complaint_id = decrypt_url($online_complaint_id);
		if($ajax) {
			ctools_include('ajax');
			ctools_include('modal');
			
			$form_state = array(
				'ajax' => TRUE,
				'title' => t('Action Report Details'),
				'online_complaint_id' => $online_complaint_id,
			);
			
			/*$form_state = array(
			'ajax' => true,
			'title' => t('Edit quote'), 
			'is_ajax_update' => TRUE,
			'quote' => $quote,
			);
			*/
			// Use ctools to generate ajax instructions for the browser to create
			// a form in a modal popup.
			$output = ctools_modal_form_wrapper('view_action_report_divn_subdivn_form', $form_state);
			
			// If the form has been submitted, there may be additional instructions
			// such as dismissing the modal popup.
			if(!empty($form_state['ajax_commands'])) {
				$output = $form_state['ajax_commands'];
			}
			
			// Return the ajax instructions to the browser via ajax_render().
			print ajax_render($output);
			drupal_exit();
			
		} else {
			return drupal_get_form('view_action_report_divn_subdivn_form');
		}
		
	}
	
	function view_action_report_divn_subdivn_form($form, &$form_state) {
		
		$online_complaint_id = $form_state['online_complaint_id'];
		
		$result = fetch_action_report($online_complaint_id);
		$data = $result->fetchObject();
		
		
		$form['complaint_no'] = array(
			'#title' => t('Compalint No.'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#attributes' => array('readonly' => 'readonly'),
			'#default_value' => $data->complaint_no,
		);
		
		$form['complaint_date'] = array(
			'#title' => t('Compalint Date'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#attributes' => array('readonly' => 'readonly'),
			'#default_value' => implode('/', array_reverse(explode('-', $data->complaint_date))),
		);
		
		$form['complaint_type'] = array(
			'#title' => t('Compalint Type'),
			'#type' => 'textfield',
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
			'#attributes' => array('readonly' => 'readonly'),
			'#default_value' => $data->complaint_type, 
		);
		
		$form['complaints_details'] = array(
			'#title' => t('The specific details of the complaint'),
			'#type' => 'textarea',
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
			'#attributes' => array('readonly' => 'readonly'),
			'#default_value' => $data->complaint_details, 
		);
		
		$form['subdivn_action_report'] = array(
			'#title' => t('Action Report By Sub-Division'),
			'#type' => 'textarea',
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
			'#attributes' => array('readonly' => 'readonly'),
			'#default_value' => $data->subdivn_action_report, 
		);
		
		$form['action_report_to_occupant'] = array(
			'#title' => t('Action Report Sent To Occupant (By Division)'),
			'#type' => 'textarea',
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
			'#attributes' => array('readonly' => 'readonly'),
			'#default_value' => $data->action_report_to_occupant, 
		);
												
		return $form;				
		
	}