<?php
/*fetch cs license application status*/
function fetch_cs_licence_app_status($status){
		global $user;
	 	$query = db_select('housing_license_application', 'hla');
		$query->join('housing_online_application', 'hoa', 'hla.online_application_id = hoa.online_application_id');
		$query->innerJoin('housing_applicant_official_detail', 'haod',
		'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
		$db_and = db_and();
		$query->addField('hoa', 'status');
		$query->addField('hoa', 'online_application_id');
		$db_and->condition('hoa.online_application_id', max_cs_licence_application_id($status),'=');
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('hla.type_of_application', 'cs', '=');
		$query->condition($db_and);
		return $query->execute();
}
/* fetch allotment detail*/
 function fetch_cs_allotment_detail(&$form){
	 $online_application_id = max_cs_licence_application_id(array('reject','cancel'));
	 
	 $form['prrsonal_info']['online_cs_licence_id']['#default_value'] = trim($online_application_id);
	 if($online_application_id == 0){
		$online_application_id = max_cs_online_application_id(array('reject','cancel'));
		if($online_application_id == 0){
			display_applicant_official_info_first_time($form);
		}
		
		$result = fetch_cs_flat_occupant_detail_old($online_application_id);
		if($result->rowcount() > 0) {
			$data = $result->fetchObject();
			
			$form['allotment_info']['allotment_no']['#default_value'] = trim($data->allotment_no);
			$form['allotment_info']['allotment_date']['#default_value'] = trim( implode('/', array_reverse(explode('-', $data->allotment_date))));
			$form['allotment_info']['allotment_district']['#default_value'] = trim($data->district_name);
			$form['allotment_info']['allotment_estate']['#default_value'] = trim($data->estate_name);
			//$form['allotment_info']['allotment_flat']['#default_value'] = trim($data->flat_no);
			$form['allotment_info']['allotment_address']['#default_value'] = trim($data->estate_address);
			
			$form['allotment_info']['allotment_flat_id']['#default_value'] = trim($data->flat_id);
			
		}
	 }
	 else {
		$result = fetch_cs_flat_occupant_detail($online_application_id);
		if($result->rowcount() > 0) {
			$data = $result->fetchObject();
			
			$form['document_upload']['file']['#default_value'] = trim($data->document);
			$form['allotment_info']['allotment_no']['#default_value'] = trim($data->allotment_no);
			$form['allotment_info']['allotment_date']['#default_value'] = trim( implode('/', array_reverse(explode('-', $data->allotment_date))));
			$form['allotment_info']['allotment_district']['#default_value'] = trim($data->district_name);
			$form['allotment_info']['allotment_estate']['#default_value'] = trim($data->estate_name);
			//$form['allotment_info']['allotment_flat']['#default_value'] = trim($data->flat_no);
			$form['allotment_info']['allotment_address']['#default_value'] = trim($data->estate_address);
			
			$form['allotment_info']['allotment_flat_id']['#default_value'] = trim($data->allotment_flat_id);
			
		}
	 }
	 
	 if($online_application_id != 0)
	 	fetch_applicant_official_info($form,$online_application_id);
	
	return $form;
	   	
   }
   
   /*fetch flat_occupant old details before licence apply*/
   function fetch_cs_flat_occupant_detail_old($online_application_id = ''){
		global $user;
		$query = db_select('housing_applicant_official_detail', 'haod');
		$query->innerJoin('housing_online_application', 'hoa',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->innerJoin('housing_flat_occupant', 'hfo', 
		'hfo.online_application_id = hoa.online_application_id');
		$query->innerJoin('housing_flat', 'hf', 
		'hf.flat_id = hfo.flat_id');
		$query->innerJoin('housing_estate', 'he', 
		'hf.estate_id = he.estate_id');
		$query->innerJoin('housing_flat_type', 'hft', 
		'hf.flat_type_id = hft.flat_type_id');
		$query->innerJoin('housing_district', 'hd', 
		'he.district_code = hd.district_code');
		$query->addField('hoa', 'online_application_id');
		$query->addField('hfo', 'flat_occupant_id');
		$query->addField('hfo', 'flat_id');
		$query->addField('hfo', 'allotment_no');
		$query->addField('hfo', 'allotment_date');
		$query->addField('hf', 'flat_no');
		$query->addField('hft', 'flat_type');
		$query->addField('he', 'estate_name');
		$query->addField('he', 'estate_address');
		$query->addField('hd', 'district_name');
		$db_and = db_and();
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('hoa.online_application_id', $online_application_id, '=');
		$db_and->condition('hfo.accept_reject_status', 'Accept', '=');
		$query->condition($db_and);
		
		//echo $query;
		return $query->execute();
	
   }
   
   /* fetch flat_occupant detail*/
 	function fetch_cs_flat_occupant_detail($online_application_id = ''){
		global $user;
		$query = db_select('housing_applicant_official_detail', 'haod');
		$query->innerJoin('housing_online_application', 'hoa',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->innerJoin('housing_license_application', 'hla', 
		'hla.online_application_id = hoa.online_application_id');
		$query->leftJoin('file_managed', 'fm', 'fm.fid = hla.document');
		$query->innerJoin('housing_flat', 'hf', 
		'hf.flat_id = hla.allotment_flat_id');
		$query->innerJoin('housing_estate', 'he', 
		'hf.estate_id = he.estate_id');
		$query->innerJoin('housing_flat_type', 'hft', 
		'hf.flat_type_id = hft.flat_type_id');
		$query->innerJoin('housing_district', 'hd', 
		'he.district_code = hd.district_code');
		$query->addField('hoa', 'online_application_id');
		$query->addField('hla', 'allotment_flat_id');
		$query->addField('hla', 'allotment_no');
		$query->addField('hla', 'allotment_date');
		$query->addField('hft', 'flat_type');
		$query->addField('hd', 'district_name');
		$query->addField('he', 'estate_name');
		$query->addField('he', 'estate_address');
		$query->addField('hla', 'document');
		$query->addField('fm', 'uri');
		$db_and = db_and();
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('hoa.online_application_id', $online_application_id, '=');
		$query->condition($db_and);
		
		//echo $query;
		return $query->execute();
	
   }
 
   /*fetch max online application id respective to new allotment application, with not rejected or canceled application*/
   function max_cs_licence_application_id($status){
	   	global $user;
   		$query = db_select('housing_applicant_official_detail', 'haod');
		$query->innerJoin('housing_online_application', 'hoa',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->innerJoin('housing_license_application', 'hla',
		'hoa.online_application_id = hla.online_application_id');
		$query->addExpression('COALESCE(MAX(hoa.online_application_id),0)','id');
		$db_and = db_and();
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('hla.type_of_application', 'cs', '=');
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
   
   /*fetch max cs online application id, with not rejected or canceled application*/
   function max_cs_online_application_id($status){
	   	global $user;
		
		//$status = "'" . implode("','", $status) . "'";
   		/*$query = db_select('housing_applicant_official_detail', 'haod');
		$query->innerJoin('housing_online_application', 'hoa',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->addExpression('COALESCE(MAX(hoa.online_application_id),0)', 'id');
		$db_and = db_and();
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('hoa.status', $status, 'NOT IN');
		$db_and->condition('SUBSTRING(hoa.application_no, 1, 2)', 'CS', '=');
		$query->condition($db_and);
		$result = $query->execute();*/
		
		$result = db_query("SELECT COALESCE(MAX(hoa.online_application_id),0) AS id
								FROM {housing_applicant_official_detail} haod 
								INNER JOIN {housing_online_application} hoa 
								ON hoa.applicant_official_detail_id = haod.applicant_official_detail_id 
								WHERE haod.uid = :uid AND hoa.status NOT IN (:status) 
								AND substr(hoa.application_no, 1, 2) = :app_no", 
								array(':uid' => $user->uid, ':status' => $status, ':app_no' => 'CS'));
		
		$id = 0; 
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$id = $data->id;
		}
		return $id;
   }
	
