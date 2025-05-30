<?php

function rhe_allotment_form($form, &$form_state) {
	
	
	 $allotment_type =  !empty($form_state['values']['allotment_type']) ? $form_state['values']['allotment_type'] : '';
	
	 $form['allotment_type'] = array(
		'#title' => t('Select Allotment Type'),
		'#type' => 'select',
		'#options' => rhe_flat_type(),
		'#required' => TRUE,
		'#prefix' => '<div class="two">',
 		'#suffix' => '</div>',
		'#ajax' => array(
			'event' => 'change',
			//'wrapper' => 'no_of_vacancy',
			'callback' => '_reload_no_of_vacancy',
			'method' => 'replace',
	  	),
	  );
	  
	  
	   $form['allotment'] = array(
		'#type' => 'submit',
		'#value' => 'Click For Allotment',
		'#prefix' => '<div class="two" style="margin-top:43px;height: 30px;">',
 		'#suffix' => '</div>',
	  	);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_rhe_allotment_form()');
	
	//no of vacancy
	$form['no_of_vacancy'] = array(
		'#default_value' => '',
		'#prefix' => '<div class="one" id="no_of_vacancy">',
 		'#suffix' => '</div>',
	  );
	if($allotment_type != '')	 {
		$form['no_of_vacancy'] = array(
		'#prefix' => '<div class="one" id="no_of_vacancy">Total no of Vacancy : '.get_no_of_vacancy($allotment_type),
		'#suffix' => '</div>',
		);
	}
	
	//no of applicant
  	$form['no_of_applicant'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant">',
 		'#suffix' => '</div>',
	);
   	  
	if($allotment_type != '')	 {
		$form['no_of_applicant'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant">Total no of Applicant : '.get_no_of_applicant($allotment_type),
 		'#suffix' => '</div>',
	  	);
	}  
	
//vacancy details
	/*$form['vacancy_details'] = array(
		'#prefix' => '<div class="two" id="vacancy_details">',
 		'#suffix' => '</div>',
	  );
	  
	  
	 if($allotment_type != '')	 {
		 $vacancy_details = array();
		 $no_of_vacancy = get_no_of_vacancy($allotment_type);
		 $vacancy_details = get_vacancy_details($allotment_type, $no_of_vacancy);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Flat Type</b></td>';
		 $output .= '<td><b>Flat ID</b></td>';
		 $output .= '<td><b>Roaster Counter</b></td>';
		 $output .= '<td><b>Allotment Category</b></td>';
		 foreach($vacancy_details as $val) {
			  $output .= '<tr>';
			  if($val['allotment_type'] == 5) {
				  $output .= '<td>A+</td>';  
			  }
			  else if($val['allotment_type'] == 1) {
				  $output .= '<td>A</td>';  
			  }
			  else if($val['allotment_type'] == 2) {
				  $output .= '<td>B</td>';  
			  }
			  else if($val['allotment_type'] == 3) {
				  $output .= '<td>C</td>';  
			  }
			  else if($val['allotment_type'] == 4) {
				  $output .= '<td>D</td>';  
			  }
			  $output .= '<td>'.$val['flat_id'].'</td>';
			  $output .= '<td>'.$val['counter'].'</td>';
			  $output .= '<td>'.$val['allotment_category'].'</td>';
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
	  
	  if($allotment_type != '')	 {
		 $applicant_details = array();
		 //$no_of_vacancy = get_no_of_vacancy($allotment_type);
		 $applicant_details = get_applicant_details($allotment_type);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Online Application ID</b></td>';
		 $output .= '<td><b>Flat Type</b></td>';
		 $output .= '<td><b>Allotment Category</b></td>';
		 foreach($applicant_details as $val) {
			  $output .= '<tr>';
			  $output .= '<td>'.$val['online_application_id'].'</td>';
			  if($val['allotment_type'] == 5) {
				  $output .= '<td>A+</td>';  
			  }
			  else if($val['allotment_type'] == 1) {
				  $output .= '<td>A</td>';  
			  }
			  else if($val['allotment_type'] == 2) {
				  $output .= '<td>B</td>';  
			  }
			  else if($val['allotment_type'] == 3) {
				  $output .= '<td>C</td>';  
			  }
			  else if($val['allotment_type'] == 4) {
				  $output .= '<td>D</td>';  
			  }
			  $output .= '<td>'.$val['allotment_category'].'</td>';
			  $output .= '</tr>';
		 }
		 $output .= '</tr>';
		 $output .= '</table>';
		 
		 
		 
		$form['applicant_details'] = array(
		'#prefix' => '<div class="two" id="applicant_details">Applicant Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}*/
	
//	
	/*$form['allotment_details'] = array(
		'#prefix' => '<div class="one" id="allotment_details">',
 		'#suffix' => '</div>',
	  );
	  
	   if($allotment_type != '')	 {
		 $vacancy_details = get_vacancy_details($allotment_type, $no_of_vacancy);  
		 $allotment_details = array();
		 $allotment_details = get_allotment_details($allotment_type, $no_of_vacancy);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 foreach($allotment_details as $val) {
			  $output .= '<tr>';
			  $output .= '<td>'.$val['flat_id'].'</td>';
			  $output .= '<td>'.$val['online_application_id'].'</td>';
			  $output .= '</tr>';
		 }
		 $output .= '</table>';
		 
		 
		 
		$form['allotment_details'] = array(
		'#prefix' => '<div class="one" id="allotment_details" style="margin-top:250px;">Allotment Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}  */
	  

	  	
			
	 return $form;
}





