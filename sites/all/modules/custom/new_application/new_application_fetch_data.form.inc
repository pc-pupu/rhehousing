<?php
/*fetch new application status*/
function fetch_new_app_status($status){
	 	global $user;
	 	$query = db_select('housing_new_allotment_application', 'hna');
		$query->fields('hoa', array('status','online_application_id'));
		$query->join('housing_online_application', 'hoa', 'hna.online_application_id = hoa.online_application_id');
		$query->innerJoin('housing_applicant_official_detail', 'haod',
		'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
		$db_and = db_and();
		$db_and->condition('hoa.online_application_id', max_new_allotment_application_id($status),'=');
		$db_and->condition('haod.uid', $user->uid, '=');
		$query->condition($db_and);
		
		return $query->execute();
}

/* fetch application detail*/
 function fetch_application_data(&$form){
	//echo '3rd';die;
	 $online_application_id = max_new_allotment_application_id(array('reject','cancel'));
	 $form['prrsonal_info']['online_new_app_id']['#default_value'] = trim($online_application_id);
	 if($online_application_id == 0){
		 $online_application_id = max_online_application_id(array('reject','cancel'));
		 if($online_application_id == 0){
		 	display_applicant_official_info_first_time($form);
		 }
	 }
	 else{
	 	$query = db_select('housing_new_allotment_application', 'hnaa');
		$query->leftJoin('file_managed', 'fm', 'fm.fid = hnaa.document');
		$query->addField('hnaa', 'allotment_category');
		$query->addField('hnaa', 'flat_type_id');
		/*$query->addField('hna', 'estate_id_choice1');
		$query->addField('hna', 'estate_id_choice2');
		$query->addField('hna', 'estate_id_choice3');
		$query->addField('hna', 'estate_id_choice4');*/
		$query->addField('hnaa', 'document');
		$query->addField('hnaa', 'scaned_sign');
		$query->addField('hnaa', 'extra_doc');
		//$query->addField('hnaa', 'is_pp_sww_ph');
		$query->addField('fm', 'uri');
		$query->condition('online_application_id', trim($online_application_id), '=');
		$result = $query->execute();
		//echo "<pre>";print_r($result);exit;
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$rhe_flat_type = fetch_rhe_flat_name_rst_id($data->flat_type_id);
			$form['document_upload']['file']['#default_value'] = trim($data->document);
			$form['document_upload']['scaned_sign']['#default_value'] = trim($data->scaned_sign);
			
			/*if(!empty($data->is_pp_sww_ph)) {
				$form['document_upload']['chk_extra_doc']['#default_value'] = array($data->is_pp_sww_ph);
			}*/
			
			$form['allotment_reason']['rhe_flat_type']['#default_value'] = trim($rhe_flat_type);
			$form['allotment_reason']['reason']['#options'] = allotment_category_list(trim($rhe_flat_type));
			$form['allotment_reason']['reason']['#default_value'] = trim($data->allotment_category);
			
			if(trim($data->allotment_category) == 'Transfer' || trim($data->allotment_category) == 'Physically Handicapped Or Serious Illness' || trim($data->allotment_category) == 'Officer on Transfer having earmarked Bungalow or Quater in their immediate previous posting') {
				$form['document_upload']['extra_doc']['#default_value'] = trim($data->extra_doc);		
			}
			
			/*$estate = array();
			$estate[0] = 0;
			$form['define_allotment']['choice_1']['#options'] = allotment_choice_list($rhe_flat_type , $estate);
			$form['define_allotment']['choice_1']['#default_value'] = trim($data->estate_id_choice1);
			$estate[1] = $data->estate_id_choice1;
			$form['define_allotment']['choice_2']['#options'] = allotment_choice_list($rhe_flat_type , $estate);
			$form['define_allotment']['choice_2']['#default_value'] = trim($data->estate_id_choice2);
			$estate[2] = $data->estate_id_choice2;
			$form['define_allotment']['choice_3']['#options'] = allotment_choice_list($rhe_flat_type , $estate);
			$form['define_allotment']['choice_3']['#default_value'] = trim($data->estate_id_choice3);
			$estate[3] = $data->estate_id_choice3;
			$form['define_allotment']['choice_4']['#options'] = allotment_choice_list($rhe_flat_type , $estate);
			$form['define_allotment']['choice_4']['#default_value'] = trim($data->estate_id_choice4);*/
		}
	 }
	 if($online_application_id != 0) {
	 	fetch_applicant_official_info($form,$online_application_id);
	 }
	return $form;
	   	
   }
 
   /*fetch max online application id respective to new allotment application, with not rejected or canceled application*/
   function max_new_allotment_application_id($status){
	  
	   	global $user;
		
		
		 /*echo '<pre>';
	   print_r($status); 
	   echo '<br />';
	   print_r('hello'.$user->uid);
	    echo '<br />';*/
		
		
   		$query = db_select('housing_applicant_official_detail', 'haod');
		$query->innerJoin('housing_online_application', 'hoa',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->innerJoin('housing_new_allotment_application', 'hna',
		'hoa.online_application_id = hna.online_application_id');
		$query->addExpression('COALESCE(MAX(hoa.online_application_id),0)','id');
		$db_and = db_and();
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('hoa.status', $status, 'NOT IN');
		$query->condition($db_and);
		$result = $query->execute();
		$id = 0; 
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$id = $data->id;
		} 
		return $id; 
   }

   
