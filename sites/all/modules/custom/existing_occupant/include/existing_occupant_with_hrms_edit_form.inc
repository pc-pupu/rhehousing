<?php
// Done by Subham dt.19-05-2025
function existing_occupant_with_hrms_edit_form($form, &$form_state, $uid) {
    $uid = decrypt_url($uid);
		
    $query = db_select('housing_applicant', 'ha');
    $query->innerJoin('housing_applicant_official_detail', 'haod', 'ha.housing_applicant_id = haod.housing_applicant_id');  //added by dg 30-12-2024 
    $query->innerJoin('housing_online_application', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
    $query->innerJoin('housing_flat_occupant', 'hfo', 'hfo.online_application_id = hoa.online_application_id');
    $query->innerJoin('housing_flat', 'hf', 'hf.flat_id = hfo.flat_id');
    $query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
    $query->innerJoin('housing_flat_type', 'hft', 'hft.flat_type_id = hf.flat_type_id');
    $query->innerJoin('users', 'u', 'u.uid = haod.uid');
    $query->innerJoin('housing_ddo', 'hd', 'hd.ddo_id = haod.ddo_id');
    $query->innerJoin('housing_district', 'hdis', 'hdis.district_code = hd.district_code');
    $query->innerJoin('housing_occupant_license', 'hol', 'hol.flat_occupant_id = hfo.flat_occupant_id');
    $query->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
    $query->innerJoin('housing_district', 'hdis_present', 'hdis_present.district_code = ha.present_district');
    $query->innerJoin('housing_district', 'hdis_permanent', 'hdis_permanent.district_code = ha.permanent_district');
    $query->innerJoin('housing_district', 'hdis_office', 'hdis_office.district_code = haod.office_district');

    $query->condition('hoa.status', 'existing_occupant', '=');
    $query->condition('haod.uid',$uid);

    $query->fields('ha', array('applicant_name','applicant_name','guardian_name','date_of_birth','mobile_no','gender','permanent_street','permanent_city_town_village','permanent_post_office','permanent_pincode','permanent_district','permanent_present_same','present_street','present_city_town_village','present_post_office','present_pincode','present_district','mobile_no'));
    $query->addField('he', 'estate_name');
    $query->addField('hft', 'flat_type');
    $query->fields('haod', array('hrms_id','applicant_designation','applicant_headquarter','applicant_posting_place','pay_in_the_pay_band','date_of_joining','date_of_retirement','office_name','office_street','office_city_town_village','office_post_office','office_pin_code','office_district','office_phone_no'));
    $query->fields('u', array('status','mail'));
    $query->fields('hoa', array('application_no', 'date_of_application'));
    $query->fields('hd', array('ddo_designation', 'ddo_address'));
    $query->addField('hdis', 'district_name');
    $query->fields('hol', array('license_issue_date', 'license_expiry_date','existing_occupant_license_no','authorised_or_not'));
    $query->addField('hf', 'flat_no');
    $query->addField('hf', 'floor');
    $query->addField('he', 'estate_name');
    $query->addField('hb', 'block_name');
    $query->addField('hdis_present', 'district_name', 'present_district_name');
    $query->addField('hdis_permanent', 'district_name', 'permanent_district_name');
    $query->addField('hdis_office', 'district_name', 'office_district_name');

    $result =$query->execute();
    $data = $result->fetchObject();

    $form['prrsonal_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Occupant\'s Personal Information(According to Service Book)'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
    );
						
    $form['prrsonal_info']['occupant_name'] = array(
        '#title' => t('Occupant\'s Name'),
        '#type' => 'textfield',
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#default_value' => $data->applicant_name,
        '#element_validate' => array('element_validate_alphabatic_fullstop'),
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
        '#required' => TRUE,
    );
    
    $form['prrsonal_info']['occupant_father_name'] = array(
        '#title' => t('Father\'s / Husband\'s Name'),
        '#type' => 'textfield',
        '#default_value' => $data->guardian_name,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#element_validate' => array('element_validate_alphabatic_fullstop'),
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
        '#required' => TRUE,
    );
		
	//Permanent Address
    $form['prrsonal_info']['permanent_address'] = array(
        '#type' => 'fieldset',
        '#title' => t('Permanent Address'),
        '#collapsible' => FALSE, 
        '#collapsed' => FALSE,  
    );
    $form['prrsonal_info']['permanent_address']['permanent_street'] = array(
        '#title' => t('Address'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_streetaddress'), 
        '#default_value' => $data->permanent_street,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
    );
    $form['prrsonal_info']['permanent_address']['permanent_city_town_village'] = array(
        '#title' => t('City / Town / Village'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'), 
        '#default_value' => $data->permanent_city_town_village,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
    );
    $form['prrsonal_info']['permanent_address']['permanent_post_office'] = array(
        '#title' => t('Post Office'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'), 
        '#default_value' => $data->permanent_post_office,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
    );
    $form['prrsonal_info']['permanent_address']['permanent_district'] = array(
        '#title' => t('District'),
        '#type' => 'select',
        '#options' => district_list(),
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class'=>array('form-select')),
        '#default_value' => $data->permanent_district,
    );
    $form['prrsonal_info']['permanent_address']['permanent_pincode'] = array(
        '#title' => t('Pincode'),
        '#type' => 'textfield',
        '#maxlength' => 6,
        '#required' => TRUE,
        '#element_validate' => array('element_validate_numeric_positive'), 
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
        '#default_value' => $data->permanent_pincode
    );
    
    //Present Address
    $form['prrsonal_info']['present_address'] = array(
        '#type' => 'fieldset',
        '#title' => t('Present Address'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE, 
        '#prefix' => '<div id="reload_present_address">',
        '#suffix' => '</div>',
    );
    
    $form['prrsonal_info']['present_address']['present_street'] = array(
        '#title' => t('Address'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6" id="reload_present_street"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_streetaddress'), 
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), //'id' => 'present_street', 
        '#default_value' => $data->present_street,
    );
    $form['prrsonal_info']['present_address']['present_city_town_village'] = array(
        '#title' => t('City / Town / Village'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6" id="reload_present_city_town_village"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'), 
        '#default_value' => $data->present_city_town_village,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), //'id' => 'present_city_town_village', 
    );
    $form['prrsonal_info']['present_address']['present_post_office'] = array(
        '#title' => t('Post Office'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6" id="reload_present_post_office"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'), 
        '#default_value' => $data->present_post_office,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), //'id' => 'present_post_office', 
    );
    $form['prrsonal_info']['present_address']['present_district'] = array(
        '#title' => t('District'),
        '#type' => 'select',
        '#options' => district_list(),
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6" id="reload_present_district"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class'=>array('form-select')),
        '#default_value' => $data->present_district,
    );
    $form['prrsonal_info']['present_address']['present_pincode'] = array(
        '#title' => t('Pincode'),
        '#type' => 'textfield',
        '#maxlength' => 6,
        '#required' => TRUE,
        '#element_validate' => array('element_validate_numeric_positive'), 
        '#prefix' => '<div class="row"><div class="col-md-6" id="reload_present_pincode"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')), //'id' => 'present_pincode', 
        '#default_value' => $data->present_pincode
    );
    
    $form['prrsonal_info']['mobile'] = array(
        '#title' => t('Mobile no'),
        '#type' => 'textfield',
        '#default_value' => $data->mobile_no,
        '#maxlength' => 10,
        '#required' => TRUE,
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
        '#required' => TRUE,
        '#element_validate' => array('element_validate_email'),
        '#attributes' => array('oninput'=>"this.value=this.value.toLowerCase()",'class'=>array('form-control')),
        '#default_value' => $data->mail,
    );
    
    $form['prrsonal_info']['dob'] = array(
        '#title' => t('Date of Birth(According to Service Book)'),
        '#type' => 'textfield',
        '#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dob','class'=>array('form-control')),
        '#required' => TRUE,
        '#validated' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_date', 'element_validate_age'),
        '#default_value' => $data->date_of_birth,
    );
    
    $form['prrsonal_info']['gender'] = array(
        '#title' => t('Gender'),
        '#type' => 'radios',
        '#options' => array('M' => 'Male', 'F' => 'Female'),
        '#default_value' => $data->gender,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#required' => TRUE,
    );
    
    // occupant's official information
    $form['official_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Occupant\'s Official Information'),
        '#collapsible' => FALSE, 
        '#collapsed' => FALSE, 
    );
    
    $form['official_info']['hrms_id'] = array(
        '#title' => t('Employee HRMS ID'),
        '#type' => 'textfield',
        '#default_value' => $data->hrms_id,
        '#maxlength' => 10,
        '#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_hrms_id'),
        '#required' => TRUE,
    );
    
    $form['official_info']['occupant_designation'] = array(
        '#title' => t('Designation'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#element_validate' => array('element_validate_textarea'),
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
        //'#attributes' => array('id' => 'edit-app-designation', 'oncopy' => "return false", 'onpaste' => "return false"),
        '#default_value' => $data->applicant_designation,
    );

    $form['official_info']['pay_band'] = array(
        '#title' => t('Basic Pay Range'),
        '#type' => 'select',
        '#options' => pay_band_list(),
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#validated' => TRUE,
        '#attributes' => array('class'=>array('form-control'))
    );

    $form['official_info']['pay_in'] = array(
        '#title' => t('Basic Pay'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#element_validate' => array('element_validate_numeric_positive'), 
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
        '#default_value' => $data->pay_in_the_pay_band
    );
    
    $form['official_info']['occupant_posting_place'] = array(
        '#title' => t('Place of Posting'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'),
        '#default_value' => $data->applicant_posting_place,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),  
    ); 

    $form['official_info']['occupant_headquarter'] = array(
        '#title' => t('Headquarter'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'), 
        '#default_value' => $data->applicant_headquarter,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
    );

    $form['official_info']['doj'] = array(
        '#title' => t('Date of Joining'),
        '#type' => 'textfield',
        '#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doj','class'=>array('form-control')),
        '#default_value' => $data->date_of_joining,
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        // '#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
    );
    
    $form['official_info']['dor'] = array(
        '#title' => t('Date of Retirement(According to Service Book)'),
        '#type' => 'textfield',
        //'#attributes' => array('readonly' => 'readonly'),
        '#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dor','class'=>array('form-control')),
        '#default_value' => $data->date_of_retirement,
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        // '#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
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
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_textarea'),
        '#default_value' => $data->office_name,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),  
    );
    
    $form['office_add']['office_street'] = array(
        '#title' => t('Address of the Office'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#element_validate' => array('element_validate_streetaddress'), 
        '#default_value' => $data->office_street,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
    );

    $form['office_add']['office_city'] = array(
        '#title' => t('City / Town / Village'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'), 
        '#default_value' => $data->office_city_town_village,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
    );

    $form['office_add']['office_post_office'] = array(
        '#title' => t('Post Office'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'), 
        '#default_value' => $data->office_post_office,
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
    );

    $form['office_add']['office_district'] = array(
        '#title' => t('District'),
        '#type' => 'select',
        '#options' => district_list(),
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#attributes' => array('class'=>array('form-select')),
        '#default_value' => $data->office_district
    );

    $form['office_add']['office_pincode'] = array(
        '#title' => t('Pincode'),
        '#type' => 'textfield',
        '#maxlength' => 6,
        '#required' => TRUE,
        '#element_validate' => array('element_validate_numeric_positive'), 
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
        '#default_value' => $data->office_pin_code
    );

    $form['office_add']['office_phone_no'] = array(
        '#title' => t('Phone No.(With STD Code)'),
        '#type' => 'textfield',
        '#maxlength' => 15,
        '#required' => TRUE,
        '#element_validate' => array('element_validate_telephoneno'), 
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class' => array('numeric_positive'),'class'=>array('form-control')),
        '#default_value' => $data->office_phone_no
    );
    
    // ddo details
    $form['ddo'] = array(
        '#type' => 'fieldset',
        '#title' => t('DDO with Full Address'),
        '#collapsible' => FALSE, 
        '#collapsed' => FALSE, 
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
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#attributes' => array('class'=>array('form-select')),
        
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
        '#required' => TRUE,
        '#validated' => TRUE,
        '#prefix' => '<div id="replace_designation" class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class'=>array('form-select')),
    );

    
    $form['ddo']['address'] = array(
        '#title' => t('DDO Address'),
        '#type' => 'textarea',
        '#attributes' => array('readonly' => 'readonly'),
        '#prefix' => '<div id="replace_ddo_address" class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        // '#required' => TRUE,
        '#validated' => TRUE,
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
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_alphabatic_text'), 
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')), 
        '#default_value' => 'NA'
    );

    $form['license']['dol'] = array(
        '#title' => t('License Issue Date'),
        '#type' => 'textfield',
        '#attributes' => array('readonly' => 'readonly', 'id' => 'edit-dol','class'=>array('form-control')),
        '#required' => TRUE,
        '#validated' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#element_validate' => array('element_validate_date', 'element_validate_age'),
    );

    $form['license']['authorised_or_not'] = array(
        '#title' => t('Occupant Status'),
        '#type' => 'select',
        //'#options' => pay_band_list(),
        '#options' => ['authorised' => 'Authorised Occupant', 'unauthorised' => 'Unauthorised Occupant'],
        '#required' => TRUE,
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
        '#upload_validators' => array(
            'file_validate_extensions' => array("pdf"),
        ),
        '#upload_location' => 'public://doc/',
        '#process' => array('vertical_shifting_element_process'),
    );
    
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


    return $form;
}