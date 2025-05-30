<?php
// Done by Subham dt.28-05-2025
function user_tagging_form($form, &$form_state) {

    $form['personal_info'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => '</div>',
    );
						
    $form['personal_info']['applicant_name'] = array(
        '#title' => t('Applicant\'s Name'),
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#default_value' => '',
        '#element_validate' => array('element_validate_alphabatic_fullstop'),
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()", 'class'=>array('form-control')),
        '#required' => TRUE,
    );

    $form['personal_info']['mobile_no'] = array(
        '#title' => t('Mobile no'),
        '#type' => 'textfield',
        '#maxlength' => 10,
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_mobile'),
        '#attributes' => array('id' => 'mobile_no', 'class'=>array('form-control')),
    );

    $form['personal_info']['email'] = array(
        '#title' => t('Email ID'),
        '#type' => 'textfield',
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_email'),
        '#attributes' => array('oninput'=>"this.value=this.value.toLowerCase()", 'class'=>array('form-control')),
        '#default_value' => '',
    );

    $form['personal_info']['identification_no'] = array(
        '#title' => t('Any Identification No. (HRMS/Aadhaar/PAN)'),
        '#type' => 'textfield',
        '#maxlength' => 10,
        '#attributes' => array('class'=>array('form-control', 'numeric_positive')),
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('element_validate_hrms_id'),
        '#required' => TRUE,
    );

    $form['flat_info'] = array(
        '#prefix' => '<div class="row">',
        '#suffix' => '</div>',
    );

    $form['flat_info']['rhe_name'] = array(
        '#title' => t('Name of the RHE'),
        '#type' => 'select',
        '#options' => rhe_list(),
        '#required' => TRUE,
        '#attributes' => array('class' => array('form-select')),
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
	);

    $form['flat_info']['flat_type'] = array(
        '#title' => t('Flat Type'),
        '#type' => 'select',
        '#options' => rhe_flat_type(),
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class' => array('form-select')),
	);

    $form['flat_info']['rhe_block'] = array(
        '#title' => t('Name of the Block'),
        '#type' => 'select',
        '#options' => rhe_block_list(),
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#attributes' => array('class' => array('form-select')),
    );
    
    $form['flat_info']['flat_floor'] = array(
        '#title' => t('Floor No.'),
        '#type' => 'select',
        '#options' => array('Ground' => 'Ground', 'First' => 'First', 'Second' => 'Second', 'Third' => 'Third','Fourth'=>'Fourth',
                            'Fifth'=>'Fifth','Sixth'=>'Sixth','Seventh'=>'Seventh','Eighth'=>'Eighth','Top'=>'Top'),
        '#required' => TRUE,
        '#prefix' => '<div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div></div>',
        '#attributes' => array('class' => array('form-select')),
    );
    
    $form['flat_info']['flat_no'] = array(
        '#title' => t('Flat No.'),
        '#type' => 'textfield',
        '#default_value' => '',
        '#required' => TRUE,
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#element_validate' => array('validate_flat_no'),
        '#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()",'class'=>array('form-control')),
    );
     
    $form['submit_row'] = array(
        '#prefix' => '<div class="row"><div class="col-md-12 text-center">',
        '#suffix' => '</div></div>',
    );

    $form['submit_row']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#attributes' => array('class' => array('btn bg-primary btn-sm px-5 rounded-pill text-white fw-bolder')),
        '#submit' => array('user_tagging_submit')
    );
                            
    return $form;
}

function user_tagging_submit($form, &$form_state) {
    $form_data = array();

    $form_data['applicant_name'] = trim($form_state['values']['applicant_name']);
    $form_data['mobile_no'] = trim($form_state['values']['mobile_no']);
    $form_data['email'] = trim($form_state['values']['email']);
    $form_data['identification_no'] = trim($form_state['values']['identification_no']);
    $form_data['estate_id'] = trim($form_state['values']['rhe_name']);
    $form_data['flat_type_id'] = trim($form_state['values']['flat_type']);
    $form_data['block_id'] = trim($form_state['values']['rhe_block']);
    $form_data['floor'] = trim($form_state['values']['flat_floor']);
    $form_data['flat_no'] = trim($form_state['values']['flat_no']);
    $form_data['created_date'] = date('Y-m-d H:i:s');
    $form_data['status'] = '1';
    $form_data['flag'] = 'new';  // New or Tagged
  
    // echo '<<pre>'; print_r($form_data); die;

    db_insert('housing_user_tagging')
        ->fields($form_data)
        ->execute();
    drupal_set_message(t('Successfully User Tagged'));
    drupal_goto('dashboard');
}
