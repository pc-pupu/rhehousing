<?php

	function allotment_list_approve_form($form, &$form_state) {
	
		$allotment_process_date =  isset($form_state['values']['allotment_process_date']) && !empty($form_state['values']['allotment_process_date']) ? $form_state['values']['allotment_process_date'] : '';
		
		$allotment_process_no =  isset($form_state['values']['allotment_process_no']) && !empty($form_state['values']['allotment_process_no']) ? $form_state['values']['allotment_process_no'] : '';
		
		$allotment_process_type =  isset($form_state['values']['allotment_process_type']) && !empty($form_state['values']['allotment_process_type']) ? $form_state['values']['allotment_process_type'] : '';
		

		
		$form['allotment_process_date'] = array(
			'#title' => t('Allotment Process Date'),
			'#type' => 'select',
			'#options' => allotment_process_date(),
			'#required' => TRUE,
			//'#attributes' => array('class' => array('dropdown3')),//sd 24-06-2024 turned off
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_process_no',
					   'method' => 'replace',
			),
			//'#prefix' => '<div class="three">',//sd 24-06-2024 turned off
			//'#suffix' => '</div>',//sd 24-06-2024 turned off
			'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
			'#prefix' => '<div class="row"><div class="col-md-4"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div>',//sd 24-06-2024
			'#default_value' => $allotment_process_date,
	  	);
		
		
		$form['allotment_process_no'] = array(
			/*'#title' => t('Allotment Process No.'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_process_type',
					   'method' => 'replace',
			),*/
			//'#prefix' => '<div class="three" id="allotment_process_no_replace">', //sd 24-06-2024 turned off
			//'#suffix' => '</div>', //sd 24-06-2024 turned off
			'#attributes' => array('class' => array('form-select')),//sd 24-06-2024 turned off
			'#prefix' => '<div class="col-md-4" id="allotment_process_no_replace"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div>',//sd 24-06-2024

			//'#default_value' => $allotment_process_no,
		);		

		
		if($allotment_process_date != '') {
			$form['allotment_process_no'] = array(
				'#title' => t('Allotment Process No.'),
				'#type' => 'select',
				'#options' => allotment_process_no($allotment_process_date),
				'#required' => TRUE,
				'#attributes' => array('class' => array('dropdown3')),
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_allotment_process_type',
						   'method' => 'replace',
				),
				//'#prefix' => '<div class="three" id="allotment_process_no_replace">', //sd 24-06-2024 turned off
				//'#suffix' => '</div>', //sd 24-06-2024 turned off
				'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
				'#prefix' => '<div class="col-md-4" id="allotment_process_no_replace"><div class="form-floating">',//sd 24-06-2024
				'#suffix' => '</div></div>',//sd 24-06-2024

				'#default_value' => $allotment_process_no,
			);
		}
		
		$form['allotment_process_type'] = array(
			/*'#title' => t('Allotment Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_list',
					   'method' => 'replace',
			),*/
			//'#prefix' => '<div class="three" id="allotment_process_type_replace">', //sd 24-06-2024  turned off
			//'#suffix' => '</div>', //sd 24-06-2024  turned off
			'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
			'#prefix' => '<div class="col-md-4" id="allotment_process_type_replace"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div></div>',//sd 24-06-2024

			//'#default_value' => $allotment_process_type,
		);		

		
		if($allotment_process_date != '' && $allotment_process_no != '') {
			$form['allotment_process_type'] = array(
				'#title' => t('Allotment Process Type'),
				'#type' => 'select',
				'#options' => array('' => 'Select Allotment Process Type', 'NAL' => 'New Allotment', 'VSAL' => 'Floor Shifting', 'CSAL' => 'Category Shifting'),
				'#required' => TRUE,
				//'#attributes' => array('class' => array('dropdown3')),//sd 24-06-2024 turned off
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_allottee_list',
						   'method' => 'replace',
				),
				'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
				'#prefix' => '<div class="col-md-4" id="allotment_process_type_replace"><div class="form-floating">',//sd 24-06-2024
				'#suffix' => '</div></div></div>',//sd 24-06-2024
				'#default_value' => $allotment_process_type,
			);
		}
		
		$form['submit_approve'] = array(
			'#prefix' => '<div id="submit_approve_allotteelist">',
			'#suffix' => '</div>',
  		);
		$form['submit_reject'] = array(
			'#prefix' => '<div id="submit_reject_allotteelist">',
			'#suffix' => '</div>',
  		);
		$form['allottee_info'] = array(
			'#prefix' => '<div id="allottee_info">',
			'#suffix' => '</div>',
		);
		
		
		if($allotment_process_date != '' && $allotment_process_no != '' && $allotment_process_type != '') {
			$result = fetch_all_allottee_details_for_approve($allotment_process_date, $allotment_process_no, $allotment_process_type);
			
			//$header = array(); //sd 24-06-2024 turned off
			
			if($allotment_process_type == 'NAL') {
				$header = array(
					'sl_no' => array('data' => 'Sl. No.'),
					'name_desig' => array('data' => 'Name and Designation'),
					'app_no_posting_doa' => array('data' => '1. Application No.<br>2. Place of Posting<br>3. Date of Application'),
					'flat_allotted' => array('data' => 'Flat Allotted'),
					'floor' => array('data' => 'Floor'),
					'rhe_name' => array('data' => 'Name of R.H.E.'),
					'dor' => array('data' => 'Date of Retirement'),
					'remarks' => array('data' => 'Remarks'),
				);
			} else if($allotment_process_type == 'VSAL' || $allotment_process_type == 'CSAL') {
				$header = array(
					'sl_no' => array('data' => 'Sl. No.'),
					'applicant_name' => array('data' => 'Name'),
					'dop_doa_dor' => array('data' => '1. Date of Possession<br>2. Date of Application<br>3. Date of Retirement'),
					'flat_allotted' => array('data' => 'Allotted Flat No.'),
					'flat_type' => array('data' => 'Type of Flat'),
					'floor' => array('data' => 'Floor'),
					'from_flat_no' => array('data' => 'From Flat No.'),
					'to_flat_no' => array('data' => 'To Flat No.'),
					'remarks' => array('data' => 'Remarks'),
				);
			}
			
			$i = 1;
			$onclick="return confirm('Are you sure you want to Approve?')";
			$onclick1="return confirm('Are you sure you want to Reject?')";
			
			if($result->rowCount() > 0) {
				$form['submit_approve'] = array(
					'#type' => 'submit',
					'#value' => t('Click to Approve Allotment'),
					'#attributes' => array('onclick' => $onclick,'class'=>array('btn bg-success btn-sm px-5 rounded-pill text-white mb-4 fw-bolder')),// sd 24-06-2024
					//'#prefix' => '<div class="two-one" id="submit_approve_allotteelist" style="height: 50%">',// sd 24-06-2024 turned off
					//'#suffix' => '</div>',// sd 24-06-2024 turned off
					'#prefix' => '<div class="row"><div class="col-md-6 two-one" id="submit_approve_allotteelist">',
					'#suffix' => '</div>',
				);
				$form['submit_reject'] = array(
					'#type' => 'submit',
					'#value' => t('Click to Reject Allotment'),
					'#attributes' => array('onclick' => $onclick1,'class'=>array('btn bg-danger btn-sm px-5 rounded-pill text-white mb-4 fw-bolder')),// sd 24-06-2024
					'#submit' => array('allottee_list_reject'),
					//'#prefix' => '<div class="four" id="submit_reject_allotteelist" style="height: 50%">',// sd 24-06-2024 turned off
					//'#suffix' => '</div>',// sd 24-06-2024 turned off
					'#prefix' => '<div class="col-md-6" id="submit_reject_allotteelist">',
					'#suffix' => '</div></div>',
				);
			}
			
			$options = array();
			
			foreach($result as $record) {
				
				/*if(trim($record->floor) == 'F') {
					$floor = '1st';	
				} else if(trim($record->floor) == 'S') {
					$floor = '2nd';	
				} else {
					$floor = $record->floor;	
				}*/

				$floor = $record->floor; // sd 24-06-2024 
				
				if($record->allowed_for_floor_shifting != '' && $record->allowed_for_floor_shifting == 'N') {
					$allowed_for_fs = 'No Floor Shifting Henceforth';		
				} else {
					$allowed_for_fs = '';	
				}
				
				if($allotment_process_type == 'NAL') {
					if($record->roaster_vacancy_position != '') {
						if($record->roaster_vacancy_position == 1 || $record->roaster_vacancy_position == 21) {
							$remarks = $record->roaster_vacancy_position.'st Vacancy<br>'.$record->allotment_reason.'<br>'.$allowed_for_fs;	
						} else if($record->roaster_vacancy_position == 2 || $record->roaster_vacancy_position == 22) {
							$remarks = $record->roaster_vacancy_position.'nd Vacancy<br>'.$record->allotment_reason.'<br>'.$allowed_for_fs;	
						} else if($record->roaster_vacancy_position == 3 || $record->roaster_vacancy_position == 23) {
							$remarks = $record->roaster_vacancy_position.'rd Vacancy<br>'.$record->allotment_reason.'<br>'.$allowed_for_fs;	
						} else {
							$remarks = $record->roaster_vacancy_position.'th Vacancy<br>'.$record->allotment_reason.'<br>'.$allowed_for_fs;
						}
					} else {
						$remarks = $allowed_for_fs;		
					}
					
					$options[$record->online_application_id] = array(
						'sl_no' => $i,
						'name_desig' => $record->applicant_name.'<br>'.$record->applicant_designation,
						'app_no_posting_doa' => '1. '.$record->application_no.'<br>'.'2. '.$record->applicant_posting_place.'<br>'.'3. '.implode('/', array_reverse(explode('-', $record->date_of_application))),
						'flat_allotted' => $record->flat_no,
						'floor' => $floor,
						'rhe_name' => $record->estate_name,
						'dor' => implode('/', array_reverse(explode('-', $record->date_of_retirement))),
						'remarks' => $remarks,
					);
					
				} else if($allotment_process_type == 'VSAL' || $allotment_process_type == 'CSAL') {
					if($allotment_process_type == 'VSAL') {
						$occupied_flat = $record->occupied_flat_vs;
						$remarks = 'Floor Shifting';	
					} else if($allotment_process_type == 'VSAL' || $allotment_process_type == 'CSAL') {
						$occupied_flat = $record->occupied_flat_cs;
						$remarks = 'Category Shifting';	
					}
					
					$options[$record->online_application_id] = array(
						'sl_no' => $i,
						'applicant_name' => $record->applicant_name,
						'dop_doa_dor' => '1. '.implode('/', array_reverse(explode('-', $record->possession_date))).'<br>'.'2. '.implode('/', array_reverse(explode('-', $record->date_of_application))).'<br>'.'3. '.implode('/', array_reverse(explode('-', $record->date_of_retirement))),
						'flat_allotted' => $record->flat_no,
						'flat_type' => $record->flat_type,
						'floor' => $floor,
						'from_flat_no' => $occupied_flat,
						'to_flat_no' => $record->flat_no,
						'remarks' => $remarks,
					);	
					
				}
				
				$i++;
			}
		
			$form['allottee_info'] = array(
				'#type' => 'tableselect',
				'#header' => $header,
				'#options' => $options,
				'#empty' => t('No allottee available.'),
				'#prefix' => '<div id="allottee_info">',
				'#suffix' => '</div>',
				'#attributes'=>array('class'=>array('table table-list')),//sd 24-06-2024
			); 	
			
	  	}
		
		return $form;
	}
	
	function allotment_list_approve_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
		
		$i = 0;
		$all_allottee = $form_state['values']['allottee_info'];
		foreach($all_allottee as $allottee_app_id => $selected_allottee) {
			if($selected_allottee != 0) {
				$i = 1;	
			}
		}
		if($i == 0) {
			form_set_error($selected_allottee, t('No allottees are selected for allotment approve or reject!!!'));	
		}
	}
	
	function allotment_list_approve_form_submit($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
		
		$all_allottee = $form_state['values']['allottee_info'];
		
	
		foreach($all_allottee as $allottee_app_id => $selected_allottee) {
			if($selected_allottee != 0) {
				db_update('housing_online_application')
				->fields(array(
					//'status' => 'allotted_approved',// turned off sd 10-09-2024
					'status' => 'housing_official_approved',// added sd 10-09-2024
					'date_of_verified' => date('Y-m-d H:i:s')  // added by debaleena 25-11-2024
					)
				)
				->condition('online_application_id', $allottee_app_id, '=')
				->execute();

				//added sd 10-09-2024
				global $user;
				$process_flow_arr = array(
					'online_application_id' => $allottee_app_id,
					'status_id' => 9, // status_id of housing_official_approved // Updated by Subham 22/11/2024
					'created_at' => date('Y-m-d H:i:s'),
					'uid' => $user->uid,
					'short_code' =>'housing_official_approved'
				);
				db_insert('housing_process_flow')->fields($process_flow_arr)->execute();

				//end
				
				db_update('housing_flat_occupant')
				->fields(array(
					'allotment_approve_or_reject_date' => date('Y-m-d'),
					)
				)
				->condition('online_application_id', $allottee_app_id, '=')
				->execute();
				
			//code for allottee email list array for email send
				$query_sendmail = db_select('users', 'u');
				$query_sendmail->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
				$query_sendmail->innerJoin('housing_online_application', 'hoa', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
				$query_sendmail->fields('u', array('mail'));
				$query_sendmail->condition('hoa.online_application_id', $allottee_app_id, '=');
				$result_sendmail = $query_sendmail->execute();
				$data_sendmail = $result_sendmail->fetchObject();
				
				$receiver_email_arr[] = $data_sendmail->mail;
			}
		}
		
		//code for email send to approved allottee
		$receiver_email_list[] = $receiver_email_arr;
		$email_subject = 'Offer of Allotment';
		$message = '<html><body>Dear Applicant,<br><br>		
		A flat has been allotted to you. Please login to your account and accept the Offer of Allotment within 30 days from the date you receive this mail to avoid cancellation of the flat allotment.
		<br><br>			
		Regards,<br>
		Housing Department<br>
		Government of West Bengal
		</html></body>';
				
		//sendmail_allotment($receiver_email_list, $email_subject, $message); // turned of sd 10-09-2024
	
		drupal_set_message(t('Allotment of Allottees are Approved.'));
		
	}
	
	function allottee_list_reject($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
		// echo "lll";die;
		$all_allottee = $form_state['values']['allottee_info'];
		// /print_r($all_allottee);die;
		foreach($all_allottee as $allottee_app_id => $selected_allottee) {
			if($selected_allottee != 0) {
				
				db_update('housing_online_application')
				->fields(array(
					//'status' => 'allotted_rejected',// turned off sd 10-09-2024
					'status' => 'housing_official_reject',//added sd 10-09-2024
					)
				)
				->condition('online_application_id', $allottee_app_id, '=')
				->execute();
				
				db_update('housing_flat_occupant')
				->fields(array(
					// 'accept_reject_status' => 'Cancel',// turned off sd 10-09-2024
					//'accept_reject_status' => 'housing_official_reject',//added sd 10-09-2024
					'allotment_approve_or_reject_date' => date('Y-m-d'),
					)
				)
				->condition('online_application_id', $allottee_app_id, '=')
				->execute();
				
				$status_id = get_status_id('housing_official_reject');  //added by dg 16-12-2024


				//added sd 10-09-2024
				global $user;
				$process_flow_arr = array(
					'online_application_id' => $allottee_app_id,
					'status_id' => $status_id, // status_id of housing_official_reject
					'created_at' => date('Y-m-d H:i:s'),
					'uid' => $user->uid,
					'short_code' =>'housing_official_reject'
				);
				db_insert('housing_process_flow')->fields($process_flow_arr)->execute();

				//end
				
				

				$query = db_select('housing_applicant_official_detail','haod');
				$query->innerjoin('housing_online_application ', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
				$query->leftjoin('housing_flat_occupant ', 'hfo', 'hfo.online_application_id = hoa.online_application_id');
				$query->addField('haod', 'applicant_official_detail_id');
				$query->addField('hfo', 'flat_id');
				$query->condition('hoa.online_application_id', $allottee_app_id, '=');
				$result = $query->execute();
				$data = $result->fetchObject();
				// print_r($data);die;
				db_update('housing_applicant_official_detail')
					->fields(array(
						'is_active' => 0,
						)
					)
				->condition('applicant_official_detail_id',$data->applicant_official_detail_id, '=')
				->execute();
				
				db_update('housing_flat')
				->fields(array(
					'flat_status_id' => 1,
					)
				)
				->condition('flat_id', $data->flat_id, '=')
				->execute();
				
			}
		}
		// drupal_set_message(t('Occupants are successfully rejected.')); //10-09-2024
		drupal_set_message(t('Allotments are Cancelled.'));
	}
	
	function _reload_allotment_process_no($form, &$form_state) {
		$commands[] = ajax_command_replace('#allotment_process_no_replace', drupal_render($form['allotment_process_no']));
		$commands[] = ajax_command_replace('#allotment_process_type_replace', drupal_render($form['allotment_process_type']));
		$commands[] = ajax_command_replace("#submit_approve_allotteelist", drupal_render($form['submit_approve']));
		$commands[] = ajax_command_replace("#submit_reject_allotteelist", drupal_render($form['submit_reject']));
		$commands[] = ajax_command_replace("#allottee_info", drupal_render($form['allottee_info']));
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}
	
	function _reload_allotment_process_type($form, &$form_state) {
		$commands[] = ajax_command_replace('#allotment_process_type_replace', drupal_render($form['allotment_process_type']));
		$commands[] = ajax_command_replace("#submit_approve_allotteelist", drupal_render($form['submit_approve']));
		$commands[] = ajax_command_replace("#submit_reject_allotteelist", drupal_render($form['submit_reject']));
		$commands[] = ajax_command_replace("#allottee_info", drupal_render($form['allottee_info']));
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}
	
	function _reload_allottee_list($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#submit_approve_allotteelist", drupal_render($form['submit_approve']));
		$commands[] = ajax_command_replace("#submit_reject_allotteelist", drupal_render($form['submit_reject']));
		$commands[] = ajax_command_replace("#allottee_info", drupal_render($form['allottee_info']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}