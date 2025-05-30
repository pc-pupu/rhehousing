<?php
function _reload_rhe_list($form, &$form_state) {

	$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	$rhe_list = fetch_RHE_rst_pay_band($pay_band_id);
	$commands = array();
	$form['allotment_info']['estate_name']['#options'] = $rhe_list;
	
	$commands[] = ajax_command_replace('#estate_list', drupal_render($form['allotment_info']['estate_name']));
	return array('#type' => 'ajax', '#commands' => $commands);
 
}
function _reload_flat_list($form, &$form_state) {

	$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	$estate_id = isset($form_state['values']['estate_name']) && !empty($form_state['values']['estate_name']) ? $form_state['values']['estate_name'] : 0;
	$flat_list = fetch_flat_rst_estate_pay_band($pay_band_id, $estate_id);
	$commands = array();
	$form['allotment_info']['flat_name']['#options'] = $flat_list;
	
	$commands[] = ajax_command_replace('#flat_list', drupal_render($form['allotment_info']['flat_name']));
	return array('#type' => 'ajax', '#commands' => $commands);
 
}
function fetch_RHE_rst_pay_band($pay_band_id = 0){
	
	$query = db_select('housing_pay_band', 'hpb');
	$query->innerJoin('housing_flat_type', 'hft',
	'hft.flat_type_id = hpb.flat_type_id');
	$query->innerJoin('housing_flat', 'hf',
	'hf.flat_type_id = hpb.flat_type_id');
	$query->innerJoin('housing_flat_status', 'hfs',
	'hf.flat_status_id = hfs.flat_status_id');
	$query->innerJoin('housing_estate', 'he',
	'hf.estate_id = he.estate_id');
	$query->addField('he', 'estate_id');
	$query->addField('he', 'estate_name');
	$db_and = db_and();
	$db_and->condition('hpb.pay_band_id', $pay_band_id, '=');
	$db_and->condition('hfs.is_occupied', FALSE, '=');
	$query->condition($db_and);
	$result = $query->execute();
	$rhe_options = array(''=>'- Select -');
	foreach($result as $val) {
		$rhe_options[$val->estate_id] = $val->estate_name;
	}
	return $rhe_options;
}