function rhe_allotment_form_submit($form, &$form_state) {
	     
		 $allotment_type = $form_state['values']['allotment_type'];
		 $no_of_vacancy = get_no_of_vacancy($allotment_type);
		 
		 $no_of_applicant = get_no_of_applicant($allotment_type);
		 
		 if($no_of_vacancy > 0 && $no_of_applicant > 0) {
			 $vacancy_details = get_vacancy_details($allotment_type, $no_of_vacancy);  
			 update_allotment_details($allotment_type, $no_of_vacancy);
			 
			 switch($allotment_type) {
				 case '1' :
				 $allotment_type = 'A';
				 break;
				 
				 case '2' :
				 $allotment_type = 'B';
				 break;
				 
				 case '3' :
				 $allotment_type = 'C';
				 break;
				 
				 case '4' :
				 $allotment_type = 'D';
				 break;
				 
				 case '5' :
				 $allotment_type = 'A+';
				 break;
				 
				 default :
				 $allotment_type = '';
			 }
			 
			 drupal_set_message('Successfully alloted of type '.$allotment_type);
		
			 $form_state['rebuild'] = TRUE;
		 }
		 else {
			drupal_set_message('No. of vacancy or No. of Applicant or both are Zero, Allotment not possible!!!', 'error');
			$form_state['rebuild'] = TRUE;	 
		 }
}

function _reload_no_of_vacancy($form, &$form_state) {
    $commands = array();
    $commands[] = ajax_command_replace("#no_of_vacancy", drupal_render($form['no_of_vacancy']));
	$commands[] = ajax_command_replace("#no_of_applicant", drupal_render($form['no_of_applicant']));
	$commands[] = ajax_command_replace("#vacancy_details", drupal_render($form['vacancy_details']));
	$commands[] = ajax_command_replace("#applicant_details", drupal_render($form['applicant_details']));
    return array('#type' => 'ajax', '#commands' => $commands);
  
}

function get_no_of_vacancy($allotment_type = '') {
	$no_of_vacancy = 0;
	$floor = array('G', 'T');
	$query = db_select('housing_flat', 'hf')
	->fields('hf')
	->condition('flat_type_id', $allotment_type)
	->condition('floor', $floor, 'IN')
	->condition('flat_category_id', 1)
	->condition('flat_status_id', 1);
	$no_of_vacancy = $query->execute()->rowCount();
	
	return $no_of_vacancy;
	
}
function get_no_of_applicant($allotment_type = '') {
	$no_of_applicant = 0;
	
	$query = db_select('housing_online_application', 'hoa');
	$query->innerJoin('housing_new_allotment_application', 'hnaa', 'hnaa.online_application_id = hoa.online_application_id');
	$query->fields('hoa');
	$query->fields('hnaa');
	$db_and = db_and();
	$db_and->condition('hoa.status', 'verified');
	$db_and->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'NA'));
	$db_and->condition('hnaa.flat_type_id', $allotment_type);
	$query->condition($db_and);
	$no_of_applicant = $query->execute()->rowCount();
	
	return $no_of_applicant;
	
}


