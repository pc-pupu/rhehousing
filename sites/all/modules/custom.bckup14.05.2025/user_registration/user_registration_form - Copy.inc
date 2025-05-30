<?php
	function user_registration_form($form, &$form_state) {
	  
		// drupal_add_library('system','ui.datepicker');
		//personal information
		$form['form_begin'] = array(
			'#type' => 'markup',
			'#markup' => '<div class="user_reg">',
		);
		
		$form['applicant_name'] = array(
			'#title' => t('Name of the Applicant'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#attributes' => array('placeholder' => 'Enter Name', 'oninput' => "this.value=this.value.toUpperCase()"),
			'#element_validate' => array('element_validate_alphabatic_fullstop'), 
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		$form['dob'] = array(
			'#title' => t('Date of Birth'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dob', 'placeholder' => 'Enter Date of Birth'),
			'#default_value' => '',
			'#required' => TRUE,
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date'),
		);
		$form['gender'] = array(
			'#title' => t('Gender'),
			'#type' => 'radios',
			'#options' => array('M' => 'Male', 'F' => 'Female'),
			'#attributes' => array('class' => array('gender')),
			'#default_value' => 'M',
			'#required' => TRUE,
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
		);
		
		/*$form['username'] = array(
			'#title' => t('Username'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#attributes' => array('placeholder' => 'Enter unique username'),
			'#required' => TRUE,
			'#prefix' => '<div class="four ">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_username'), 
		);*/
		
		$form['mobile'] = array(
			'#title' => t('Mobile no'),
			'#type' => 'textfield',
			'#maxlength' => 10,
			'#default_value' => '',
			'#attributes' => array('placeholder' => 'Enter Mobile No', 'id' => 'mobile_no'),
			'#required' => TRUE,
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_mobile'),
		);
		$form['email'] = array(
			'#title' => t('Email ID'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#attributes' => array('placeholder' => 'Enter Email ID', 'oninput' => "this.value=this.value.toLowerCase()"),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_email'),
		);
		$form['hrms_id'] = array(
			'#title' => t('Employee HRMS ID'),
			'#type' => 'textfield',
			'#maxlength' => 10,
			'#default_value' => '',
			'#attributes' => array('placeholder' => 'Enter Employee HRMS ID', 'class' => array('numeric_positive')),
			'#required' => TRUE,
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_hrms_id'),
		);
		$form['app_designation'] = array(
			'#title' => t('Designation'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_textarea'),
			'#attributes' => array('placeholder' => 'Enter Designation', 'oninput'=>"this.value=this.value.toUpperCase()"),
		);
		$form['office_add']['office_name'] = array(
			'#title' => t('Name of the Office'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_textarea'), 
			'#attributes' => array('placeholder' => 'Enter Office Name', 'oninput'=>"this.value=this.value.toUpperCase()"),
		);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_applicant_regform()');
		
		$form['submit'] = array(
			'#value' => t('Register'),
			'#type' => 'submit',
		);
		
		$form['form_end'] = array(
			'#type' => 'markup',
			'#markup' => '</div>',
		);
		
		return $form;
	}
  
	function user_registration_form_validate($form, &$form_state) {
		// validation code
		/*if(!empty($form_state['values']['gender'])) {
			$gender = $form_state['values']['gender'];
			if($gender != 'M' || $gender != 'F') {
				form_set_error('[gender]', t('Invalid input.'));		
			}
		}*/
		
		
		/*if(!empty($form_state['values']['username'])) {
		   
			 $username = trim($form_state['values']['username']);
			 
			 $query = db_select('users','u');
			 $query->addExpression('name','name');
			 $query->condition('name', $username);
			 $result =$query->execute();
			 
			 
			 if($result->rowCount() > 0)
			 	form_set_error('username', 'This username already exist.');
		
		}*/
		
		if(!empty($form_state['values']['dob'])) {
		   
			 $dob = trim($form_state['values']['dob']);
			 if (!empty($dob)) {
			 	$date = DateTime::createFromFormat('d/m/Y', $dob);
				$dob= $date->format('Y-m-d');
				if(!validateAge($dob)){
					form_set_error('dob', 'Check Date of Birth. Minimum age should be 18 Years.');
				}
			 }else{
			 	form_set_error('dob', 'Date of Birth Can\'t be empty.');
			 }
		}		
		
		if(!empty($form_state['values']['mobile']) && is_numeric($form_state['values']['mobile'])) {
		   
			 $mobile = trim($form_state['values']['mobile']);
			 
			 $query = db_select('housing_applicant','applicant');
			 $query->addExpression('mobile_no','mobile');
			 $query->condition('mobile_no', $mobile);
			 $result =$query->execute();
			 
			 
			 if($result->rowCount() > 0)
			 	form_set_error('mobile', 'This Mobile No. already exist.');
		
		}
		
		if(!empty($form_state['values']['email'])) {
		   
			$email = strtolower(trim($form_state['values']['email']));
			
			$query = db_select('users','u');
			$query->addExpression('mail','email');
			$query->condition('mail', $email);
			$result =$query->execute();
			
			/*if (!valid_email_address($email)) {
				form_set_error('[email]', t('The email address appears to be invalid.'));
			}*/
			
			if($result->rowCount() > 0)
				form_set_error('email', 'This Email ID already exist.');
		
		}
		
		if(!empty($form_state['values']['hrms_id']) && is_numeric($form_state['values']['hrms_id'])) {
		   
			 $hrms_id = trim($form_state['values']['hrms_id']);
			 
			 $query = db_select('housing_applicant_official_detail','haod');
			 $query->fields('haod');
			 $query->condition('hrms_id', $hrms_id);
			 $result =$query->execute();
			 
			 
			 if($result->rowCount() > 0)
			 	form_set_error('hrms_id', 'This Employee HRMS ID already exist.');
		
		}
	}
    
	function user_registration_form_submit($form, &$form_state) {  
	  
		/*echo "<pre>";
		print_r($form_state['values']);
		die();*/
		
		//$password = getToken(8);
		
		$word_c = str_word_count(trim($form_state['values']['applicant_name']));
		$splitter = " ";
		$pieces = explode($splitter, trim($form_state['values']['applicant_name']));
		
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
		
		$newUser	   	   = array();
		//$newUser['name']   = trim($form_state['values']['username']);
		$newUser['name'] = $username;
		$newUser['pass'] = $username;
		/*$str[0].$str[1].trim($form_state['values']['username']).'@'.$dob_t.strrev($str1[0].$str1[1]);*/																																																						
		$newUser['mail']   = strtolower(trim($form_state['values']['email']));
		$newUser['status'] = 1;
		
		user_save(null, $newUser);
		
		/*get last inserted uid*/
		
		$query = db_select('users','u');
		$query->addExpression('MAX(uid)','max_uid');
		$result = $query->execute();
		$data = $result->fetchObject();
		
		/*insert into housing_applicant table*/
		
		$user_reg_arr = array();
		$user_reg_arr['uid'] 				=  $data->max_uid;
		$user_reg_arr['applicant_name'] 	=  strtoupper(trim($form_state['values']['applicant_name']));
		$user_reg_arr['gender'] 			=  trim($form_state['values']['gender']);
		$user_reg_arr['date_of_birth'] 	=  trim( implode('-', array_reverse(explode('/', $form_state['values']['dob']))));
		$user_reg_arr['mobile_no'] 		=  trim($form_state['values']['mobile']);
		
		db_insert('housing_applicant')
		->fields($user_reg_arr)
		->execute();
		
		/*insert into housing_applicant_official_detail table*/
		
		$app_off_detail_arr = array();
		$app_off_detail_arr['uid'] = $data->max_uid;
		$app_off_detail_arr['hrms_id']  =  trim($form_state['values']['hrms_id']);
		$app_off_detail_arr['applicant_designation']  =  strtoupper(trim($form_state['values']['app_designation']));
		$app_off_detail_arr['office_name']  =  strtoupper(trim($form_state['values']['office_name']));
		
		db_insert('housing_applicant_official_detail')
  	  	->fields($app_off_detail_arr)
  	  	->execute();
		
		/*assign user roles*/
		
		$arr_user_roles = array();
		$arr_user_roles['uid'] = $user_reg_arr['uid'];
		$arr_user_roles['rid'] = 4;
		
		db_insert('users_roles')
		->fields($arr_user_roles)
		->execute();
		
	//For mail username and password.
		$receiver_mobile = trim($form_state['values']['mobile']);
		$receiver_email = strtolower(trim($form_state['values']['email']));
		
		$ack_msg = '<html><body>Dear Applicant,<br><br>
		You have Successfully Registered. Please find below your login details. Please change your password after login.<br><br>
		Username	-	'.$username.'<br><br>
		Password	-	'.$username.'<br><br>
		Please login using your username and password to apply.<br><br>
		Regards,<br>
		Housing Department<br>
		Government of West Bengal
		</html></body>';

		$email_subject = 'Applicant Login Details';
		
		//send_sms($receiver_mobile, $ack_msg);
		sendmail_registration($receiver_email, $email_subject, $ack_msg);
		
	//End
		
		$uid = encrypt_url($data->max_uid);
		drupal_set_message(t('You have Successfully Registered!!! You should receive an email from us soon containing your login details!!!'));
		drupal_goto('application_registration/'.$uid);
		/*after login*/
		
		/*$username = $form_state['values']['username'];
		$pass = 'housing';
		$userRecord = user_authenticate($username, $pass);
		$form_state['uid'] = $userRecord;
		user_login_submit(array(), $form_state);*/
		
		
	}
	
	/*function element_validate_alphabatic_text1($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[a-zA-Z\s]*$/",$value)) {
			form_error($element, t('" %name " must be a alphabatic letter.', array('%name' => $element['#title'])));
			$form_state['rebuild'] = TRUE;
		}
	}*/
	
	/*function element_validate_mobile1($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/[6789][0-9]{9}/",$value)) {
			form_error($element, t('" %name " must be a valid 10 digits no.', array('%name' => $element['#title'])));
			$form_state['rebuild'] = TRUE;
		}
	}*/