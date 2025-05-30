<?php

/*fetch max online application id, with not rejected or canceled application*/
function redir( $checkingUrl = '', $Entity = '', $db_and = '', $online_application_id = 0){
	
		global $user;
		$query = db_select($Entity, 'alias');
		$query->fields('hoa', array('status'));
		$query->innerJoin('housing_online_application', 'hoa', 'alias.online_application_id = hoa.online_application_id');
		$query->innerJoin('housing_applicant_official_detail', 'haod',
		'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
		
		$db_and->condition('hoa.online_application_id', $online_application_id,'=');
		$db_and->condition('haod.uid', $user->uid, '=');
		$query->condition($db_and);
		
		$result = $query->execute();
		$row_count = $result->rowCount();
		if($row_count > 0) {
			$data = $result->fetchObject();
			global $custom_url;
			if($_SERVER['REQUEST_URI'] == $custom_url.'/'.$checkingUrl && $data->status != 'draft') 
			drupal_goto('application-status/'.$data->status);
		}
}
/* fetch pay band*/ 
 function pay_band_list() {
	
	$pay_band_options = array(''=>'- Select -');
	$query = db_select('housing_pay_band_categories', 'hpb')->fields('hpb')->orderBy('pay_band_id', 'ASC');
	$result = $query->execute();
	foreach($result as $val) {

		if($val->scale_from == 0 && $val->scale_to != 0) {
			$str = '(Up to Rs'.$val->scale_to.'/-)';
		}else if($val->scale_from != 0 && $val->scale_to != 0)
		{
			$str = '(Rs.'.$val->scale_from.'/ Up to Rs. '.$val->scale_to.'/-)';
		}else{
			$str = '(Rs '.$val->scale_from.'/- and above)';
		}
		$pay_band_options[$val->pay_band_id] = $str;
	}
	
	return $pay_band_options;
}
/* fetch rhe flat_type corresponding to payband*/
  function rhe_flat_type_rst_pay_band_id($pay_band_id) {

	$query = db_select('housing_pay_band', 'hpb');
	$query->innerJoin('housing_flat_type', 'hft',
	'hft.flat_type_id = hpb.flat_type_id');
	$query->addField('hft', 'flat_type');
	$query->condition('hpb.pay_band_id', $pay_band_id, '=');
	$result = $query->execute();
	$str = '';
	if($result->rowcount() > 0){
		$data = $result->fetchObject();
		$str = $data->flat_type;
	}
	return $str;
	
	
	
	
}
/*fetch Allotment Category list based on RHE flat type*/
function allotment_category_list($rhe_flat_type = '') {
	$rhe_flat_type = trim($rhe_flat_type);
	
	$i = 0;
	$allotment_reason_options = array('' => '--Choose Allotment Reason--');
	if(!empty($rhe_flat_type)) {
		if($rhe_flat_type == 'A+') {
			$query = db_select('housing_roasterAplus_master', 'hrm');
		}
		else if($rhe_flat_type == 'A' || $rhe_flat_type == 'B') {
			$query = db_select('housing_roaster4ab_master', 'hrm');
		}
		else {
			$query = db_select('housing_roaster4cd_master', 'hrm');
		}
	$query->fields('hrm', array('category'));
	$query->groupBy('category');
	$result = $query->execute();
	
	foreach($result as $val) {
		$i++;
		$allotment_reason_options[$val->category] = $val->category;
	}
	}
	if($i == 0){
		$allotment_reason_options = array(''=>'- Select -');
	}
	
	return $allotment_reason_options;
}
/*fetch all RHE flat type list*/
  function rhe_flat_type_list() {

	$rhe_flat_type_options = array(''=>'- Select -');
	$query = db_select('housing_flat_type', 'hft')->fields('hft')->orderBy('hft.flat_type', 'DESC');
	$result = $query->execute();
	foreach($result as $val) {
		$rhe_flat_type_options[$val->flat_type] = $val->flat_type;
	}
	
	return $rhe_flat_type_options;
}
/*fetch RHE flat id*/
  function fetch_rhe_flat_id($flat_type) {
	  

		$query = db_select('housing_flat_type', 'hft');
		$query->addField('hft', 'flat_type_id','id');
		$query->condition('flat_type', trim($flat_type), '=');
		$result = $query->execute();
		$id = 0; 
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$id = $data->id;
		}
		return $id;
	}
	
