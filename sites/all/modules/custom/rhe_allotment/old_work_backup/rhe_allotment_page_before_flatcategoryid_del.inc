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
	
	//no of vacancy for category shifting
	$form['no_of_vacancy_cs'] = array(
		'#default_value' => '',
		'#prefix' => '<div class="one" id="no_of_vacancy_cs">',
 		'#suffix' => '</div>',
	  );
	if($allotment_type != '')	 {
		$form['no_of_vacancy_cs'] = array(
		'#prefix' => '<div class="one" id="no_of_vacancy_cs">Total no of Vacancy for Category Shifting : '.get_no_of_vacancy_cs($allotment_type),
		'#suffix' => '</div>',
		);
	}
	
	//no of applicant for category shifting
  	$form['no_of_applicant_cs'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant_cs">',
 		'#suffix' => '</div>',
	);
   	  
	if($allotment_type != '')	 {
		$form['no_of_applicant_cs'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant_cs">Total no of Applicant for Category Shifting : '.get_no_of_applicant_cs($allotment_type),
 		'#suffix' => '</div>',
	  	);
	}
	
	//no of vacancy for new allotment
	$form['no_of_vacancy'] = array(
		'#default_value' => '',
		'#prefix' => '<div class="one" id="no_of_vacancy">',
 		'#suffix' => '</div>',
	  );
	if($allotment_type != '')	 {
		$form['no_of_vacancy'] = array(
		'#prefix' => '<div class="one" id="no_of_vacancy">Total no of Vacancy for New Allotment : '.get_no_of_vacancy_before_alot($allotment_type),
		'#suffix' => '</div>',
		);
	}
	
	//no of applicant for new allotment
  	$form['no_of_applicant'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant">',
 		'#suffix' => '</div>',
	);
   	  
	if($allotment_type != '')	 {
		$form['no_of_applicant'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant">Total no of Applicant for New Allotment : '.get_no_of_applicant($allotment_type),
 		'#suffix' => '</div>',
	  	);
	}
	
	//no of vacancy for floor shifting
	$form['no_of_vacancy_fs'] = array(
		'#default_value' => '',
		'#prefix' => '<div class="one" id="no_of_vacancy_fs">',
 		'#suffix' => '</div>',
	  );
	if($allotment_type != '')	 {
		$form['no_of_vacancy_fs'] = array(
		'#prefix' => '<div class="one" id="no_of_vacancy_fs">Total no of Vacancy for Floor Shifting : '.get_no_of_vacancy_fs($allotment_type),
		'#suffix' => '</div>',
		);
	}
	
	//no of applicant for floor shifting
  	$form['no_of_applicant_fs'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant_fs">',
 		'#suffix' => '</div>',
	);
   	  
	if($allotment_type != '')	 {
		$form['no_of_applicant_fs'] = array(
		'#prefix' => '<div class="one" id="no_of_applicant_fs">Total no of Applicant for Floor Shifting : '.get_no_of_applicant_fs($allotment_type),
 		'#suffix' => '</div>',
	  	);
	}
	
//new allotment vacancy details
	/*$form['vacancy_details'] = array(
		'#prefix' => '<div class="two" id="vacancy_details">',
 		'#suffix' => '</div>',
	  );
	  
	  
	 if($allotment_type != '')	 {
		 $vacancy_details = array();
		 $no_of_vacancy = get_no_of_vacancy_before_alot($allotment_type);
		 $vacancy_details = get_vacancy_details($allotment_type, $no_of_vacancy);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Flat Type</b></td>';
		 //$output .= '<td><b>Flat ID</b></td>';
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
			 // $output .= '<td>'.$val['flat_id'].'</td>';
			  $output .= '<td>'.$val['counter'].'</td>';
			  $output .= '<td>'.$val['allotment_category'].'</td>';
			  $output .= '</tr>';
		 }
		 $output .= '</tr>';
		 $output .= '</table><br>';
		 
		 
		 
		$form['vacancy_details'] = array(
		'#prefix' => '<div class="two" id="vacancy_details">New Allotment Vacancy Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}*/
	
//new allotment applicant details
	/*$form['applicant_details'] = array(
		'#prefix' => '<div class="two" id="applicant_details">',
 		'#suffix' => '</div>',
	  );
	  
	  if($allotment_type != '')	 {
		 $applicant_details = array();
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
		 $output .= '</table><br>';
		 
		 
		 
		$form['applicant_details'] = array(
		'#prefix' => '<div class="two" id="applicant_details">New Allotment Applicant Details : '.$output,
 		'#suffix' => '</div>',
	  	);
	}*/
	
	
//category shifting vacancy details
	/*$form['vacancy_details_cs'] = array(
		'#prefix' => '<div class="two" id="vacancy_details_cs">',
 		'#suffix' => '</div>',
	  );
	  
	  
	 if($allotment_type != '')	 {
		 $vacancy_details_cs = array();
		 $no_of_vacancy_cs = get_no_of_vacancy_cs($allotment_type);
		 $vacancy_details_cs = get_vacancy_details_cs($allotment_type, $no_of_vacancy_cs);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Estate ID</b></td>';
		 $output .= '<td><b>Estate Name</b></td>';
		 $output .= '<td><b>Flat ID</b></td>';
		 $output .= '<td><b>Flat Type</b></td>';
		 foreach($vacancy_details_cs as $val) {
			  $output .= '<tr>';
			  $output .= '<td>'.$val['estate_id'].'</td>';
			  $output .= '<td>'.$val['estate_name'].'</td>';
			  $output .= '<td>'.$val['flat_id'].'</td>';
			  if($val['flat_type_id'] == 5) {
				  $output .= '<td>A+</td>';  
			  }
			  else if($val['flat_type_id'] == 1) {
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
			  $output .= '</tr>';
		 }
		 $output .= '</tr>';
		 $output .= '</table>';
		 
		 
		 
		$form['vacancy_details_cs'] = array(
		'#prefix' => '<div class="two" id="vacancy_details_cs">Category Shifting Vacancy Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}*/
	
//category shifting applicant details
	 /* $form['applicant_details_cs'] = array(
		'#prefix' => '<div class="two" id="applicant_details_cs">',
 		'#suffix' => '</div>',
	  );
	  
	  if($allotment_type != '')	 {
		 $applicant_details_cs = array();
		 $applicant_details_cs = get_applicant_details_cs($allotment_type);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Online Application ID</b></td>';
		 $output .= '<td><b>Flat Type</b></td>';
		 $output .= '<td><b>Estate Name</b></td>';
		 foreach($applicant_details_cs as $val) {
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
			  $output .= '<td>'.$val['estate_name'].'</td>';
			  $output .= '</tr>';
		 }
		 $output .= '</tr>';
		 $output .= '</table>';
		 
		 
		 
		$form['applicant_details_cs'] = array(
		'#prefix' => '<div class="two" id="applicant_details_cs">Category Shifting Applicant Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}*/
	
	
