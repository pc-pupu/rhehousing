<?php

	//function existing_occupant_form($form, &$form_state, $flat_id, $hrms_id) {
	function existing_occupant_draft_form($form, &$form_state, $flat_id) {
		$flat_id = decrypt_url($flat_id);


		
		$result = occupant_entry_check($flat_id);
		$result_draft = occupant_entry_check_draft($flat_id);
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

		if($result->rowCount() > 0 || $result_draft->rowCount() > 0) {
			drupal_set_message('Occupant Entry Already Exist for '.$flat_no ,'error');
			//drupal_goto('occupant_entry_done');
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
				//'#element_validate' => array('element_validate_alphabatic_text'),
				// '#required' => TRUE,
		  	);
			
			$form['occupied_info']['occupied_estate'] = array(
				'#title' => t('Rental Housing Estate Name'),
				'#type' => 'textfield',
				'#default_value' => $estate_name,
				'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
				'#prefix' => '<div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				//'#element_validate' => array('element_validate_streetaddress'),
				// '#required' => TRUE,
			);
			
			$form['occupied_info']['occupied_flattype'] = array(
				'#title' => t('Flat Type'),
				'#type' => 'textfield',
				'#default_value' => $flat_type,
				'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
				'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div>',
				'#element_validate' => array('validate_rhe_flattype'),
				// '#required' => TRUE,
			);
			
			$form['occupied_info']['occupied_block'] = array(
				'#title' => t('Block Name'),
				'#type' => 'textfield',
				'#default_value' => $block_name,
				'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
				'#prefix' => '<div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				'#element_validate' => array('validate_rhe_block1'),
				// '#required' => TRUE,
			);
			
			$form['occupied_info']['occupied_flat'] = array(
				'#title' => t('Flat No.'),
				'#type' => 'textfield',
				'#default_value' => $flat_no,
				'#attributes' => array('readonly' => 'readonly','class'=>array('form-control')),
				'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				//'#element_validate' => array('validate_flat_no'),
				// '#required' => TRUE,
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
				//'#element_validate' => array('element_validate_alphabatic_fullstop'),
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
				//'#element_validate' => array('element_validate_streetaddress'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
			);
			$form['prrsonal_info']['permanent_address']['permanent_city_town_village'] = array(
				'#title' => t('City / Town / Village'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				//'#element_validate' => array('element_validate_alphabatic_text'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
			);
			$form['prrsonal_info']['permanent_address']['permanent_post_office'] = array(
				'#title' => t('Post Office'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div>',
				//'#element_validate' => array('element_validate_alphabatic_text'), 
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
				//'#element_validate' => array('element_validate_numeric_positive'), 
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
				//'#element_validate' => array('element_validate_mobile'),
				'#attributes' => array('id' => 'mobile_no','class'=>array('form-control')),
			);
			
			$form['prrsonal_info']['email'] = array(
				'#title' => t('Email ID'),
				'#type' => 'textfield',
				'#prefix' => '<div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				// '#required' => TRUE,
				//'#element_validate' => array('element_validate_email'),
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
				//'#element_validate' => array('element_validate_date', 'element_validate_age'),
			);
			
			$form['prrsonal_info']['gender'] = array(
				'#title' => t('Gender'),
				'#type' => 'radios',
				'#options' => array('M' => 'Male', 'F' => 'Female'),
				// '#attributes' => array('class' => array('gender')),
				// '#default_value' => 'M',
				// /'#attributes' => array('class' => array('form-check-input')),
				//'#default_value' => 'M',
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
				//'#element_validate' => array('element_validate_hrms_id'),
				// '#required' => TRUE,
			);
			
			$form['official_info']['occupant_designation'] = array(
				'#title' => t('Designation'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				//'#element_validate' => array('element_validate_textarea'),
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
				'#validated' => TRUE,
				'#attributes' => array('class'=>array('form-control')),
				
			);
			$form['official_info']['pay_in'] = array(
			 	'#title' => t('Basic Pay'),
				'#type' => 'textfield',
			 	// '#required' => TRUE,
			 	//'#element_validate' => array('element_validate_numeric_positive'), 
			 	'#prefix' => '<div class="col-md-6"><div class="form-floating">',
			 	'#suffix' => '</div></div></div>',
			 	'#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
			);
		
			
			$form['official_info']['occupant_posting_place'] = array(
				'#title' => t('Place of Posting'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div>',
				//'#element_validate' => array('element_validate_alphabatic_text'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),  
			); 
			$form['official_info']['occupant_headquarter'] = array(
				'#title' => t('Headquarter'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				//'#element_validate' => array('element_validate_alphabatic_text'), 
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
				//'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
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
				//'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
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
				//'#element_validate' => array('element_validate_textarea'),
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),  
			);
			
			$form['office_add']['office_street'] = array(
				'#title' => t('Address of the Office'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				//'#element_validate' => array('element_validate_streetaddress'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
			);
			$form['office_add']['office_city'] = array(
				'#title' => t('City / Town / Village'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div>',
				//'#element_validate' => array('element_validate_alphabatic_text'), 
				'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
			);
			$form['office_add']['office_post_office'] = array(
				'#title' => t('Post Office'),
				'#type' => 'textfield',
				// '#required' => TRUE,
				'#prefix' => '<div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div></div>',
				//'#element_validate' => array('element_validate_alphabatic_text'), 
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
				//'#element_validate' => array('element_validate_telephoneno'), 
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
				'#validated' => TRUE,
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
				'#validated' => TRUE,
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
				//'#// '#required' => TRUE,
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
				//'#element_validate' => array('element_validate_alphabatic_text'), 
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
				//'#element_validate' => array('element_validate_date', 'element_validate_age'),
			);

			$form['license']['authorised_or_not'] = array(
				'#title' => t('Occupant Status'),
				'#type' => 'select',
				//'#options' => pay_band_list(),
				'#options' => ['0' => 'Select', 'authorised' => 'Authorised Occupant', 'unauthorised' => 'Unauthorised Occupant'],
				// '#required' => TRUE,
				'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
				'#suffix' => '</div></div>',
				'#validated' => TRUE,
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

			
			
			
			
			//$form['#attributes'] = array('onsubmit' => 'return validate_existing_occupant_form()');
			
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
		}
		//return '<div class="mb-5 pb-3">'.$form.'</div>';
		
	}
	
	// function existing_occupant_form_validate($form, &$form_state) {
		
	// 	if($form_state['values']['pay_band'] == '') {
  	// 		form_set_error('district', t('Please select payband.'));
	// 	}
	// 	if($form_state['values']['district'] == '') {
  	// 		form_set_error('district', t('Please select district.'));
	// 	}
	// 	if($form_state['values']['designation'] == '') {
  	// 		form_set_error('designation', t('Please select ddo designation.'));
	// 	}
	// 	/*if($form_state['values']['reason'] == '') {
  	// 		form_set_error('reason', t('Please select allotment reason.'));
	// 	}*/
			
		
	// 	if(!empty($form_state['values']['mobile']) && is_numeric($form_state['values']['mobile'])) {
		   
	// 		 $mobile = trim($form_state['values']['mobile']);
			 
	// 		 $query = db_select('housing_applicant','applicant');
	// 		 $query->addExpression('mobile_no','mobile');
	// 		 $query->condition('mobile_no', $mobile);
	// 		 $result =$query->execute();
			 
			 
	// 		 if($result->rowCount() > 0)
	// 		 	form_set_error('mobile', 'This mobile no. already exist.');
		
	// 	}
		
	// 	if(!empty($form_state['values']['email'])) {
		   
	// 		$email = trim($form_state['values']['email']);
			
	// 		$query = db_select('users','u');
	// 		$query->addExpression('mail','email');
	// 		$query->condition('mail', $email);
	// 		$result =$query->execute();
			
	// 		/*if (!valid_email_address($email)) {
	// 			form_set_error('[email]', t('The email address appears to be invalid.'));
	// 		}*/
			
	// 		if($result->rowCount() > 0)
	// 			form_set_error('email', 'This email address already exist.');
		
	// 	}
		
	// 	if(!empty($form_state['values']['hrms_id']) && is_numeric($form_state['values']['hrms_id'])) {
		   
	// 		 $hrms_id = trim($form_state['values']['hrms_id']);
			 
	// 		 $query = db_select('housing_applicant_official_detail','haod');
	// 		 $query->fields('haod');
	// 		 $query->condition('hrms_id', $hrms_id);
	// 		 $result =$query->execute();
			 
			 
	// 		 if($result->rowCount() > 0)
	// 		 	form_set_error('hrms_id', 'This Employee HRMS ID already exist.');
		
	// 	}
		
		
	// }
	
	
	function existing_occupant_draft_form_submit($form, &$form_state) {
		global $user;
		
		//print_r($form_state['values']);die;
		
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
		
		
		/*insert into housing_existing_occupant_draft table*/

		if(isset($form_state['values']['dol']))
		{
			$license_issue_date = trim(implode('-', array_reverse(explode('/', $form_state['values']['dol'])))); // Converts dd/mm/yyyy to yyyy-mm-dd
			$license_expiry_date = date('Y-m-d', strtotime($license_issue_date . ' +3 years -1 day'));
		}else{
			$license_issue_date = NULL;
			$license_expiry_date = NULL;
		}
			
			//echo $license_expiry_date;die;
		
		$applicant_personal_detail_arr = array();

		$applicant_personal_detail_arr['applicant_name'] 	=  !empty(trim($form_state['values']['occupant_name'])) ? trim($form_state['values']['occupant_name']) : 0;
		$applicant_personal_detail_arr['guardian_name'] 	=  !empty(trim($form_state['values']['occupant_father_name'])) ? trim($form_state['values']['occupant_father_name']) : NULL;
		$applicant_personal_detail_arr['date_of_birth'] 	=  !empty($form_state['values']['dob']) ? trim(implode('-', array_reverse(explode('/', $form_state['values']['dob'])))) : NULL;
		$applicant_personal_detail_arr['gender'] 			=  !empty(trim($form_state['values']['gender'])) ? trim($form_state['values']['gender']) : NULL;
		$applicant_personal_detail_arr['mobile_no'] 			=  !empty(trim($form_state['values']['mobile'])) ? trim($form_state['values']['mobile']) : NULL;
		
		$applicant_personal_detail_arr['permanent_street']  =  !empty(trim($form_state['values']['permanent_street']))? strtoupper(trim($form_state['values']['permanent_street'])): NULL;
		$applicant_personal_detail_arr['permanent_city_town_village']  =  !empty(trim($form_state['values']['permanent_city_town_village']))? strtoupper(trim($form_state['values']['permanent_city_town_village'])): NULL;
		$applicant_personal_detail_arr['permanent_post_office']  =  !empty(trim($form_state['values']['permanent_post_office']))? strtoupper(trim($form_state['values']['permanent_post_office'])): NULL;
		$applicant_personal_detail_arr['permanent_district']  =  !empty(trim($form_state['values']['permanent_district'])) ? trim($form_state['values']['permanent_district']) : NULL;
		$applicant_personal_detail_arr['permanent_pincode']  =  !empty(trim($form_state['values']['permanent_pincode'])) ? trim($form_state['values']['permanent_pincode']) : NULL;

		$applicant_personal_detail_arr['present_street']  =  !empty(trim($form_state['values']['present_street']))? strtoupper(trim($form_state['values']['present_street'])): NULL;
		$applicant_personal_detail_arr['present_city_town_village']  =  !empty(trim($form_state['values']['present_city_town_village']))? strtoupper(trim($form_state['values']['present_city_town_village'])): NULL;
		$applicant_personal_detail_arr['present_post_office']  =  !empty(trim($form_state['values']['present_post_office']))? strtoupper(trim($form_state['values']['present_post_office'])): NULL;
		$applicant_personal_detail_arr['present_district']  =  !empty(trim($form_state['values']['present_district']))? trim($form_state['values']['present_district']): NULL;
		$applicant_personal_detail_arr['present_pincode']  =  !empty(trim($form_state['values']['present_pincode']))? trim($form_state['values']['present_pincode']): NULL;

		$applicant_personal_detail_arr['ddo_id']  =  !empty(trim($form_state['values']['designation']))? trim($form_state['values']['designation']): NULL; 
		$applicant_personal_detail_arr['applicant_designation']  =  !empty(trim($form_state['values']['occupant_designation']))? strtoupper(trim($form_state['values']['occupant_designation'])): NULL;
		$applicant_personal_detail_arr['applicant_posting_place']  = !empty(trim($form_state['values']['occupant_posting_place']))? strtoupper(trim($form_state['values']['occupant_posting_place'])): NULL; 
		$applicant_personal_detail_arr['applicant_headquarter']  = !empty(trim($form_state['values']['occupant_headquarter']))? strtoupper(trim($form_state['values']['occupant_headquarter'])): NULL;  
		$applicant_personal_detail_arr['pay_band_id']  = !empty(trim($form_state['values']['pay_band']))? strtoupper(trim($form_state['values']['pay_band'])): NULL; 
		$applicant_personal_detail_arr['pay_in_the_pay_band']  = !empty(trim($form_state['values']['pay_in']))? strtoupper(trim($form_state['values']['pay_in'])): NULL; 
		$applicant_personal_detail_arr['date_of_joining']  =  !empty($form_state['values']['doj']) ? trim(implode('-', array_reverse(explode('/', $form_state['values']['doj'])))) : NULL;
		$applicant_personal_detail_arr['date_of_retirement']  =  !empty($form_state['values']['dor']) ? trim(implode('-', array_reverse(explode('/', $form_state['values']['dor'])))) : NULL;
		
		$applicant_personal_detail_arr['office_name']  = !empty(trim($form_state['values']['office_name']))? strtoupper(trim($form_state['values']['office_name'])): NULL; 
		$applicant_personal_detail_arr['office_street']  = !empty(trim($form_state['values']['office_street']))? strtoupper(trim($form_state['values']['office_street'])): NULL; 
		$applicant_personal_detail_arr['office_city_town_village']  = !empty(trim($form_state['values']['office_city']))? strtoupper(trim($form_state['values']['office_city'])): NULL;  
		$applicant_personal_detail_arr['office_post_office']  =  !empty(trim($form_state['values']['office_post_office']))? strtoupper(trim($form_state['values']['office_post_office'])): NULL; 
		$applicant_personal_detail_arr['office_district']  =  !empty(trim($form_state['values']['office_district'])) ? trim($form_state['values']['office_district']) : NULL;
		$applicant_personal_detail_arr['office_pin_code']  = !empty(trim($form_state['values']['office_pincode'])) ? trim($form_state['values']['office_pincode']) : NULL; 
		$applicant_personal_detail_arr['office_phone_no']  = !empty(trim($form_state['values']['office_phone_no'])) ? trim($form_state['values']['office_phone_no']) : NULL;
		$applicant_personal_detail_arr['flat_id'] = $form_state['values']['flat_id'];
		$applicant_personal_detail_arr['license_no']  = !empty(trim($form_state['values']['license_no'])) ? trim($form_state['values']['license_no']) : NULL; 
		$applicant_personal_detail_arr['license_issue_date']  = !empty(trim($license_issue_date)) ? trim($license_issue_date) : NULL; 
		$applicant_personal_detail_arr['authorised_or_not']  = !empty(trim($form_state['values']['authorised_or_not'])) ? trim($form_state['values']['authorised_or_not']) : NULL; 
		$applicant_personal_detail_arr['license_expiry_date']  =isset($license_expiry_date) ? $license_expiry_date : null;

		if($form_state['values']['uploaded_licence'] != 0) {
			$file_licence = file_load($form_state['values']['uploaded_licence']);
			if($file_licence->status==0) {
				$file_licence->status = FILE_STATUS_PERMANENT;
				file_save($file_licence);
				file_usage_add($file_licence, 'existing_occupant', 'Current Licence', $user->uid);
				$applicant_personal_detail_arr['uploaded_licence']  =  $file_licence->fid;	
			}
		}

		$occupant_sts_entry = array();
		db_update('housing_flat')
			->fields(array(
				'flat_status_id' => '2')
			)
			->condition('flat_id', $form_state['values']['flat_id'])
			->execute();


		
		

		db_insert('housing_existing_occupant_draft')
  	  	->fields($applicant_personal_detail_arr)
  	  	->execute();
		
		

		
		$flatno = $form_state['values']['occupied_flat'];
		drupal_set_message('Occupant Data for Flat No.- '.$flatno.' Inserted Successfully.');
		drupal_goto('rhewise_flatlist_draft');
	}
	