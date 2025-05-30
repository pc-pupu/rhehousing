<?php
		
	function rhewise_flatlist_form($form, &$form_state) {
		/*$rhe_name_default = isset($form['rhe_name']['#default_value']) && !empty($form['rhe_name']['#default_value']) ? $form['rhe_name']['#default_value'] : 0;
		$flat_type_default = isset($form['flat_type']['#default_value']) && !empty($form['flat_type']['#default_value']) ? $form['flat_type']['#default_value'] : 0;
		$block_name_default = isset($form['block_name']['#default_value']) && !empty($form['block_name']['#default_value']) ? $form['block_name']['#default_value'] : 0;
		$flat_no_default = isset($form['flat_no']['#default_value']) && !empty($form['flat_no']['#default_value']) ? $form['flat_no']['#default_value'] : 0;*/
		
		$rhe_name =  isset($form_state['values']['rhe_name']) && !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : 0;
		$flat_type =  isset($form_state['values']['flat_type']) &&!empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : 0;
		$block_name =  isset($form_state['values']['block_name']) &&!empty($form_state['values']['block_name']) ? $form_state['values']['block_name'] : 0;
		$flat_no =  isset($form_state['values']['flat_no']) &&!empty($form_state['values']['flat_no']) ? $form_state['values']['flat_no'] : 0;
		
		
		$form['rhe_name'] = array(
			'#title' => t('Name of the RHE'),
			'#type' => 'select',
			//'#options' => rhe_list(),
			'#options' => rhe_list_specific(),
			'#required' => TRUE,
			//'#weight' => -10,
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_flat_type',
				'method' => 'replace',
			),
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)
		);
		
		$form['flat_type'] = array(
			'#prefix' => '<div class="three" id="flat_type_replace">',
			'#suffix' => '</div>',
		);
			
		if($rhe_name != 0) {
			$form['flat_type'] = array(
				'#title' => t('Flat Type'),
				'#type' => 'select',
				'#options' => flat_type_under_rhe($rhe_name),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="flat_type_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_blocklist',
					'method' => 'replace',
				),
			);
		}
		
		$form['block_name'] = array(
			'#prefix' => '<div class="three" id="block_name_replace">',
			'#suffix' => '</div>',
		);
			
		if($rhe_name != 0 && $flat_type != 0) {
			$form['block_name'] = array(
				'#title' => t('Name of the Block'),
				'#type' => 'select',
				'#options' => block_name_under_rhe($rhe_name, $flat_type),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="block_name_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_flatlist',
					'method' => 'replace',
				),
			);
		}
		
		$form['flat_no'] = array(
			'#prefix' => '<div class="three" id="flat_no_replace">',
			'#suffix' => '</div>',
		);
			
		if($rhe_name != 0 && $flat_type != 0 && $block_name != 0) {
			$form['flat_no'] = array(
				'#title' => t('Flat No.'),
				'#type' => 'select',
				'#options' => flatno_under_rhe($rhe_name, $flat_type, $block_name),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="flat_no_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_occupant_entry',
					'method' => 'replace',
				),
			);
		}
		
		
		/*$form['hrms_id'] = array(
			'#prefix' => '<div class="two" id="hrms_id_replace">',
			'#suffix' => '</div>',
		);*/
		$form['submit_button'] = array(
			'#prefix' => '<div class="two-one" id="submit_button_replace">',
			'#suffix' => '</div>',
		);
		
		if($rhe_name != 0 && $flat_type != 0 && $block_name != 0 && $flat_no != 0) {
			/*$form['hrms_id'] = array(
				'#title' => t('HRMS ID'),
				'#type' => 'textfield',
				'#prefix' => '<div class="two" id="hrms_id_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_numeric_positive'),
				'#attributes' => array('class' => array('numeric_positive')), 
				'#required' => TRUE,
			);*/
			
			$form['submit_button']=array(
				'#type' => 'submit',
				'#prefix' => '<div class="two-one" id="submit_button_replace">',
				'#suffix' => '</div>',
				//'#value' => t('Search Details'),
				'#value' => t('Insert Occupant Details'),
			);
		}
		$form['#attributes'] = array('onsubmit' => 'return validate_rhewise_occupant_entry_form()');
		
		return $form;
	}
	
	function rhewise_flatlist_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
		
	}
	
	function rhewise_flatlist_form_submit($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
		
		//$hrms_id = $form_state['values']['hrms_id'];
		$flat_id = $form_state['values']['flat_no'];
		//die($hrms_id);
		/*$result = fetch_hrms_details($hrms_id);
		$result1 = check_hrms_id_entry($hrms_id);*/
		
		/*echo '<pre>';
		print_r($result);
		die();*/
		
		//for api
		/*if($result['status'] == 1) {
			if($result1->rowCount() <= 0) {
				drupal_goto('rhewise_occupant_data_entry/'.encrypt_url($flat_id).'/'.encrypt_url($hrms_id));
			} else {
				drupal_set_message('HRMS ID. already inserted.', 'error');	
				$form_state['rebuild'] = TRUE;
			}
		} elseif($result['status'] == 0) {
			$form_state['rebuild'] = TRUE;
			drupal_set_message('Invalid HRMS ID.', 'error');	
		}*/
		
		//for hrms local table
		/*if($result->rowCount() > 0) {
			if($result1->rowCount() <= 0) {
				drupal_goto('rhewise_occupant_data_entry/'.encrypt_url($flat_id).'/'.encrypt_url($hrms_id));
			} else {
				drupal_set_message('HRMS ID. already inserted.', 'error');	
				$form_state['rebuild'] = TRUE;
			}
		} else {
			$form_state['rebuild'] = TRUE;
			drupal_set_message('Invalid HRMS ID.', 'error');	
		}*/
		
		drupal_goto('rhewise_occupant_data_entry/'.encrypt_url($flat_id));
	}
	
	function _reload_rhewise_flat_type($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_type_replace", drupal_render($form['flat_type']));
		$commands[] = ajax_command_replace("#block_name_replace", drupal_render($form['block_name']));
		$commands[] = ajax_command_replace("#flat_no_replace", drupal_render($form['flat_no']));
		
		$commands[] = ajax_command_replace("#hrms_id_replace", drupal_render($form['hrms_id']));
		$commands[] = ajax_command_replace("#submit_button_replace", drupal_render($form['submit_button']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_blocklist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#block_name_replace", drupal_render($form['block_name']));
		$commands[] = ajax_command_replace("#flat_no_replace", drupal_render($form['flat_no']));
		
		$commands[] = ajax_command_replace("#hrms_id_replace", drupal_render($form['hrms_id']));
		$commands[] = ajax_command_replace("#submit_button_replace", drupal_render($form['submit_button']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_flatlist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_no_replace", drupal_render($form['flat_no']));
		
		$commands[] = ajax_command_replace("#hrms_id_replace", drupal_render($form['hrms_id']));
		$commands[] = ajax_command_replace("#submit_button_replace", drupal_render($form['submit_button']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_occupant_entry($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#hrms_id_replace", drupal_render($form['hrms_id']));
		$commands[] = ajax_command_replace("#submit_button_replace", drupal_render($form['submit_button']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}