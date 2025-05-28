<?php

	//function existing_occupant_form($form, &$form_state, $flat_id, $hrms_id) {
	function existing_occupant_form($form, &$form_state, $flat_id) {
		$flat_id = decrypt_url($flat_id);
		//$hrms_id = decrypt_url($hrms_id);
		
		//die($flat_id.' '.$hrms_id);
		$result = occupant_entry_check($flat_id);
		$occupant_rhe = get_occupant_rhe_details($flat_id)->fetchObject();
		//$hrms_details = fetch_hrms_details($hrms_id);
		
		//for custom hrms table
		/*$hrms_details_data = $hrms_details->fetchObject();*/
		
		$district = isset($form_state['values']['district']) && !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
		$designation = isset($form_state['values']['designation']) && !empty($form_state['values']['designation']) ? $form_state['values']['designation'] : '';
		
		$dob = isset($form_state['values']['dob']) && !empty($form_state['values']['dob']) ? $form_state['values']['dob'] : '';
		
		$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	  	$rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
	  	//$reason = isset($form_state['values']['reason']) && !empty($form_state['values']['reason']) ? $form_state['values']['reason'] : '';
		
		$district_name = trim($occupant_rhe->district_name);
		$estate_name = trim($occupant_rhe->estate_name);
		$flat_type = trim($occupant_rhe->flat_type);
		$block_name = trim($occupant_rhe->block_name);
		$flat_no = trim($occupant_rhe->flat_no);
		
		$flat_type_id = trim($occupant_rhe->flat_type_id);
		
		if($result->rowCount() > 0) {
			drupal_goto('occupant_entry_done');
		} else {
		$form['form_begin'] = array(
			'#type' => 'markup',
			'#markup' => '<div class="online_application">',
			'#weight' => -2
		);
		
		$form['flat_type_id'] = array(
			'#type' => 'hidden',
			'#default_value' => $flat_type_id,
			//'#weight' => -11,
	  	);
		
		$form['flat_id'] = array(
			'#type' => 'hidden',
			'#default_value' => $flat_id,
			//'#weight' => -11,
	  	);
		
		/*$form['hrms_id'] = array(
			'#type' => 'hidden',
			'#default_value' => $hrms_id,
			//'#weight' => -11,
	  	);*/
		
		//Occupied information
		$form['occupied_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Occupied Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE, // Added
		);
		
		$form['occupied_info']['occupied_district'] = array(
			'#title' => t('District Name'),
			'#type' => 'textfield',
			'#default_value' => $district_name,
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'),
			'#required' => TRUE,
	  	);
		
		$form['occupied_info']['occupied_estate'] = array(
			'#title' => t('Rental Housing Estate Name'),
			'#type' => 'textfield',
			'#default_value' => $estate_name,
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_streetaddress'),
			'#required' => TRUE,
		);
		
		$form['occupied_info']['occupied_flattype'] = array(
			'#title' => t('Flat Type'),
			'#type' => 'textfield',
			'#default_value' => $flat_type,
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('validate_rhe_flattype'),
			'#required' => TRUE,
		);
		
		$form['occupied_info']['occupied_block'] = array(
			'#title' => t('Block Name'),
			'#type' => 'textfield',
			'#default_value' => $block_name,
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('validate_rhe_block1'),
			'#required' => TRUE,
		);
		
		$form['occupied_info']['occupied_flat'] = array(
			'#title' => t('Flat No.'),
			'#type' => 'textfield',
			'#default_value' => $flat_no,
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('validate_flat_no'),
			'#required' => TRUE,
		);
		
		//personal information
		$form['prrsonal_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Personal Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
						
		$form['prrsonal_info']['occupant_name'] = array(
			'#title' => t('Occupant\'s Name'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#default_value' => '',
			//for api
			//'#default_value' => strtoupper($hrms_details['data']['ai_worker_name']),
			//for custom hrms table
			//'#default_value' => strtoupper($hrms_details_data->emp_name),
			'#element_validate' => array('element_validate_alphabatic_text'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
			'#required' => TRUE,
		);
		
		$form['prrsonal_info']['occupant_father_name'] = array(
			'#title' => t('Father / Husband Name'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			//for custom hrms table
			//'#default_value' => strtoupper($hrms_details_data->emp_father_name),
			'#element_validate' => array('element_validate_alphabatic_text'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
			'#required' => TRUE,
		);
		$form['prrsonal_info']['mobile'] = array(
			'#title' => t('Mobile no'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#maxlength' => 10,
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_mobile'),
			'#attributes' => array('id' => 'mobile_no'),
		);
		$form['prrsonal_info']['email'] = array(
			'#title' => t('Email ID'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#required' => TRUE,
			'#element_validate' => array('element_validate_email'),
			'#attributes' => array('oninput'=>"this.value=this.value.toLowerCase()"),
		);
		
		$form['prrsonal_info']['dob'] = array(
			'#title' => t('Date of Birth'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dob'),
			'#required' => TRUE,
			//'#validated' => TRUE,
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date', 'element_validate_age'),
		);
		
		$form['prrsonal_info']['gender'] = array(
			'#title' => t('Gender'),
			'#type' => 'radios',
			'#options' => array('M' => 'Male', 'F' => 'Female'),
			'#attributes' => array('class' => array('gender')),
			'#default_value' => 'M',
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#required' => TRUE,
		);
		
		// occupant's official information
		$form['official_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Occupant\'s Official Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		
		/*$form['official_info']['hrmsid'] = array(
			'#title' => t('HRMS ID'),
			'#type' => 'textfield',
			'#default_value' => $hrms_id,
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_numeric_positive'),
			'#required' => TRUE,
		);*/
		
		$form['official_info']['occupant_designation'] = array(
			'#title' => t('Designation'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
			//'#attributes' => array('id' => 'edit-app-designation', 'oncopy' => "return false", 'onpaste' => "return false"),
		);
		
		$form['official_info']['pay_band'] = array(
			'#title' => t('Pay Band'),
			'#type' => 'select',
			'#options' => pay_band_list_specific($flat_type_id),
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div class="two-one">',
			'#suffix' => '</div>',
		);
		$form['official_info']['pay_in'] = array(
			'#title' => t('Pay in the Pay Band'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		$form['official_info']['grade_pay'] = array(
			'#title' => t('Grade Pay'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		$form['official_info']['gpf_no'] = array(
			'#title' => t('GPF No.'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#element_validate' => array('gpf_no_validate'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);
		
		$form['official_info']['occupant_posting_place'] = array(
			'#title' => t('Place of Posting'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),  
		); 
		$form['official_info']['occupant_headquarter'] = array(
			'#title' => t('Headquarter'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
		);
		$form['official_info']['doj'] = array(
			'#title' => t('Date of Joining'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doj'),
			'#default_value' => '',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
		);
		
		$form['official_info']['dor'] = array(
			'#title' => t('Date of Retirement'),
			'#type' => 'textfield',
			//'#attributes' => array('readonly' => 'readonly'),
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dor'),
			'#default_value' => '',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date'),
		);
		
		
		// occupant's office address
		$form['office_add'] = array(
			'#type' => 'fieldset',
			'#title' => t('Name and Address of the Office'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		$form['office_add']['office_name'] = array(
			'#title' => t('Name of the Office'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_hyphenFullStopAmpersand'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),  
		);
		
		$form['office_add']['office_street'] = array(
			'#title' => t('Address of the Office'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two-one">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_streetaddress'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
		);
		$form['office_add']['office_city'] = array(
			'#title' => t('City/Town/Village of the Office'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
		);
		$form['office_add']['office_post_office'] = array(
			'#title' => t('Post Office Name of the Office'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
		);
		$form['office_add']['office_pincode'] = array(
			'#title' => t('Pincode of the Office'),
			'#type' => 'textfield',
			'#maxlength' => 6,
			'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		// ddo details
		$form['ddo'] = array(
			'#type' => 'fieldset',
			'#title' => t('DDO with Full Address'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		$form['ddo']['district'] = array(
			'#title' => t('DDO District'),
			'#type' => 'select',
			'#options' => district_list(),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_ddo_designation',
					  // 'wrapper' => 'replace_designation',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						), 
			 ),
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
			)
		);
		
		
		$form['ddo']['designation'] = array(
			'#title' => t('DDO Designation'),
			'#type' => 'select',
			//'#options' => array('- Select -'),
			'#options' => ddo_desig_list($district),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_ddo_address',
					   'wrapper' => 'replace_ddo_address',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						 ),
			 ),
			'#default_value' => $designation,
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div id="replace_designation" class="two">',
			'#suffix' => '</div>',
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
			)
		);
		
		$form['ddo']['address'] = array(
			'#title' => t('DDO Address'),
			'#type' => 'textarea',
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div id="replace_ddo_address" >',
			'#suffix' => '</div>',
			//'#required' => TRUE,
			//'#validated' => TRUE,
		);
		
		//allotment type and category
		/*$form['allotment_reason'] = array(
			'#type' => 'fieldset',
			'#title' => t('Allotment Category'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		
		$form['allotment_reason']['rhe_flat_type'] = array(
			'#title' => t('Flat TYPE'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly'),
			'#default_value' => '',
			'#required' => TRUE,
			'#prefix' => '<div class="two" id="replace_rhe_flat_type" >',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_flat_type'),
		 );*/
	     
		 
		 /*$form['allotment_reason']['reason'] = array(
			'#title' => t('Allotment Category'),
			'#type' => 'select',
			//'#options' => array(''=>'- Select -'),
			'#options' => allotment_category_list(trim($rhe_flat_type)),
			'#default_value' => $reason,
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div id="replace_allotment_category" class="two">',
			'#suffix' => '</div>',
		 );*/
		
		
		 /*$form['official_info']['pay_band']['#ajax'] = array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_category',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						 )
		 );*/
		
		$form['#attributes'] = array('onsubmit' => 'return validate_existing_occupant_form()');
		
		$form['submit_button']=array(
										'#type'=>'submit',
										'#value'=>t('Submit')
								);
								
		$form['cancel_button']=array(
										'#type'=>'button',
										'#value'=>t('Cancel'),
										'#attributes' => array('onClick' => 'history.go(-1); event.preventDefault();'),
								);
								
		$form['form_end'] = array(
			'#type' => 'markup',
			'#markup' => '</div>',
		);
		
		return $form;
		}
	}
	
	function existing_occupant_form_validate($form, &$form_state) {
		
		if($form_state['values']['pay_band'] == '') {
  			form_set_error('district', t('Please select payband.'));
		}
		if($form_state['values']['district'] == '') {
  			form_set_error('district', t('Please select district.'));
		}
		if($form_state['values']['designation'] == '') {
  			form_set_error('designation', t('Please select ddo designation.'));
		}
		/*if($form_state['values']['reason'] == '') {
  			form_set_error('reason', t('Please select allotment reason.'));
		}*/
			
		
		if(!empty($form_state['values']['mobile']) && is_numeric($form_state['values']['mobile'])) {
		   
			 $mobile = trim($form_state['values']['mobile']);
			 
			 $query = db_select('housing_applicant','applicant');
			 $query->addExpression('mobile_no','mobile');
			 $query->condition('mobile_no', $mobile);
			 $result =$query->execute();
			 
			 
			 if($result->rowCount() > 0)
			 	form_set_error('mobile', 'This mobile no. already exist.');
		
		}
		
		if(!empty($form_state['values']['email'])) {
		   
			$email = trim($form_state['values']['email']);
			
			$query = db_select('users','u');
			$query->addExpression('mail','email');
			$query->condition('mail', $email);
			$result =$query->execute();
			
			/*if (!valid_email_address($email)) {
				form_set_error('[email]', t('The email address appears to be invalid.'));
			}*/
			
			if($result->rowCount() > 0)
				form_set_error('email', 'This email address already exist.');
		
		}
		
		if($form_state['values']['pay_band'] == 1) {
			if($form_state['values']['pay_in'] < 0 || $form_state['values']['pay_in'] > 7999) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
		}
		else if($form_state['values']['pay_band'] == 2) {
			if($form_state['values']['pay_in'] < 8000 || $form_state['values']['pay_in'] > 12499) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
		}
		else if($form_state['values']['pay_band'] == 3) {
			if($form_state['values']['pay_in'] < 12500 || $form_state['values']['pay_in'] > 15999) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
		}
		else if($form_state['values']['pay_band'] == 4) {
			if($form_state['values']['pay_in'] < 16000) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
			else {
				if($form_state['values']['grade_pay'] < 0 || $form_state['values']['grade_pay'] > 7599) {
					form_set_error('grade_pay', t('Please enter proper Grade Pay.'));	
				}		
			}
		}
		else if($form_state['values']['pay_band'] == 5) {
			if($form_state['values']['pay_in'] < 16000) {
				form_set_error('pay_in', t('Please enter proper Pay in the Pay Band.'));	
			}
			else {
				if($form_state['values']['grade_pay'] < 7600) {
					form_set_error('grade_pay', t('Please enter proper Grade Pay.'));	
				}		
			}
		}
		
	}
	
	
	function existing_occupant_form_submit($form, &$form_state) {
		/*echo '<pre>';
		print_r($form_state['values']);die();*/
		//$name = strtolower(trim($form_state['values']['applicant_name']));
		//$name1 = str_replace(" ","",$name);
		//$username = str_replace(".","",$name1).rand();
		
		$word_c = str_word_count(trim($form_state['values']['occupant_name']));
		$splitter = " ";
		$pieces = explode($splitter, trim($form_state['values']['occupant_name']));
		
		if($word_c < 2) {
			$name = strtolower(substr($pieces[0], 0, 3));
		}
		else if($word_c == 2) {
			if($pieces[0] == 'Dr.' || $pieces[0] == 'Dr' || $pieces[0] == 'dr.' || $pieces[0] == 'dr' || $pieces[0] == 'DR.' || $pieces[0] == 'DR') {
				$name = strtolower(substr($pieces[1], 0, 3));
			}
			else {
				$name = strtolower(substr($pieces[0], 0, 3)).strtolower(substr($pieces[1], 0, 3));
			}
		}
		else {
			if($pieces[0] == 'Dr.' || $pieces[0] == 'Dr' || $pieces[0] == 'dr.' || $pieces[0] == 'dr' || $pieces[0] == 'DR.' || $pieces[0] == 'DR') {
				$name = strtolower(substr($pieces[1], 0, 3)).strtolower(substr($pieces[2], 0, 3));
			}
			else {
				$name = strtolower(substr($pieces[0], 0, 3)).strtolower(substr($pieces[1], 0, 3));
			}
		}
		
		$username = str_replace(".","",$name).rand(1, 100000);
		
		/*insert into user table*/
		$newUser	   	   = array();
		$newUser['name']   = trim($username);
		$newUser['pass']   = trim($username);
		/*$str[0].$str[1].trim($form_state['values']['username']).'@'.$dob_t.strrev($str1[0].$str1[1]);*/																																																						
		$newUser['mail']   = trim($form_state['values']['email']);
		$newUser['status'] = 0;
		
		user_save(null, $newUser);
		
		/*get last inserted uid*/
		
		$query = db_select('users','u');
		$query->addExpression('MAX(uid)','max_uid');
		$result = $query->execute();
		$data = $result->fetchObject();
		
		/*insert into housing_applicant table*/
		
		$user_reg_arr = array();
		$user_reg_arr['uid'] 				=  trim($data->max_uid);
		$user_reg_arr['applicant_name'] 	=  trim($form_state['values']['occupant_name']);
		$user_reg_arr['guardian_name'] 		=  trim($form_state['values']['occupant_father_name']);
		$user_reg_arr['date_of_birth'] 		=  trim(implode('-', array_reverse(explode('/', $form_state['values']['dob']))));
		$user_reg_arr['gender'] 			=  trim($form_state['values']['gender']);
		$user_reg_arr['mobile_no'] 			=  trim($form_state['values']['mobile']);
		
		
		db_insert('housing_applicant')
		->fields($user_reg_arr)
		->execute();
		
		/*assign user roles*/
		
		$arr_user_roles = array();
		$arr_user_roles['uid'] = trim($data->max_uid);
		$arr_user_roles['rid'] = 5;
		
		db_insert('users_roles')
		->fields($arr_user_roles)
		->execute();
		
		/*add applicant_official_detail  data*/
		$app_off_detail_arr = array();
		$app_off_detail_arr['uid']  =  trim($data->max_uid);
		//$app_off_detail_arr['hrms_id']  =  trim($form_state['values']['hrmsid']);
		$app_off_detail_arr['applicant_designation']  =  trim($form_state['values']['occupant_designation']);
		$app_off_detail_arr['pay_band_id']  =  trim($form_state['values']['pay_band']);
		$app_off_detail_arr['pay_in_the_pay_band']  =  trim($form_state['values']['pay_in']);
		$app_off_detail_arr['grade_pay']  =  trim($form_state['values']['grade_pay']);
		$app_off_detail_arr['gpf_no']  =  trim($form_state['values']['gpf_no']);
		$app_off_detail_arr['applicant_posting_place']  =  trim($form_state['values']['occupant_posting_place']);
		$app_off_detail_arr['applicant_headquarter']  =  trim($form_state['values']['occupant_headquarter']);
		$app_off_detail_arr['date_of_joining']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['doj']))));
		$app_off_detail_arr['date_of_retirement']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['dor']))));
		$app_off_detail_arr['office_name']  =  trim($form_state['values']['office_name']);
		$app_off_detail_arr['office_street']  =  trim($form_state['values']['office_street']);
		$app_off_detail_arr['office_city_town_village']  =  trim($form_state['values']['office_city']);
		$app_off_detail_arr['office_post_office']  =  trim($form_state['values']['office_post_office']);
		$app_off_detail_arr['office_pin_code']  =  trim($form_state['values']['office_pincode']);
		$app_off_detail_arr['ddo_id']  =   trim($form_state['values']['designation']);
		
		db_insert('housing_applicant_official_detail')
  	  	->fields($app_off_detail_arr)
  	  	->execute();
		
		/*fetching applicant_official_detail_id*/
		$query1 = db_select('housing_applicant_official_detail', 'haod');
		$query1->addExpression('MAX(applicant_official_detail_id)','id');
		$query1->condition('haod.uid', $data->max_uid, '=');
		$result1 = $query1->execute();
		$data1 = $result1->fetchObject();
		
		/*add online application*/
		
		$online_app_arr = array();
		$online_app_arr['applicant_official_detail_id']  =  trim($data1->id);
		$online_app_arr['status']  =  'allotted';
		$online_app_arr['date_of_application']  =  NULL;
		$online_app_arr['is_backlog_applicant']  =  2;		
				
		db_insert('housing_online_application')
		->fields($online_app_arr)
		->execute();
		
		/*fetching online_application_id*/
		$query2 = db_select('housing_online_application', 'hoa');
		$query2->addExpression('MAX(online_application_id)','oid');
		$query2->condition('hoa.applicant_official_detail_id', $data1->id, '=');
		$result2 =$query2->execute();
		$data2 = $result2->fetchObject();
		
		/*$online_app_arr_upd = array();
		$online_app_arr_upd['application_no']  = 'NA-'.trim(date('dmY')).'-'.$data2->oid;
			
		db_update('housing_online_application')
		->fields($online_app_arr_upd)
		->condition('online_application_id', $data2->oid)
		->execute();*/
		
		/* add new alltment application*/  
		$new_allotment_app_arr = array();
		$new_allotment_app_arr['online_application_id']  =  trim($data2->oid);
		
		$new_allotment_app_arr['flat_type_id'] = trim($form_state['values']['flat_type_id']);
		//$new_allotment_app_arr['allotment_category']  =  trim($form_state['values']['reason']);
		
		db_insert('housing_new_allotment_application')
  	  	->fields($new_allotment_app_arr)
  	  	->execute();
		
		/*Flat status update and Add flat occupant details*/
		db_update('housing_flat')
			->fields(array(
						'flat_status_id' => 2
					))
			->condition('flat_id', $flat_id)
			->execute();
			
		$allotment_ins_arr = array();
		$allotment_ins_arr['online_application_id']  = trim($data2->oid);
		$allotment_ins_arr['flat_id']  = trim($form_state['values']['flat_id']);;
		$allotment_ins_arr['allotment_date']  =  NULL;
		
		//$allotment_ins_arr['allotment_no'] = 'NAL-'.$data2->oid.'-'.date("dmY");
		//$allotment_ins_arr['allotment_process_no'] = ;
	
		db_insert('housing_flat_occupant')
		->fields($allotment_ins_arr)
		->execute();
		
		$flatno = $form_state['values']['occupied_flat'];
		drupal_set_message('Occupant Data for Flat No.- '.$flatno.' Inserted Successfully.');
		drupal_goto('rhewise_flatlist');
	}
	