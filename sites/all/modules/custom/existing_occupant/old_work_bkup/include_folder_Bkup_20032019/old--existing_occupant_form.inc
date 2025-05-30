<?php

	function existing_occupant_form($form, &$form_state, $param) {
		
		$district = isset($form_state['values']['district']) && !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
		
		$designation = isset($form_state['values']['designation']) && !empty($form_state['values']['designation']) ? $form_state['values']['designation'] : '';
		$dob = isset($form_state['values']['dob']) && !empty($form_state['values']['dob']) ? $form_state['values']['dob'] : '';
		
		$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	  $rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
	  $reason = isset($form_state['values']['reason']) && !empty($form_state['values']['reason']) ? $form_state['values']['reason'] : '';
	  
	  
	  $occupied_estate_default = isset($form['occupied_estate']['#default_value']) && !empty($form['occupied_estate']['#default_value']) ? $form['occupied_estate']['#default_value'] : '';
	
		$occupied_block_default = isset($form['occupied_block']['#default_value']) && !empty($form['occupied_block']['#default_value']) ? $form['occupied_block']['#default_value'] : '';
	
		$occupied_estate = isset($form_state['values']['occupied_estate']) && !empty($form_state['values']['occupied_estate']) ? $form_state['values']['occupied_estate'] : $occupied_estate_default;
	
		$occupied_block = isset($form_state['values']['occupied_block']) && !empty($form_state['values']['occupied_block']) ? $form_state['values']['occupied_block'] : $occupied_block_default;
		
		
		$form['form_begin'] = array(
			'#type' => 'markup',
			'#markup' => '<div class="online_application">',
			'#weight' => -2
		);
		
		//personal information
		$form['prrsonal_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Personal Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE,  // Added
		);
						
		$form['prrsonal_info']['applicant_name'] = array(
			'#title' => t('Applicant\'s Name'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two ">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#required' => TRUE,
		);
		
		$form['prrsonal_info']['applicant_father_name'] = array(
			'#title' => t('Father / Husband Name'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#required' => TRUE,
		);
		$form['prrsonal_info']['mobile'] = array(
			'#title' => t('Mobile no'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#maxlength' => 10,
			//'#required' => TRUE,
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_mobile'),
			'#attributes' => array('id' => 'mobile_no'),
		);
		$form['prrsonal_info']['email'] = array(
			'#title' => t('Email ID'),
			'#type' => 'textfield',
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_email'),
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
		
		// applicant's official information
		$form['official_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Applicant\'s Official Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		$form['official_info']['app_designation'] = array(
			'#title' => t('Designation'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			//'#attributes' => array('id' => 'edit-app-designation', 'oncopy' => "return false", 'onpaste' => "return false"),
		);
		
		$form['official_info']['pay_band'] = array(
			'#title' => t('Pay Band'),
			'#type' => 'select',
			'#options' => pay_band_list(),
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div class="three">',
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
			//'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		$form['official_info']['gpf_no'] = array(
			'#title' => t('GPF No.'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#element_validate' => array('gpf_no_validate'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
		);
		
		$form['official_info']['app_posting_place'] = array(
			'#title' => t('Place of Posting'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
		); 
		$form['official_info']['app_headquarter'] = array(
			'#title' => t('Headquarter'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
		);
		$form['official_info']['doj'] = array(
			'#title' => t('Date of Joining'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doj'),
			'#default_value' => '',
			//'#required' => TRUE,
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
		
		
		// applicant's office address
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
		);
		
		$form['office_add']['office_street'] = array(
			'#title' => t('Street'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="two-one">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_streetaddress'), 
		);
		$form['office_add']['office_city'] = array(
			'#title' => t('City / Town / Village'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
		);
		$form['office_add']['office_post_office'] = array(
			'#title' => t('Post Office'),
			'#type' => 'textfield',
			//'#required' => TRUE,
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
		);
		$form['office_add']['office_pincode'] = array(
			'#title' => t('Pincode'),
			'#type' => 'textfield',
			'#maxlength' => 6,
			'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		// ddo details
		$form['ddo'] = array(
			'#type' => 'fieldset',
			'#title' => t('DDO with full address'),
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
			'#title' => t('DDO Addres'),
			'#type' => 'textarea',
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div id="replace_ddo_address" >',
			'#suffix' => '</div>',
			//'#required' => TRUE,
			//'#validated' => TRUE,
		);
		
		//allotment type and category
		$form['allotment_reason'] = array(
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
		 );
	     
		 
		 $form['allotment_reason']['reason'] = array(
			'#title' => t('Allotment Category'),
			'#type' => 'select',
			//'#options' => array(''=>'- Select -'),
			'#options' => allotment_category_list(trim($rhe_flat_type)),
			'#default_value' => $reason,
			'#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div id="replace_allotment_category" class="two">',
			'#suffix' => '</div>',
		 );
		 
		 $form['allotment_reason']['doa'] = array(
			'#title' => t('Date of Application'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doa'),
			'#required' => TRUE,
			//'#validated' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_date'),
		);
		
		$form['allotment_reason']['computer_serial_no'] = array(
			'#title' => t('Computer Serial No.'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#element_validate' => array('element_validate_alphanumeric'), 
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		
		$form['allotment_reason']['remarks'] = array(
			'#title' => t('Remarks'),
			'#type' => 'textarea',
			'#prefix' => '<div class="one">',
			'#suffix' => '</div>',
			'#element_validate' => array('element_validate_textarea'), 
		);
		
		//Occupied information
		$form['occupied_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Occupied Information'),
			'#collapsible' => TRUE, // Added
			'#collapsed' => TRUE,  // Added
		);
		
		$form['occupied_info']['allotment_no'] = array(
			'#title' => t('Allotment No.'),
			'#type' => 'textfield',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#required' => TRUE,
	  	);
		
		$form['occupied_info']['allotment_date'] = array(
			'#title' => t('Allotment Date'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'allotment-date'),
			'#default_value' => '',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#required' => TRUE,
	  	);
		
		$form['occupied_info']['occupied_estate'] = array(
			'#title' => t('Housing'),
			'#type' => 'select',
			'#options' => get_housing_estate(),
			//'#default_value' => '',
			'#required' => TRUE,
			'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_occupied_flat_no1',
						   'effect' => 'fade',
						   'progress' => array(
							  'type' => '',
							  'message' => '',
							),
				),
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#validated' => TRUE,
		);
		
		$form['occupied_info']['occupied_block'] = array(
			'#title' => t('Block'),
			'#type' => 'select',
			'#options' => get_housing_block(),
			//'#default_value' => '',
			'#required' => TRUE,
			'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_occupied_flat_no1',
						   'effect' => 'fade',
						   'progress' => array(
							  'type' => '',
							  'message' => '',
							),
				),
			'#prefix' => '<div class="three" id="occupied_block_replace">',
			'#suffix' => '</div>',
			'#validated' => TRUE,
		);
		
		$form['occupied_info']['occupied_flat'] = array(
			'#title' => t('Flat No.'),
			'#type' => 'select',
			'#options' => get_housing_flat1($occupied_estate, $occupied_block),
			'#required' => TRUE,
			'#prefix' => '<div class="three" id="occupied_flat_no_replace">',
			'#suffix' => '</div>',
			'#validated' => TRUE,
		);
		 
		 $form['official_info']['pay_band']['#ajax'] = array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_category',
					   'effect' => 'fade',
					   'progress' => array(
						  'type' => '',
						  'message' => '',
						 )
		);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_existing_occupant_form()');
		
		$form['form_end'] = array(
			'#type' => 'markup',
			'#markup' => '</div>',
		);
		
		$form['submit_button']=array(
										'#type'=>'submit',
										'#value'=>t('Submit')
								);
		
		return $form;
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
		if($form_state['values']['reason'] == '') {
  			form_set_error('reason', t('Please select allotment reason.'));
		}
		
		if($form_state['values']['occupied_estate'] == '') {
			form_set_error('occupied_estate', t('Please select the housing'));
		}
		  
		if($form_state['values']['occupied_block'] == '') {
			form_set_error('occupied_block', t('Please select the block'));
		}
		  
		if($form_state['values']['occupied_flat'] == '') {
			form_set_error('occupied_flat', t('Please select the flat no.'));
		}	
		
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
		
	}
	
	
	function existing_occupant_form_submit($form, &$form_state) {
		
		die(print_r($form_state['values']));
		
	}
	
	
	
	function _reload_occupied_flat_no1($form, &$form_state) {
	
		$commands[] = ajax_command_replace('#occupied_block_replace', drupal_render($form['occupied_info']['occupied_block']));
		$commands[] = ajax_command_replace('#occupied_flat_no_replace', drupal_render($form['occupied_info']['occupied_flat']));
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}
	