//floor shifting vacancy details
	/*$form['vacancy_details_fs'] = array(
		'#prefix' => '<div class="two" id="vacancy_details_fs">',
 		'#suffix' => '</div>',
	  );
	  
	  
	 if($allotment_type != '')	 {
		 $vacancy_details_fs = array();
		 $no_of_vacancy_fs = get_no_of_vacancy_fs($allotment_type);
		 $vacancy_details_fs = get_vacancy_details_fs($allotment_type, $no_of_vacancy_fs);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Estate ID</b></td>';
		 $output .= '<td><b>Estate Name</b></td>';
		 $output .= '<td><b>Flat ID</b></td>';
		 $output .= '<td><b>Flat Type</b></td>';
		 foreach($vacancy_details_fs as $val) {
			  $output .= '<tr>';
			  $output .= '<td>'.$val['estate_id'].'</td>';
			  $output .= '<td>'.$val['estate_name'].'</td>';
			  $output .= '<td>'.$val['flat_id'].'</td>';
			  if($val['flat_type_id'] == 5) {
				  $output .= '<td>A+</td>';  
			  }
			  else if($val['flat_type_id'] == 1) {
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
			  $output .= '</tr>';
		 }
		 $output .= '</tr>';
		 $output .= '</table>';
		 
		 
		 
		$form['vacancy_details_fs'] = array(
		'#prefix' => '<div class="two" id="vacancy_details_fs">Floor Shifting Vacancy Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}*/
	
//floor shifting applicant details
	 /* $form['applicant_details_fs'] = array(
		'#prefix' => '<div class="two" id="applicant_details_fs">',
 		'#suffix' => '</div>',
	  );
	  
	  if($allotment_type != '')	 {
		 $applicant_details_fs = array();
		 $applicant_details_fs = get_applicant_details_fs($allotment_type);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Online Application ID</b></td>';
		 $output .= '<td><b>Flat Type</b></td>';
		 $output .= '<td><b>Estate Name</b></td>';
		 foreach($applicant_details_fs as $val) {
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
			  $output .= '<td>'.$val['estate_name'].'</td>';
			  $output .= '</tr>';
		 }
		 $output .= '</tr>';
		 $output .= '</table>';
		 
		 
		 
		$form['applicant_details_fs'] = array(
		'#prefix' => '<div class="two" id="applicant_details_fs">Floor Shifting Applicant Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}*/
	
	
//allotment details
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
		 
		 //for new allotment
		 $no_of_vacancy = get_no_of_vacancy_before_alot($allotment_type);
		 $no_of_applicant = get_no_of_applicant($allotment_type);
		 
		 //for category shifting
		 $no_of_vacancy_cs = get_no_of_vacancy_cs($allotment_type);
		 
		 //for floor shifting
		 $no_of_vacancy_fs = get_no_of_vacancy_fs($allotment_type);
		 
		 if($no_of_vacancy > 0 && $no_of_applicant > 0) {
			 /*$vacancy_details = array();
			 $vacancy_details = get_vacancy_details($allotment_type, $no_of_vacancy);*/  
			 update_allotment_details($allotment_type, $no_of_vacancy, $no_of_vacancy_cs, $no_of_vacancy_fs);
			 
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
	//new allotment
    $commands[] = ajax_command_replace("#no_of_vacancy", drupal_render($form['no_of_vacancy']));
	$commands[] = ajax_command_replace("#no_of_applicant", drupal_render($form['no_of_applicant']));
	
	//category shifting
	$commands[] = ajax_command_replace("#no_of_vacancy_cs", drupal_render($form['no_of_vacancy_cs']));
	$commands[] = ajax_command_replace("#no_of_applicant_cs", drupal_render($form['no_of_applicant_cs']));
	
	//floor shifting
	$commands[] = ajax_command_replace("#no_of_vacancy_fs", drupal_render($form['no_of_vacancy_fs']));
	$commands[] = ajax_command_replace("#no_of_applicant_fs", drupal_render($form['no_of_applicant_fs']));
	
	//new allotment details
	/*$commands[] = ajax_command_replace("#vacancy_details", drupal_render($form['vacancy_details']));
	$commands[] = ajax_command_replace("#applicant_details", drupal_render($form['applicant_details']));*/
	
	//category shifting details
	/*$commands[] = ajax_command_replace("#vacancy_details_cs", drupal_render($form['vacancy_details_cs']));
	$commands[] = ajax_command_replace("#applicant_details_cs", drupal_render($form['applicant_details_cs']));*/
	
	//floor shifting details
	/*$commands[] = ajax_command_replace("#vacancy_details_fs", drupal_render($form['vacancy_details_fs']));
	$commands[] = ajax_command_replace("#applicant_details_fs", drupal_render($form['applicant_details_fs']));*/
	
    return array('#type' => 'ajax', '#commands' => $commands);
  
}


//start of no of vacany and applicant for category shifting
	function get_no_of_vacancy_cs($allotment_type = '') {
		$no_of_vacancy_cs = 0;
		$floor = array('G', 'T');
		
		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
		$query->addField('he', 'estate_id');
		$db_and = db_and();
		$db_and->condition('flat_type_id', $allotment_type);
		$db_and->condition('floor', $floor, 'IN');
		$db_and->condition('hdist.district_code', 17, '=');
		//db_and->condition('flat_category_id', 1);
		$db_and->condition('flat_status_id', 1, '=');
		$query->condition($db_and);
		$query->groupBy('he.estate_id');
		$query->orderBy('he.estate_id', 'ASC');
		$result = $query->execute();
		if($result->rowCount() > 0) {
			while($data = $result->fetchObject()) {
				$query1 = db_select('housing_online_application', 'hoa');
				$query1->innerJoin('housing_cs_application', 'hca', 'hca.online_application_id = hoa.online_application_id');
				$query1->fields('hoa');
				$query1->fields('hca');
				$db_and1 = db_and();
				$db_and1->condition('hoa.status', 'verified');
				$db_and1->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'CS'));
				$db_and1->condition('hca.flat_type_id', $allotment_type);
				$db_and1->condition('hca.occupation_estate', $data->estate_id, '=');
				$query1->condition($db_and1);
				$result1 = $query1->execute();
				if($result1->rowCount() > 0) {
					$query2 = db_select('housing_flat', 'hf');
					$query2->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
					$query2->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
					$query2->fields('hf');
					$db_and2 = db_and();
					$db_and2->condition('flat_type_id', $allotment_type);
					$db_and2->condition('floor', $floor, 'IN');
					$db_and2->condition('hdist.district_code', 17, '=');
					//db_and->condition('flat_category_id', 1);
					$db_and2->condition('flat_status_id', 1, '=');
					$db_and2->condition('he.estate_id', $data->estate_id, '=');
					$query2->condition($db_and2);
					$no_of_vacancy_cs1 = $query2->execute()->rowCount();
					
					//cs vacany count as per 2:1 ratio
					$no_of_vacancy_cs2 = floor($no_of_vacancy_cs1*(1/3));
					
					$no_of_vacancy_cs = $no_of_vacancy_cs + $no_of_vacancy_cs2;
				}
			}
		}
		
		return $no_of_vacancy_cs;
		
	}
	function get_no_of_applicant_cs($allotment_type = '') {
		$no_of_applicant_cs = 0;
		
		$query = db_select('housing_online_application', 'hoa');
		$query->innerJoin('housing_cs_application', 'hca', 'hca.online_application_id = hoa.online_application_id');
		$query->fields('hoa');
		$query->fields('hca');
		$db_and = db_and();
		$db_and->condition('hoa.status', 'verified');
		$db_and->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'CS'));
		$db_and->condition('hca.flat_type_id', $allotment_type);
		$query->condition($db_and);
		$no_of_applicant_cs = $query->execute()->rowCount();
		
		return $no_of_applicant_cs;
		
	}