/************************************************ AJAX **************************************************************/

/*reload Allotment Category and Choice 1 (Ajax Call)*/
function _reload_allotment_category($form, &$form_state) {

	$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	$rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
	
	if($rhe_flat_type != ''){
		$form['allotment_reason']['rhe_flat_type']['#value'] = trim($rhe_flat_type);
		$form['allotment_reason']['reason']['#options'] = allotment_category_list(trim($rhe_flat_type));
		//$estate = array(0);
		//$form['define_allotment']['choice_1']['#options'] = allotment_choice_list($rhe_flat_type,$estate);
	}
	else{
		$form['allotment_reason']['rhe_flat_type']['#value'] = '';
		$form['allotment_reason']['reason']['#options'] = array(''=>'- Select -');
		//$form['define_allotment']['choice_1']['#options'] = array(''=>'- Select -');
	}
	
	$commands = array();
	/*$form['define_allotment']['choice_2']['#options'] = array(''=>'- Select -');
	$form['define_allotment']['choice_3']['#options'] = array(''=>'- Select -');
	$form['define_allotment']['choice_4']['#options'] = array(''=>'- Select -');*/
	$commands[] = ajax_command_replace('#replace_rhe_flat_type', drupal_render($form['allotment_reason']['rhe_flat_type']));
	$commands[] = ajax_command_replace('#replace_allotment_category', drupal_render($form['allotment_reason']['reason']));
	/*$commands[] = ajax_command_replace('#replace_choice1', drupal_render($form['define_allotment']['choice_1']));
	$commands[] = ajax_command_replace('#replace_choice2', drupal_render($form['define_allotment']['choice_2']));
	$commands[] = ajax_command_replace('#replace_choice3', drupal_render($form['define_allotment']['choice_3']));
	$commands[] = ajax_command_replace('#replace_choice4', drupal_render($form['define_allotment']['choice_4']));*/
	return array('#type' => 'ajax', '#commands' => $commands);
}

/*function _reload_upload_document($form, &$form_state) {
	$commands[] = array();
	$commands[] = ajax_command_replace('#extra_doc', drupal_render($form['document_upload']['extra_doc']));
	return array('#type' => 'ajax', '#commands' => $commands);
 
}*/

/*fetch Housing Allotment Choice  list based on RHE flat type*/
/*function allotment_choice_list($rhe_flat_type = '', $estate) {
	
	$allotment_choice1_options = array('' => '-- Choose Housing --');
		
	$query = db_select('housing_estate', 'he');
	$query->innerJoin('housing_flat', 'hf',
	'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_flat_type', 'hft',
	'hft.flat_type_id = hf.flat_type_id');
	$query->innerJoin('housing_flat_status', 'hfs',
	'hfs.flat_status_id = hf.flat_status_id');
	$query->addField('he', 'estate_id');
	$query->addField('he', 'district_code');
	$query->addField('he', 'estate_type_id');
	$query->addField('he', 'estate_name');
	$query->addField('he', 'estate_address');
	$db_and = db_and();
	$db_and->condition('hfs.availability', TRUE, '=');
	$db_and->condition('he.estate_id', $estate, 'NOT IN');
	$db_and->condition('hft.flat_type', $rhe_flat_type, '=');
	$query->condition($db_and);
	$result = $query->execute();
	$i = 0;
	foreach($result as $val) {
		$i++;
		$allotment_choice1_options[$val->estate_id] = $val->estate_name;
	}
	if($i == 0){
		$allotment_choice1_options = array(''=>'- Select -');
	}
	
	return $allotment_choice1_options;
}*/