/*fetch RHE flat type respect to flat_type_id*/
	function fetch_rhe_flat_type($flat_type_id) {

		$query = db_select('housing_flat_type', 'hft');
		$query->addField('hft', 'flat_type');
		$query->condition('flat_type_id', trim($flat_type_id), '=');
		$result = $query->execute();
		
		return $result;
	}
	
/*fetch RHE flat name respective to id*/
  function fetch_rhe_flat_name_rst_id($flat_type_id) {

		$query = db_select('housing_flat_type', 'hft');
		$query->addField('hft', 'flat_type');
		$query->condition('flat_type_id', trim($flat_type_id), '=');
		$flat_type = ''; 
		$result = $query->execute();
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$flat_type = $data->flat_type;
		}
		return $flat_type;
	}
/* fetch all district*/
  function district_list() {
	
	
	$dist_options = array(''=>'- Select -');
	$query = db_select('housing_district', 'hd');
	$query->addExpression('trim(hd.district_name)','district_name');
	$query->addField('hd','district_code');
	$query->orderBy('district_name', 'ASC');
	$result = $query->execute();
	
	foreach($result as $val) {
		$dist_options[$val->district_code] = $val->district_name;
	}
	
	return $dist_options;
}

/* fetch particular district*/
	function particular_district_list($dist_code = '') {
		$query = db_select('housing_district', 'hdist');
		$query->addField('hdist', 'district_name');
		$query->Condition('district_code', $dist_code, '=');
		return $query->execute();
	}
	
   /*show applicant personal information*/
   function fetch_applicant_personal_info(&$form){
	
		global $user;
		$query1 = db_select('users', 'u');
		$query1->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
		$query1->innerJoin('housing_online_application', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query1->addField('hoa', 'is_backlog_applicant');
		$query1->condition('u.uid', $user->uid, '=');
		$result1 = $query1->execute();
		$data1 = $result1->fetchObject();
	   
	   
		$result = applicant_personal_info(); //echo '<pre>'; print_r($result); die;
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$form['prrsonal_info']['applicant_name']['#default_value'] = strtoupper(trim($data->applicant_name));
			if(trim($data->applicant_name) != '') {
				$form['prrsonal_info']['applicant_name']['#disabled'] = TRUE;
			}

			$form['prrsonal_info']['applicant_father_name']['#default_value'] = (!empty($data->guardian_name)) ? strtoupper(trim($data->guardian_name)) : NULL;
			
		//permanent address
			$form['prrsonal_info']['permanent_address']['permanent_street']['#default_value'] = (!empty($data->permanent_street)) ? strtoupper(trim($data->permanent_street)) : NULL;
			$form['prrsonal_info']['permanent_address']['permanent_city_town_village']['#default_value'] = (!empty($data->permanent_city_town_village)) ? strtoupper(trim($data->permanent_city_town_village)) : NULL;
			$form['prrsonal_info']['permanent_address']['permanent_post_office']['#default_value'] = (!empty($data->permanent_post_office)) ? strtoupper(trim($data->permanent_post_office)) : NULL;
			$form['prrsonal_info']['permanent_address']['permanent_district']['#default_value'] = (!empty($data->permanent_district)) ? trim($data->permanent_district) : NULL;
			$form['prrsonal_info']['permanent_address']['permanent_pincode']['#default_value'] = (!empty($data->permanent_pincode)) ? trim($data->permanent_pincode): NULL;
		//permanent address same as present address
			if(isset($data->permanent_present_same) && !empty($data->permanent_present_same) && trim($data->permanent_present_same) == 1) {
				$form['prrsonal_info']['chk_permanent_address']['#default_value'] = (!empty($data->permanent_present_same)) ? trim($data->permanent_present_same): NULL;		
			} else {
				$form['prrsonal_info']['present_address']['present_street']['#default_value'] = (!empty($data->present_street))? strtoupper(trim($data->present_street)) : NULL;
				$form['prrsonal_info']['present_address']['present_city_town_village']['#default_value'] = (!empty($data->present_city_town_village))? strtoupper(trim($data->present_city_town_village)): NULL;
				$form['prrsonal_info']['present_address']['present_post_office']['#default_value'] = (!empty($data->present_post_office)) ? strtoupper(trim($data->present_post_office)): NULL;
				$form['prrsonal_info']['present_address']['present_district']['#default_value'] = (!empty($data->present_district)) ? trim($data->present_district) : NULL;
				$form['prrsonal_info']['present_address']['present_pincode']['#default_value'] = (!empty($data->present_pincode)) ? trim($data->present_pincode):NULL;	
			}
			
			$form['prrsonal_info']['dob']['#default_value'] = trim( implode('/', array_reverse(explode('-', $data->date_of_birth))));
			if(trim($data->date_of_birth) != '') {
				$form['prrsonal_info']['dob']['#disabled'] = TRUE;
			}
			$form['prrsonal_info']['gender']['#default_value'] = trim($data->gender);
			if(trim($data->gender) != '') {
				$form['prrsonal_info']['gender']['#disabled'] = TRUE;
			}
			$form['prrsonal_info']['mobile']['#default_value'] = trim($data->mobile_no);
			if(trim($data->mobile_no) != '') {
				if(isset($data1->is_backlog_applicant) && $data1->is_backlog_applicant == 1 && current_path() == 'new_license') {
					$form['prrsonal_info']['mobile']['#disabled'] = FALSE;
				} else {
					$form['prrsonal_info']['mobile']['#disabled'] = TRUE;
				}
			}
			$form['prrsonal_info']['email']['#default_value'] = strtolower(trim($data->mail));
			if(trim($data->mail) != '') {
				if(isset($data1->is_backlog_applicant) && $data1->is_backlog_applicant == 1 && current_path() == 'new_license') {
					$form['prrsonal_info']['email']['#disabled'] = FALSE;
				} else {
					$form['prrsonal_info']['email']['#disabled'] = TRUE;
				}
			}
		}
   }
   
   /*fetch applicant personal information*/
   function applicant_personal_info(){
	
	    global $user;
		// echo $user->uid;die;
	    $query = db_select('users', 'u');
		$query->innerJoin('housing_applicant', 'ha', 'u.uid = ha.uid');
		$query->innerJoin('housing_applicant_official_detail', 'haod', 'ha.housing_applicant_id = haod.housing_applicant_id');
		$query->addField('u', 'mail');
		/*$query->addField('ha', 'applicant_name');
		$query->addField('ha', 'guardian_name');
		$query->addField('ha', 'gender');
		$query->addField('ha', 'mobile_no');
		$query->addField('ha', 'date_of_birth');*/
		$query->fields('ha');
		$query->condition('u.uid', $user->uid, '=');
		$query->condition('haod.is_active', 1 , '=');
		// echo $query;die;
		// $result = $query->execute();
		// $result = $result->fetchObject();
		// print_r($result);die;
		return $query->execute();
   }
   
   /*fetch applicant official information 1st time*/
	function fetch_applicant_official_info_first_time() {
		global $user;
		$query = db_select('users', 'u');
		$query->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
		$query->addField('haod', 'applicant_designation');
		$query->addField('haod', 'office_name');
		$query->addField('haod', 'hrms_id');
		$query->condition('u.uid', $user->uid, '=');
		return $query->execute();	   
	}
	function display_applicant_official_info_first_time(&$form){
		$result = fetch_applicant_official_info_first_time();
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$form['official_info']['hrms_id']['#default_value'] = strtoupper(trim($data->hrms_id));
			if(trim($data->hrms_id) != '') {
				$form['official_info']['hrms_id']['#disabled'] = TRUE;	
			}
			$form['official_info']['app_designation']['#default_value'] = strtoupper(trim($data->applicant_designation));
			if(trim($data->applicant_designation) != '') {
				if(current_path() == 'new-apply') {
					$form['official_info']['app_designation']['#disabled'] = TRUE;
				}
			}
			$form['office_add']['office_name']['#default_value'] = strtoupper(trim($data->office_name));
			if(trim($data->office_name) != '') {
				if(current_path() == 'new-apply') {
					$form['office_add']['office_name']['#disabled'] = TRUE;
				}
			}
		}
	}
	//End
   
   /*fetch applicant official information*/
   function fetch_applicant_official_info(&$form,$online_application_id){
		
		global $user;
		$query1 = db_select('users', 'u');
		$query1->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
		$query1->innerJoin('housing_online_application', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		//$query1->addField('haod', 'applicant_designation');
		//$query1->addField('haod', 'office_name');
		$query1->addField('hoa', 'is_backlog_applicant');
		$query1->condition('u.uid', $user->uid, '=');
		$result1 = $query1->execute();
		$data1 = $result1->fetchObject();
		
		
	    $result = fetch_applicant_official_info_rst_to_online_app_id($online_application_id);
   		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$form['official_info']['hrms_id']['#default_value'] = trim($data->hrms_id);
			if(trim($data->hrms_id) != '') {
				if($data1->is_backlog_applicant == 1 && current_path() == 'new_license') {
					$form['official_info']['hrms_id']['#disabled'] = FALSE;
				} else {
					$form['official_info']['hrms_id']['#disabled'] = TRUE;
				}
			}
			$form['official_info']['app_designation']['#default_value'] = strtoupper(trim($data->applicant_designation));
			if(trim($data->applicant_designation) != '') {
				if(current_path() == 'new-apply') {
					$form['official_info']['app_designation']['#disabled'] = TRUE;
				}
			}
			//$form['official_info']['pay_band']['#default_value'] = trim($data->pay_band_id);
			//$form['official_info']['pay_in']['#default_value'] = trim($data->pay_in_the_pay_band);
			$form['official_info']['grade_pay']['#default_value'] = trim($data->grade_pay);
			//$form['official_info']['gpf_no']['#default_value'] = strtoupper(trim($data->gpf_no));
			$form['official_info']['app_posting_place']['#default_value'] = strtoupper(trim($data->applicant_posting_place));
			$form['official_info']['app_headquarter']['#default_value'] = strtoupper(trim($data->applicant_headquarter));
			$form['official_info']['doj']['#default_value'] = trim( implode('/', array_reverse(explode('-', $data->date_of_joining))));
			$form['official_info']['dor']['#default_value'] = trim( implode('/', array_reverse(explode('-', $data->date_of_retirement))));
			
			$form['office_add']['office_name']['#default_value'] = strtoupper(trim($data->office_name));
			if(trim($data->office_name) != '') {
				if(current_path() == 'new-apply') {
					$form['office_add']['office_name']['#disabled'] = TRUE;
				}
			}
			$form['office_add']['office_street']['#default_value'] = strtoupper(trim($data->office_street));
			$form['office_add']['office_city']['#default_value'] = strtoupper(trim($data->office_city_town_village));
			$form['office_add']['office_post_office']['#default_value'] = strtoupper(trim($data->office_post_office));
			$form['office_add']['office_district']['#default_value'] = trim($data->office_district);
			$form['office_add']['office_pincode']['#default_value'] = trim($data->office_pin_code);
			$form['office_add']['office_phone_no']['#default_value'] = trim($data->office_phone_no);
			$form['ddo']['district']['#default_value'] = trim($data->district_code);
			$form['ddo']['designation']['#options'] = ddo_desig_list($data->district_code);
			$form['ddo']['designation']['#default_value'] = trim($data->ddo_id);
			$form['ddo']['address']['#default_value'] = trim($data->ddo_address);
			
		}
   }
    /*fetch applicant official information respective to particular id*/
   function fetch_applicant_official_info_rst_to_online_app_id($online_application_id){
	    $query = db_select('housing_applicant_official_detail', 'haod');
		$query->innerJoin('housing_online_application', 'hoa',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->innerJoin('housing_ddo', 'hd',
		'hd.ddo_id = haod.ddo_id');
		
		$query->addField('hd', 'district_code');
		$query->addField('hd', 'ddo_id');
		$query->addField('hd', 'ddo_address');
		$query->addField('haod', 'applicant_official_detail_id');
		$query->addField('haod', 'applicant_designation');
		$query->addField('haod', 'applicant_headquarter');
		$query->addField('haod', 'applicant_posting_place');
		$query->addField('haod', 'pay_band_id');
		$query->addField('haod', 'pay_in_the_pay_band');
		$query->addField('haod', 'grade_pay');
		$query->addField('haod', 'gpf_no');
		$query->addField('haod', 'date_of_joining');
		$query->addField('haod', 'date_of_retirement');
		$query->addField('haod', 'office_name');
		$query->addField('haod', 'office_street');
		$query->addField('haod', 'office_city_town_village');
		$query->addField('haod', 'office_post_office');
		$query->addField('haod', 'office_pin_code');
		$query->addField('haod', 'hrms_id');
		$query->addField('haod', 'office_district');
		$query->addField('haod', 'office_phone_no');
		$query->condition('hoa.online_application_id', $online_application_id, '=');
		return $query->execute();
   }
   
   /*fetch max online application id, with not rejected or canceled application*/
   function max_online_application_id($status){
	   	global $user;
   		$query = db_select('housing_applicant_official_detail', 'haod');
		$query->innerJoin('housing_online_application', 'hoa',
		'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->addExpression('COALESCE(MAX(hoa.online_application_id),0)','id');
		$db_and = db_and();
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('hoa.status', $status, 'NOT IN');
		// $db_and->condition('haod.is_active', '1', '=');
		$query->condition($db_and);
		$result = $query->execute();
		$id = 0; 
		if($result->rowcount() > 0){
			$data = $result->fetchObject();
			$id = $data->id;
		}
		return $id;
   }
   
  /*function check_applicant_official_detail_data(&$form_state){
		global $user;
	  	//fetching applicant_official_detail_id
		$query = db_select('housing_applicant_official_detail', 'haod');
		$query->addField('haod', 'applicant_official_detail_id','id');
		$db_and = db_and();
		$db_and->condition('haod.uid', $user->uid, '=');
		$db_and->condition('haod.ddo_id', trim($form_state['values']['designation']), '=');
		$db_and->condition('haod.applicant_designation', trim($form_state['values']['app_designation']), '=');
		$db_and->condition('haod.applicant_headquarter', trim($form_state['values']['app_headquarter']), '=');
		$db_and->condition('haod.applicant_posting_place', trim($form_state['values']['app_posting_place']), '=');
		$db_and->condition('haod.pay_band_id',trim($form_state['values']['pay_band']) , '=');
		$db_and->condition('haod.pay_in_the_pay_band',trim($form_state['values']['pay_in']) , '=');
		$db_and->condition('haod.grade_pay',trim($form_state['values']['grade_pay']), '=');
		$db_and->condition('haod.date_of_joining',trim( implode('-', array_reverse(explode('/', $form_state['values']['doj'])))), '=');
		$db_and->condition('haod.date_of_retirement', trim( implode('-', array_reverse(explode('/', $form_state['values']['dor'])))), '=');
		$db_and->condition('haod.office_name', trim($form_state['values']['office_name']), '=');
		$db_and->condition('haod.office_street', trim($form_state['values']['office_street']), '=');
		$db_and->condition('haod.office_city_town_village', trim($form_state['values']['office_city']), '=');
		$db_and->condition('haod.office_post_office', trim($form_state['values']['office_post_office']), '=');
		$query->condition($db_and);
		
		$result =$query->execute();
		$id = 0;
		if($result->rowCount() > 0){
			$data = $result->fetchObject();
			$id = $data->id;
		}
		return $id;
   }*/
 
 /************************************************ AJAX **************************************************************/
 
	function _reload_present_address($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace('#reload_present_address', drupal_render($form['prrsonal_info']['present_address']));
		
		/*$commands[] = ajax_command_replace('#reload_present_street', drupal_render($form['prrsonal_info']['present_address']['present_street']));
		$commands[] = ajax_command_replace('#reload_present_city_town_village', drupal_render($form['prrsonal_info']['present_address']['present_city_town_village']));
		$commands[] = ajax_command_replace('#reload_present_post_office', drupal_render($form['prrsonal_info']['present_address']['present_post_office']));
		$commands[] = ajax_command_replace('#reload_present_district', drupal_render($form['prrsonal_info']['present_address']['present_district']));
		$commands[] = ajax_command_replace('#reload_present_pincode', drupal_render($form['prrsonal_info']['present_address']['present_pincode']));*/
		return array('#type' => 'ajax', '#commands' => $commands); 
	 
	}

/*reload DDO designation list (Ajax Call)*/
	function _reload_ddo_designation($form, &$form_state) {
		
		$district = isset($form_state['values']['district']) && !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
		
		$form['ddo']['address']['#value'] = '';
		if($district == '') {
			$form['ddo']['designation']['#options'] = array(''=>'- Select -');
		}
		else {
			$form['ddo']['designation']['#options'] = ddo_desig_list($district);
		}
		$commands = array();
		$commands[] = ajax_command_replace('#replace_ddo_address', drupal_render($form['ddo']['address']));
		$commands[] = ajax_command_replace('#replace_designation', drupal_render($form['ddo']['designation']));
		$form_state['rebuild'] = TRUE;
		return array('#type' => 'ajax', '#commands' => $commands);
	}

/* fetch all ddo designation respective to dictrict code*/
	function ddo_desig_list($district = 0) {
		
		$district = trim($district);	
		$ddo_desig_options = array('' => '-- Choose DDO Designation --');
		if(!empty($district)) {
			$query = db_select('housing_ddo', 'hd');
			$query->addExpression('ddo_id','ddo_id');
			$query->addExpression('trim(hd.ddo_designation)','ddo_designation');
			$query->condition('district_code', $district, '=');
			$query->orderBy('ddo_designation', 'ASC');
			$query->orderBy('ddo_type_id', 'ASC');
			$result = $query->execute();
			//$result = db_query("select * from {housing_district} order by district_code");
		
			foreach($result as $val) {
				$ddo_desig_options[$val->ddo_id] = $val->ddo_designation;
			}
		}
		//echo "<pre>";print_r($ddo_desig_options);die;
		
		return $ddo_desig_options;
	}
/*-------END---------*/

///////////debaleena start 13.06.24/////

function get_ddo_desig($ddo_code ='')
{
	$query = db_select('housing_ddo', 'hd');
	$query->addExpression('ddo_id','ddo_id');
	$query->addExpression('trim(hd.ddo_designation)','ddo_designation');
	$query->condition('ddo_code', $ddo_code, '=');
	$query->condition('is_active', 'Y', '=');
	//echo $ddo_code;echo $query;die;
	$result = $query->execute();
	$result = $result->fetchObject();
	if($result != NULL){
		
		foreach($result as $val) {
			$ddo_desig_options1[$result->ddo_id] = $result->ddo_designation;
		}
	}else{
		$ddo_desig_options1=[];
	}
	return $ddo_desig_options1;
	//return $result->ddo_designation;
}

function get_ddo_all_data($ddo_code =''){
	$query = db_select('housing_ddo', 'hd');
	$query->fields('hd',array());
	$query->condition('ddo_code', $ddo_code, '=');
	$query->condition('is_active', 'Y', '=');
	$result = $query->execute();
	$result = $result->fetchAssoc();
	if($result != NULL){
		return $result;
	}else{
		return '';
	}
}


////end//////

/*reload DDO address (Ajax Call)*/
 function _reload_ddo_address($form, &$form_state) {
	 $ddo = isset($form_state['values']['designation']) && !empty($form_state['values']['designation']) ? $form_state['values']['designation'] : '';
	 $form['ddo']['address']['#value'] = ddo_add($ddo);
	 $form['ddo']['address']['#attributes']['readonly'] = 'readonly';
	 $commands = array();
	 $commands[] = ajax_command_replace('#replace_ddo_address', drupal_render($form['ddo']['address']));
	 return array('#type' => 'ajax', '#commands' => $commands);
 
}

/*fetch DDO address respective to DDO designation*/
function ddo_add($ddo = '') {
	
	
	$ddo_add = '';
	if(!empty($ddo)) {
	$query = db_select('housing_ddo', 'hd')->fields('hd', array('ddo_address'));
	$query->condition('ddo_id', $ddo);
	$result = $query->execute()->fetchAssoc();
	$ddo_add = $result['ddo_address'];
		
	}
	
	return $ddo_add;
}

/*reload date of retirement (ajax call)*/
	function _reload_dor($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace('#replace_dor', drupal_render($form['official_info']['dor']));
		return array('#type' => 'ajax', '#commands' => $commands);	
	}

/*reload date of retirement*/
	function dor_reload($dob = '') {
		
		$dor = '';
		$dob1 = trim(implode('-', array_reverse(explode('/', $dob))));
		if(!empty($dob1)) {
			$date = new DateTime($dob1);
			$date->modify('+60 year');
			$date->modify('-1 day');
			$dor = $date->format('d/m/Y');
		}
		
		return $dor;
			
	}
/*-------END---------*/



//mail function for sending mail to all allottee
	function sendmail_allotment($receiver_email_list, $email_subject, $email_msg){
		
		$subject = $email_subject;
		$message = $email_msg;
		
		$bcc = implode(",", $receiver_email_list);
		
		//echo '<pre>'; print_r($bcc); die();
		
		$headers = "MIME-Version: 1.0" . "\r\n";
		$headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";
		$headers .= "From: eallotment-rhe@rhe.wbhousing.gov.in\r\n";
		//$headers .= "From: subhabrata.mukherjee31@gmail.com\r\n";
		$headers .= "Bcc: ".$bcc."\r\n";
		mail(NULL, $subject, $message, $headers);
		
	}
	
	
	
//mail function for sending mail to licensee
	function sendmail_licence($receiver_email, $email_subject, $email_msg){
		
		$to = $receiver_email;
		$subject = $email_subject;
		$message = $email_msg;
		
		//code for mail()
		$headers = "MIME-Version: 1.0" . "\r\n";
		$headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";
		$headers .= "From: eallotment-rhe@rhe.wbhousing.gov.in\r\n";
		//$headers .= "From: subhabrata.mukherjee31@gmail.com\r\n";
		//$headers .= "Bcc: ".$bcc."\r\n";
		
		mail($to, $subject, $message, $headers);
		
	}
	
	
//mail function for sending remainder mail to allotted applicant
	function sendmail_remainder_offer_allotment($emailId, $email_subject, $email_msg) {
		
		$subject = $email_subject;
		$message = $email_msg;
		
		$bcc = implode(",", $emailId);
		
		//echo '<pre>'; print_r($bcc); die();
		
		$headers = "MIME-Version: 1.0" . "\r\n";
		$headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";
		$headers .= "From: eallotment-rhe@rhe.wbhousing.gov.in\r\n";
		//$headers .= "From: subhabrata.mukherjee31@gmail.com\r\n";
		$headers .= "Bcc: ".$bcc."\r\n";
		mail(NULL, $subject, $message, $headers);	
		
	}
	
	
	/* fetch pay band details*/ 
 	/*function pay_band_list() {
		$query = db_select('housing_pay_band', 'hpb');
		$query->fields('hpb');
		$query->orderBy('pay_band_id', 'ASC');
		$result = $query->execute();
		
		return $result;
		
	}*/
	
	
//Function for digital signed checkinh	
	function isStringInFile($fid = '', $string = ''){

		$result1 = db_select('file_managed', 'fm')
						->fields('fm')
						->condition('fid', $fid)
						->execute();
						
		$data1 = $result1->fetchObject();
		$file = $data1->uri;
		 
		$handle = fopen($file, 'r');
		$valid = false; // init as false
		while (($buffer = fgets($handle)) !== false) {
			if (strpos($buffer, $string) !== false) {
				$valid = TRUE;
				break; // Once you find the string, you should break out the loop.
			}      
		}
		fclose($handle);
	
		return $valid;
	
	}
		

//function to fetch online application id of new application using uid	
	function fetch_online_app_id_new_application_uid() {
		global $user;
		
		$query = db_select('users', 'u');
		$query->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
		$query->innerJoin('housing_online_application', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->innerJoin('housing_new_allotment_application', 'hnaa', 'hnaa.online_application_id = hoa.online_application_id');
		$query->addField('hoa', 'online_application_id');
		
		$db_and = db_and();
		$db_and->condition('u.uid', $user->uid, '=');
		$db_and->condition('hoa.is_backlog_applicant', 1, '=');
		//$db_and->condition('hnaa.scaned_sign', NULL, 'IS');
		$query->condition($db_and);
		
		return $query->execute();
		
	}
	
	
//function to fetch scanned signature of applicant
	function fetch_applicant_scanned_sign($entityType = '') {
		global $user;
		
		$query = db_select('users', 'u');
		$query->innerJoin('housing_applicant_official_detail', 'haod', 'u.uid = haod.uid');
		$query->innerJoin('housing_online_application', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');

		if($entityType == 'New Allotment') {
			$query->innerJoin('housing_new_allotment_application', 'hnaa', 'hnaa.online_application_id = hoa.online_application_id');
			$query->leftJoin('file_managed', 'fm2', 'fm2.fid = hnaa.scaned_sign');
		}else if($entityType == 'Vertical Shifting'){
			$query->innerJoin('housing_vs_application', 'hva', 'hva.online_application_id = hoa.online_application_id');
			$query->leftJoin('file_managed', 'fm2', 'fm2.fid = hva.scanned_sign');
		}else if($entityType == 'Category Shifting'){
			$query->innerJoin('housing_cs_application', 'hca', 'hca.online_application_id = hoa.online_application_id');
			$query->leftJoin('file_managed', 'fm2', 'fm2.fid = hca.scanned_sign');
		}
		
		//$query->leftJoin('file_managed', 'fm2', 'fm2.fid = hnaa.scaned_sign');
		
		$query->addField('hoa', 'online_application_id');
		$query->addField('fm2', 'uri', 'uri_scaned_sign');
		
		$db_and = db_and();
		$db_and->condition('u.uid', $user->uid, '=');
		//$db_and->condition('hnaa.scaned_sign', NULL, 'IS NOT');
		if($entityType == 'New Allotment') {
			$db_and->condition('hnaa.scaned_sign', NULL, 'IS NOT');
		}else if($entityType == 'Vertical Shifting'){
			$db_and->condition('hva.scanned_sign', NULL, 'IS NOT');
		}else if($entityType == 'Category Shifting'){
			$db_and->condition('hca.scanned_sign', NULL, 'IS NOT');
		}
		$query->condition($db_and);
		
		return $query->execute();
		
	}
		