<?php

	function user_profile_edit_form($form, &$form_state, $uid) {
		global $user_role;
		$uid = decrypt_url($uid);
		
		if(!empty($uid)) {
			$user_info = get_user_all_details_by_uid($uid);
		}
	
		$form['user_id'] = array(
			'#type' => 'hidden',
			'#default_value' => $uid,
	  	);
		
		if($user_role == 8 || $user_role == 7 || $user_role == 6 || $user_role == 9 || $user_role == 10) {
			$form['full_name'] = array(
				'#type' => 'textfield',
				'#title' => 'Name',
				'#default_value' => $user_info['full_name'],
				'#required' => TRUE,
				'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('readonly' => 'readonly', 'oninput' => "this.value=this.value.toUpperCase()"),
				'#prefix' => '<div class="two">',
				'#suffix' => '</div>', 
			);
			
			$form['email'] = array(
				'#title' => t('Email ID'),
				'#type' => 'textfield',
				'#default_value' => $user_info['mail'],
				'#attributes' => array('oninput' => "this.value=this.value.toLowerCase()"),
				'#required' => TRUE,
				'#prefix' => '<div class="two">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_email'),
			);
			
			$form['mobile_no'] = array(
				'#type' => 'textfield',
				'#title' => 'Mobile No',
				'#default_value' => $user_info['mobile_no'],
				'#maxlength' => 10,
				'#attributes' => array('id' => 'user_mobile_no'),
				'#required' => TRUE,
				'#element_validate' => array('element_validate_mobile'),
				'#prefix' => '<div class="two">',
				'#suffix' => '</div>',  
			);
			
			$form['office_phone_no'] = array(
				'#type' => 'textfield',
				'#title' => 'Telephone No.(With STD Code)',
				'#default_value' => $user_info['office_phone_no'],
				'#maxlength' => 15,
				'#attributes' => array('id' => 'office_phone_no'),
				'#required' => TRUE,
				'#element_validate' => array('element_validate_telephoneno'),
				'#prefix' => '<div class="two">',
				'#suffix' => '</div>', 
			);
			
			$form['#attributes'] = array('onsubmit' => 'return validate_user_profile_edit_form()');
			
			$form['submit'] = array(
				'#value' => t('Update'),
				'#type' => 'submit',
			);
		}
		
		return $form;
	}
	
	function user_profile_edit_form_validate($form, &$form_state) {
		global $user_role;
		$uid = trim($form_state['values']['user_id']);
		
		$query = db_select('users', 'u');
		$query->innerJoin('users_details', 'ud', 'u.uid = ud.uid');
		$query->fields('u', array());
		$query->fields('ud', array());
		$query->condition('u.uid', $uid, '=');
		$result = $query->execute();
		$row_count = $result->rowCount();
		if($row_count > 0) {
			$data = $result->fetchObject();
		}
		
		$value_fullname = strtoupper(trim($form_state['values']['full_name']));
		$value_email = strtolower(trim($form_state['values']['email']));
		$value_mobile = trim($form_state['values']['mobile_no']);
		$value_office_phone_no = trim($form_state['values']['office_phone_no']);
		
		if($user_role == 8 || $user_role == 7 || $user_role == 6 || $user_role == 9 || $user_role == 10) {
			if($value_fullname != '' && $value_email != '' && $value_mobile != '' && $value_office_phone_no != ''){
				if($value_fullname == $data->full_name && $value_email == $data->mail && $value_mobile == $data->mobile_no && $value_office_phone_no == $data->office_phone_no) {
					form_set_error('', t('Data are same. No data changed.'));	
				}
			}	
		}
		
		//email id duplicate checking
		if(!empty($value_email)) {
			 
			$query1 = db_select('users', 'u');
			$query1->fields('u', array('mail'));
			
			$query1->condition('u.uid', $uid, '=');
			
			$result1 = $query1->execute();
			while($data = $result1->fetchObject()) {
				if($data->mail != $value_email) {
					$query = db_select('users','u');
					$query->addExpression('mail','email');
					$query->condition('mail', $value_email);
					$result = $query->execute();
					
					if($result->rowCount() > 0)
						form_set_error('email', 'This Email address already exist.');
				}
			}
		
		}
		
		//mobile no duplicate checking
		if(!empty($value_mobile) && is_numeric($value_mobile)) {
			 
			 $query = db_select('users_details', 'ud');
			 $query->addField('ud', 'mobile_no');
			 $query->condition('ud.uid', $uid, '=');
			 $result = $query->execute();
			 while($data = $result->fetchObject()) {
				if($data->mobile_no != $value_mobile) {
					$query1 = db_select('users_details','ud');
					$query1->addExpression('mobile_no','mobile');
					$query1->condition('mobile_no', $value_mobile);
					$result1 = $query1->execute();
			 
					if($result1->rowCount() > 0)
						form_set_error('mobile_no', 'This mobile no. already exist.');
				}
			 }
		
		}
		
	}
	
	function user_profile_edit_form_submit($form, &$form_state) {
		global $user_role;	
		
		$uid = trim($form_state['values']['user_id']);
		
		if($user_role == 8 || $user_role == 7 || $user_role == 6 || $user_role == 9 || $user_role == 10) {
			
			$user_tbl_arr = array();
			$user_tbl_arr['mail'] = strtolower(trim($form_state['values']['email']));
			db_update('users')
			->fields($user_tbl_arr)
			->condition('uid', $uid, '=')
			->execute();
			
			$user_details_tbl_arr = array();
				
			if($form_state['values']['mobile_no'] != '')
				$user_details_tbl_arr['mobile_no'] = $form_state['values']['mobile_no'];
			
			//if($form_state['values']['office_phone_no'] != '')
				$user_details_tbl_arr['office_phone_no'] = $form_state['values']['office_phone_no'];
				
			db_update('users_details')
			->fields($user_details_tbl_arr)
			->condition('uid', $uid)
			->execute();
			
			drupal_set_message(t('You have Successfully Updated Your Profile.'));
			drupal_goto('user');	
			
		}
		
	}