function fetch_flat_rst_estate_pay_band($pay_band_id = 0, $estate_id = 0){
	
	$query = db_select('housing_pay_band', 'hpb');
	$query->innerJoin('housing_flat_type', 'hft',
	'hft.flat_type_id = hpb.flat_type_id');
	$query->innerJoin('housing_flat', 'hf',
	'hf.flat_type_id = hpb.flat_type_id');
	$query->innerJoin('housing_flat_status', 'hfs',
	'hf.flat_status_id = hfs.flat_status_id');
	$query->addField('hf', 'flat_id');
	$query->addField('hf', 'flat_no');
	$db_and = db_and();
	$db_and->condition('hpb.pay_band_id', $pay_band_id, '=');
	$db_and->condition('hf.estate_id', $estate_id, '=');
	$db_and->condition('hfs.is_occupied', FALSE, '=');
	$query->condition($db_and);
	$result = $query->execute();
	$flat_options = array(''=>'- Select -');
	foreach($result as $val) {
		$flat_options[$val->flat_id] = $val->flat_no;
	}
	return $flat_options;
}
 function rhe_eoccupant_list($online_application_id = 0) {

	$query = db_select('housing_flat_occupant', 'hfo');
	$query->innerJoin('housing_online_application', 'hoa',
		'hoa.online_application_id = hfo.online_application_id');
	$query->innerJoin('housing_applicant_official_detail', 'haod',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');	
	$query->innerJoin('housing_applicant', 'ha',
		'ha.uid = haod.uid');
	$query->innerJoin('users', 'u',
		'ha.uid = u.uid');	
	$query->innerJoin('housing_ddo', 'hd',
		'haod.ddo_id = hd.ddo_id');	
	$query->innerJoin('housing_pay_band', 'hpb',
		'haod.pay_band_id = hpb.pay_band_id');
	$query->leftJoin('housing_occupant_license', 'hol',
		'hol.flat_occupant_id = hfo.flat_occupant_id');
	$query->innerJoin('housing_flat', 'hf',
		'hfo.flat_id = hf.flat_id');
	$query->innerJoin('housing_estate', 'he',
		'hf.estate_id = he.estate_id');
	$query->innerJoin('housing_flat_type', 'hft',
		'hf.flat_type_id = hft.flat_type_id');
	$query->addField('hfo','online_application_id');
	$query->addField('ha', 'applicant_name');
	$query->addField('ha', 'guardian_name');
	$query->addField('ha', 'date_of_birth');
	$query->addField('ha', 'mobile_no');
	$query->addField('u', 'mail');
	$query->addField('ha', 'gender');
	$query->addField('hd', 'ddo_designation');
	$query->addField('hd', 'ddo_address');
	$query->addField('haod', 'applicant_designation');	
	$query->addField('haod', 'applicant_headquarter');
	$query->addField('haod', 'applicant_posting_place');
	$query->addField('hpb', 'payband');
	$query->addField('hpb', 'scale_from');
	$query->addField('hpb', 'scale_to');
	$query->addField('haod', 'pay_in_the_pay_band');	
	$query->addField('haod', 'grade_pay');
	$query->addField('haod', 'date_of_joining');
	$query->addField('haod', 'date_of_retirement');	
	$query->addField('haod', 'office_name');
	$query->addField('haod', 'office_street');
	$query->addField('haod', 'office_city_town_village');	
	$query->addField('haod', 'office_post_office');
	$query->addField('haod', 'office_pin_code');
	$query->addField('hfo', 'allotment_no');	
	$query->addField('hfo', 'allotment_date','allotment_date');
	$query->addField('hol', 'license_no');
	$query->addField('hol', 'license_issue_date');	
	$query->addField('hol', 'license_expiry_date');
	$query->addField('hf', 'flat_no');
	$query->addField('hft', 'flat_type');
	$query->addField('he', 'estate_name');
	//$query->orderBy('flat_status', 'DESC');
	if($online_application_id != 0){
		$query->condition('hfo.online_application_id',$online_application_id,'=');
	}
	return $query->execute();
	
}

 function rhe_occupant_list($existing_flat_occupant_id = 0) {

	$query = db_select('housing_existing_flat_occupant', 'hefo');
	$query->innerJoin('housing_ddo', 'hd',
		'hefo.ddo_id = hd.ddo_id');
	$query->innerJoin('housing_pay_band', 'hpb',
		'hefo.pay_band_id = hpb.pay_band_id');	
	$query->innerJoin('housing_flat_occupant', 'hfo',
		'hefo.existing_flat_occupant_id = hfo.housing_existing_flat_occupant_id');
	$query->leftJoin('housing_occupant_license', 'hol',
		'hfo.flat_occupant_id = hol.flat_occupant_id');
	$query->innerJoin('housing_flat', 'hf',
		'hfo.flat_id = hf.flat_id');
	$query->innerJoin('housing_estate', 'he',
		'hf.estate_id = he.estate_id');
	$query->innerJoin('housing_flat_type', 'hft',
		'hf.flat_type_id = hft.flat_type_id');
	$query->addField('hefo', 'existing_flat_occupant_id');
	$query->addField('hefo', 'applicant_name');
	$query->addField('hefo', 'guardian_name');
	$query->addField('hefo', 'date_of_birth');
	$query->addField('hefo', 'mobile_no');
	$query->addField('hefo', 'mail');
	$query->addField('hefo', 'gender');
	$query->addField('hd', 'ddo_designation');
	$query->addField('hd', 'ddo_address');
	$query->addField('hefo', 'applicant_designation');	
	$query->addField('hefo', 'applicant_headquarter');
	$query->addField('hefo', 'applicant_posting_place');
	$query->addField('hpb', 'payband');
	$query->addField('hpb', 'scale_from');
	$query->addField('hpb', 'scale_to');
	$query->addField('hefo', 'pay_in_the_pay_band');	
	$query->addField('hefo', 'grade_pay');
	$query->addField('hefo', 'date_of_joining');
	$query->addField('hefo', 'date_of_retirement');	
	$query->addField('hefo', 'office_name');
	$query->addField('hefo', 'office_street');
	$query->addField('hefo', 'office_city_town_village');	
	$query->addField('hefo', 'office_post_office');
	$query->addField('hefo', 'office_pin_code');
	$query->addField('hfo', 'allotment_no');	
	$query->addField('hfo', 'allotment_date','allotment_date');
	$query->addField('hol', 'license_no');
	$query->addField('hol', 'license_issue_date');	
	$query->addField('hol', 'license_expiry_date');
	$query->addField('hf', 'flat_no');
	$query->addField('hft', 'flat_type');
	$query->addField('he', 'estate_name');
	//$query->orderBy('flat_status', 'DESC');
	if($existing_flat_occupant_id != 0){
		$query->condition('hefo.existing_flat_occupant_id',$existing_flat_occupant_id,'=');
		$query->orderBy('hefo.existing_flat_occupant_id', 'ASC');
	}
	$query->orderBy('hefo.existing_flat_occupant_id', 'ASC');
	return $query->execute();
 }

 function fetch_occupant_id($flat_id = 0) {
		$query = db_select('housing_flat_occupant', 'hfo');
		$query->addField('hfo','housing_existing_flat_occupant_id');
		$query->addField('hfo','online_application_id');
		$query->condition('hfo.flat_id', $flat_id, '=');
		$result =$query->execute();
		$data = $result->fetchObject();
		if($data->housing_existing_flat_occupant_id != NULL)
			return $data->housing_existing_flat_occupant_id;
		else
			return $data->online_application_id;
 }