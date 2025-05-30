<?php

	function rhewise_occupantlist_form($form, &$form_state) {
		$rhe_name =  !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : 0;
		$flat_type =  !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : 0;
		
		$form['rhe_name'] = array(
			'#title' => t('Name of the RHE'),
			'#type' => 'select',
			'#options' => rhe_list(),
			'#required' => TRUE,
			//'#weight' => -10,
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
			//'#weight' => -10,
			'#prefix' => '<div class="three" id="flat_type_replace">',
			'#suffix' => '</div>',
			'#attributes' => array('class'	=> array('dropdown3')),
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
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="flat_type_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_occupantlist',
					'method' => 'replace',
				),
			);
		}
		
		
		/*$form['rhewise_occupantlist'] = array(
			'#prefix' => '<div  id="rhewise_occupantlist">',
			'#suffix' => '</div>',
		);*/
		$form['submit'] = array(
			'#prefix' => '<div  id="submit_occupantlist">',
			'#suffix' => '</div>',
  		);
		$form['occupant_info'] = array(
			'#prefix' => '<div  id="occupant_info">',
			'#suffix' => '</div>',
		);
		$form['pager'] = array(
			'#prefix' => '<div  id="pager">',
			'#suffix' => '</div>',
		);
		
		if($rhe_name != 0 && $flat_type != 0) {
			
			/*$form['rhewise_occupantlist'] = array(
				'#type' => 'markup',
				'#markup' => rhewise_occupantlist_page($rhe_name, $flat_type),
				'#prefix' => '<div id="rhewise_occupantlist">',
				'#suffix' => '</div>',
			);*/
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
			
			$form['submit'] = array(
				'#type' => 'submit',
				'#value' => t('Click to Approve Occupants'),
				'#prefix' => '<div  id="submit_occupantlist">',
				'#suffix' => '</div>',
			);
			
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
				'#prefix' => '<div  id="occupant_info">',
				'#suffix' => '</div>',
			);
		
			$form['pager'] = array(
				'#markup' => theme('pager'),
				'#prefix' => '<div  id="pager">',
				'#suffix' => '</div>',
			);
		 
	  	}
		
		return $form;	
	}
	
	function rhewise_occupantlist_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
		$all_occupant = $form_state['values']['occupant_info'];
		$error = 0;
		foreach($all_occupant as $occupant_uid => $selected_occupant) {
			if($selected_occupant <= 0) {
				$error = 1;	
			}
		}
		if($error == 1) {
			form_set_error($selected_occupant, t('No occupant are selected for approve!!!'));	
		}
	}
	
	function rhewise_occupantlist_form_submit($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
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
	
	function _reload_rhewise_flat_type($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_type_replace", drupal_render($form['flat_type']));
		//$commands[] = ajax_command_replace("#rhewise_occupantlist", drupal_render($form['rhewise_occupantlist']));
		$commands[] = ajax_command_replace("#submit_occupantlist", drupal_render($form['submit']));
		$commands[] = ajax_command_replace("#occupant_info", drupal_render($form['occupant_info']));
		$commands[] = ajax_command_replace("#pager", drupal_render($form['pager']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_occupantlist($form, &$form_state) {
		$commands = array();
		//$commands[] = ajax_command_replace("#rhewise_occupantlist", drupal_render($form['rhewise_occupantlist']));
		$commands[] = ajax_command_replace("#submit_occupantlist", drupal_render($form['submit']));
		$commands[] = ajax_command_replace("#occupant_info", drupal_render($form['occupant_info']));
		$commands[] = ajax_command_replace("#pager", drupal_render($form['pager']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
		