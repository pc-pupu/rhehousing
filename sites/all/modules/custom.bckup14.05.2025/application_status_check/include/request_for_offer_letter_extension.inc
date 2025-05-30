<?php // Done by Subham 06-12-2024
function request_for_offer_letter_extension_form($form,&$form_state, $app_id = '', $app_status = '', $uid = '', $off_detail_id = '', $dov = '') {
  global $user, $user_role;
  

  $enc_app_id = decrypt_url($app_id);
  $enc_app_status = decrypt_url($app_status);
  
  $enc_uid = decrypt_url($uid);
  $enc_off_detail_id = decrypt_url($off_detail_id);
  $enc_dov = decrypt_url($dov);
  //print_r($enc_dov);die;
  $date_only = date('Y-m-d', strtotime($enc_dov));
  //echo $date_only;die;

  drupal_add_js(array('application_status_check' => array('date_only' => $date_only)), 'setting');

  $form['offer_letter_extension_reason_dropdown'] = array(
    '#title' => t('Reason for Offer Letter Extension'),
    '#type' => 'select',
    '#options' => array(
                'Reason_1' => t('Reason-1'),
                'Reason_2' => t('Reason-2')
    ),
    '#required' => TRUE,
    '#prefix' => '<div class="row"><div class="col-md-4"><div class="form-floating">',
		'#suffix' => '</div></div>'
  );

  $form['add_offer_letter_extension_date'] = array(
		'#title' => t('Enter Extension Date :'),
		'#type' => 'textfield',
		'#attributes' => array('id' => 'edit-extension', 'class' => array('numeric_positive form-control')),
		'#default_value' => '',
		'#required' => TRUE,
		'#prefix' => '<div class="row"><div class="col-md-4"><div class="form-floating">',
		'#suffix' => '</div></div>'
	);

  $form['offer_letter_extension_reason_file'] = array(
    '#title' => t('Upload valid reason for offer letter extension: '),
    '#type' => 'managed_file',
    '#description' => t('<b>Allowed Extension: pdf<br>Maximum File Size: 2 MB</b>'),
    '#progress_message' => t('Please wait...'),
    '#progress_indicator' => 'bar',
    '#default_value' => variable_get('Upload File', ''),
    '#upload_validators' => array(
                   'file_validate_extensions' => array("pdf"),
                   'file_validated_size' => array(2*1024*1024),
                ),
    '#upload_location' => 'public://doc/'.$user->uid,
    '#required' => TRUE,
    '#process' => array('offer_letter_upload_element_process')
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#prefix' => '<div class="col-md-4"><div class="form-floating">',
    '#suffix' => '</div></div></div>',
    '#attributes' => array('class' => array('text-centre btn bg-primary btn-sm px-5 mt-5 rounded-pill text-white fw-bolder')),
  );

  $form['app_id'] = array(
		'#title' => t('App_id: '),
		'#type' => 'hidden',
		'#default_value' => $enc_app_id,
	);

  $form['official_detail_id'] = array(
		'#title' => t('Off_detail_id: '),
		'#type' => 'hidden',
		'#default_value' => $enc_off_detail_id,
	);

  $form['uid'] = array(
		'#title' => t('Uid: '),
		'#type' => 'hidden',
		'#default_value' => $enc_uid,
	);

  $form['app_status'] = array(
		'#title' => t('App_sts: '),
		'#type' => 'hidden',
		'#default_value' => $enc_app_status
	);
  
  return $form;
}

function offer_letter_upload_element_process($element, &$form_state, $form) {
  global $user;
  $element = file_managed_file_process($element, $form_state, $form);
  $element['upload_button']['#access'] = FALSE;
  return $element;
}

function request_for_offer_letter_extension_form_submit($form, &$form_state){
  global $user;
  // echo "<pre>";print_r($form_state['values']);die;
  $offer_letter_extension_reason = $form_state['values']['offer_letter_extension_reason_dropdown'];
  $extension_date = $form_state['values']['add_offer_letter_extension_date'];
  $date_object = DateTime::createFromFormat('d/m/Y', $extension_date);
  $extension_date = $date_object->format('Y-m-d');
  //echo $extension_date;die;
  $app_id = $form_state['values']['app_id'];
  $uid = $form_state['values']['uid'];
  $app_status = $form_state['values']['app_status'];
  //echo $app_status;die;
  $official_detail_id = $form_state['values']['official_detail_id'];
  // echo $official_detail_id;die;
  // print_r(['values']['uid']);die;
  if (!empty($form_state['values']['offer_letter_extension_reason_file'])) {
    $file = file_load($form_state['values']['offer_letter_extension_reason_file']);
    $dynamic_folder = 'public://doc/'. $user->uid;
    file_prepare_directory($dynamic_folder, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
    $file_name = time().$file->filename;
    $destination = $dynamic_folder . '/' .$file_name ;
    $file = file_copy($file, $destination, FILE_EXISTS_REPLACE);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    $fid = $file->fid;
  }

  $status_id = get_status_id('offer_letter_extended');

  $status_updation_arr  = array();
  $status_updation_arr['status']  =  'offer_letter_extended';
  $status_updation_arr['date_of_verified']  =  date('Y-m-d H:i:s');

  db_update('housing_online_application')
  ->fields($status_updation_arr)
  ->condition('online_application_id', $app_id, '=')
  ->execute();

  $app_off_detail_arr_status_update = array();
  $app_off_detail_arr_status_update['is_active']  =  '1';
  // echo $official_detail_id;die;
  db_update('housing_applicant_official_detail')
  ->fields($app_off_detail_arr_status_update)
  ->condition('applicant_official_detail_id', $official_detail_id, '=')
  ->execute();

  $insert_process_flow = array(
                  'online_application_id' => $app_id,
                  'status_id' => $status_id,
                  'created_at' => date("Y-m-d H:i:s"),
                  'uid' => $user->uid,
                  'short_code' => 'offer_letter_extended'
  );

  db_insert('housing_process_flow')
  ->fields($insert_process_flow)
  ->execute();

  if ($app_status == 'offer_letter_cancel') {
      $display_type_of_extension = 'Offer Letter';
  }
  $insert_housing_license_offer_letter_extension = array(
                  'uid' => $uid,
                  'online_application_id' => $app_id,
                  'status' => 'offer_letter_extended',
                  'created_date' => date('Y-m-d H:i:s'),
                  'extended_upto' => $extension_date,
                  'type_of_extension' => $display_type_of_extension,
                  'reason_for_extension' => $offer_letter_extension_reason,
                  'doc_fid' => $fid,
                  'departmental_uid' => $user->uid
  );
  db_insert('housing_license_offer_letter_extension')
  ->fields($insert_housing_license_offer_letter_extension)
  ->execute();

  $update_housing_flat_occupant = array();
  $update_housing_flat_occupant = array(
                  'cancellation_extension_status' => 'offer_letter_extended',
                  'cancellation_extension_date' => date('Y-m-d H:i:s')
  );
  db_update('housing_flat_occupant')
  ->fields($update_housing_flat_occupant)
  ->condition('online_application_id', $app_id, '=')
  ->execute();
  
  drupal_set_message(t('Offer Letter has been Extended!'));
  drupal_goto('common-application-view/'.encrypt_url($app_id).'/'.encrypt_url($app_status));
}