/*reload Choice 2 (Ajax Call)*/
/*function _reload_choice2($form, &$form_state) {

	$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	$rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
	$choice1 = isset($form_state['values']['choice_1']) && !empty($form_state['values']['choice_1']) ? $form_state['values']['choice_1'] : 0;
	$estate = array($choice1);
	$commands = array();
	if($rhe_flat_type!=''){
		$form['define_allotment']['choice_2']['#options'] = allotment_choice_list($rhe_flat_type,$estate);
	}else{
		$form['define_allotment']['choice_2']['#options'] = array(''=>'- Select -');
	}
	$form['define_allotment']['choice_3']['#options'] = array(''=>'- Select -');
	$form['define_allotment']['choice_4']['#options'] = array(''=>'- Select -');
	$commands[] = ajax_command_replace('#replace_choice2', drupal_render($form['define_allotment']['choice_2']));
	$commands[] = ajax_command_replace('#replace_choice3', drupal_render($form['define_allotment']['choice_3']));
	$commands[] = ajax_command_replace('#replace_choice4', drupal_render($form['define_allotment']['choice_4']));
	return array('#type' => 'ajax', '#commands' => $commands);
 
}*/
/*reload Choice 3 (Ajax Call)*/
/*function _reload_choice3($form, &$form_state) {

	$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	$rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
	$choice1 = isset($form_state['values']['choice_1']) && !empty($form_state['values']['choice_1']) ? $form_state['values']['choice_1'] : 0;
	$choice2 = isset($form_state['values']['choice_2']) && !empty($form_state['values']['choice_2']) ? $form_state['values']['choice_2'] : 0;
	$estate = array($choice1,$choice2);
	$commands = array();
	if($rhe_flat_type!=''){
		$form['define_allotment']['choice_3']['#options'] = allotment_choice_list($rhe_flat_type,$estate);
	}else{
		$form['define_allotment']['choice_3']['#options'] = array(''=>'- Select -');
	}
	$form['define_allotment']['choice_4']['#options'] = array(''=>'- Select -');
	$commands[] = ajax_command_replace('#replace_choice3', drupal_render($form['define_allotment']['choice_3']));
	$commands[] = ajax_command_replace('#replace_choice4', drupal_render($form['define_allotment']['choice_4']));
	return array('#type' => 'ajax', '#commands' => $commands);
 
}*/

/*reload Choice 4 (Ajax Call)*/
/*function _reload_choice4($form, &$form_state) {

	$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	$rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
	$choice1 = isset($form_state['values']['choice_1']) && !empty($form_state['values']['choice_1']) ? $form_state['values']['choice_1'] : 0;
	$choice2 = isset($form_state['values']['choice_2']) && !empty($form_state['values']['choice_2']) ? $form_state['values']['choice_2'] : 0;
	$choice3 = isset($form_state['values']['choice_3']) && !empty($form_state['values']['choice_3']) ? $form_state['values']['choice_3'] : 0;
	$estate = array($choice1,$choice2,$choice3);
	$commands = array();
	if($rhe_flat_type!=''){
		$form['define_allotment']['choice_4']['#options'] = allotment_choice_list($rhe_flat_type,$estate);
	}else{
		$form['define_allotment']['choice_4']['#options'] = array(''=>'- Select -');
	}
	$commands[] = ajax_command_replace('#replace_choice4', drupal_render($form['define_allotment']['choice_4']));
	return array('#type' => 'ajax', '#commands' => $commands);
 
}*/
/*-------END---------*/