//end of no of vacany and applicant for category shifting

//start of no of vacany and applicant for new allotment
	function get_no_of_vacancy_before_alot($allotment_type = '') {
		$no_of_vacancy = 0;
		$floor = array('G', 'T');
		
		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
		$query->addField('he', 'estate_id');
		$db_and = db_and();
		$db_and->condition('flat_type_id', $allotment_type);
		$db_and->condition('floor', $floor, 'IN');
		$db_and->condition('hdist.district_code', 17, '=');
		//db_and->condition('flat_category_id', 1);
		$db_and->condition('flat_status_id', 1, '=');
		$query->condition($db_and);
		$query->groupBy('he.estate_id');
		$query->orderBy('he.estate_id', 'ASC');
		$result = $query->execute();
		if($result->rowCount() > 0) {
			while($data = $result->fetchObject()) {
				$query1 = db_select('housing_online_application', 'hoa');
				$query1->innerJoin('housing_cs_application', 'hca', 'hca.online_application_id = hoa.online_application_id');
				$query1->fields('hoa');
				$query1->fields('hca');
				$db_and1 = db_and();
				$db_and1->condition('hoa.status', 'verified');
				$db_and1->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'CS'));
				$db_and1->condition('hca.flat_type_id', $allotment_type);
				$db_and1->condition('hca.occupation_estate', $data->estate_id, '=');
				$query1->condition($db_and1);
				$result1 = $query1->execute();
				if($result1->rowCount() > 0) {
					$query2 = db_select('housing_flat', 'hf');
					$query2->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
					$query2->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
					$query2->fields('hf');
					$db_and2 = db_and();
					$db_and2->condition('flat_type_id', $allotment_type);
					$db_and2->condition('floor', $floor, 'IN');
					$db_and2->condition('hdist.district_code', 17, '=');
					//db_and->condition('flat_category_id', 1);
					$db_and2->condition('flat_status_id', 1, '=');
					$db_and2->condition('he.estate_id', $data->estate_id, '=');
					$query2->condition($db_and2);
					$no_of_vacancy1 = $query2->execute()->rowCount();
					
					//new allotment vacany count as per 2:1 ratio
					$no_of_vacancy2 = ceil($no_of_vacancy1*(2/3));
					
					$no_of_vacancy = $no_of_vacancy + $no_of_vacancy2;
				} else {
					$query2 = db_select('housing_flat', 'hf');
					$query2->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
					$query2->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
					$query2->fields('hf');
					$db_and2 = db_and();
					$db_and2->condition('flat_type_id', $allotment_type);
					$db_and2->condition('floor', $floor, 'IN');
					$db_and2->condition('hdist.district_code', 17, '=');
					//db_and->condition('flat_category_id', 1);
					$db_and2->condition('flat_status_id', 1, '=');
					$db_and2->condition('he.estate_id', $data->estate_id, '=');
					$query2->condition($db_and2);
					$no_of_vacancy1 = $query2->execute()->rowCount();
					
					$no_of_vacancy = $no_of_vacancy + $no_of_vacancy1;
				}
			}
		}
		
		return $no_of_vacancy;
		
	}
	function get_no_of_vacancy_after_alot($allotment_type = '') {
		$no_of_vacancy = 0;
		$floor = array('G', 'T');
		
		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
		$query->fields('hf');
		$db_and = db_and();
		$db_and->condition('flat_type_id', $allotment_type);
		$db_and->condition('floor', $floor, 'IN');
		$db_and->condition('hdist.district_code', 17, '=');
		//db_and->condition('flat_category_id', 1);
		$db_and->condition('flat_status_id', 1, '=');
		$query->condition($db_and);
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
//end of no of vacany and applicant for new allotment

//start of no of vacany and applicant for floor shifting
	function get_no_of_vacancy_fs($allotment_type = '') {
		$no_of_vacancy_fs = 0;
		$floor = array('F', 'S');
		
		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
		$query->fields('hf');
		$db_and = db_and();
		$db_and->condition('flat_type_id', $allotment_type);
		$db_and->condition('floor', $floor, 'IN');
		$db_and->condition('hdist.district_code', 17, '=');
		//db_and->condition('flat_category_id', 3);
		$db_and->condition('flat_status_id', 1, '=');
		$query->condition($db_and);
		$no_of_vacancy_fs = $query->execute()->rowCount();
		
		return $no_of_vacancy_fs;
		
	}
	function get_no_of_applicant_fs($allotment_type = '') {
		$no_of_applicant_fs = 0;
		
		$query = db_select('housing_online_application', 'hoa');
		$query->innerJoin('housing_vs_application', 'hva', 'hva.online_application_id = hoa.online_application_id');
		$query->fields('hoa');
		$query->fields('hva');
		$db_and = db_and();
		$db_and->condition('hoa.status', 'verified');
		$db_and->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'VS'));
		$db_and->condition('hva.flat_type_id', $allotment_type);
		$query->condition($db_and);
		$no_of_applicant_fs = $query->execute()->rowCount();
		
		return $no_of_applicant_fs;
		
	}
//end of no of vacany and applicant for floor shifting

//start for new allotment vacany and applicant details
function get_vacancy_details($allotment_type = '', $no_of_vacancy = '') {
	$vacancy_details = array();
	
	$result_counter = db_query("select last_roaster_counter from {housing_allotment_roaster_counter} where allotment_type = :allotment_type and id = (select max(id) from {housing_allotment_roaster_counter} where allotment_type = :allotment_type1)", array(':allotment_type' => $allotment_type, ':allotment_type1' => $allotment_type));
	
	if($result_counter->rowCount() > 0) {
		$data_counter = $result_counter->fetchObject();
		$offset_val = $data_counter->last_roaster_counter;
	} else {	
		$offset_val = 0;
	}
	
	
	if($allotment_type == 1 || $allotment_type == 5) {
	
		if(29 - $offset_val >= $no_of_vacancy) {
			$result = db_query("select * from {housing_roaster4a_aplus_master} order by counter limit :no_of_vacancy offset :offset_val", array(':no_of_vacancy' => $no_of_vacancy, ':offset_val' => $offset_val)); 
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
			$rest_tab .= "(select * from {housing_roaster4a_aplus_master} order by counter)";
			}
			/*echo "(select * from housing_roaster4a_aplus_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab;*/
			$result = db_query(" (select * from housing_roaster4a_aplus_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab);
			
		}
	
		$allotment_category_arr = array();
		while($data = $result->fetchObject()){
			$roaster_counter_arr[] = $data->counter;
			$allotment_category_arr[] = $data->category;
		}
	
	}
	else if($allotment_type == 2) {	
	
		if(29 - $offset_val >= $no_of_vacancy) {
			$result = db_query("select * from {housing_roaster4b_master} order by counter limit :no_of_vacancy offset :offset_val", array(':no_of_vacancy' => $no_of_vacancy, ':offset_val' => $offset_val)); 
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
			$rest_tab .= "(select * from {housing_roaster4b_master} order by counter)";
			}
			/*echo "(select * from housing_roaster4b_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab;*/
			$result = db_query(" (select * from housing_roaster4b_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab);
			
		}
	
		$allotment_category_arr = array();
		while($data = $result->fetchObject()){
			$roaster_counter_arr[] = $data->counter;
			$allotment_category_arr[] = $data->category;
		}
			
	}
	else if($allotment_type == 3 || $allotment_type == 4) {
	
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
			$rest_tab .= "(select * from {housing_roaster4cd_master} order by counter)";
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
	
	
	for($i=0; $i<$no_of_vacancy; $i++) {
		$vacancy_details[] = array(
		'allotment_type' => $allotment_type, 
		'allotment_category' => $allotment_category_arr[$i], 
		'counter' => $roaster_counter_arr[$i],
		);		
	}
	
	/*echo '<pre>';
	print_r($vacancy_details);die();*/
	
	return $vacancy_details;
	
	
}

function get_applicant_details($allotment_type = '') {
	$applicant_details = array();
	
	$query = db_select('housing_online_application', 'hoa');
	$query->innerJoin('housing_applicant_official_detail', 'haod', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
	$query->innerJoin('housing_new_allotment_application', 'hnaa', 'hnaa.online_application_id = hoa.online_application_id');
	$query->fields('hoa', array('online_application_id'));
	$query->fields('hnaa', array('flat_type_id', 'allotment_category'));
	$db_and = db_and();
	$db_and->condition('hoa.status', 'verified');
	$db_and->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'NA'));
	$db_and->condition('hnaa.flat_type_id', $allotment_type);
	$query->condition($db_and);
	
	if($allotment_type == 5) {
		$query->orderBy('grade_pay', 'DESC');
		$query->orderBy('hoa.online_application_id', 'ASC');
	}
	else {
		$query->orderBy('hoa.online_application_id', 'ASC');
	}
	
	$result = $query->execute();
    while($data = $result->fetchObject()){
		$applicant_details[] = array(
			'online_application_id' => $data->online_application_id, 
			'allotment_type' => $data->flat_type_id, 
			'allotment_category' => $data->allotment_category,
		);
	}
	
	return $applicant_details;
	
	
}
//end for new allotment vacany and applicant details

