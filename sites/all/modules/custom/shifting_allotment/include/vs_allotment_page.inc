<?php

	function vs_allotment_form($form, &$form_state) {
		$rhe_name =  !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : '';
		
		$form['rhe_name'] = array(
			'#title' => t('Select RHE Name'),
			'#type' => 'select',
			'#options' => rhe_name_vs(),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				//'wrapper' => 'no_of_vacancy',
				'callback' => '_reload_no_of_vacancy_vs',
				'method' => 'replace',
			),
	  	);
	  
	  
	   $form['vs_allotment'] = array(
		'#type' => 'submit',
		'#value' => 'Click For Vertical Shifting Allotment',
		'#prefix' => '<div class="two" style="margin-top:43px;height: 30px;">',
 		'#suffix' => '</div>',
	  );
	  
	  $form['#attributes'] = array('onsubmit' => 'return validate_shifting_allotment_form()');
	  
	  //no of vacancy
	$form['no_of_vacancy'] = array(
		'#default_value' => '',
		'#prefix' => '<div class="one" id="no_of_vacancy">',
 		'#suffix' => '</div>',
	  );
	if($rhe_name != '')	 {
		$form['no_of_vacancy'] = array(
		'#prefix' => '<div class="one" id="no_of_vacancy">Total no of Vacancy : '.get_no_of_vacancy_vs($rhe_name),
		'#suffix' => '</div>',
		);
	}
	
	//no of applicant
  	$form['no_of_applicant'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant">',
 		'#suffix' => '</div>',
	);
   	  
	if($rhe_name != '')	 {
		$form['no_of_applicant'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant">Total no of Applicant : '.get_no_of_applicant_vs($rhe_name),
 		'#suffix' => '</div>',
	  	);
	}
	
	//vacancy details
	/*$form['vacancy_details'] = array(
		'#prefix' => '<div class="two" id="vacancy_details">',
 		'#suffix' => '</div>',
	  );
	  
	  
	 if($rhe_name != '') {
		 $vacancy_details = array();
		 $no_of_vacancy = get_no_of_vacancy_vs($rhe_name);
		 $vacancy_details = get_vacancy_details_vs($rhe_name, $no_of_vacancy);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Flat ID</b></td>';
		 $output .= '<td><b>Flat Type</b></td>';
		 foreach($vacancy_details as $val) {
			  $output .= '<tr>';
			  $output .= '<td>'.$val['flat_id'].'</td>';
			  if($val['flat_type_id'] == 1) {
				  $output .= '<td>A</td>';  
			  }
			  else if($val['flat_type_id'] == 2) {
				  $output .= '<td>B</td>';  
			  }
			  else if($val['flat_type_id'] == 3) {
				  $output .= '<td>C</td>';  
			  }
			  else if($val['flat_type_id'] == 4) {
				  $output .= '<td>D</td>';  
			  }
			  else if($val['flat_type_id'] == 5) {
				  $output .= '<td>A+</td>';  
			  }
			  $output .= '</tr>';
		 }
		 $output .= '</tr>';
		 $output .= '</table>';
		 
		 
		 
		$form['vacancy_details'] = array(
		'#prefix' => '<div class="two" id="vacancy_details">Vacancy Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}*/
	
	//applicant details
	/*$form['applicant_details'] = array(
		'#prefix' => '<div class="two" id="applicant_details">',
 		'#suffix' => '</div>',
	  );
	  
	  if($rhe_name != '')	 {
		 $applicant_details = array();
		 //$no_of_vacancy = get_no_of_vacancy($allotment_type);
		 $applicant_details = get_applicant_details_vs($rhe_name);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Online Application ID</b></td>';
		 $output .= '<td><b>Flat Type</b></td>';
		 foreach($applicant_details as $val) {
			  $output .= '<tr>';
			  $output .= '<td>'.$val['online_application_id'].'</td>';
			  if($val['flat_type_id'] == 1) {
				  $output .= '<td>A</td>';  
			  }
			  else if($val['flat_type_id'] == 2) {
				  $output .= '<td>B</td>';  
			  }
			  else if($val['flat_type_id'] == 3) {
				  $output .= '<td>C</td>';  
			  }
			  else if($val['flat_type_id'] == 4) {
				  $output .= '<td>D</td>';  
			  }
			  else if($val['flat_type_id'] == 5) {
				  $output .= '<td>A+</td>';  
			  }
			  $output .= '</tr>';
		 }
		 $output .= '</tr>';
		 $output .= '</table>';
		 
		 
		 
		$form['applicant_details'] = array(
		'#prefix' => '<div class="two" id="applicant_details">Applicant Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}*/
	
		return $form;
		
	}
	
	function vs_allotment_form_submit($form, &$form_state) {
		$rhe_name = $form_state['values']['rhe_name'];
		 $no_of_vacancy = get_no_of_vacancy_vs($rhe_name);
		 
		 $no_of_applicant = get_no_of_applicant_vs($rhe_name);
		 
		 if($no_of_vacancy > 0 && $no_of_applicant > 0) {
			//
			$vacancy_details = get_vacancy_details_vs($rhe_name, $no_of_vacancy);  
			update_allotment_details_vs($rhe_name, $no_of_vacancy);
			
			drupal_set_message('Successfully done allotment');
			$form_state['rebuild'] = TRUE; 
		 }
		  else {
			drupal_set_message('No. of vacancy or No. of Applicant or both are Zero, Allotment not possible!!!', 'error');
			$form_state['rebuild'] = TRUE;	 
		 }
	}
	
	
	function _reload_no_of_vacancy_vs($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#no_of_vacancy", drupal_render($form['no_of_vacancy']));
		$commands[] = ajax_command_replace("#no_of_applicant", drupal_render($form['no_of_applicant']));
		$commands[] = ajax_command_replace("#vacancy_details", drupal_render($form['vacancy_details']));
		$commands[] = ajax_command_replace("#applicant_details", drupal_render($form['applicant_details']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}

	function get_no_of_vacancy_vs($rhe_name = '') {
		$no_of_vacancy = 0;
		$floor = array('F', 'S');
		$query = db_select('housing_flat', 'hf')
		->fields('hf')
		->condition('estate_id', $rhe_name)
		->condition('floor', $floor, 'IN')
		->condition('flat_category_id', 3)
		->condition('flat_status_id', 1);
		$no_of_vacancy = $query->execute()->rowCount();
		
		return $no_of_vacancy;
		
	}
	function get_no_of_applicant_vs($rhe_name = '') {
		$no_of_applicant = 0;
		
		$query = db_select('housing_online_application', 'hoa');
		$query->innerJoin('housing_vs_application', 'hva', 'hva.online_application_id = hoa.online_application_id');
		$query->fields('hoa');
		$query->fields('hva');
		$query->condition('hoa.status', 'verified');
		$query->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'VS'));
		$query->condition('hva.occupation_estate', $rhe_name);
		
		$no_of_applicant = $query->execute()->rowCount();
		
		return $no_of_applicant;
		
	}
	
	function rhe_name_vs() {
		$floor = array('F', 'S');
		$rhe_name_options = array(''=>'- Select -');
		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query->fields('hf');
		$query->fields('he');
		$query->condition('floor', $floor, 'IN');
		$query->condition('flat_status_id', 1);
		$query->condition('flat_category_id', 3);
		$query->orderBy('flat_id', 'ASC');
		$result = $query->execute();
		foreach($result as $val) {
			$rhe_name_options[$val->estate_id] = $val->estate_name;
		}
	
		return $rhe_name_options;
	}
	
	function get_vacancy_details_vs($rhe_name = '', $no_of_vacancy = '') {
		$vacancy_details = array();

		$floor = array('F', 'S');
		$query_for_flat_vacancy = db_select('housing_flat', 'hf')
		->fields('hf')
		->condition('estate_id', $rhe_name)
		->condition('floor', $floor, 'IN')
		->condition('flat_status_id', 1)
		->condition('flat_category_id', 3)
		->orderBy('flat_id', 'ASC')
		->orderBy('floor', 'ASC');
		$result_for_flat_vacancy = $query_for_flat_vacancy->execute();
		while($data_flat_vacancy = $result_for_flat_vacancy->fetchObject()){
			$flat_vacancy[] = $data_flat_vacancy->flat_id;
			$flat_type[] = $data_flat_vacancy->flat_type_id;
		}
	
		for($i=0; $i<$no_of_vacancy; $i++) {
			$vacancy_details[] = array(
			'flat_id' => $flat_vacancy[$i], 
			'flat_type_id' => $flat_type[$i], 
			);		
		}
	
		return $vacancy_details;
	}
	
	function get_applicant_details_vs($rhe_name = '') {
		$applicant_details = array();
		
		
		$query = db_select('housing_online_application', 'hoa');
		$query->innerJoin('housing_applicant_official_detail', 'haod', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
		$query->innerJoin('housing_pay_band', 'hpb', 'hpb.pay_band_id = haod.pay_band_id');
		$query->innerJoin('housing_vs_application', 'hva', 'hva.online_application_id = hoa.online_application_id');
		$query->fields('hoa', array('online_application_id'));
		$query->fields('haod');
		$query->fields('hpb', array('flat_type_id'));
		$query->fields('hva');
		$query->condition('hoa.status', 'verified');
		$query->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'VS'));
		$query->condition('hva.occupation_estate', $rhe_name);
		$query->orderBy('hoa.online_application_id', 'ASC');
		
		$result = $query->execute();
		while($data = $result->fetchObject()){
			$applicant_details[] = array(
			'online_application_id' => $data->online_application_id, 'flat_type_id' => $data->flat_type_id,
			);
		}
		
		return $applicant_details;
	
	
	}
	
	
	function update_allotment_details_vs($rhe_name = '', $no_of_vacancy = '') {
		
		$allotment_process_result = db_query("select * from {housing_allotment_process} 
												where allotment_process_type = :allotment_process_type", 
												array(':allotment_process_type' => 'VSAL'));
		$no_of_rows = $allotment_process_result->rowCount();
		if($no_of_rows <= 0) {
			//$x = 1;
			$allotment_process_no = 'VSAL-01';
			$allotment_process_arr = array();
			$allotment_process_arr['allotment_process_no'] = $allotment_process_no;
			$allotment_process_arr['allotment_process_type']  = 'VSAL';
	
			db_insert('housing_allotment_process')
			->fields($allotment_process_arr)
			->execute();
		}
		else {
			$result_process_no = db_query("select max(substr(allotment_process_no, 6)) as allotment_process_no 
											from {housing_allotment_process} 
											where allotment_process_type = :allotment_process_type", 
											array(':allotment_process_type' => 'VSAL'));
			$data_process_no = $result_process_no->fetchObject();
			$x = $data_process_no->allotment_process_no;
			if($x < 9) {
				$x = $x + 1;
				$allotment_process_no = $x;
				$allotment_process_no = 'VSAL-0'.$allotment_process_no;
			}
			else {
				$x = $x + 1;
				$allotment_process_no = $x;
				$allotment_process_no = 'VSAL-'.$allotment_process_no;
			}
			
			$allotment_process_arr = array();
			$allotment_process_arr['allotment_process_no'] = $allotment_process_no;
			$allotment_process_arr['allotment_process_type']  = 'VSAL';
	
			db_insert('housing_allotment_process')
			->fields($allotment_process_arr)
			->execute();
		}
		
		$allotment_details = array();
		$vacancy_details = get_vacancy_details_vs($rhe_name, $no_of_vacancy);
		
		
		for($i=0; $i<sizeof($vacancy_details); $i++) {
			
			$flat_id = $vacancy_details[$i]['flat_id'];
			$flat_type = $vacancy_details[$i]['flat_type_id'];
			$result = db_query("select hoa.online_application_id, hpb.flat_type_id, hva.occupation_estate, hva.occupation_flat from {housing_online_application} as hoa
			inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
			inner join {housing_pay_band} as hpb on hpb.pay_band_id = haod.pay_band_id
			inner join {housing_vs_application} as hva on hva.online_application_id = hoa.online_application_id
			where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hva.occupation_estate = :occupation_estate and hpb.flat_type_id = :flat_type_id
			order by hoa.online_application_id limit 1", 
			array(':status' => 'verified', ':app_no' => 'VS', ':occupation_estate' => $rhe_name, ':flat_type_id' => $flat_type));
		
			$data = $result->fetchObject();
		
			if($result->rowCount() > 0) {
				
				//$counter = $vacancy_details[$i]['counter'];
				$allotment_upd_arr = array();
				$allotment_upd_arr['status']  = 'allotted';
				$allotment_upd_arr['online_application_id']  = $data->online_application_id;
			
				db_update('housing_online_application')
				->fields($allotment_upd_arr)
				->condition('online_application_id', $allotment_upd_arr['online_application_id'])
				->execute();
				
				db_update('housing_flat')
				->fields(array(
							'flat_status_id' => 2
						))
				->condition('flat_id', $flat_id)
				->execute();
				
				db_update('housing_flat')
				->fields(array(
							'flat_status_id' => 1
						))
				->condition('flat_id', $data->occupation_flat)
				->execute();	
			
				//db_query('update housing_flat set flat_status_id = 2 where flat_id = '.$flat_id);
				
				//db_query('update housing_flat set flat_status_id = 1 where flat_id = '.$data->occupation_flat);
				
				$allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no 
													from {housing_allotment_process} 
													where allotment_process_type = :allotment_process_type", 
													array(':allotment_process_type' => 'VSAL'));
				$data_process_no = $allotment_process_no->fetchObject();
				
				$allotment_ins_arr = array();
				$allotment_ins_arr['online_application_id']  = $data->online_application_id;
				$allotment_ins_arr['flat_id']  = $flat_id;
				$allotment_ins_arr['allotment_no'] = 'VSAL-'.$data->online_application_id.'-'.date("dmY");
				$allotment_ins_arr['allotment_process_no'] = $data_process_no->allotment_process_no;
			
				db_insert('housing_flat_occupant')
				->fields($allotment_ins_arr)
				->execute();
		
			//code for allottee email list array for email send
		
				$query_sendmail = db_select('users', 'u');
				$query_sendmail->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
				$query_sendmail->innerJoin('housing_online_application', 'hoa', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
				$query_sendmail->fields('u', array('mail'));
				$query_sendmail->condition('hoa.online_application_id', $data->online_application_id, '=');
				$result_sendmail = $query_sendmail->execute();
				$data_sendmail = $result_sendmail->fetchObject();
				
				$receiver_email_arr[] = $data_sendmail->mail;
				
			//echo 'alloted'.'<br />';
			
			} 
			else {
		
			//echo 'vacant'.'<br />';
			
			}
			
			
		}
		
	//code for email send to all allottee
	
		$receiver_email_list[] = $receiver_email_arr;
		$email_subject = 'Offer of Allotment';
		$message = '<html><body>Dear Applicant,<br><br>		
		A flat has been allotted for you. Kindy login to your account and accept the Offer of Allotment with in one month from the Date of Allotment to avoid the cancellation of flat allotment.
		<br><br>			
		Regards,<br>
		Housing Department<br>
		Government of West Bengal
		</html></body>';
				
		sendmail_allotment($receiver_email_list, $email_subject, $message);
		
		return;
	}