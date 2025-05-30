<?php
	function fetch_vs_app_status($status){
	 	global $user;
	 	$query = db_select('housing_vs_application', 'hva');
		$query->fields('hoa', array('status','online_application_id'));
		$query->join('housing_online_application', 'hoa', 'hva.online_application_id = hoa.online_application_id');
		$query->innerJoin('housing_applicant_official_detail', 'haod',
		'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
		$db_and = db_and();
		$db_and->condition('hoa.online_application_id', max_vs_application_id($status),'=');
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('haod.is_active', '1', '=');   ///added by debaleena 27-1-2024
		$query->condition($db_and);
		// echo $query;die;
		return $query->execute();
	}

/* fetch application detail*/
 function fetch_vs_data(&$form){

	 $online_application_id = max_vs_application_id(array('reject','cancel'));
	 $form['prrsonal_info']['online_vs_id']['#default_value'] = trim($online_application_id);
	 if($online_application_id == 0){
		$online_application_id = max_online_application_id(array('reject','cancel'));
		if($online_application_id == 0){
			display_applicant_official_info_first_time($form);
		}
	 }
	 else{
	 	$query = db_select('housing_vs_application', 'hva');
		$query->fields('hva');
		$query->condition('online_application_id', trim($online_application_id), '=');
		$result = $query->execute();
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			
			$form['current_occupation']['occupation_estate']['#default_value'] = trim($data->occupation_estate);
			$form['current_occupation']['occupation_block']['#default_value'] = trim($data->occupation_block);
			$form['current_occupation']['occupation_flat']['#default_value'] = trim($data->occupation_flat);
			
			
			$form['current_occupation']['possession_date']['#default_value'] = trim( implode('/', array_reverse(explode('-', $data->possession_date))));
			$form['current_occupation']['file_licence']['#default_value'] = trim($data->file_licence);
			
		}
	 }
	 
		
	/*$result1 = ();
	if($result1->rowcount() > 0) {
		$data1 = $result1->fetchObject();
		
		$form['current_occupation']['occupation_district']['#default_value'] = trim($data1->district_name);
		//$form['current_occupation']['occupation_estate']['#default_value'] = trim($data1->estate_name);
		$form['current_occupation']['occupation_address']['#default_value'] = trim($data1->estate_address);
		//$form['current_occupation']['occupation_flat']['#default_value'] = trim($data1->flat_no);
		
		$form['current_occupation']['flat_occupant_id']['#default_value'] = trim($data1->flat_occupant_id);
		
	}*/
	
	// debaleena 14-06-2024 turned off
	/*if($online_application_id != 0) {
	 	fetch_applicant_official_info($form,$online_application_id, 'vs');
	}*/
	
	return $form;
 }
 
 function fetch_vs_data1(&$form){
	 $online_application_id = max_vs_application_id(array('reject','cancel'));
	 $form['prrsonal_info']['online_vs_id']['#default_value'] = trim($online_application_id);
	 if($online_application_id == 0){
		 $online_application_id = max_online_application_id(array('reject','cancel'));
	 }
	 else{
	 	$query = db_select('housing_vs_application', 'hva');
		$query->fields('hva');
		$query->condition('online_application_id', trim($online_application_id), '=');
		$result = $query->execute();
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			
			$form['current_occupation']['occupation_estate']['#default_value'] = trim($data->occupation_estate);
			$form['current_occupation']['occupation_block']['#default_value'] = trim($data->occupation_block);
			$form['current_occupation']['occupation_flat']['#default_value'] = trim($data->occupation_flat);
			
			
			$form['current_occupation']['possession_date']['#default_value'] = trim( implode('/', array_reverse(explode('-', $data->possession_date))));
			$form['current_occupation']['file_licence']['#default_value'] = trim($data->file_licence);
			
		}
	 }
	
	return $form;
 }
//end
 
   /*fetch max online application id respective to new allotment application, with not rejected or canceled application*/
   function max_vs_application_id($status){
	   	global $user;
   		$query = db_select('housing_applicant_official_detail', 'haod');
		$query->innerJoin('housing_online_application', 'hoa',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->innerJoin('housing_vs_application', 'hva',
		'hoa.online_application_id = hva.online_application_id');
		$query->addExpression('COALESCE(MAX(hoa.online_application_id),0)','id');
		$db_and = db_and();
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('hoa.status', $status, 'NOT IN');
		$query->condition($db_and);
		//echo $query;
		$result = $query->execute();
		$id = 0; 
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$id = $data->id;
		}
		return $id;
   }