//start for category shifting vacany and applicant details
function get_vacancy_details_cs($allotment_type = '', $no_of_vacancy_cs = '') {
	$vacancy_details_cs = array();
	$floor = array('G', 'T');
		
	$query = db_select('housing_flat', 'hf');
	$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
	$query->addField('he', 'estate_id');
	$db_and = db_and();
	$db_and->condition('flat_type_id', $allotment_type);
	$db_and->condition('floor', $floor, 'IN');
	$db_and->condition('hdist.district_code', 17, '=');
	//db_and->condition('flat_category_id', 1);
	$db_and->condition('flat_status_id', 1, '=');
	$query->condition($db_and);
	$query->groupBy('he.estate_id');
	$query->orderBy('he.estate_id', 'ASC');
	$result = $query->execute();
	if($result->rowCount() > 0) {
		while($data = $result->fetchObject()) {
			$query1 = db_select('housing_online_application', 'hoa');
			$query1->innerJoin('housing_cs_application', 'hca', 'hca.online_application_id = hoa.online_application_id');
			$query1->fields('hoa');
			$query1->fields('hca');
			$db_and1 = db_and();
			$db_and1->condition('hoa.status', 'verified');
			$db_and1->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'CS'));
			$db_and1->condition('hca.flat_type_id', $allotment_type);
			$db_and1->condition('hca.occupation_estate', $data->estate_id, '=');
			$query1->condition($db_and1);
			$result1 = $query1->execute();
			if($result1->rowCount() > 0) {
				$query2 = db_select('housing_flat', 'hf');
				$query2->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
				$query2->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
				$query2->fields('hf');
				$query2->addField('he', 'estate_name');
				$db_and2 = db_and();
				$db_and2->condition('flat_type_id', $allotment_type);
				$db_and2->condition('floor', $floor, 'IN');
				$db_and2->condition('hdist.district_code', 17, '=');
				//db_and->condition('flat_category_id', 1);
				$db_and2->condition('flat_status_id', 1, '=');
				$db_and2->condition('he.estate_id', $data->estate_id, '=');
				$query2->condition($db_and2);
				$query2->orderBy('he.estate_id', 'ASC');
				$query2->orderBy('flat_id', 'ASC');
				$result2 = $query2->execute();
				$estate_total_no_of_vacancy = $result2->rowCount();
				
			//cs vacany count as per 2:1 ratio
				$estate_cs_no_of_vacancy = floor($estate_total_no_of_vacancy*(1/3));
				
				for($j=0; $j<$estate_cs_no_of_vacancy; $j++) {
					$data2 = $result2->fetchObject();
					$estate_id_vacancy[] = $data2->estate_id;
					$estate_name_vacancy[] = $data2->estate_name;
					$flat_id_vacancy[] = $data2->flat_id;
					$flat_type[] = $data2->flat_type_id;
				}
			}
		}
	}
	
	for($i=0; $i<$no_of_vacancy_cs; $i++) {
		$vacancy_details_cs[] = array(
			'estate_id' => $estate_id_vacancy[$i],
			'estate_name' => $estate_name_vacancy[$i],
			'flat_id' => $flat_id_vacancy[$i], 
			'flat_type_id' => $flat_type[$i], 
		);		
	}
	
	/*echo '<pre>';
	print_r($vacancy_details_cs);die();*/
	
	return $vacancy_details_cs;
}

function get_applicant_details_cs($allotment_type = '') {
	$applicant_details_cs = array();
	
	$query = db_select('housing_online_application', 'hoa');
	$query->innerJoin('housing_applicant_official_detail', 'haod', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
	$query->innerJoin('housing_cs_application', 'hca', 'hca.online_application_id = hoa.online_application_id');
	$query->innerJoin('housing_estate', 'he', 'he.estate_id = hca.occupation_estate');
	$query->fields('hoa', array('online_application_id'));
	$query->fields('hca');
	$query->fields('he', array('estate_name'));
	$db_and = db_and();
	$db_and->condition('hoa.status', 'verified');
	$db_and->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'CS'));
	$db_and->condition('hca.flat_type_id', $allotment_type);
	$query->condition($db_and);
	if($allotment_type == 5) {
		$query->orderBy('grade_pay', 'DESC');
		$query->orderBy('hoa.online_application_id', 'ASC');
	}
	else {
		$query->orderBy('hoa.online_application_id', 'ASC');
	}
	
	$result = $query->execute();
	while($data = $result->fetchObject()){
		$applicant_details_cs[] = array(
			'online_application_id' => $data->online_application_id, 
			'allotment_type' => $data->flat_type_id,
			'estate_name' => $data->estate_name,
		);
	}
	
	
	return $applicant_details_cs;


}
//end for category shifting vacany and applicant details

