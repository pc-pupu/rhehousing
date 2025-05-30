<?php 
function add_possession_det_form($form,&$form_state, $app_id = '', $app_status = '') {

  $enc_app_id = decrypt_url($app_id);
  $enc_app_status = decrypt_url($app_status);

  $form['add_possession_date'] = array(
		'#title' => t('Enter Possession Date :'),
		'#type' => 'textfield',
		//'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doj'),
		'#attributes' => array('id' => 'edit-possession', 'class' => array('numeric_positive form-control')),
		'#default_value' => '',
		'#required' => TRUE,
		'#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
		'#suffix' => '</div></div>',
		//'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
		
	);

  $form['app_id'] = array(
		'#title' => t('Enter Possession Date :'),
		'#type' => 'hidden',
		//'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doj'),
		// '#attributes' => array('id' => 'edit-possession', 'class' => array('numeric_positive form-control')),
		 '#default_value' => $enc_app_id,
		// '#required' => TRUE,
		// '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
		// '#suffix' => '</div></div>',
		//'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
		
	);

  $form['app_status'] = array(
		'#title' => t('Enter Possession Date :'),
		'#type' => 'hidden',
		//'#attributes' => array('readonly' => 'readonly', 'id' => 'edit-doj'),
		// '#attributes' => array('id' => 'edit-possession', 'class' => array('numeric_positive form-control')),
		 '#default_value' => $enc_app_status,
		// '#required' => TRUE,
		// '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
		// '#suffix' => '</div></div>',
		//'#element_validate' => array('element_validate_date', 'element_validate_joining_age'),
		
	);

 

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="col-md-4"><div class="form-floating">',
    '#suffix' => '</div></div></div>',
    '#attributes' => array('class' => array('text-centre btn bg-primary btn-sm px-5 mt-5 rounded-pill text-white fw-bolder')),
    '#weight' => 3
  );

  return $form;
}


function add_possession_det_form_submit($form, &$form_state){
  global $user;
 
  $possession_date = $form_state['values']['add_possession_date'];
  $app_id = $form_state['values']['app_id'];
  $app_status = $form_state['values']['app_status'];
  $date_object = DateTime::createFromFormat('d/m/Y', $possession_date);
  $possession_date = $date_object->format('Y-m-d');
  // echo $possession_date;die;
  $enc_app_id = encrypt_url($app_id);
  $enc_app_status = encrypt_url($app_status);
  
  $query = db_select('housing_occupant_license', 'hol');
  $query->innerJoin('housing_license_application', 'hla', 'hla.license_application_id = hol.license_application_id');
  //$query->innerJoin('housing_occupant_license', 'hol', 'hol.flat_occupant_id = hol.license_application_id');
  $query->innerJoin('housing_flat_occupant', 'hfo', 'hfo.flat_occupant_id = hol.flat_occupant_id');
  //$query->innerJoin('housing_applicant', 'ha', 'ha.uid = haod.uid');
  $query->addField('hol', 'occupant_license_id');
  $query->addField('hfo', 'flat_id');
 // $query->addField('hoa', 'application_no');
  
  $query->condition('hla.online_application_id',$app_id,'=');

  $result = $query->execute();
  $data = $result->fetchObject();

  $occupant_license_id = $data->occupant_license_id;
  $flat_id = $data->flat_id;

  $possession_date_arr['possession_date']  = $possession_date;
  $possession_date_arr['authorised_or_not']  = 'authorised';  //added by dg 08-01-2025

  db_update('housing_occupant_license')
  ->fields($possession_date_arr)
  ->condition('occupant_license_id', $occupant_license_id)
  ->execute();

  $flat_status_id['flat_status_id']  = 2;    //for occupied

  db_update('housing_flat')
  ->fields($flat_status_id)
  ->condition('flat_id', $flat_id)
  ->execute();


  $query1 = db_select('housing_allotment_status_master', 'hasm');
  $query1->addField('hasm', 'status_id');
  
  $query1->condition('hasm.short_code','flat_possession_taken','=');

  $result1 = $query1->execute();
  $data1 = $result1->fetchObject();

  $possession_date_process_flow_arr['online_application_id']  = $app_id;
  $possession_date_process_flow_arr['status_id']              = $data1->status_id;
  $possession_date_process_flow_arr['created_at']             = date("Y-m-d H:i:s");
  $possession_date_process_flow_arr['uid']                    = $user->uid;
  $possession_date_process_flow_arr['short_code']             = 'flat_possession_taken';

  db_insert('housing_process_flow')
  ->fields($possession_date_process_flow_arr)
  ->execute();
  
  drupal_set_message(t('Possession Date Added Successfully.'));
	drupal_goto('common-application-view'.'/'.$enc_app_id.'/'.$enc_app_status);


  
  

  
 
 
}