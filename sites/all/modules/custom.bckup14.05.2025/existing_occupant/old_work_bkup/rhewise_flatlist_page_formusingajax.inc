<?php
		
	function rhewise_flatlist_form($form, &$form_state) {
		/*$rhe_name_default = isset($form['rhe_name']['#default_value']) && !empty($form['rhe_name']['#default_value']) ? $form['rhe_name']['#default_value'] : 0;
		$flat_type_default = isset($form['flat_type']['#default_value']) && !empty($form['flat_type']['#default_value']) ? $form['flat_type']['#default_value'] : 0;
		$block_name_default = isset($form['block_name']['#default_value']) && !empty($form['block_name']['#default_value']) ? $form['block_name']['#default_value'] : 0;
		$flat_no_default = isset($form['flat_no']['#default_value']) && !empty($form['flat_no']['#default_value']) ? $form['flat_no']['#default_value'] : 0;*/
		
		$rhe_name =  isset($form_state['values']['rhe_name']) && !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : 0;
		$flat_type =  isset($form_state['values']['flat_type']) &&!empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : 0;
		$block_name =  isset($form_state['values']['block_name']) &&!empty($form_state['values']['block_name']) ? $form_state['values']['block_name'] : 0;
		$flat_no =  isset($form_state['values']['flat_no']) &&!empty($form_state['values']['flat_no']) ? $form_state['values']['flat_no'] : 0;
		
		$dob = isset($form_state['values']['dob']) && !empty($form_state['values']['dob']) ? $form_state['values']['dob'] : '';
		
		$district = isset($form_state['values']['district']) && !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
		$designation = isset($form_state['values']['designation']) && !empty($form_state['values']['designation']) ? $form_state['values']['designation'] : '';
		
		$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	  	//$rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
		
		/*$query = db_select('housing_pay_band', 'hpb')->fields('hpb');
		$query->condition('flat_type_id', $flat_type, '=');
		$result = $query->execute();
		$data = $result->fetchObject();*/
		
		$form['rhe_name'] = array(
			'#title' => t('Name of the RHE'),
			'#type' => 'select',
			//'#options' => rhe_list_specific(),
			'#options' => rhe_list_specific(),
			'#required' => TRUE,
			//'#weight' => -10,
			'#prefix' => '<div>',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_flat_type',
				'method' => 'replace',
			),
			'#select2' => array(
				'width' => '150',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)
		);
		
		$form['flat_type'] = array(
			'#title' => t('Flat Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			//'#weight' => -10,
			'#prefix' => '<div class="three" id="flat_type_replace">',
			'#suffix' => '</div>',
			'#attributes' => array('class'	=> array('dropdown3')),
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_blocklist',
				'method' => 'replace',
			),
		);
			
		if($rhe_name != 0) {
			$form['flat_type'] = array(
				'#title' => t('Flat Type'),
				'#type' => 'select',
				'#options' => flat_type_under_rhe($rhe_name),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="flat_type_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_blocklist',
					'method' => 'replace',
				),
			);
		}
		
		$form['block_name'] = array(
			'#title' => t('Name of the Block'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			//'#weight' => -10,
			'#prefix' => '<div class="three" id="block_name_replace">',
			'#suffix' => '</div>',
			'#attributes' => array('class'	=> array('dropdown3')),
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_flatlist',
				'method' => 'replace',
			),
		);
			
		if($rhe_name != 0 && $flat_type != 0) {
			$form['block_name'] = array(
				'#title' => t('Name of the Block'),
				'#type' => 'select',
				'#options' => block_name_under_rhe($rhe_name, $flat_type),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="block_name_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_flatlist',
					'method' => 'replace',
				),
			);
		}
		
		$form['flat_no'] = array(
			'#title' => t('Flat No.'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			//'#weight' => -10,
			'#prefix' => '<div class="three" id="flat_no_replace">',
			'#suffix' => '</div>',
			'#attributes' => array('class'	=> array('dropdown3')),
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_occupant_entry',
				'method' => 'replace',
			),
		);
			
		if($rhe_name != 0 && $flat_type != 0 && $block_name != 0) {
			$form['flat_no'] = array(
				'#title' => t('Flat No.'),
				'#type' => 'select',
				'#options' => flatno_under_rhe($rhe_name, $flat_type, $block_name),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="flat_no_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_occupant_entry',
					'method' => 'replace',
				),
			);
		}
		
		
		$form['occupant_name'] = array(
			'#prefix' => '<div id="occupant_name_replace">',
			'#suffix' => '</div>',
		);
		$form['occupant_father_name'] = array(
			'#prefix' => '<div id="occupant_father_name_replace">',
			'#suffix' => '</div>',
		);
		$form['mobile'] = array(
			'#prefix' => '<div id="mobile_replace">',
			'#suffix' => '</div>',
		);
		$form['email'] = array(
			'#prefix' => '<div id="email_replace">',
			'#suffix' => '</div>',
		);
		$form['dob'] = array(
			'#prefix' => '<div id="dob_replace">',
			'#suffix' => '</div>',
		);
		$form['gender'] = array(
			'#prefix' => '<div id="gender_replace">',
			'#suffix' => '</div>',
		);
		
		$form['occupant_designation'] = array(
			'#prefix' => '<div  id="occupant_designation_replace">',
			'#suffix' => '</div>',
		);
		$form['pay_band'] = array(
			'#prefix' => '<div  id="pay_band_replace">',
			'#suffix' => '</div>',
		);
		$form['pay_in'] = array(
			'#prefix' => '<div  id="pay_in_replace">',
			'#suffix' => '</div>',
		);
		$form['grade_pay'] = array(
			'#prefix' => '<div  id="grade_pay_replace">',
			'#suffix' => '</div>',
		);
		$form['gpf_no'] = array(
			'#prefix' => '<div  id="gpf_no_replace">',
			'#suffix' => '</div>',
		);
		$form['occupant_posting_place'] = array(
			'#prefix' => '<div  id="occupant_posting_place_replace">',
			'#suffix' => '</div>',
		);
		$form['occupant_headquarter'] = array(
			'#prefix' => '<div  id="occupant_headquarter_replace">',
			'#suffix' => '</div>',
		);
		$form['doj'] = array(
			'#prefix' => '<div  id="doj_replace">',
			'#suffix' => '</div>',
		);
		$form['dor'] = array(
			'#prefix' => '<div  id="dor_replace">',
			'#suffix' => '</div>',
		);
		
		$form['office_name'] = array(
			'#prefix' => '<div id="office_name_replace">',
			'#suffix' => '</div>',
		);
		
		$form['office_street'] = array(
			'#prefix' => '<div id="office_street_replace">',
			'#suffix' => '</div>',
		);
		$form['office_city'] = array(
			'#prefix' => '<div id="office_city_replace">',
			'#suffix' => '</div>',
		);
		$form['office_post_office'] = array(
			'#prefix' => '<div id="office_post_office_replace">',
			'#suffix' => '</div>',
		);
		$form['office_pincode'] = array( 
			'#prefix' => '<div id="office_pincode_replace">',
			'#suffix' => '</div>',
		);
			
		$form['district'] = array(
			'#prefix' => '<div id="ddo_district_replace">',
			'#suffix' => '</div>',
		);
		$form['designation'] = array(
			'#prefix' => '<div id="replace_designation">',
			'#suffix' => '</div>',
		);
		$form['address'] = array(
			'#prefix' => '<div id="replace_ddo_address">',
			'#suffix' => '</div>',
		);
		
		/*$form['rhe_flat_type'] = array(
			'#prefix' => '<div id="replace_rhe_flat_type">',
			'#suffix' => '</div>',
		);*/
		$form['submit_button'] = array(
			'#prefix' => '<div class="two" id="submit_button_replace" >',
			'#suffix' => '</div>',
		);
		
		if($rhe_name != 0 && $flat_type != 0 && $block_name != 0 && $flat_no != 0) {
			//personal information
			$form['occupant_name'] = array(
				'#title' => t('Occupant\'s Name'),
				'#type' => 'textfield',
				'#prefix' => '<div class="two" id="occupant_name_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
				'#required' => TRUE,
			);
			
			$form['occupant_father_name'] = array(
				'#title' => t('Father / Husband Name'),
				'#type' => 'textfield',
				'#default_value' => '',
				'#prefix' => '<div class="two" id="occupant_father_name_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
				'#required' => TRUE,
			);
			$form['mobile'] = array(
				'#title' => t('Mobile no'),
				'#type' => 'textfield',
				'#default_value' => '',
				'#maxlength' => 10,
				'#required' => TRUE,
				'#prefix' => '<div class="four" id="mobile_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_mobile'),
				'#attributes' => array('id' => 'mobile_no'),
			);
			$form['email'] = array(
				'#title' => t('Email ID'),
				'#type' => 'textfield',
				'#prefix' => '<div class="four" id="email_replace">',
				'#suffix' => '</div>',
				'#required' => TRUE,
				'#element_validate' => array('element_validate_email'),
				'#attributes' => array('oninput'=>"this.value=this.value.toLowerCase()"),
			);
			
			$form['dob'] = array(
				'#title' => t('Date of Birth'),
				'#type' => 'textfield',
				'#attributes' => array('readonly' => 'readonly', 'id' => 'occupant-dob'),
				'#required' => TRUE,
				//'#validated' => TRUE,
				'#prefix' => '<div class="four" id="dob_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_date', 'element_validate_age'),
			);
			
			$form['gender'] = array(
				'#title' => t('Gender'),
				'#type' => 'radios',
				'#options' => array('M' => 'Male', 'F' => 'Female'),
				'#attributes' => array('class' => array('gender')),
				'#default_value' => 'M',
				'#prefix' => '<div class="four" id="gender_replace">',
				'#suffix' => '</div>',
				'#required' => TRUE,
			);
			
			// occupant's official information
			$form['occupant_designation'] = array(
				'#title' => t('Designation'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#prefix' => '<div class="three" id="occupant_designation_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
				//'#attributes' => array('id' => 'edit-app-designation', 'oncopy' => "return false", 'onpaste' => "return false"),
			);
			
			/*$form['pay_band'] = array(
				'#title' => t('Pay Band'),
				'#type' => 'select',
				'#options' => pay_band_list(),
				'#required' => TRUE,
				'#validated' => TRUE,
				'#prefix' => '<div class="two-one" id="pay_band_replace">',
				'#suffix' => '</div>',
			);*/
			
			$form['pay_band'] = array(
				'#title' => t('Pay Band'),
				'#type' => 'select',
				'#options' => pay_band_list_specific($flat_type),
				//'#default_value' => $data->pay_band_id,
				//'#disabled' => TRUE,
				'#required' => TRUE,
				'#validated' => TRUE,
				'#prefix' => '<div class="two-one" id="pay_band_replace">',
				'#suffix' => '</div>',
			);
			
			$form['pay_in'] = array(
				'#title' => t('Pay in the Pay Band'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#element_validate' => array('element_validate_numeric_positive'), 
				'#prefix' => '<div class="three" id="pay_in_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class' => array('numeric_positive')),
			);
			
			$form['grade_pay'] = array(
				'#title' => t('Grade Pay'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#element_validate' => array('element_validate_numeric_positive'), 
				'#prefix' => '<div class="three" id="grade_pay_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class' => array('numeric_positive')),
			);
			
			$form['gpf_no'] = array(
				'#title' => t('GPF No.'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#element_validate' => array('gpf_no_validate'), 
				'#prefix' => '<div class="three" id="gpf_no_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
			);
			
			$form['occupant_posting_place'] = array(
				'#title' => t('Place of Posting'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#prefix' => '<div class="two" id="occupant_posting_place_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
			); 
			$form['occupant_headquarter'] = array(
				'#title' => t('Office Headquarter'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#prefix' => '<div class="two" id="occupant_headquarter_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
			);
			$form['doj'] = array(
				'#title' => t('Date of Joining'),
				'#type' => 'textfield',
				'#attributes' => array('readonly' => 'readonly', 'id' => 'occupant-doj'),
				'#default_value' => '',
				'#required' => TRUE,
				'#prefix' => '<div class="two" id="doj_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
			);
			
			$form['dor'] = array(
				'#title' => t('Date of Retirement'),
				'#type' => 'textfield',
				//'#attributes' => array('readonly' => 'readonly'),
				'#attributes' => array('readonly' => 'readonly', 'id' => 'occupant-dor'),
				'#default_value' => '',
				'#required' => TRUE,
				'#prefix' => '<div class="two" id="dor_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_date'),
			);
			
			// occupant's office address
			$form['office_name'] = array(
				'#title' => t('Name of the Office'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#prefix' => '<div class="three" id="office_name_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_hyphenFullStopAmpersand'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
			);
			
			$form['office_street'] = array(
				'#title' => t('Address of the Office'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#prefix' => '<div class="two-one" id="office_street_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_streetaddress'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
			);
			$form['office_city'] = array(
				'#title' => t('City/Town/Village of the Office'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#prefix' => '<div class="three" id="office_city_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), 
			);
			$form['office_post_office'] = array(
				'#title' => t('Post Office of the Office'),
				'#type' => 'textfield',
				'#required' => TRUE,
				'#prefix' => '<div class="three" id="office_post_office_replace">',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
			);
			$form['office_pincode'] = array(
				'#title' => t('Pincode of the Office'),
				'#type' => 'textfield',
				'#maxlength' => 6,
				'#required' => TRUE,
				'#element_validate' => array('element_validate_numeric_positive'), 
				'#prefix' => '<div class="three" id="office_pincode_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class' => array('numeric_positive')),
			);
		
			// ddo details
			$form['district'] = array(
				'#title' => t('DDO District'),
				'#type' => 'select',
				'#options' => district_list(),
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_designation_of_ddo',
						  // 'wrapper' => 'replace_designation',
						   'effect' => 'fade',
						   'progress' => array(
							  'type' => '',
							  'message' => '',
							), 
				 ),
				'#required' => TRUE,
				'#validated' => TRUE,
				'#prefix' => '<div class="two" id="ddo_district_replace">',
				'#suffix' => '</div>',
			);
			
			
			$form['designation'] = array(
				'#title' => t('DDO Designation'),
				'#type' => 'select',
				//'#options' => array('- Select -'),
				'#options' => ddo_desig_list($district),
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_address_of_ddo',
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
				'#attributes' => array('class'	=> array('designation_selectize')),
			);
			
			$form['address'] = array(
				'#title' => t('DDO Address'),
				'#type' => 'textarea',
				'#attributes' => array('readonly' => 'readonly'),
				'#prefix' => '<div id="replace_ddo_address" class="one">',
				'#suffix' => '</div>',
				//'#required' => TRUE,
				//'#validated' => TRUE,
			);
			
			//allotment type and category
			/*$form['rhe_flat_type'] = array(
				'#title' => t('Flat TYPE'),
				'#type' => 'textfield',
				'#attributes' => array('readonly' => 'readonly'),
				'#default_value' => $flat_type,
				'#required' => TRUE,
				'#prefix' => '<div class="two-one" id="replace_rhe_flat_type" >',
				'#suffix' => '</div>',
				'#element_validate' => array('element_validate_flat_type'),
			 );
			 
			 $form['pay_band']['#ajax'] = array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_rhe_flat_type',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						 )
			 );*/
			 
			
			 $form['submit_button']=array(
					'#type'=>'submit',
					'#prefix' => '<div class="two" id="submit_button_replace" >',
					'#suffix' => '</div>',
					'#value'=>t('Submit'),
			 );
		}
		$form['#attributes'] = array('onsubmit' => 'return validate_existing_occupant_form()');
		
		return $form;
	}
	
	function rhewise_flatlist_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
		
		if($form_state['values']['pay_band'] == '') {
  			form_set_error('payband', t('Please select payband.'));
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
	
	function rhewise_flatlist_form_submit($form, &$form_state) {
		//$form_state['rebuild'] = TRUE;
		
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
		$newUser['name']   = $username;
		$newUser['pass']   = $username;
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
		$user_reg_arr['uid'] 				=  $data->max_uid;
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
		$arr_user_roles['uid'] = $user_reg_arr['uid'];
		$arr_user_roles['rid'] = 5;
		
		db_insert('users_roles')
		->fields($arr_user_roles)
		->execute();
		
		/*add applicant_official_detail  data*/
		$app_off_detail_arr = array();
		$app_off_detail_arr['uid']  =  $data->max_uid;
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
		$result1 =$query1->execute();
		$data1 = $result1->fetchObject();
		
		/*add online application*/
		
		$online_app_arr = array();
		$online_app_arr['applicant_official_detail_id']  =  $data1->id;
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
		$new_allotment_app_arr['online_application_id']  =  $data2->oid;
		
		$new_allotment_app_arr['flat_type_id'] = trim($form_state['values']['flat_type']);
		//$new_allotment_app_arr['allotment_category']  =  trim($form_state['values']['reason']);
		
		db_insert('housing_new_allotment_application')
  	  	->fields($new_allotment_app_arr)
  	  	->execute();
		
		/*Flat status update and Add flat occupant details*/
		db_update('housing_flat')
			->fields(array(
						'flat_status_id' => 2
					))
			->condition('flat_id', $form_state['values']['flat_no'])
			->execute();
			
		$allotment_ins_arr = array();
		$allotment_ins_arr['online_application_id']  = $data2->oid;
		$allotment_ins_arr['flat_id']  = trim($form_state['values']['flat_no']);;
		$allotment_ins_arr['allotment_date']  =  NULL;
		
		//$allotment_ins_arr['allotment_no'] = 'NAL-'.$data2->oid.'-'.date("dmY");
		//$allotment_ins_arr['allotment_process_no'] = ;
	
		db_insert('housing_flat_occupant')
		->fields($allotment_ins_arr)
		->execute();
		
		//$flatno = $form_state['values']['occupied_flat'];
		//drupal_set_message('Occupant Data for Flat No.- '.$flatno.' Inserted Successfully.');
		drupal_set_message('Occupant Data Inserted Successfully.');
		drupal_goto('rhewise_flatlist');
	}
	
	function _reload_rhewise_flat_type($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_type_replace", drupal_render($form['flat_type']));
		$commands[] = ajax_command_replace("#block_name_replace", drupal_render($form['block_name']));
		$commands[] = ajax_command_replace("#flat_no_replace", drupal_render($form['flat_no']));
		
		$commands[] = ajax_command_replace("#occupant_name_replace", drupal_render($form['occupant_name']));
		$commands[] = ajax_command_replace("#occupant_father_name_replace", drupal_render($form['occupant_father_name']));
		$commands[] = ajax_command_replace("#mobile_replace", drupal_render($form['mobile']));
		$commands[] = ajax_command_replace("#email_replace", drupal_render($form['email']));
		$commands[] = ajax_command_replace("#dob_replace", drupal_render($form['dob']));
		$commands[] = ajax_command_replace("#gender_replace", drupal_render($form['gender']));
		
		$commands[] = ajax_command_replace("#occupant_designation_replace", drupal_render($form['occupant_designation']));
		$commands[] = ajax_command_replace("#pay_band_replace", drupal_render($form['pay_band']));
		$commands[] = ajax_command_replace("#pay_in_replace", drupal_render($form['pay_in']));
		$commands[] = ajax_command_replace("#grade_pay_replace", drupal_render($form['grade_pay']));
		$commands[] = ajax_command_replace("#gpf_no_replace", drupal_render($form['gpf_no']));
		$commands[] = ajax_command_replace("#occupant_posting_place_replace", drupal_render($form['occupant_posting_place']));
		$commands[] = ajax_command_replace("#occupant_headquarter_replace", drupal_render($form['occupant_headquarter']));
		$commands[] = ajax_command_replace("#doj_replace", drupal_render($form['doj']));
		$commands[] = ajax_command_replace("#dor_replace", drupal_render($form['dor']));
		
		$commands[] = ajax_command_replace("#office_name_replace", drupal_render($form['office_name']));
		$commands[] = ajax_command_replace("#office_street_replace", drupal_render($form['office_street']));
		$commands[] = ajax_command_replace("#office_city_replace", drupal_render($form['office_city']));
		$commands[] = ajax_command_replace("#office_post_office_replace", drupal_render($form['office_post_office']));
		$commands[] = ajax_command_replace("#office_pincode_replace", drupal_render($form['office_pincode']));
		
		$commands[] = ajax_command_replace("#ddo_district_replace", drupal_render($form['district']));
		$commands[] = ajax_command_replace("#replace_designation", drupal_render($form['designation']));
		$commands[] = ajax_command_replace("#replace_ddo_address", drupal_render($form['address']));
		
		//$commands[] = ajax_command_replace("#replace_rhe_flat_type", drupal_render($form['rhe_flat_type']));
		$commands[] = ajax_command_replace("#submit_button_replace", drupal_render($form['submit_button']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_blocklist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#block_name_replace", drupal_render($form['block_name']));
		$commands[] = ajax_command_replace("#flat_no_replace", drupal_render($form['flat_no']));
		
		$commands[] = ajax_command_replace("#occupant_name_replace", drupal_render($form['occupant_name']));
		$commands[] = ajax_command_replace("#occupant_father_name_replace", drupal_render($form['occupant_father_name']));
		$commands[] = ajax_command_replace("#mobile_replace", drupal_render($form['mobile']));
		$commands[] = ajax_command_replace("#email_replace", drupal_render($form['email']));
		$commands[] = ajax_command_replace("#dob_replace", drupal_render($form['dob']));
		$commands[] = ajax_command_replace("#gender_replace", drupal_render($form['gender']));
		
		$commands[] = ajax_command_replace("#occupant_designation_replace", drupal_render($form['occupant_designation']));
		$commands[] = ajax_command_replace("#pay_band_replace", drupal_render($form['pay_band']));
		$commands[] = ajax_command_replace("#pay_in_replace", drupal_render($form['pay_in']));
		$commands[] = ajax_command_replace("#grade_pay_replace", drupal_render($form['grade_pay']));
		$commands[] = ajax_command_replace("#gpf_no_replace", drupal_render($form['gpf_no']));
		$commands[] = ajax_command_replace("#occupant_posting_place_replace", drupal_render($form['occupant_posting_place']));
		$commands[] = ajax_command_replace("#occupant_headquarter_replace", drupal_render($form['occupant_headquarter']));
		$commands[] = ajax_command_replace("#doj_replace", drupal_render($form['doj']));
		$commands[] = ajax_command_replace("#dor_replace", drupal_render($form['dor']));
		
		$commands[] = ajax_command_replace("#office_name_replace", drupal_render($form['office_name']));
		$commands[] = ajax_command_replace("#office_street_replace", drupal_render($form['office_street']));
		$commands[] = ajax_command_replace("#office_city_replace", drupal_render($form['office_city']));
		$commands[] = ajax_command_replace("#office_post_office_replace", drupal_render($form['office_post_office']));
		$commands[] = ajax_command_replace("#office_pincode_replace", drupal_render($form['office_pincode']));
		
		$commands[] = ajax_command_replace("#ddo_district_replace", drupal_render($form['district']));
		$commands[] = ajax_command_replace("#replace_designation", drupal_render($form['designation']));
		$commands[] = ajax_command_replace("#replace_ddo_address", drupal_render($form['address']));
		
		//$commands[] = ajax_command_replace("#replace_rhe_flat_type", drupal_render($form['rhe_flat_type']));
		$commands[] = ajax_command_replace("#submit_button_replace", drupal_render($form['submit_button']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_flatlist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_no_replace", drupal_render($form['flat_no']));
		
		$commands[] = ajax_command_replace("#occupant_name_replace", drupal_render($form['occupant_name']));
		$commands[] = ajax_command_replace("#occupant_father_name_replace", drupal_render($form['occupant_father_name']));
		$commands[] = ajax_command_replace("#mobile_replace", drupal_render($form['mobile']));
		$commands[] = ajax_command_replace("#email_replace", drupal_render($form['email']));
		$commands[] = ajax_command_replace("#dob_replace", drupal_render($form['dob']));
		$commands[] = ajax_command_replace("#gender_replace", drupal_render($form['gender']));
		
		$commands[] = ajax_command_replace("#occupant_designation_replace", drupal_render($form['occupant_designation']));
		$commands[] = ajax_command_replace("#pay_band_replace", drupal_render($form['pay_band']));
		$commands[] = ajax_command_replace("#pay_in_replace", drupal_render($form['pay_in']));
		$commands[] = ajax_command_replace("#grade_pay_replace", drupal_render($form['grade_pay']));
		$commands[] = ajax_command_replace("#gpf_no_replace", drupal_render($form['gpf_no']));
		$commands[] = ajax_command_replace("#occupant_posting_place_replace", drupal_render($form['occupant_posting_place']));
		$commands[] = ajax_command_replace("#occupant_headquarter_replace", drupal_render($form['occupant_headquarter']));
		$commands[] = ajax_command_replace("#doj_replace", drupal_render($form['doj']));
		$commands[] = ajax_command_replace("#dor_replace", drupal_render($form['dor']));
		
		$commands[] = ajax_command_replace("#office_name_replace", drupal_render($form['office_name']));
		$commands[] = ajax_command_replace("#office_street_replace", drupal_render($form['office_street']));
		$commands[] = ajax_command_replace("#office_city_replace", drupal_render($form['office_city']));
		$commands[] = ajax_command_replace("#office_post_office_replace", drupal_render($form['office_post_office']));
		$commands[] = ajax_command_replace("#office_pincode_replace", drupal_render($form['office_pincode']));
		
		$commands[] = ajax_command_replace("#ddo_district_replace", drupal_render($form['district']));
		$commands[] = ajax_command_replace("#replace_designation", drupal_render($form['designation']));
		$commands[] = ajax_command_replace("#replace_ddo_address", drupal_render($form['address']));
		
		//$commands[] = ajax_command_replace("#replace_rhe_flat_type", drupal_render($form['rhe_flat_type']));
		$commands[] = ajax_command_replace("#submit_button_replace", drupal_render($form['submit_button']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_occupant_entry($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#occupant_name_replace", drupal_render($form['occupant_name']));
		$commands[] = ajax_command_replace("#occupant_father_name_replace", drupal_render($form['occupant_father_name']));
		$commands[] = ajax_command_replace("#mobile_replace", drupal_render($form['mobile']));
		$commands[] = ajax_command_replace("#email_replace", drupal_render($form['email']));
		$commands[] = ajax_command_replace("#dob_replace", drupal_render($form['dob']));
		$commands[] = ajax_command_replace("#gender_replace", drupal_render($form['gender']));
		
		$commands[] = ajax_command_replace("#occupant_designation_replace", drupal_render($form['occupant_designation']));
		$commands[] = ajax_command_replace("#pay_band_replace", drupal_render($form['pay_band']));
		$commands[] = ajax_command_replace("#pay_in_replace", drupal_render($form['pay_in']));
		$commands[] = ajax_command_replace("#grade_pay_replace", drupal_render($form['grade_pay']));
		$commands[] = ajax_command_replace("#gpf_no_replace", drupal_render($form['gpf_no']));
		$commands[] = ajax_command_replace("#occupant_posting_place_replace", drupal_render($form['occupant_posting_place']));
		$commands[] = ajax_command_replace("#occupant_headquarter_replace", drupal_render($form['occupant_headquarter']));
		$commands[] = ajax_command_replace("#doj_replace", drupal_render($form['doj']));
		$commands[] = ajax_command_replace("#dor_replace", drupal_render($form['dor']));
		
		$commands[] = ajax_command_replace("#office_name_replace", drupal_render($form['office_name']));
		$commands[] = ajax_command_replace("#office_street_replace", drupal_render($form['office_street']));
		$commands[] = ajax_command_replace("#office_city_replace", drupal_render($form['office_city']));
		$commands[] = ajax_command_replace("#office_post_office_replace", drupal_render($form['office_post_office']));
		$commands[] = ajax_command_replace("#office_pincode_replace", drupal_render($form['office_pincode']));
		
		$commands[] = ajax_command_replace("#ddo_district_replace", drupal_render($form['district']));
		$commands[] = ajax_command_replace("#replace_designation", drupal_render($form['designation']));
		$commands[] = ajax_command_replace("#replace_ddo_address", drupal_render($form['address']));
		
		//$commands[] = ajax_command_replace("#replace_rhe_flat_type", drupal_render($form['rhe_flat_type']));
		$commands[] = ajax_command_replace("#submit_button_replace", drupal_render($form['submit_button']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	/*reload DDO designation list (Ajax Call)*/
	function _reload_designation_of_ddo($form, &$form_state) {
		/*$output = "<script>jQuery('.designation_selectize').select2();</script>";*/
		
		$district = isset($form_state['values']['district']) && !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
		
		$form['address']['#value'] = '';
		if($district == '') {
			$form['designation']['#options'] = array(''=>'- Select -');
		}
		else {
			$form['designation']['#options'] = ddo_desig_list($district);
		}
		$commands = array();
		$commands[] = ajax_command_replace('#replace_ddo_address', drupal_render($form['address']));
		$commands[] = ajax_command_replace('#replace_designation', drupal_render($form['designation']));
		$form_state['rebuild'] = TRUE;
		
		
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	/*reload DDO address (Ajax Call)*/
	function _reload_address_of_ddo($form, &$form_state) {
		 $ddo = isset($form_state['values']['designation']) && !empty($form_state['values']['designation']) ? $form_state['values']['designation'] : '';
		 $form['address']['#value'] = ddo_add($ddo);
		 $form['address']['#attributes']['readonly'] = 'readonly';
		 $commands = array();
		 $commands[] = ajax_command_replace('#replace_ddo_address', drupal_render($form['address']));
		 return array('#type' => 'ajax', '#commands' => $commands);
	 
	}

	/*reload Allotment Category and Choice 1 (Ajax Call)*/
	/*function _reload_allotment_rhe_flat_type($form, &$form_state) {
	
		$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
		$rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
		
		if($rhe_flat_type != ''){
			$form['rhe_flat_type']['#value'] = trim($rhe_flat_type);
		}
		else{
			$form['rhe_flat_type']['#value'] = '';
		}
		
		$commands = array();
		$commands[] = ajax_command_replace('#replace_rhe_flat_type', drupal_render($form['rhe_flat_type']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}*/