<?php


    function update_applicant_official_detail($form, &$form_state,$applicant_official_detail_id){  
	
		global $user;
		
   		/*update applicant_official_detail  data*/
		$app_off_detail_arr = array();
		$app_off_detail_arr['uid']  =  $user->uid;
		$app_off_detail_arr['ddo_id']  =   trim($form_state['values']['designation']);
		$app_off_detail_arr['hrms_id']  =  trim($form_state['values']['hrms_id']);
		$app_off_detail_arr['applicant_designation']  =  strtoupper(trim($form_state['values']['app_designation']));
		$app_off_detail_arr['applicant_headquarter']  =  strtoupper(trim($form_state['values']['app_headquarter']));
		$app_off_detail_arr['applicant_posting_place']  =  strtoupper(trim($form_state['values']['app_posting_place']));
		$app_off_detail_arr['pay_band_id']  =  trim($form_state['values']['pay_band']);
		$app_off_detail_arr['pay_in_the_pay_band']  =  trim($form_state['values']['pay_in']);
		//$app_off_detail_arr['grade_pay']  =  trim($form_state['values']['grade_pay']);
		
		//$app_off_detail_arr['gpf_no']  =  strtoupper(trim($form_state['values']['gpf_no']));
		
		$app_off_detail_arr['date_of_joining']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['doj']))));
		$app_off_detail_arr['date_of_retirement']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['dor']))));
		$app_off_detail_arr['office_name']  =  strtoupper(trim($form_state['values']['office_name']));
		$app_off_detail_arr['office_street']  =  strtoupper(trim($form_state['values']['office_street']));
		$app_off_detail_arr['office_city_town_village']  = strtoupper(trim($form_state['values']['office_city']));
		$app_off_detail_arr['office_post_office']  =  strtoupper(trim($form_state['values']['office_post_office']));
		$app_off_detail_arr['office_pin_code']  =  trim($form_state['values']['office_pincode']);
		$app_off_detail_arr['office_district']  =  trim($form_state['values']['office_district']);
		$app_off_detail_arr['office_phone_no']  =  trim($form_state['values']['office_phone_no']);
		$app_off_detail_arr['is_active']  =  1;
		// echo $applicant_official_detail_id.'<br>'. print_r($app_off_detail_arr);die;
		db_update('housing_applicant_official_detail')    
  	  	->fields($app_off_detail_arr)
	  	->condition('applicant_official_detail_id', $applicant_official_detail_id, '=')
  	  	->execute();
		
	  
   }


   ////added function by debaleena 19-11-2024///
      
	function update_applicant_official_detail_updated($form, &$form_state, $max_housing_applicant_id = ''){
		global $user;
		
   		/*update applicant_official_detail  data*/
		$app_off_detail_arr = array();
		$app_off_detail_arr['uid']  =  $user->uid;
		$app_off_detail_arr['ddo_id']  =   trim($form_state['values']['designation']);
		$app_off_detail_arr['hrms_id']  =  trim($form_state['values']['hrms_id']);
		$app_off_detail_arr['applicant_designation']  =  strtoupper(trim($form_state['values']['app_designation']));
		$app_off_detail_arr['applicant_headquarter']  =  strtoupper(trim($form_state['values']['app_headquarter']));
		$app_off_detail_arr['applicant_posting_place']  =  strtoupper(trim($form_state['values']['app_posting_place']));
		$app_off_detail_arr['pay_band_id']  =  trim($form_state['values']['pay_band']);
		$app_off_detail_arr['pay_in_the_pay_band']  =  trim($form_state['values']['pay_in']);
		//$app_off_detail_arr['grade_pay']  =  trim($form_state['values']['grade_pay']);
		
		//$app_off_detail_arr['gpf_no']  =  strtoupper(trim($form_state['values']['gpf_no']));
		
		$app_off_detail_arr['date_of_joining']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['doj']))));
		$app_off_detail_arr['date_of_retirement']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['dor']))));
		$app_off_detail_arr['office_name']  =  strtoupper(trim($form_state['values']['office_name']));
		$app_off_detail_arr['office_street']  =  strtoupper(trim($form_state['values']['office_street']));
		$app_off_detail_arr['office_city_town_village']  = strtoupper(trim($form_state['values']['office_city']));
		$app_off_detail_arr['office_post_office']  =  strtoupper(trim($form_state['values']['office_post_office']));
		$app_off_detail_arr['office_pin_code']  =  trim($form_state['values']['office_pincode']);
		$app_off_detail_arr['office_district']  =  trim($form_state['values']['office_district']);
		$app_off_detail_arr['office_phone_no']  =  trim($form_state['values']['office_phone_no']);
		if(isset($max_housing_applicant_id)){
			$app_off_detail_arr['housing_applicant_id']  =  trim($max_housing_applicant_id);
		}
		
		db_insert('housing_applicant_official_detail')    // change update to insert by debaleena 19-11-2024
  	  	->fields($app_off_detail_arr)
	  	//->condition('applicant_official_detail_id', $applicant_official_detail_id, '=')
  	  	->execute();
		/////////// added by debaleena 19-11-2024//////////
		$query = db_select('housing_applicant_official_detail', 'haod');
		$query->addExpression('MAX(applicant_official_detail_id)','id');
		$query->condition('haod.uid', $user->uid, '=');
		$result =$query->execute();
		$data = $result->fetchObject();
		// echo'data';
		// print_r($data);die;
		return $data->id;
	  
   }
   
   function update_online_application($status,$form,&$form_state,$online_application_id){
	   
	    update_applicant_personal_detail($form, $form_state);
   		global $user;
		/*fetching applicant_official_detail_id*/
		$query = db_select('housing_online_application', 'hoa');
		$query->addField('hoa', 'applicant_official_detail_id');
		$query->condition('hoa.online_application_id', trim($online_application_id), '=');
		$result =$query->execute();
		$data = $result->fetchObject();
		/*update online application*/
		$online_app_arr = array();
		update_applicant_official_detail($form, $form_state,$data->applicant_official_detail_id);
		$online_app_arr['status']  =  trim($status);
		
		db_update('housing_online_application')
  	  	->fields($online_app_arr)
	  	->condition('online_application_id', $online_application_id, '=')
  	  	->execute();
   }
   
  
  