function get_vacancy_details($allotment_type = '', $no_of_vacancy = '') {
	$vacancy_details = array();
	/*$vacancy_details = array(
	
	'allotment_type' => $allotment_type, 'allotment_category' => 'General',
	'allotment_type' => $allotment_type, 'allotment_category' => 'Judicial',
	);*/
	
	
	$result_counter = db_query("select last_roaster_counter from {housing_allotment_roaster_counter} where allotment_type = :allotment_type and id = (select max(id) from {housing_allotment_roaster_counter} where allotment_type = :allotment_type1)", array(':allotment_type' => $allotment_type, ':allotment_type1' => $allotment_type));
	
	if($result_counter->rowCount() > 0) {
	$data_counter = $result_counter->fetchObject();
	$offset_val = $data_counter->last_roaster_counter;
	} else {	
	$offset_val = 0;
	}
	
	
	if($allotment_type == 1 || $allotment_type == 2 || $allotment_type == 5) {
	
	if(29 - $offset_val >= $no_of_vacancy) {
		$result = db_query("select * from {housing_roaster4ab_master} order by counter limit :no_of_vacancy offset :offset_val", array(':no_of_vacancy' => $no_of_vacancy, ':offset_val' => $offset_val)); 
	} 
	else {
		
		$no_from_1st_tab = 29 - $offset_val;
		$no_of_rest_vacancy = $no_of_vacancy - $no_from_1st_tab;
		$no_of_iteration = 0;
		if($no_of_rest_vacancy % 29 == 0)
			$no_of_iteration = $no_of_rest_vacancy / 29;
		else
			$no_of_iteration = ($no_of_rest_vacancy / 29) + 1;
		
		$rest_tab = '';
		for($i=1; $i<= $no_of_iteration; $i++) {
		$rest_tab .= " UNION ALL ";
		$rest_tab .= "(select * from {housing_roaster4ab_master})";
		}
		/*echo "(select * from housing_roaster4ab_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab;*/
		$result = db_query(" (select * from housing_roaster4ab_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab);
		
	}
	
	$allotment_category_arr = array();
	while($data = $result->fetchObject()){
		$roaster_counter_arr[] = $data->counter;
		$allotment_category_arr[] = $data->category;
	}
	
	
	}
	else if($allotment_type == 3 || $allotment_type == 4) {
	/*	$result = db_query("select * from housing_roaster4cd_master order by counter limit ".$no_of_vacancy." offset ".$offset_val);
	$allotment_category_arr = array();
	while($data = $result->fetchObject()){
		$allotment_category_arr[] = $data->category;
	}
	*/
	
	
	if(29 - $offset_val >= $no_of_vacancy) {
		$result = db_query("(select * from {housing_roaster4cd_master} order by counter limit :no_of_vacancy offset :offset_val)", array(':no_of_vacancy' => $no_of_vacancy, ':offset_val' => $offset_val)); 
	} 
	else {
		
		$no_from_1st_tab = 29 - $offset_val;
		$no_of_rest_vacancy = $no_of_vacancy - $no_from_1st_tab;
		$no_of_iteration = 0;
		if($no_of_rest_vacancy % 29 == 0)
			$no_of_iteration = $no_of_rest_vacancy / 29;
		else
			$no_of_iteration = ($no_of_rest_vacancy / 29) + 1;
		
		$rest_tab = '';
		for($i=1; $i<= $no_of_iteration; $i++) {
		$rest_tab .= " UNION ALL ";
		$rest_tab .= "(select * from {housing_roaster4cd_master})";
		}
		/*echo "(select * from housing_roaster4cd_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab;*/
		$result = db_query("(select * from housing_roaster4cd_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab);
		
	}
	
	$allotment_category_arr = array();
	while($data = $result->fetchObject()){
		$roaster_counter_arr[] = $data->counter;
		$allotment_category_arr[] = $data->category;
	}
	
	
	
	
	}

	$floor = array('G', 'T');
	$query_for_flat_vacancy = db_select('housing_flat', 'hf')
	->fields('hf')
	->condition('flat_type_id', $allotment_type)
	->condition('floor', $floor, 'IN')
	->condition('flat_status_id', 1)
	->condition('flat_category_id', 1)
	->orderBy('flat_id', 'ASC');
	$result_for_flat_vacancy = $query_for_flat_vacancy->execute();
	while($data_flat_vacancy = $result_for_flat_vacancy->fetchObject()){
		$flat_vacancy[] = $data_flat_vacancy->flat_id;
	}
	
	for($i=0; $i<$no_of_vacancy; $i++) {
		$vacancy_details[] = array(
		'flat_id' => $flat_vacancy[$i], 
		'allotment_type' => $allotment_type, 
		'allotment_category' => $allotment_category_arr[$i], 
		'counter' => $roaster_counter_arr[$i],
		);		
	}
	
	return $vacancy_details;
	
	
}




function get_applicant_details($allotment_type = '') {
	$applicant_details = array();
	
	
	$query = db_select('housing_online_application', 'hoa');
	$query->innerJoin('housing_new_allotment_application', 'hnaa', 'hnaa.online_application_id = hoa.online_application_id');
	$query->fields('hoa', array('online_application_id'));
	$query->fields('hnaa', array('flat_type_id', 'allotment_category'));
	$query->condition('hoa.status', 'verified');
	$query->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'NA'));
	$query->condition('hnaa.flat_type_id', $allotment_type);
	$query->orderBy('online_application_id', 'ASC');
	
	$result = $query->execute();
    while($data = $result->fetchObject()){
		$applicant_details[] = array(
		'online_application_id' => $data->online_application_id, 'allotment_type' => $data->flat_type_id, 'allotment_category' => $data->allotment_category,
		);
	}
	
	return $applicant_details;
	
	
}