//start for floor shifting vacany and applicant details
function get_vacancy_details_fs($allotment_type = '', $no_of_vacancy_fs = '') {
	$vacancy_details_fs = array();
	$floor = array('F', 'S');
	
	$query_for_flat_vacancy = db_select('housing_flat', 'hf');
	$query_for_flat_vacancy->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
	$query_for_flat_vacancy->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
	$query_for_flat_vacancy->fields('he');
	$query_for_flat_vacancy->fields('hf');
	$db_and = db_and();
	$db_and->condition('flat_type_id', $allotment_type, '=');
	$db_and->condition('floor', $floor, 'IN');
	$db_and->condition('flat_status_id', 1, '=');
	$db_and->condition('hdist.district_code', 17, '=');
	//db_and->condition('flat_category_id', 3);
	$query_for_flat_vacancy->condition($db_and);
	$query_for_flat_vacancy->orderBy('he.estate_id', 'ASC');
	$query_for_flat_vacancy->orderBy('flat_id', 'ASC');
	$result_for_flat_vacancy = $query_for_flat_vacancy->execute();
	while($data_flat_vacancy = $result_for_flat_vacancy->fetchObject()){
		$estate_id_vacancy[] = $data_flat_vacancy->estate_id;
		$estate_name_vacancy[] = $data_flat_vacancy->estate_name;
		$flat_id_vacancy[] = $data_flat_vacancy->flat_id;
		$flat_type[] = $data_flat_vacancy->flat_type_id;
	}

	for($i=0; $i<$no_of_vacancy_fs; $i++) {
		$vacancy_details_fs[] = array(
		'estate_id' => $estate_id_vacancy[$i],
		'estate_name' => $estate_name_vacancy[$i],
		'flat_id' => $flat_id_vacancy[$i], 
		'flat_type_id' => $flat_type[$i], 
		);		
	}
	
	/*echo '<pre>';
	print_r($vacancy_details_fs);die();*/
	
	return $vacancy_details_fs;
}

