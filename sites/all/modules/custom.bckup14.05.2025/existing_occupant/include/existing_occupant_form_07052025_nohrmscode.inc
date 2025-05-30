<?php

	//function existing_occupant_form($form, &$form_state, $flat_id, $hrms_id) {
	function existing_occupant_form($form, &$form_state, $flat_id) {
		$flat_id = decrypt_url($flat_id);
		//$hrms_id = decrypt_url($hrms_id);
		
		$result = occupant_entry_check($flat_id);
		$occupant_rhe = get_occupant_rhe_details($flat_id)->fetchObject();
		//print_r($result);die;//$occupant_rhe)
		//for both api and hrms custom table this line is needed
		/*$hrms_details = fetch_hrms_details($hrms_id);*/
		
		//for custom hrms table only
		/*$hrms_details_data = $hrms_details->fetchObject();*/
		
		$district = isset($form_state['values']['district']) && !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
		$designation = isset($form_state['values']['designation']) && !empty($form_state['values']['designation']) ? $form_state['values']['designation'] : '';
		
		$dob = isset($form_state['values']['dob']) && !empty($form_state['values']['dob']) ? $form_state['values']['dob'] : '';
		
		$pay_band_id = isset($form_state['values']['pay_band']) && !empty($form_state['values']['pay_band']) ? $form_state['values']['pay_band'] : 0;
	  	$rhe_flat_type = rhe_flat_type_rst_pay_band_id($pay_band_id);
	  	//$reason = isset($form_state['values']['reason']) && !empty($form_state['values']['reason']) ? $form_state['values']['reason'] : '';
		
		$chk_permanent_address = isset($form_state['values']['chk_permanent_address']) ? $form_state['values']['chk_permanent_address'] : '';
		
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
			'#title' => t('Occupant\'s Flat Information'),
			//'#collapsible' => TRUE, // Added
			'#collapsible' => FALSE,
			'#collapsed' => FALSE, // Added
		);
		
		$form['occupied_info']['occupied_district'] = array(
			'#title' => t('District Name'),
			'#type' => 'textfield',
			'#default_value' => $district_name,
			'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_alphabatic_text'),
			'#required' => TRUE,
	  	);
		
		$form['occupied_info']['occupied_estate'] = array(
			'#title' => t('Rental Housing Estate Name'),
			'#type' => 'textfield',
			'#default_value' => $estate_name,
			'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('element_validate_streetaddress'),
			'#required' => TRUE,
		);
		
		$form['occupied_info']['occupied_flattype'] = array(
			'#title' => t('Flat Type'),
			'#type' => 'textfield',
			'#default_value' => $flat_type,
			'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('validate_rhe_flattype'),
			'#required' => TRUE,
		);
		
		$form['occupied_info']['occupied_block'] = array(
			'#title' => t('Block Name'),
			'#type' => 'textfield',
			'#default_value' => $block_name,
			'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('validate_rhe_block1'),
			'#required' => TRUE,
		);
		
		$form['occupied_info']['occupied_flat'] = array(
			'#title' => t('Flat No.'),
			'#type' => 'textfield',
			'#default_value' => $flat_no,
			'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			//'#element_validate' => array('validate_flat_no'),
			'#required' => TRUE,
		);
		
		//personal information
		$form['prrsonal_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Occupant\'s Personal Information(According to Service Book)'),
			//'#collapsible' => TRUE, // Added
			//'#collapsed' => TRUE,  // Added
			'#collapsible' => FALSE, // Added
			'#collapsed' => FALSE,  // Added
		);
						
		$form['prrsonal_info']['occupant_name'] = array(
			'#title' => t('Occupant\'s Name'),
			'#type' => 'textfield',
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#default_value' => '',
			//for api
			//'#default_value' => strtoupper($hrms_details['data']['ai_worker_name']),
			//for custom hrms table
			//'#default_value' => strtoupper($hrms_details_data->emp_name),
			'#element_validate' => array('element_validate_alphabatic_fullstop'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
			'#required' => TRUE,
		);
		
		$form['prrsonal_info']['occupant_father_name'] = array(
			'#title' => t('Father\'s / Husband\'s Name'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			//for custom hrms table
			//'#default_value' => strtoupper($hrms_details_data->emp_father_name),
			'#element_validate' => array('element_validate_alphabatic_fullstop'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
			// '#required' => TRUE,
		);
		
	//Permanent Address
		$form['prrsonal_info']['permanent_address'] = array(
			'#type' => 'fieldset',
			'#title' => t('Permanent Address'),
			'#collapsible' => FALSE, // Added
			'#collapsed' => FALSE,  // Added
		);
		$form['prrsonal_info']['permanent_address']['permanent_street'] = array(
			'#title' => t('Address'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_streetaddress'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
		);
		$form['prrsonal_info']['permanent_address']['permanent_city_town_village'] = array(
			'#title' => t('City / Town / Village'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
		);
		$form['prrsonal_info']['permanent_address']['permanent_post_office'] = array(
			'#title' => t('Post Office'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
		);
		$form['prrsonal_info']['permanent_address']['permanent_district'] = array(
			'#title' => t('District'),
			'#type' => 'select',
			'#options' => district_list(),
			// '#required' => TRUE,
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#attributes' => array('class'=>array('form-select')),
			// '#select2' => array(
			// 	'width' => '500',
			// 	//'placeholder' => '- Select -',
			// 	'allowClear' => TRUE
   //      	)
		);
		$form['prrsonal_info']['permanent_address']['permanent_pincode'] = array(
			'#title' => t('Pincode'),
			'#type' => 'textfield',
			'#maxlength' => 6,
			// '#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
		);
	//end
	
		// $form['prrsonal_info']['chk_permanent_address'] = array(
		// 	/*'#type' => 'checkboxes',
		// 	'#title' => '',
		// 	'#options' => array(1 => t('Check if Your Present Address is same as Your Permanent Address.')),*/
			
		// 	'#type' => 'checkbox',
		// 	'#title' => 'Check if Your Present Address is same as Your Permanent Address.',
		// 	'#default_value' => '',
		// 	//'#attributes' => array('id' => 'chk_present_address'),     //for this ajax callback not working.
		// 	'#ajax' => array(
		// 			   'event' => 'change',
		// 			   'callback' => '_reload_present_address',
		// 			   'wrapper' => 'replace_present_address',
		// 			   'effect' => 'fade',
		// 			   'progress' => array(
		// 				  'type' => '',
		// 				  'message' => '',
		// 				), 
		// 	 ),
	    // );

		
		if($chk_permanent_address != 1) {
		//Present Address
			$form['prrsonal_info']['present_address'] = array(
				'#type' => 'fieldset',
				'#title' => t('Present Address'),
				'#collapsible' => FALSE, // Added
				'#collapsed' => FALSE,  // Added
				'#prefix' => '<div id="reload_present_address">',
				'#suffix' => '</div>',
			);
			
			$form['prrsonal_info']['present_address']['present_street'] = array(
				'#title' => t('Address'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="row"><div class="col-md-6" id="reload_present_street"><div class="form-floating">',
				'#suffix' => '</div></div>',
				'#element_validate' => array('element_validate_streetaddress'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), //'id' => 'present_street', 
			);
			$form['prrsonal_info']['present_address']['present_city_town_village'] = array(
				'#title' => t('City / Town / Village'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="col-md-6" id="reload_present_city_town_village"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				'#element_validate' => array('element_validate_alphabatic_text'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), //'id' => 'present_city_town_village', 
			);
			$form['prrsonal_info']['present_address']['present_post_office'] = array(
				'#title' => t('Post Office'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="row"><div class="col-md-6" id="reload_present_post_office"><div class="form-floating">',
				'#suffix' => '</div></div>',
				'#element_validate' => array('element_validate_alphabatic_text'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), //'id' => 'present_post_office', 
			);
			$form['prrsonal_info']['present_address']['present_district'] = array(
				'#title' => t('District'),
				'#type' => 'select',
				'#options' => district_list(),
				// '#required' => TRUE,
				'#prefix' => '<div class="col-md-6" id="reload_present_district"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				'#attributes' => array('class'=>array('form-select')),
				//'#attributes' => array('id' => 'present_district'),
				// '#select2' => array(
				// 	'width' => '500',
				// 	//'placeholder' => '- Select -',
				// 	'allowClear' => TRUE
				// ),
			);
			$form['prrsonal_info']['present_address']['present_pincode'] = array(
				'#title' => t('Pincode'),
				'#type' => 'textfield',
				'#maxlength' => 6,
				// '#required' => TRUE,
				'#element_validate' => array('element_validate_numeric_positive'), 
				'#prefix' => '<div class="row"><div class="col-md-6" id="reload_present_pincode"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				'#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')), //'id' => 'present_pincode', 
			);
		} else {
			
			$form['prrsonal_info']['present_address'] = array(
				'#prefix' => '<div id="reload_present_address">',
				'#suffix' => '</div>',
			);
			/*
			$form['prrsonal_info']['present_address']['present_street'] = array(
				'#prefix' => '<div id="reload_present_street">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_city_town_village'] = array(
				'#prefix' => '<div id="reload_present_city_town_village">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_post_office'] = array(
				'#prefix' => '<div id="reload_present_post_office">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_district'] = array(
				'#prefix' => '<div id="reload_present_district">',
				'#suffix' => '</div>',
			);
			$form['prrsonal_info']['present_address']['present_pincode'] = array( 
				'#prefix' => '<div id="reload_present_pincode">',
				'#suffix' => '</div>',
			);*/
		}
	//end
	
		$form['prrsonal_info']['mobile'] = array(
			'#title' => t('Mobile no'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#maxlength' => 10,
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_mobile'),
			'#attributes' => array('id' => 'mobile_no','class'=>array('form-control')),
		);
		
		$form['prrsonal_info']['email'] = array(
			'#title' => t('Email ID'),
			'#type' => 'textfield',
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			// '#required' => TRUE,
			'#element_validate' => array('element_validate_email'),
			'#attributes' => array('oninput'=>"this.value=this.value.toLowerCase()",'class'=>array('form-control')),
		);
		
		$form['prrsonal_info']['dob'] = array(
			'#title' => t('Date of Birth(According to Service Book)'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dob','class'=>array('form-control')),
			// '#required' => TRUE,
			//'#validated' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_date', 'element_validate_age'),
		);
		
		$form['prrsonal_info']['gender'] = array(
			'#title' => t('Gender'),
			'#type' => 'radios',
			'#options' => array('M' => 'Male', 'F' => 'Female'),
			// '#attributes' => array('class' => array('gender')),
			// '#default_value' => 'M',
			// /'#attributes' => array('class' => array('form-check-input')),
			'#default_value' => 'M',
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			// '#required' => TRUE,
		);
		
		// occupant's official information
		$form['official_info'] = array(
			'#type' => 'fieldset',
			'#title' => t('Occupant\'s Official Information'),
			'#collapsible' => FALSE, // Added
			'#collapsed' => FALSE,  // Added
		);
		
		$form['official_info']['hrms_id'] = array(
			'#title' => t('Employee HRMS ID'),
			'#type' => 'textfield',
			'#default_value' => '',
			//'#default_value' => $hrms_id,
			//for api or hrms custom table
			//'#attributes' => array('readonly' => 'readonly', 'class' => array('numeric_positive')),
			'#maxlength' => 10,
			'#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_hrms_id'),
			// '#required' => TRUE,
		);
		
		$form['official_info']['occupant_designation'] = array(
			'#title' => t('Designation'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('element_validate_textarea'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
			//'#attributes' => array('id' => 'edit-app-designation', 'oncopy' => "return false", 'onpaste' => "return false"),
		);

		$form['official_info']['pay_band'] = array(
			'#title' => t('Basic Pay Range'),
			'#type' => 'select',
			'#options' => pay_band_list(),
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			// '#validated' => TRUE,
			'#attributes' => array('class'=>array('form-control')),
			
		);
		$form['official_info']['pay_in'] = array(
		 	'#title' => t('Basic Pay'),
			'#type' => 'textfield',
		 	// '#required' => TRUE,
		 	'#element_validate' => array('element_validate_numeric_positive'), 
		 	'#prefix' => '<div class="col-md-6"><div class="form-floating">',
		 	'#suffix' => '</div></div></div>',
		 	'#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
		);
		
		/*$form['official_info']['pay_band'] = array(
			'#title' => t('Pay Band'),
			'#type' => 'select',
			'#options' => pay_band_list_specific($flat_type_id),
			// '#required' => TRUE,
			'#validated' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		$form['official_info']['pay_in'] = array(
			'#title' => t('Pay in the Pay Band'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		);
		
		 $form['official_info']['grade_pay'] = array(
			'#title' => t('Grade Pay'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="four">',
			'#suffix' => '</div>',
			'#attributes' => array('class' => array('numeric_positive')),
		); */
		
		/*$form['official_info']['gpf_no'] = array(
			'#title' => t('GPF No.'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#element_validate' => array('gpf_no_validate'), 
			'#prefix' => '<div class="three">',
			'#suffix' => '</div>',
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"),
		);*/
		
		$form['official_info']['occupant_posting_place'] = array(
			'#title' => t('Place of Posting'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_alphabatic_text'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),  
		); 
		$form['official_info']['occupant_headquarter'] = array(
			'#title' => t('Headquarter'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
		);
		$form['official_info']['doj'] = array(
			'#title' => t('Date of Joining'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doj','class'=>array('form-control')),
			'#default_value' => '',
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
		);
		
		$form['official_info']['dor'] = array(
			'#title' => t('Date of Retirement(According to Service Book)'),
			'#type' => 'textfield',
			//'#attributes' => array('readonly' => 'readonly'),
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dor','class'=>array('form-control')),
			'#default_value' => '',
			// '#required' => TRUE,
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
		);
		
		
		// occupant's office address
		$form['office_add'] = array(
			'#type' => 'fieldset',
			'#title' => t('Name and Address of the Office'),
			'#collapsible' => FALSE, // Added
			'#collapsed' => FALSE,  // Added
		);
		$form['office_add']['office_name'] = array(
			'#title' => t('Name of the Office'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_textarea'),
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),  
		);
		
		$form['office_add']['office_street'] = array(
			'#title' => t('Address of the Office'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('element_validate_streetaddress'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
		);
		$form['office_add']['office_city'] = array(
			'#title' => t('City / Town / Village'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
		);
		$form['office_add']['office_post_office'] = array(
			'#title' => t('Post Office'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
		);
		$form['office_add']['office_district'] = array(
			'#title' => t('District'),
			'#type' => 'select',
			'#options' => district_list(),
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#attributes' => array('class'=>array('form-select')),
			// '#select2' => array(
			// 	'width' => '500',
			// 	//'placeholder' => '- Select -',
			// 	'allowClear' => TRUE
   //      	)
		);
		$form['office_add']['office_pincode'] = array(
			'#title' => t('Pincode'),
			'#type' => 'textfield',
			'#maxlength' => 6,
			// '#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'), 
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
		);
		$form['office_add']['office_phone_no'] = array(
			'#title' => t('Phone No.(With STD Code)'),
			'#type' => 'textfield',
			'#maxlength' => 15,
			// '#required' => TRUE,
			'#element_validate' => array('element_validate_telephoneno'), 
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
		);
		
		// ddo details
		$form['ddo'] = array(
			'#type' => 'fieldset',
			'#title' => t('DDO with Full Address'),
			'#collapsible' => FALSE, // Added
			'#collapsed' => FALSE,  // Added
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
			// '#required' => TRUE,
			// '#validated' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#attributes' => array('class'=>array('form-select')),
			// '#select2' => array(
			// 	'width' => '500',
			// 	//'placeholder' => '- Select -',
			// 	'allowClear' => TRUE
			// )
		);
		

		$form['ddo']['designation'] = array(
			'#title' => t('DDO Designation'),
			'#type' => 'select',
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
			'#default_value' => '', // $designation
			// '#required' => TRUE,
			// '#validated' => TRUE,
			'#prefix' => '<div id="replace_designation" class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#attributes' => array('class'=>array('form-select')),
			// '#select2' => array(
			//  'width' => '500',
			//  //'placeholder' => '- Select -',
			//  'allowClear' => TRUE
			// )
			);
	
		
		$form['ddo']['address'] = array(
			'#title' => t('DDO Address'),
			'#type' => 'textarea',
			'#attributes' => array('readonly' => 'readonly'),
			'#prefix' => '<div id="replace_ddo_address" class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			// '#required' => TRUE,
			//'#validated' => TRUE,
		);
		//license part//
		$form['license'] = array(
			'#type' => 'fieldset',
			'#title' => t('License Details'),
			'#collapsible' => FALSE, // Added
			'#collapsed' => FALSE,  // Added
		);

		$form['license']['license_no'] = array(
			'#title' => t('License No.'),
			'#type' => 'textfield',
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			'#element_validate' => array('element_validate_alphabatic_text'), 
			'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
		);

		$form['license']['dol'] = array(
			'#title' => t('License Issue Date'),
			'#type' => 'textfield',
			'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dol','class'=>array('form-control')),
			// '#required' => TRUE,
			//'#validated' => TRUE,
			'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div></div>',
			'#element_validate' => array('element_validate_date', 'element_validate_age'),
		);

		$form['license']['authorised_or_not'] = array(
			'#title' => t('Occupant Status'),
			'#type' => 'select',
			//'#options' => pay_band_list(),
			'#options' => ['authorised' => 'Authorised Occupant', 'unauthorised' => 'Unauthorised Occupant'],
			// '#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
			'#suffix' => '</div></div>',
			// '#validated' => TRUE,
			'#attributes' => array('class'=>array('form-control')),
			
		);

		$form['license']['uploaded_licence'] = array(
			'#title' => t('Upload Current Licence'),
			'#type' => 'managed_file',
			'#description' => t('<b>Allowed Extension: pdf<br>Maximum File Size: 1 MB</b>'),
			'#progress_message' => t('Please wait...'),
			'#progress_indicator' => 'bar',
			'#default_value' => variable_get('Upload File', ''),
			// '#prefix' => '<div class="col-md-6"><div class="form-floating">',
			// '#suffix' => '</div></div></div>',
			//'#theme' => 'common_application_thumb_upload',
			'#upload_validators' => array(
										 'file_validate_extensions' => array("pdf"),
										//'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
			
									),
			'#upload_location' => 'public://doc/',
			// '#required' => TRUE,
			'#process' => array('vertical_shifting_element_process'),
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
			// '#required' => TRUE,
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
										'#value'=>t('Submit'),
										'#attributes' => array('class'=>array('btn bg-primary btn-sm px-5 rounded-pill text-white fw-bolder')),
								);
								
		$form['cancel_button']=array(
										'#type'=>'button',
										'#value'=>t('Cancel'),
										'#attributes' => array('onClick' => 'history.go(-1); event.preventDefault();','class'=>array('btn bg-danger btn-sm px-5 rounded-pill text-white fw-bolder')),
								);
								
		$form['form_end'] = array(
			'#type' => 'markup',
			'#markup' => '</div><div class="mb-5 pb-3"></div>',
		);
		
		return $form;
		//return '<div class="mb-5 pb-3">'.$form.'</div>';
		}
	}
	
	function existing_occupant_form_validate($form, &$form_state) {
		
		// if($form_state['values']['pay_band'] == '') {
  		// 	form_set_error('district', t('Please select payband.'));
		// }
		// if($form_state['values']['district'] == '') {
  		// 	form_set_error('district', t('Please select district.'));
		// }
		// if($form_state['values']['designation'] == '') {
  		// 	form_set_error('designation', t('Please select ddo designation.'));
		// }
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
		
		if(!empty($form_state['values']['hrms_id']) && is_numeric($form_state['values']['hrms_id'])) {
		   
			 $hrms_id = trim($form_state['values']['hrms_id']);
			 
			 $query = db_select('housing_applicant_official_detail','haod');
			 $query->fields('haod');
			 $query->condition('hrms_id', $hrms_id);
			 $result =$query->execute();
			 
			 
			 if($result->rowCount() > 0)
			 	form_set_error('hrms_id', 'This Employee HRMS ID already exist.');
		
		}
		
		/*if($form_state['values']['pay_band'] == 1) {
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
		}*/
		
	}
	
	
	function existing_occupant_form_submit($form, &$form_state) {
		global $user;
		// print_r($form_state['values' ]) ;die;
		/*echo '<pre>';
		print_r($form_state['values']);die();*/
		//$name = strtolower(trim($form_state['values']['applicant_name']));
		//$name1 = str_replace(" ","",$name);
		//$username = str_replace(".","",$name1).rand();
		// $license_issue_date = trim( implode('-', array_reverse(explode('/', $form_state['values']['dol']))));
		// $licence_expiry_date = date('Y-m-d', strtotime($license_issue_date.'+3 years -1 day'));
		// echo $licence_expiry_date;die;
		
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
		
		//$username = str_replace(".","",$name).rand(1, 100000);

		// added by moumita 05-06-2024
		// for login with HRMS id after existing occupant entry

		$username = trim($form_state['values']['hrms_id']);
		
		/*insert into user table*/
		$newUser	   	   = array();
		$newUser['name']   = trim($username);
		$newUser['pass']   = trim($username);
		/*$str[0].$str[1].trim($form_state['values']['username']).'@'.$dob_t.strrev($str1[0].$str1[1]);*/																																																						
		$newUser['mail']   = strtolower(trim($form_state['values']['email']));
		$newUser['status'] = 0;
		
		// added by moumita on 07/05/25 for non hrms existing occupant
		if($form_state['values']['hrms_id'] != ''){
			user_save(null, $newUser);

			/*get last inserted uid*/
		
			$query = db_select('users','u');
			$query->addExpression('MAX(uid)','max_uid');
			$result = $query->execute();
			$data = $result->fetchObject();

			/*assign user roles*/
		
			$arr_user_roles = array();
			$arr_user_roles['uid'] = trim($data->max_uid);
			$arr_user_roles['rid'] = 5;
			
			db_insert('users_roles')
			->fields($arr_user_roles)
			->execute();
			$max_uid = $data->max_uid;

		}else{
			$data['max_uid'] = NULL;
			$max_uid = 0;
			$data = (object)$data;

			$data5['max_housing_applicant_id'] = NULL;
			$data5 = (object)$data5;
		}
				
		
		
		/*insert into housing_applicant table*/
		
		$applicant_personal_detail_arr = array();
		$applicant_personal_detail_arr['uid'] 				=  trim($max_uid);
		$applicant_personal_detail_arr['applicant_name'] 	=  trim($form_state['values']['occupant_name']);
		$applicant_personal_detail_arr['guardian_name'] 	=  trim($form_state['values']['occupant_father_name']);
		$applicant_personal_detail_arr['date_of_birth'] 	=  ($form_state['values']['dob']!='')  ? trim(implode('-', array_reverse(explode('/', $form_state['values']['dob'])))) : null;
		$applicant_personal_detail_arr['gender'] 			=  trim($form_state['values']['gender']);
		$applicant_personal_detail_arr['mobile_no'] 		=  ($form_state['values']['mobile']!='') ? trim($form_state['values']['mobile']) : 0;
		
		$applicant_personal_detail_arr['permanent_street']  =  ($form_state['values']['permanent_street']!='' ) ? trim($form_state['values']['permanent_street']) : 0;
		$applicant_personal_detail_arr['permanent_city_town_village']  =  ($form_state['values']['permanent_city_town_village']!='' ) ? trim($form_state['values']['permanent_city_town_village']) : 0;
		$applicant_personal_detail_arr['permanent_post_office']  =  ($form_state['values']['permanent_post_office']!='' ) ? trim($form_state['values']['permanent_post_office']) : 0;
		$applicant_personal_detail_arr['permanent_district']  =  ($form_state['values']['permanent_district']!='' ) ? trim($form_state['values']['permanent_district']) : 0;
		$applicant_personal_detail_arr['permanent_pincode']  =  ($form_state['values']['permanent_pincode']!='') ? trim($form_state['values']['permanent_pincode']): 0;
		
		
		// $applicant_personal_detail_arr['permanent_present_same']  =  trim($form_state['values']['chk_permanent_address']); // turned off 19-12-2024
		
		// if(trim($form_state['values']['chk_permanent_address']) != 1) { // turned off 19-12-2024
			//$applicant_personal_detail_arr['permanent_present_same'] = 0;
			$applicant_personal_detail_arr['present_street']  =  ($form_state['values']['present_street'] !='') ? trim($form_state['values']['present_street']) : 0;
			$applicant_personal_detail_arr['present_city_town_village']  = ($form_state['values']['present_city_town_village'] !='') ? trim($form_state['values']['present_city_town_village']) : 0;
			//applicant_personal_detail_arr['present_post_office']  =  strtoupper(trim($form_state['values']['present_post_office']));
			$applicant_personal_detail_arr['present_post_office']  =  ($form_state['values']['present_post_office'] !='') ? trim($form_state['values']['present_post_office']) : 0;
			$applicant_personal_detail_arr['present_district']  =  ($form_state['values']['present_district'] !='' ) ? trim($form_state['values']['present_district']) : 0;
			$applicant_personal_detail_arr['present_pincode']  =  ($form_state['values']['present_pincode']!='' ) ? trim($form_state['values']['present_pincode']) : 0;

			// turned off 19-12-2024
		// } else {
		// 	$applicant_personal_detail_arr['present_street']  =  NULL;
		// 	$applicant_personal_detail_arr['present_city_town_village']  =  NULL;
		// 	$applicant_personal_detail_arr['present_post_office']  =  NULL;
		// 	$applicant_personal_detail_arr['present_district']  =  NULL;
		// 	$applicant_personal_detail_arr['present_pincode']  =  NULL;	
		// } // turned off 19-12-2024
		
		// echo "<pre>";print_r($applicant_personal_detail_arr);die;
		db_insert('housing_applicant')
		->fields($applicant_personal_detail_arr)
		->execute();
		
		///////by debaleena 05-12-2024///
		$query5 = db_select('housing_applicant','ha');
		$query5->addExpression('MAX(housing_applicant_id)','max_housing_applicant_id');
		$result5 = $query5->execute();
		$data5 = $result5->fetchObject();

		////end////
		
		/*add applicant_official_detail  data*/
		$app_off_detail_arr = array();
		// $app_off_detail_arr['uid']  =  trim($data->max_uid);
		$app_off_detail_arr['ddo_id']  =   ($form_state['values']['designation']!='' ) ? trim($form_state['values']['designation']) : NULL;
		$app_off_detail_arr['hrms_id']  =  ($form_state['values']['hrms_id']!='') ? trim($form_state['values']['hrms_id']) : 0;
		$app_off_detail_arr['applicant_designation']  =  strtoupper(trim($form_state['values']['occupant_designation']));
		$app_off_detail_arr['applicant_posting_place']  =  strtoupper(trim($form_state['values']['occupant_posting_place']));
		$app_off_detail_arr['applicant_headquarter']  =  strtoupper(trim($form_state['values']['occupant_headquarter']));
		$app_off_detail_arr['pay_band_id']  =  ($form_state['values']['pay_band']!='') ? trim($form_state['values']['pay_band']) : NULL;
		$app_off_detail_arr['pay_in_the_pay_band']  =  ($form_state['values']['pay_in']!='' ) ? trim($form_state['values']['pay_in']) : 0;
		//$app_off_detail_arr['grade_pay']  =  trim($form_state['values']['grade_pay']);
		//$app_off_detail_arr['gpf_no']  =  strtoupper(trim($form_state['values']['gpf_no']));
		$app_off_detail_arr['date_of_joining']  =  ($form_state['values']['doj']!='' ) ? trim( implode('-', array_reverse(explode('/', $form_state['values']['doj'])))) : '1900-01-01';
		$app_off_detail_arr['date_of_retirement']  =  ($form_state['values']['dor']!='' ) ? trim( implode('-', array_reverse(explode('/', $form_state['values']['dor'])))) : '1900-01-01';
		
		$app_off_detail_arr['office_name']  =  strtoupper(trim($form_state['values']['office_name']));
		$app_off_detail_arr['office_street']  =  strtoupper(trim($form_state['values']['office_street']));
		$app_off_detail_arr['office_city_town_village']  = strtoupper(trim($form_state['values']['office_city']));
		$app_off_detail_arr['office_post_office']  =  strtoupper(trim($form_state['values']['office_post_office']));
		$app_off_detail_arr['office_district']  =  ($form_state['values']['office_district']!='' ) ? trim($form_state['values']['office_district']) : 0;
		$app_off_detail_arr['office_pin_code']  =  ($form_state['values']['office_pincode']!='') ? trim($form_state['values']['office_pincode']) : 0;
		$app_off_detail_arr['office_phone_no']  =  trim($form_state['values']['office_phone_no']);
		$app_off_detail_arr['housing_applicant_id']  = ($data5->max_housing_applicant_id !='' ) ? trim($data5->max_housing_applicant_id) : 0;
		
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
		//$online_app_arr['status']  =  'allotted'; // 04-06-2024
		$online_app_arr['status'] = 'existing_occupant'; // 04-06-2024
		// $online_app_arr['date_of_application']  =  NULL; // 07-05-2025
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
		
		// update for application no generate by moumita 05-06-2024
			
		db_update('housing_online_application')
		->fields(array('application_no'=> 'EO-'.trim(date('dmY')).'-'.$data2->oid))
		->condition('online_application_id', $data2->oid)
		->execute();
		
		/* add new alltment application*/  
		$new_allotment_app_arr = array();
		$new_allotment_app_arr['online_application_id']  =  trim($data2->oid);
		
		$new_allotment_app_arr['flat_type_id'] = trim($form_state['values']['flat_type_id']);
		//$new_allotment_app_arr['allotment_category']  =  trim($form_state['values']['reason']);
		
		db_insert('housing_new_allotment_application')
  	  	->fields($new_allotment_app_arr)
  	  	->execute();
		
		// echo $flat_id;die;
		/*Flat status update and Add flat occupant details*/
		db_update('housing_flat')
			->fields(array(
						'flat_status_id' => 2
					))
			->condition('flat_id', $form_state['values']['flat_id'])
			->execute();
			
		$allotment_ins_arr = array();
		$allotment_ins_arr['online_application_id']  = trim($data2->oid);
		$allotment_ins_arr['flat_id']  = trim($form_state['values']['flat_id']);
		$allotment_ins_arr['allotment_date']  =  NULL;
		
		//$allotment_ins_arr['allotment_no'] = 'NAL-'.$data2->oid.'-'.date("dmY");
		//$allotment_ins_arr['allotment_process_no'] = ;
	
		db_insert('housing_flat_occupant')
		->fields($allotment_ins_arr)
		->execute();

		//debaleena start 28-08-2024//
		$query4 = db_select('housing_flat_occupant', 'hfo');
		$query4->addExpression('MAX(flat_occupant_id)','id');
		//$query1->condition('haod.uid', $data->max_uid, '=');
		$result4 = $query4->execute();
		$data4 = $result4->fetchObject();
		
		$license_issue_date = trim( implode('-', array_reverse(explode('/', $form_state['values']['dol']))));
		$licence_expiry_date = date('Y-m-d', strtotime($license_issue_date.'+3 years -1 day'));

		$license_details_arr = array();
		$license_details_arr['flat_occupant_id'] =  trim($data4->id);
		$license_details_arr['license_issue_date'] = ($license_issue_date!='' ) ? $license_issue_date : '1900-01-01';
		$license_details_arr['license_expiry_date'] = $licence_expiry_date;
		$license_details_arr['existing_occupant_license_no'] = ($form_state['values']['license_no'] !='' ) ? trim($form_state['values']['license_no']) : NULL;
		$license_details_arr['authorised_or_not'] = trim($form_state['values']['authorised_or_not']);

		if($form_state['values']['uploaded_licence'] != 0) {
			$file_licence = file_load($form_state['values']['uploaded_licence']);
			if($file_licence->status==0) {
				$file_licence->status = FILE_STATUS_PERMANENT;
				file_save($file_licence);
				file_usage_add($file_licence, 'existing_occupant', 'Current Licence', $user->uid);
				$license_details_arr['uploaded_licence']  =  $file_licence->fid;	
			}
		}

		db_insert('housing_occupant_license')
		->fields($license_details_arr)
		->execute();

		//end///



		
		$flatno = $form_state['values']['occupied_flat'];
		drupal_set_message('Occupant Data for Flat No.- '.$flatno.' Inserted Successfully.');
		drupal_goto('rhewise_flatlist');
	}
	