function update_allotment_details($allotment_type = '', $no_of_vacancy = '') {
	
	$allotment_process_result = db_query("select * from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'NAL'));
	$no_of_rows = $allotment_process_result->rowCount();
	if($no_of_rows <= 0) {
		//$x = 1;
    	$allotment_process_no = 'NAL-01';
		$allotment_process_arr = array();
		$allotment_process_arr['allotment_process_no'] = $allotment_process_no;
		$allotment_process_arr['allotment_process_type']  = 'NAL';
		$allotment_process_arr['allotment_flat_type']  = $allotment_type;

		db_insert('housing_allotment_process')
		->fields($allotment_process_arr)
		->execute();
	}
	else {
		$result_process_no = db_query("select max(substr(allotment_process_no, 5)) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'NAL'));
		$data_process_no = $result_process_no->fetchObject();
		$x = $data_process_no->allotment_process_no;
		if($x < 9) {
			$x = $x + 1;
			$allotment_process_no = $x;
			$allotment_process_no = 'NAL-0'.$allotment_process_no;
		}
		else {
			$x = $x + 1;
			$allotment_process_no = $x;
			$allotment_process_no = 'NAL-'.$allotment_process_no;
		}
		
		$allotment_process_arr = array();
		$allotment_process_arr['allotment_process_no'] = $allotment_process_no;
		$allotment_process_arr['allotment_process_type']  = 'NAL';
		$allotment_process_arr['allotment_flat_type']  = $allotment_type;

		db_insert('housing_allotment_process')
		->fields($allotment_process_arr)
		->execute();
	}
	
	$allotment_details = array();
	$vacancy_details = get_vacancy_details($allotment_type, $no_of_vacancy);
	
	
	for($i=0; $i<sizeof($vacancy_details); $i++) {
		
		$flat_id = $vacancy_details[$i]['flat_id'];
		$allotment_type = $vacancy_details[$i]['allotment_type'];
		$allotment_category = $vacancy_details[$i]['allotment_category'];
	   	$counter = $vacancy_details[$i]['counter'];
		$result = db_query("select hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from {housing_online_application} as hoa 
		inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category
		order by hoa.online_application_id limit 1", array(':status' => 'verified', ':app_no' => 'NA', ':flat_type_id' => $allotment_type, ':allotment_category' => $allotment_category));
	
		$data = $result->fetchObject();
	
		if($result->rowCount() > 0) {
		    
			$counter = $vacancy_details[$i]['counter'];
			$allotment_upd_arr = array();
			$allotment_upd_arr['status']  = 'allotted';
			$allotment_upd_arr['online_application_id']  = $data->online_application_id;
		
			db_update('housing_online_application')
			->fields($allotment_upd_arr)
			->condition('online_application_id', $allotment_upd_arr['online_application_id'])
			->execute();	
		
			//db_query('update housing_flat set flat_status_id = 2 where flat_id = '.$flat_id);
			
			db_update('housing_flat')
				->fields(array(
							'flat_status_id' => 2
						))
				->condition('flat_id', $flat_id)
				->execute();
			
			$allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'NAL'));
			$data_process_no = $allotment_process_no->fetchObject();
			
			$allotment_ins_arr = array();
			$allotment_ins_arr['online_application_id']  = $data->online_application_id;
			$allotment_ins_arr['flat_id']  = $flat_id;
			$allotment_ins_arr['allotment_no'] = 'NAL-'.$data->online_application_id.'-'.date("dmY");
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
	}
	
	db_insert('housing_allotment_roaster_counter')
	->fields(array('allotment_type' => $allotment_type, 'last_roaster_counter' => $counter))
	->execute();
	
	
	
//allotment of rest vacant flat after categorywise allotment to the applicant serially
	$floor = array('G', 'T');
	$query_for_flat_vacancy_new = db_select('housing_flat', 'hf')
	->fields('hf')
	->condition('flat_type_id', $allotment_type)
	->condition('floor', $floor, 'IN')
	->condition('flat_status_id', 1)
	->condition('flat_category_id', 1)
	->orderBy('flat_id', 'ASC');
	$no_of_vacancy_new = $query_for_flat_vacancy_new->execute()->rowCount();
	$result_for_flat_vacancy = $query_for_flat_vacancy_new->execute();
	while($data_flat_vacancy = $result_for_flat_vacancy->fetchObject()){
		$flat_vacancy[] = $data_flat_vacancy->flat_id;
	}
	
	for($k=0; $k<$no_of_vacancy_new; $k++) {
		$vacancy_details_new[] = array(
			'flat_id' => $flat_vacancy[$k], 
			'allotment_type' => $allotment_type,
		);		
	}
	
	for($j=0; $j<sizeof($vacancy_details_new); $j++) {
		
		$flat_id = $vacancy_details_new[$j]['flat_id'];
		$allotment_type = $vacancy_details_new[$j]['allotment_type'];
		$result = db_query("select hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from housing_online_application as hoa 
		inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hnaa.flat_type_id = :flat_type_id 
		order by hoa.online_application_id limit 1", array(':status' => 'verified', ':app_no' => 'NA', ':flat_type_id' => $allotment_type));
	
		$data = $result->fetchObject();
	
		if($result->rowCount() > 0) {
		    
			$allotment_upd_arr = array();
			$allotment_upd_arr['status']  = 'allotted';
			$allotment_upd_arr['online_application_id']  = $data->online_application_id;
		
			db_update('housing_online_application')
			->fields($allotment_upd_arr)
			->condition('online_application_id', $allotment_upd_arr['online_application_id'])
			->execute();	
		
			//db_query('update housing_flat set flat_status_id = 2 where flat_id = '.$flat_id);
			db_update('housing_flat')
			->fields(array(
							'flat_status_id' => 2
					))
			->condition('flat_id', $flat_id)
			->execute();
			
			$allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'NAL'));
			$data_process_no = $allotment_process_no->fetchObject();
			
			$allotment_ins_arr = array();
			$allotment_ins_arr['online_application_id']  = $data->online_application_id;
			$allotment_ins_arr['flat_id']  = $flat_id;
			$allotment_ins_arr['allotment_no'] = 'NAL-'.$data->online_application_id.'-'.date("dmY");
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
		
		}
	}
//end	

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


/*function rhe_allotment_form_rhe_allotment_form_alter(&$form, &$form_state, $form_id) {
	$form['captcha']['#description'] = '';
	$form['captcha']['#weight'] = 4;
	
	#krumo($form);
}*/