function get_applicant_details_fs($allotment_type = '') {
	$applicant_details_fs = array();
	
	$query = db_select('housing_online_application', 'hoa');
	$query->innerJoin('housing_applicant_official_detail', 'haod', 'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
	$query->innerJoin('housing_vs_application', 'hva', 'hva.online_application_id = hoa.online_application_id');
	$query->innerJoin('housing_estate', 'he', 'he.estate_id = hva.occupation_estate');
	$query->fields('hoa', array('online_application_id'));
	$query->fields('hva');
	$query->fields('he', array('estate_name'));
	$db_and = db_and();
	$db_and->condition('hoa.status', 'verified');
	$db_and->where('substring(hoa.application_no, \'\w+\') = :app_no', array(':app_no' => 'VS'));
	$db_and->condition('hva.flat_type_id', $allotment_type);
	$query->condition($db_and);
	if($allotment_type == 5) {
		$query->orderBy('grade_pay', 'DESC');
		$query->orderBy('hoa.online_application_id', 'ASC');
	}
	else {
		$query->orderBy('hoa.online_application_id', 'ASC');
	}
	
	$result = $query->execute();
	while($data = $result->fetchObject()){
		$applicant_details_fs[] = array(
			'online_application_id' => $data->online_application_id, 
			'allotment_type' => $data->flat_type_id,
			'estate_name' => $data->estate_name,
		);
	}
	
	
	return $applicant_details_fs;


}
//end for floor shifting vacany and applicant details

function update_allotment_details($allotment_type = '', $no_of_vacancy = '', $no_of_vacancy_cs = '', $no_of_vacancy_fs = '') {
	
	$allotment_process_result = db_query("select * from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
	$no_of_rows = $allotment_process_result->rowCount();
	if($no_of_rows <= 0) {
		//$x = 1;
    	$allotment_process_no = 'ALOT-01';
		$allotment_process_arr = array();
		$allotment_process_arr['allotment_process_no'] = $allotment_process_no;
		$allotment_process_arr['allotment_process_type']  = 'ALOT';
		$allotment_process_arr['allotment_flat_type']  = $allotment_type;

		db_insert('housing_allotment_process')
		->fields($allotment_process_arr)
		->execute();
	}
	else {
		$result_process_no = db_query("select max(substr(allotment_process_no, 6)) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
		$data_process_no = $result_process_no->fetchObject();
		$x = $data_process_no->allotment_process_no;
		if($x < 9) {
			$x = $x + 1;
			$allotment_process_no = $x;
			$allotment_process_no = 'ALOT-0'.$allotment_process_no;
		}
		else {
			$x = $x + 1;
			$allotment_process_no = $x;
			$allotment_process_no = 'ALOT-'.$allotment_process_no;
		}
		
		$allotment_process_arr = array();
		$allotment_process_arr['allotment_process_no'] = $allotment_process_no;
		$allotment_process_arr['allotment_process_type']  = 'ALOT';
		$allotment_process_arr['allotment_flat_type']  = $allotment_type;

		db_insert('housing_allotment_process')
		->fields($allotment_process_arr)
		->execute();
	}
	
//category shifting process	start

	$vacancy_details_cs = array();
	$vacancy_details_cs = get_vacancy_details_cs($allotment_type, $no_of_vacancy_cs);
	
	for($p=0; $p<sizeof($vacancy_details_cs); $p++) {
		
		$estate_id_cs = $vacancy_details_cs[$p]['estate_id'];
		$flat_id_cs = $vacancy_details_cs[$p]['flat_id'];
		$flat_type_id_cs = $vacancy_details_cs[$p]['flat_type_id'];
		
		if($allotment_type == 5) {
			$result = db_query("select hoa.online_application_id, hca.flat_type_id, hca.occupation_estate, hca.occupation_flat from {housing_online_application} as hoa
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_cs_application} as hca on hca.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hca.occupation_estate = :occupation_estate and hca.flat_type_id = :flat_type_id
		order by grade_pay DESC, hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'CS', ':occupation_estate' => $estate_id_cs, ':flat_type_id' => $allotment_type));
		}
		else {
			$result = db_query("select hoa.online_application_id, hca.flat_type_id, hca.occupation_estate, hca.occupation_flat from {housing_online_application} as hoa
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_cs_application} as hca on hca.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hca.occupation_estate = :occupation_estate and hca.flat_type_id = :flat_type_id
		order by hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'CS', ':occupation_estate' => $estate_id_cs, ':flat_type_id' => $allotment_type));
		}
	
		$data = $result->fetchObject();
	
		if($result->rowCount() > 0) {
			
			$allotment_upd_arr = array();
			$allotment_upd_arr['status']  = 'allotted';
			$allotment_upd_arr['online_application_id']  = $data->online_application_id;
		
			db_update('housing_online_application')
			->fields($allotment_upd_arr)
			->condition('online_application_id', $allotment_upd_arr['online_application_id'])
			->execute();
			
			//update new flat which allotted to applicant
			db_update('housing_flat')
			->fields(array(
						'flat_status_id' => 2
					))
			->condition('flat_id', $flat_id_cs)
			->execute();
			
			//update old flat where applicant stay
			/*db_update('housing_flat')
			->fields(array(
						'flat_status_id' => 1
					))
			->condition('flat_id', $data->occupation_flat)
			->execute();*/
			
			$allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} 
												where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
			$data_process_no = $allotment_process_no->fetchObject();
			
			$allotment_ins_arr = array();
			$allotment_ins_arr['online_application_id']  = $data->online_application_id;
			$allotment_ins_arr['flat_id']  = $flat_id_cs;
			$allotment_ins_arr['allotment_no'] = 'CSAL-'.$data->online_application_id.'-'.date("dmY");
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
	
//end of category shifting process

//new allotment process	start

	$vacancy_details = array();
	$vacancy_details = get_vacancy_details($allotment_type, $no_of_vacancy);
	
	
	for($i=0; $i<sizeof($vacancy_details); $i++) {
		
		$flat_id = '';
		
		$allotment_type = $vacancy_details[$i]['allotment_type'];
		$allotment_category = $vacancy_details[$i]['allotment_category'];
	   	$counter = $vacancy_details[$i]['counter'];
		
		if($allotment_type == 5) {
			$result = db_query("select haod.office_pin_code, hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from {housing_online_application} as hoa 
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category
		order by grade_pay DESC, hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'NA', ':flat_type_id' => $allotment_type, ':allotment_category' => $allotment_category));	
		}
		else {
			$result = db_query("select haod.office_pin_code, hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from {housing_online_application} as hoa 
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category
		order by hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'NA', ':flat_type_id' => $allotment_type, ':allotment_category' => $allotment_category));
		}
	
		$data = $result->fetchObject();
	
		if($result->rowCount() > 0) {
			
			$floor = array('G', 'T');
			$query_for_flat_vacancy = db_select('housing_flat', 'hf');
			$query_for_flat_vacancy->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
			$query_for_flat_vacancy->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
			$query_for_flat_vacancy->fields('hf');
			$query_for_flat_vacancy->fields('he');
			$db_and = db_and();
			$db_and->condition('flat_type_id', $allotment_type);
			$db_and->condition('floor', $floor, 'IN');
			$db_and->condition('flat_status_id', 1);
			$db_and->condition('hdist.district_code', 17, '=');
			$db_and->condition('estate_pincode', $data->office_pin_code, '=');
			//$db_and->condition('flat_category_id', 1);
			$query_for_flat_vacancy->condition($db_and);
			$query_for_flat_vacancy->orderBy('flat_id', 'ASC');
			$result_for_flat_vacancy = $query_for_flat_vacancy->execute();
			
			if($result_for_flat_vacancy->rowCount() > 0) {
				$data_flat_vacancy = $result_for_flat_vacancy->fetchObject();
				$flat_id = $data_flat_vacancy->flat_id;
			} else {
				$query_applicant_zone = db_select('housing_state_pincode', 'hsp');
				$query_applicant_zone->fields('hsp');
				$query_applicant_zone->condition('pincode', $data->office_pin_code, '=');
				$result_applicant_zone = $query_applicant_zone->execute();
				$data_applicant_zone = $result_applicant_zone->fetchObject();
				
				$floor = array('G', 'T');
				$query_flat_vacancy_zone_wise = db_select('housing_flat', 'hf');
				$query_flat_vacancy_zone_wise->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
				$query_flat_vacancy_zone_wise->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
				$query_flat_vacancy_zone_wise->innerJoin('housing_state_pincode', 'hsp', 'hsp.pincode = he.estate_pincode');
				$query_flat_vacancy_zone_wise->fields('he');
				$query_flat_vacancy_zone_wise->fields('hf');
				$query_flat_vacancy_zone_wise->fields('hsp');
				$db_and = db_and();
				$db_and->condition('flat_type_id', $allotment_type);
				$db_and->condition('floor', $floor, 'IN');
				$db_and->condition('flat_status_id', 1);
				$db_and->condition('hdist.district_code', 17, '=');
				$db_and->condition('zone_code', $data_applicant_zone->zone_code, '=');
				//$db_and->condition('flat_category_id', 1);
				$query_flat_vacancy_zone_wise->condition($db_and);
				$query_flat_vacancy_zone_wise->orderBy('flat_id', 'ASC');
				$query_flat_vacancy_zone_wise->range(0, 1);
				$result_flat_vacancy_zone_wise = $query_flat_vacancy_zone_wise->execute();
				
				if($result_flat_vacancy_zone_wise->rowCount() > 0) {
					$data_flat_vacancy_zone_wise = $result_flat_vacancy_zone_wise->fetchObject();
					$flat_id = $data_flat_vacancy_zone_wise->flat_id; //die($flat_id);
				} else {
					//die('not ok');
					
					$floor = array('G', 'T');
					$query_flat_vacancy_zone_wise2 = db_select('housing_flat', 'hf');
					$query_flat_vacancy_zone_wise2->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
					$query_flat_vacancy_zone_wise2->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
					$query_flat_vacancy_zone_wise2->innerJoin('housing_state_pincode', 'hsp', 'hsp.pincode = he.estate_pincode');
					$query_flat_vacancy_zone_wise2->fields('he');
					$query_flat_vacancy_zone_wise2->fields('hf');
					$query_flat_vacancy_zone_wise2->fields('hsp');
					$db_and = db_and();
					$db_and->condition('flat_type_id', $allotment_type);
					$db_and->condition('floor', $floor, 'IN');
					$db_and->condition('flat_status_id', 1);
					$db_and->condition('hdist.district_code', 17, '=');
					$db_and->condition('zone_code', $data_applicant_zone->zone_code, '!=');
					//$db_and->condition('flat_category_id', 1);
					$query_flat_vacancy_zone_wise2->condition($db_and);
					$query_flat_vacancy_zone_wise2->orderBy('flat_id', 'ASC');
					$query_flat_vacancy_zone_wise2->range(0, 1);
					$result_flat_vacancy_zone_wise2 = $query_flat_vacancy_zone_wise2->execute();
					
					if($result_flat_vacancy_zone_wise2->rowCount() > 0) {
						$data_flat_vacancy_zone_wise2 = $result_flat_vacancy_zone_wise2->fetchObject();
						$flat_id = $data_flat_vacancy_zone_wise2->flat_id; //die($flat_id);
					}
				}
				
			}
		    
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
			
			$allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
			$data_process_no = $allotment_process_no->fetchObject();
			
			$allotment_ins_arr = array();
			$allotment_ins_arr['online_application_id']  = $data->online_application_id;
			$allotment_ins_arr['flat_id']  = $flat_id;
			$allotment_ins_arr['allotment_no'] = 'NAL-'.$data->online_application_id.'-'.date("dmY");
			$allotment_ins_arr['allotment_process_no'] = $data_process_no->allotment_process_no;
			$allotment_ins_arr['roaster_vacancy_position'] = $counter;
			$allotment_ins_arr['allotment_reason'] = $allotment_category;
		
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
	
	
//allotment of rest vacant flats to the general category applicant serially waiting list wise (after categorywise allotment)
	
	$no_of_vacancy_new = get_no_of_vacancy_after_alot($allotment_type);
	
	
	for($j=0; $j<$no_of_vacancy_new; $j++) {
		
		$flat_id_new = '';
		
		if($allotment_type == 5) {
			$result = db_query("select haod.office_pin_code, hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from housing_online_application as hoa 
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category
		order by grade_pay DESC, hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'NA', ':flat_type_id' => $allotment_type, ':allotment_category' => 'General'));	
		}
		else {
			$result = db_query("select haod.office_pin_code, hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from housing_online_application as hoa 
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category
		order by hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'NA', ':flat_type_id' => $allotment_type, ':allotment_category' => 'General'));
		}
	
		$data = $result->fetchObject();
	
		if($result->rowCount() > 0) {
			
			$floor = array('G', 'T');
			$query_for_flat_vacancy_new = db_select('housing_flat', 'hf');
			$query_for_flat_vacancy_new->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
			$query_for_flat_vacancy_new->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
			$query_for_flat_vacancy_new->fields('hf');
			$query_for_flat_vacancy_new->fields('he');
			$db_and = db_and();
			$db_and->condition('flat_type_id', $allotment_type);
			$db_and->condition('floor', $floor, 'IN');
			$db_and->condition('flat_status_id', 1);
			$db_and->condition('hdist.district_code', 17, '=');
			$db_and->condition('estate_pincode', $data->office_pin_code, '=');
			//$db_and->condition('flat_category_id', 1);
			$query_for_flat_vacancy_new->condition($db_and);
			$query_for_flat_vacancy_new->orderBy('flat_id', 'ASC');
			$result_for_flat_vacancy_new = $query_for_flat_vacancy_new->execute();
			
			if($result_for_flat_vacancy_new->rowCount() > 0) {
				$data_flat_vacancy_new = $result_for_flat_vacancy_new->fetchObject();
				$flat_id_new = $data_flat_vacancy_new->flat_id; //die($flat_id_new);
			} else {
				$query_applicant_zone_new = db_select('housing_state_pincode', 'hsp');
				$query_applicant_zone_new->fields('hsp');
				$query_applicant_zone_new->condition('pincode', $data->office_pin_code, '=');
				$result_applicant_zone_new = $query_applicant_zone_new->execute();
				$data_applicant_zone_new = $result_applicant_zone_new->fetchObject();
				
				$floor = array('G', 'T');
				$query_flat_vacancy_zone_wise_new = db_select('housing_flat', 'hf');
				$query_flat_vacancy_zone_wise_new->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
				$query_flat_vacancy_zone_wise_new->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
				$query_flat_vacancy_zone_wise_new->innerJoin('housing_state_pincode', 'hsp', 'hsp.pincode = he.estate_pincode');
				$query_flat_vacancy_zone_wise_new->fields('he');
				$query_flat_vacancy_zone_wise_new->fields('hf');
				$query_flat_vacancy_zone_wise_new->fields('hsp');
				$db_and = db_and();
				$db_and->condition('flat_type_id', $allotment_type);
				$db_and->condition('floor', $floor, 'IN');
				$db_and->condition('flat_status_id', 1);
				$db_and->condition('hdist.district_code', 17, '=');
				$db_and->condition('zone_code', $data_applicant_zone_new->zone_code, '=');
				//$db_and->condition('flat_category_id', 1);
				$query_flat_vacancy_zone_wise_new->condition($db_and);
				$query_flat_vacancy_zone_wise_new->orderBy('flat_id', 'ASC');
				$query_flat_vacancy_zone_wise_new->range(0, 1);
				$result_flat_vacancy_zone_wise_new = $query_flat_vacancy_zone_wise_new->execute();
				
				if($result_flat_vacancy_zone_wise_new->rowCount() > 0) {
					$data_flat_vacancy_zone_wise_new = $result_flat_vacancy_zone_wise_new->fetchObject();
					$flat_id_new = $data_flat_vacancy_zone_wise_new->flat_id; //die($flat_id_new);
				} else {
					//die('not ok');
					
					$floor = array('G', 'T');
					$query_flat_vacancy_zone_wise_new2 = db_select('housing_flat', 'hf');
					$query_flat_vacancy_zone_wise_new2->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
					$query_flat_vacancy_zone_wise_new2->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
					$query_flat_vacancy_zone_wise_new2->innerJoin('housing_state_pincode', 'hsp', 'hsp.pincode = he.estate_pincode');
					$query_flat_vacancy_zone_wise_new2->fields('he');
					$query_flat_vacancy_zone_wise_new2->fields('hf');
					$query_flat_vacancy_zone_wise_new2->fields('hsp');
					$db_and = db_and();
					$db_and->condition('flat_type_id', $allotment_type);
					$db_and->condition('floor', $floor, 'IN');
					$db_and->condition('flat_status_id', 1);
					$db_and->condition('hdist.district_code', 17, '=');
					$db_and->condition('zone_code', $data_applicant_zone_new->zone_code, '!=');
					//$db_and->condition('flat_category_id', 1);
					$query_flat_vacancy_zone_wise_new2->condition($db_and);
					$query_flat_vacancy_zone_wise_new2->orderBy('flat_id', 'ASC');
					$query_flat_vacancy_zone_wise_new2->range(0, 1);
					$result_flat_vacancy_zone_wise_new2 = $query_flat_vacancy_zone_wise_new2->execute();
					
					if($result_flat_vacancy_zone_wise_new2->rowCount() > 0) {
						$data_flat_vacancy_zone_wise_new2 = $result_flat_vacancy_zone_wise_new2->fetchObject();
						$flat_id_new = $data_flat_vacancy_zone_wise_new2->flat_id; //die($flat_id_new);
					}
				}
				
			}
		    
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
			->condition('flat_id', $flat_id_new)
			->execute();
			
			$allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
			$data_process_no = $allotment_process_no->fetchObject();
			
			$allotment_ins_arr = array();
			$allotment_ins_arr['online_application_id']  = $data->online_application_id;
			$allotment_ins_arr['flat_id']  = $flat_id_new;
			$allotment_ins_arr['allotment_no'] = 'NAL-'.$data->online_application_id.'-'.date("dmY");
			$allotment_ins_arr['allotment_process_no'] = $data_process_no->allotment_process_no;
			$allotment_ins_arr['roaster_vacancy_position'] = NULL;
			$allotment_ins_arr['allotment_reason'] = $data->allotment_category;
		
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
//end of new allotment process

//floor shifting process start

	$vacancy_details_fs = array();
	$vacancy_details_fs = get_vacancy_details_fs($allotment_type, $no_of_vacancy_fs);
	
	for($k=0; $k<sizeof($vacancy_details_fs); $k++) {
		
		$estate_id = $vacancy_details_fs[$k]['estate_id'];
		$flat_id_fs = $vacancy_details_fs[$k]['flat_id'];
		$flat_type_id = $vacancy_details_fs[$k]['flat_type_id'];
		
		if($allotment_type == 5) {
			$result = db_query("select hoa.online_application_id, hva.flat_type_id, hva.occupation_estate, hva.occupation_flat from {housing_online_application} as hoa
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_vs_application} as hva on hva.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hva.occupation_estate = :occupation_estate and hva.flat_type_id = :flat_type_id
		order by grade_pay DESC, hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'VS', ':occupation_estate' => $estate_id, ':flat_type_id' => $allotment_type));	
		}
		else {
			$result = db_query("select hoa.online_application_id, hva.flat_type_id, hva.occupation_estate, hva.occupation_flat from {housing_online_application} as hoa
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_vs_application} as hva on hva.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hva.occupation_estate = :occupation_estate and hva.flat_type_id = :flat_type_id
		order by hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'VS', ':occupation_estate' => $estate_id, ':flat_type_id' => $allotment_type));
		}
	
		$data = $result->fetchObject();
	
		if($result->rowCount() > 0) {
			$allotment_upd_arr = array();
			$allotment_upd_arr['status']  = 'allotted';
			$allotment_upd_arr['online_application_id']  = $data->online_application_id;
		
			db_update('housing_online_application')
			->fields($allotment_upd_arr)
			->condition('online_application_id', $allotment_upd_arr['online_application_id'])
			->execute();
			
			//update new flat which allotted to applicant
			db_update('housing_flat')
			->fields(array(
						'flat_status_id' => 2
					))
			->condition('flat_id', $flat_id_fs)
			->execute();
			
			//update old flat where applicant stay
			/*db_update('housing_flat')
			->fields(array(
						'flat_status_id' => 1
					))
			->condition('flat_id', $data->occupation_flat)
			->execute();*/
			
			$allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} 
												where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
			$data_process_no = $allotment_process_no->fetchObject();
			
			$allotment_ins_arr = array();
			$allotment_ins_arr['online_application_id']  = $data->online_application_id;
			$allotment_ins_arr['flat_id']  = $flat_id_fs;
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
		}
	}
		
		
