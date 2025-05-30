<?php

	function rhewise_occupantlist_form($form, &$form_state) {
		/*$rhe_name =  isset($form_state['values']['rhe_name']) && !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : isset($_SESSION['rhe_name']) && !empty($_SESSION['rhe_name']) ? $_SESSION['rhe_name'] : 0;
		
		$flat_type =  isset($form_state['values']['flat_type']) && !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : isset($_SESSION['flat_type']) && !empty($_SESSION['flat_type']) ? $_SESSION['flat_type'] : 0;*/
		
		$rhe_name =  !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : 0;
		$flat_type =  !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : 0;
		
		$form['rhe_name'] = array(
			'#title' => t('Name of the RHE'),
			'#type' => 'select',
			'#options' => rhe_list(),
			'#required' => TRUE,
			//'#weight' => 1,
			'#prefix' => '<div>',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				//'wrapper' => 'no_of_vacancy',
				'callback' => '_reload_rhewise_flat_type',
				'method' => 'replace',
			),
			'#select2' => array(
				'width' => '150',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)
		);
		
		$form['flat_type'] = array(
			'#title' => t('Flat Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			//'#weight' => 2,
			'#prefix' => '<div class="two" id="flat_type_replace">',
			'#suffix' => '</div>',
			//'#attributes' => array('class' => array('dropdown3')),
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_occupantlist',
				'method' => 'replace',
			),
		);
			
		if($rhe_name != 0) {
			$form['flat_type'] = array(
				'#title' => t('Flat Type'),
				'#type' => 'select',
				'#options' => flat_type_under_rhe($rhe_name),
				'#required' => TRUE,
				//'#weight' => 2,
				'#prefix' => '<div class="two" id="flat_type_replace">',
				'#suffix' => '</div>',
				//'#attributes' => array('class' => array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_occupantlist',
					'method' => 'replace',
				),
			);
		}
		
		$form['submit'] = array(
			//'#weight' => 3,
			'#prefix' => '<div id="submit_occupantlist">',
			'#suffix' => '</div>',
  		);
		
		if($rhe_name != 0 && $flat_type != 0) {
			$form['submit'] = array(
				'#type' => 'submit',
				'#value' => t('Check for Pending Approval of Occupants'),
				//'#weight' => 3,
				'#prefix' => '<div class="two-one" id="submit_occupantlist">',
				'#suffix' => '</div>',
			);
			
			
	  		$output = pending_occupant_list_page($rhe_name, $flat_type);
			if(!empty($output)) {
				$form['submit_approve'] = array(
				'#type' => 'submit',
				'#value' => t('Click to Approve Occupants'),
				//'#validate' => array('occupant_list_validate'),
				'#submit' => array('occupant_list_approve'),
				'#prefix' => '<div class="two" style="height: 50%">',
				'#suffix' => '</div>',
				);
				$form['submit_reject'] = array(
					'#type' => 'submit',
					'#value' => t('Click to Reject Occupants'),
					//'#submit' => array('occupant_list_reject'),
					'#prefix' => '<div class="two" style="height: 50%">',
					'#suffix' => '</div>',
				);
				$form['breadcrumb'] = array(
					'#type' => 'markup',
					'#markup' => $output,
					//'#weight' => 4,
					'#prefix' => '<div id="bdcb">',
					'#suffix' => '</div>',
				);
			}
		}
		
		return $form;	
	}
	
	function rhewise_occupantlist_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
		if($form_state['values']['rhe_name'] == '') {
			form_set_error('rhe_name', t('Please select RHE.'));	
		}
		if($form_state['values']['flat_type'] == '') {
			form_set_error('flat_type', t('Please select Flat Type.'));	
		}
		
		$all_occupant = $form_state['values']['occupant_info'];
		$error = 0;
		foreach($all_occupant as $occupant_uid => $selected_occupant) {
			if($selected_occupant <= 0) {
				$error = 1;	
			}
		}
		if($error == 1) {
			form_set_error($selected_occupant, t('No occupant are selected for approve or reject!!!'));	
		}
	}
	
	function rhewise_occupantlist_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;	
	}
	function occupant_list_approve($form, &$form_state) {
		$all_occupant = $form_state['values']['occupant_info'];
	
		foreach($all_occupant as $occupant_uid => $selected_occupant) {
			if($selected_occupant != 0) {
				db_update('users')
				->fields(array(
					'status' => 1,
					)
				)
				->condition('uid', $occupant_uid, '=')
				->execute();
			}
		}
		drupal_set_message(t('Occupants are successfully approved.'));	
	}
	function pending_occupant_list_page($rhe_name = '', $flat_type = '') {
		$output = drupal_get_form('occupant_list_update', $rhe_name, $flat_type);
		return drupal_render($output);
	}
	
	function occupant_list_update($form, &$form_state, $rhe_name, $flat_type) {
		$result = rhe_flattype_wise_occupantlist_for_update($rhe_name, $flat_type);
		
		$header = array();
		
		$header = array(
			'sl_no' => array('data' => 'Sl. No.'),
			'district_name'	=> array('data' => 'District'),
			'block_name' => array('data' => 'Block'),
			'floor' => array('data' => 'Floor'),
			'flat_no' => array('data' => 'Flat No'),
			'applicant_name' => array('data' => 'Occupant Name'),
			'applicant_designation' => array('data' => 'Designation'),
		);
		
		$i = 1;
		
		/*$form['submit_approve'] = array(
			'#type' => 'submit',
			'#value' => t('Click to Approve Occupants'),
			//'#validate' => array('occupant_list_validate'),
			//'#submit' => array('occupant_list_approve'),
			'#prefix' => '<div class="two" style="height: 50%">',
			'#suffix' => '</div>',
		);*/
		
		/*$form['submit_reject'] = array(
			'#type' => 'submit',
			'#value' => t('Click to Reject Occupants'),
			'#submit' => array('occupant_list_reject'),
			'#prefix' => '<div class="two" style="height: 50%">',
			'#suffix' => '</div>',
		);*/
		
		$options = array();
		//$destination = drupal_get_destination();

		foreach($result as $record) {
			if($record->floor == 'G')
				$floor = 'Ground';
			else if($record->floor == 'F')
				$floor = 'Ground';
			else if($record->floor == 'S')
				$floor = 'Ground';
			else if($record->floor == 'T')
				$floor = 'Ground';
			else if($record->floor == '')
				$floor = 'Ground';
			$options[$record->uid] = array(
				'sl_no' => $i,
				'district_name' => $record->district_name,
				'block_name' => $record->block_name.' Block',
				'floor' => $floor,
				'flat_no' => $record->flat_no,
				'applicant_name' => $record->applicant_name,
				'applicant_designation' => $record->applicant_designation,
			);
			$i++;
		}
	
		$form['occupant_info'] = array(
			'#type' => 'tableselect',
			'#header' => $header,
			'#options' => $options,
			'#empty' => t('No occupant available.'),
		);
	
		$form['pager'] = array(
			'#markup' => theme('pager'),
		);
	
		return $form;	
	}
	
	function occupant_list_reject($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
		$all_occupant = $form_state['values']['occupant_info'];
	
		foreach($all_occupant as $occupant_uid => $selected_occupant) {
			if($selected_occupant != 0) {
				db_delete('users')
				->condition('uid',$occupant_uid, '=')
				->execute();
				
				db_delete('users_roles')
				->condition('uid',$occupant_uid, '=')
				->execute();
			}
		}
		drupal_set_message(t('Occupants are successfully rejected.'));
	}
	
	function _reload_rhewise_flat_type($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_type_replace", drupal_render($form['flat_type']));
		$commands[] = ajax_command_replace("#submit_occupantlist", drupal_render($form['submit']));
		$commands[] = ajax_command_replace("#bdcb", drupal_render($form['breadcrumb']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_occupantlist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#submit_occupantlist", drupal_render($form['submit']));
		$commands[] = ajax_command_replace("#bdcb", drupal_render($form['breadcrumb']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
		