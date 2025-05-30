<?php

	function rhewise_occupantlist_form($form, &$form_state) {
		global $base_path;
		//$rhe_name_default = isset($form['rhe_name']['#default_value']) && !empty($form['rhe_name']['#default_value']) ? $form['rhe_name']['#default_value'] : 0;
		//$flat_type_default = isset($form['flat_type']['#default_value']) && !empty($form['flat_type']['#default_value']) ? $form['flat_type']['#default_value'] : 0;
		
		$rhe_name = isset($form_state['values']['rhe_name']) && !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : 0;
		$flat_type = isset($form_state['values']['flat_type']) && !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : 0;
		
		$form['rhe_name'] = array(
			'#title' => t('Name of the RHE'),
			'#type' => 'select',
			'#options' => rhe_list_specific(),
			'#required' => TRUE,
			'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div>',//sd 24-06-2024
			'#ajax' => array(
				'event' => 'change',
				//'wrapper' => 'no_of_vacancy',
				'callback' => '_reload_rhewise_flat_type',
				'method' => 'replace',
			),
			// '#select2' => array(
			// 	//'width' => '500',// sd 24-06-2024 turned off
			// 	//'placeholder' => '- Select -',
			// 	'allowClear' => TRUE
        	// )
		);
		
		$form['flat_type'] = array(
			'#title' => t('Flat Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
			'#prefix' => '<div class="col-md-6" id="flat_type_replace"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div></div>',//sd 24-06-2024
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
				'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
				'#prefix' => '<div class="col-md-6" id="flat_type_replace"><div class="form-floating">',//sd 24-06-2024
				'#suffix' => '</div></div></div>',//sd 24-06-2024
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
		$form['submit_approve_start'] = array(
			'#type' => 'markup',
			'#markup' => '<div class="row">'
		);
		$form['submit_approve'] = array(
			'#prefix' => '<div  id="submit_approve_occupantlist">',
			'#suffix' => '</div>',
  		);
		$form['submit_reject'] = array(
			'#prefix' => '<div  id="submit_reject_occupantlist">',
			'#suffix' => '</div>',
  		);
		
		$form['submit_approve_end'] = array(
			'#type' => 'markup',
			'#markup' => '</div>'
		);
		$form['occupant_info'] = array(
			'#prefix' => '<div  id="occupant_info">',
			'#suffix' => '</div>',
		);
		/*$form['pager'] = array(
			'#prefix' => '<div  id="pager">',
			'#suffix' => '</div>',
		);*/
		
		if($rhe_name != 0 && $flat_type != 0) {
			
			/*$form['rhewise_occupantlist'] = array(
				'#type' => 'markup',
				'#markup' => rhewise_occupantlist_page($rhe_name, $flat_type),
				'#prefix' => '<div id="rhewise_occupantlist">',
				'#suffix' => '</div>',
			);*/
			$result = rhe_flattype_wise_occupantlist_for_update($rhe_name, $flat_type);
		
			//$header = array();// sd turned off 24-06-2024
			
			$header = array(
				'sl_no' => array('data' => 'Sl. No.'),
				'district_name'	=> array('data' => 'District'),
				'block_name' => array('data' => 'Block'),
				'floor' => array('data' => 'Floor'),
				'flat_no' => array('data' => 'Flat No'),
				'hrms_id' => array('data' => 'HRMS ID'),
				'applicant_name' => array('data' => 'Occupant Name'),
				'applicant_designation' => array('data' => 'Designation'),
				'view_details' => array('data' => 'View Details'),
			);
			
			$i = 1;
			$onclick="return confirm('Are you sure you want to Approve?')";
			$onclick1="return confirm('Are you sure you want to Reject?')";
			
			
			if($result->rowCount() > 0) {
				$form['submit_approve'] = array(
					'#type' => 'submit',
					'#value' => t('Click to Approve Occupants'),
					'#attributes' => array('onclick' => $onclick,'class'=>array('btn bg-success btn-sm px-5 rounded-pill text-white mb-4 fw-bolder')),// sd 24-06-2024 
					//'#prefix' => '<div class="two-one" id="submit_approve_occupantlist" style="height: 50%">',// sd 24-06-2024 turned off
					//'#suffix' => '</div>',// sd 24-06-2024 turned off
					'#prefix' => '<div class="col-md-6" id="submit_approve_occupantlist">',// sd 24-06-2024 
					'#suffix' => '</div></div>',// sd 24-06-2024 
				);
				$form['submit_reject'] = array(
					'#type' => 'submit',
					'#value' => t('Click to Reject Occupants'),
					'#attributes' => array('onclick' => $onclick1,'class'=>array('btn bg-danger btn-sm px-5 rounded-pill text-white mb-4 fw-bolder')),// sd 24-06-2024 
					'#submit' => array('occupant_list_reject'),
					//'#prefix' => '<div class="four" id="submit_reject_occupantlist" style="height: 50%">',// sd 24-06-2024 turned off
					//'#suffix' => '</div>',// sd 24-06-2024 turned off
					'#prefix' => '<div class="col-md-6" id="submit_reject_occupantlist">',// sd 24-06-2024 
					'#suffix' => '</div></div></div>',// sd 24-06-2024 
				);
			}
			
			
			$options = array();
			$src=$base_path.drupal_get_path('module', 'existing_occupant').'/images/view1.png';
			//$destination = drupal_get_destination();
	
			foreach($result as $record) {
				
				// if($record->floor == 'G')
				// 	$floor = 'Ground';
				// else if($record->floor == 'F')
				// 	$floor = 'First';
				// else if($record->floor == 'S')
				// 	$floor = 'Secend';
				// else if($record->floor == 'T')
				// 	$floor = 'Third';
				// else if($record->floor == '')
				// 	$floor = 'NIL';

				// added by moumita 05-06-2024

				$floor = $record->floor;
				$options[$record->uid] = array(
					'sl_no' => $i,
					'district_name' => $record->district_name,
					'block_name' => $record->block_name.' Block',
					'floor' => $floor,
					'flat_no' => $record->flat_no,
					'hrms_id' => $record->hrms_id,
					'applicant_name' => $record->applicant_name,
					'applicant_designation' => $record->applicant_designation,
					'view_details' => l(
							'View Details',
							'occupant_detail/'.encrypt_url($record->online_application_id), 
							array(
									'html'=>TRUE,
									'attributes'=> array('target' => '_blank', 'class' => array('btn bg-primary btn-sm px-5 rounded-pill text-white fw-bolder')),
							)
						)
				);
				$i++;
			}
		
			$form['occupant_info'] = array(
				'#type' => 'tableselect',
				'#header' => $header,
				'#options' => $options,
				'#attributes' => array('class' =>array('table table-list')),
				'#empty' => t('No occupant available.'),
				'#prefix' => '<div class="col-md-12"><div id="occupant_info" class="">',//sd 24-06-2024
				'#suffix' => '</div></div>'
			);
			
			/*$form['pager'] = array(
				'#markup' => theme('pager'),
				'#prefix' => '<div  id="pager">',
				'#suffix' => '</div>',
			);*/
		 
	  	}
		
		return $form;	
	}
	
	function rhewise_occupantlist_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
		
		$i = 0;
		$all_occupant = $form_state['values']['occupant_info'];
		foreach($all_occupant as $occupant_uid => $selected_occupant) {
			if($selected_occupant != 0) {
				$i = 1;	
			}
		}
		if($i == 0) {
			form_set_error($selected_occupant, t('No occupant are selected for approve or reject!!!'));	
		}
	}
	
	function rhewise_occupantlist_form_submit($form, &$form_state) {
		//echo "lll";die;
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
	
	function occupant_list_reject($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
		
		$all_occupant = $form_state['values']['occupant_info'];
	
		foreach($all_occupant as $occupant_uid => $selected_occupant) {
			if($selected_occupant != 0) {
				
				/*$query = db_select('users', 'u');
				$query->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
				$query->innerJoin('housing_online_application', 'hoa', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
				$query->innerJoin('housing_flat_occupant', 'hfo', 'hoa.online_application_id = hfo.online_application_id');
				$query->addField('hfo', 'flat_id');
				$query->condition('u.uid', $occupant_uid, '=');
				$result = $query->execute();
				$data = $result->fetchObject();
				
				db_update('housing_flat')
				->fields(array(
					'flat_status_id' => 1,
					)
				)
				->condition('flat_id', $data->flat_id, '=')
				->execute();*/
				
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
		$commands[] = ajax_command_replace("#submit_approve_occupantlist", drupal_render($form['submit_approve']));
		$commands[] = ajax_command_replace("#submit_reject_occupantlist", drupal_render($form['submit_reject']));
		$commands[] = ajax_command_replace("#occupant_info", drupal_render($form['occupant_info']));
		//$commands[] = ajax_command_replace("#pager", drupal_render($form['pager']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_occupantlist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#submit_approve_occupantlist", drupal_render($form['submit_approve']));
		$commands[] = ajax_command_replace("#submit_reject_occupantlist", drupal_render($form['submit_reject']));
		$commands[] = ajax_command_replace("#occupant_info", drupal_render($form['occupant_info']));
		//$commands[] = ajax_command_replace("#pager", drupal_render($form['pager']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
		