//allotment of rest vacant flats to the general category applicant serially waiting list wise (after floor shifting allotment)

	$no_of_vacancy_fs_new = get_no_of_vacancy_fs($allotment_type);
	
	
	for($m=0; $m<$no_of_vacancy_fs_new; $m++) {
		
		$flat_id_fs_new = '';
		
		if($allotment_type == 5) {
			$result = db_query("select haod.office_pin_code, hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from housing_online_application as hoa 
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category
		order by grade_pay DESC, hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'NA', ':flat_type_id' => $allotment_type, ':allotment_category' => 'General'));	
		}
		else {
			$result = db_query("select haod.office_pin_code, hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from housing_online_application as hoa 
		inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
		inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
		where hoa.status = :status and substring(hoa.application_no, '\w+') = :app_no and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category
		order by hoa.online_application_id ASC limit 1", array(':status' => 'verified', ':app_no' => 'NA', ':flat_type_id' => $allotment_type, ':allotment_category' => 'General'));
		}
	
		$data = $result->fetchObject();
	
		if($result->rowCount() > 0) {
			
			$floor = array('F', 'S');
			$query_for_flat_vacancy_fs_new = db_select('housing_flat', 'hf');
			$query_for_flat_vacancy_fs_new->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
			$query_for_flat_vacancy_fs_new->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
			$query_for_flat_vacancy_fs_new->fields('hf');
			$query_for_flat_vacancy_fs_new->fields('he');
			$db_and = db_and();
			$db_and->condition('flat_type_id', $allotment_type);
			$db_and->condition('floor', $floor, 'IN');
			$db_and->condition('flat_status_id', 1);
			$db_and->condition('hdist.district_code', 17, '=');
			$db_and->condition('estate_pincode', $data->office_pin_code, '=');
			//$db_and->condition('flat_category_id', 3);
			$query_for_flat_vacancy_fs_new->condition($db_and);
			$query_for_flat_vacancy_fs_new->orderBy('flat_id', 'ASC');
			$result_for_flat_vacancy_fs_new = $query_for_flat_vacancy_fs_new->execute();
			
			if($result_for_flat_vacancy_fs_new->rowCount() > 0) {
				$data_flat_vacancy_fs_new = $result_for_flat_vacancy_fs_new->fetchObject();
				$flat_id_fs_new = $data_flat_vacancy_fs_new->flat_id; //die($flat_id_fs_new);
			} else {
				$query_applicant_zone_fs_new = db_select('housing_state_pincode', 'hsp');
				$query_applicant_zone_fs_new->fields('hsp');
				$query_applicant_zone_fs_new->condition('pincode', $data->office_pin_code, '=');
				$result_applicant_zone_fs_new = $query_applicant_zone_fs_new->execute();
				$data_applicant_zone_fs_new = $result_applicant_zone_fs_new->fetchObject();
				
				$floor = array('F', 'S');
				$query_flat_vacancy_zone_wise_fs_new = db_select('housing_flat', 'hf');
				$query_flat_vacancy_zone_wise_fs_new->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
				$query_flat_vacancy_zone_wise_fs_new->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
				$query_flat_vacancy_zone_wise_fs_new->innerJoin('housing_state_pincode', 'hsp', 'hsp.pincode = he.estate_pincode');
				$query_flat_vacancy_zone_wise_fs_new->fields('he');
				$query_flat_vacancy_zone_wise_fs_new->fields('hf');
				$query_flat_vacancy_zone_wise_fs_new->fields('hsp');
				$db_and = db_and();
				$db_and->condition('flat_type_id', $allotment_type);
				$db_and->condition('floor', $floor, 'IN');
				$db_and->condition('flat_status_id', 1);
				$db_and->condition('hdist.district_code', 17, '=');
				$db_and->condition('zone_code', $data_applicant_zone_fs_new->zone_code, '=');
				//$db_and->condition('flat_category_id', 3);
				$query_flat_vacancy_zone_wise_fs_new->condition($db_and);
				$query_flat_vacancy_zone_wise_fs_new->orderBy('flat_id', 'ASC');
				$query_flat_vacancy_zone_wise_fs_new->range(0, 1);
				$result_flat_vacancy_zone_wise_fs_new = $query_flat_vacancy_zone_wise_fs_new->execute();
				
				if($result_flat_vacancy_zone_wise_fs_new->rowCount() > 0) {
					$data_flat_vacancy_zone_wise_fs_new = $result_flat_vacancy_zone_wise_fs_new->fetchObject();
					$flat_id_fs_new = $data_flat_vacancy_zone_wise_fs_new->flat_id; //die($flat_id_fs_new);
				} else {
					//die('not ok');
					
					$floor = array('F', 'S');
					$query_flat_vacancy_zone_wise_fs_new2 = db_select('housing_flat', 'hf');
					$query_flat_vacancy_zone_wise_fs_new2->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
					$query_flat_vacancy_zone_wise_fs_new2->innerJoin('housing_district', 'hdist', 'hdist.district_code = he.district_code');
					$query_flat_vacancy_zone_wise_fs_new2->innerJoin('housing_state_pincode', 'hsp', 'hsp.pincode = he.estate_pincode');
					$query_flat_vacancy_zone_wise_fs_new2->fields('he');
					$query_flat_vacancy_zone_wise_fs_new2->fields('hf');
					$query_flat_vacancy_zone_wise_fs_new2->fields('hsp');
					$db_and = db_and();
					$db_and->condition('flat_type_id', $allotment_type);
					$db_and->condition('floor', $floor, 'IN');
					$db_and->condition('flat_status_id', 1);
					$db_and->condition('hdist.district_code', 17, '=');
					$db_and->condition('zone_code', $data_applicant_zone_fs_new->zone_code, '!=');
					//$db_and->condition('flat_category_id', 3);
					$query_flat_vacancy_zone_wise_fs_new2->condition($db_and);
					$query_flat_vacancy_zone_wise_fs_new2->orderBy('flat_id', 'ASC');
					$query_flat_vacancy_zone_wise_fs_new2->range(0, 1);
					$result_flat_vacancy_zone_wise_fs_new2 = $query_flat_vacancy_zone_wise_fs_new2->execute();
					
					if($result_flat_vacancy_zone_wise_fs_new2->rowCount() > 0) {
						$data_flat_vacancy_zone_wise_fs_new2 = $result_flat_vacancy_zone_wise_fs_new2->fetchObject();
						$flat_id_fs_new = $data_flat_vacancy_zone_wise_fs_new2->flat_id; //die($flat_id_fs_new);
					}
				}
				
			}
			
		    
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
			->condition('flat_id', $flat_id_fs_new)
			->execute();
			
			$allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
			$data_process_no = $allotment_process_no->fetchObject();
			
			$allotment_ins_arr = array();
			$allotment_ins_arr['online_application_id']  = $data->online_application_id;
			$allotment_ins_arr['flat_id']  = $flat_id_fs_new;
			$allotment_ins_arr['allotment_no'] = 'NAL-'.$data->online_application_id.'-'.date("dmY");
			$allotment_ins_arr['allotment_process_no'] = $data_process_no->allotment_process_no;
			$allotment_ins_arr['roaster_vacancy_position'] = NULL;
			$allotment_ins_arr['allotment_reason'] = $data->allotment_category;
			$allotment_ins_arr['allowed_for_floor_shifting'] = 'N';
		
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
//end of floor shifting process
	
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