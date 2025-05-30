<?php 
function application_status_check_form($form,&$form_state) {
  global $user_role;

  // echo $user_role; die;

  
 // <div class="row">
  $optionList = array(
    1 => t('Application Number')
  );

  $title_txt = t('Enter Application Number: ');
  if($user_role == 6){
    $optionList[2] = t('HRMS Id');
    $title_txt = t('Enter Application Number or HRMS Id: ');
  }


  $form['select_button'] = array(
    '#type' => 'radios',
    '#title' => t('Select the option via you want to search application details :'),
    '#options' => $optionList,
    '#default_value' => 1
  );

  $form['application_or_hrms_no'] = array(
    '#type' => 'textfield',
    '#title' => $title_txt,
    '#default_value' => '',
    '#attributes' => array('placeholder' => 'Enter Details', 'class' => array('form-control form-control-sm')),
    '#required' => TRUE,
    '#prefix' => '<br><br><div class="col-md-8"><div class="form-floating">',
    '#suffix' => '</div></div>',
    '#weight' => 2
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#prefix' => '<div class="col-md-4"><div class="form-floating">',
    '#suffix' => '</div></div>',
    '#attributes' => array('class' => array('text-centre btn bg-primary btn-sm px-5 mt-5 rounded-pill text-white fw-bolder')),
    '#weight' => 3
  );

  return $form;
}



function application_status_check_form_submit($form,&$form_state){

  $select_button_status = $form_state['values']['select_button'];
 
  if($select_button_status == 1){
    $app_no = isset($form_state['values']['application_or_hrms_no']) && !empty($form_state['values']['application_or_hrms_no']) ? $form_state['values']['application_or_hrms_no'] : '';

    $query = db_select('housing_online_application', 'hoa');
    $query->fields('hoa', ['online_application_id', 'status']);
    $query->condition('hoa.application_no', $app_no);
    $result = $query->execute();
    $result = $result->fetchObject();
    if ($result) {
      $app_id = $result->online_application_id;
      $app_status = $result->status;
      drupal_goto('common-application-view/'.encrypt_url($app_id).'/'.encrypt_url($app_status));
    } else {
      drupal_set_message(t('Invalid Application Number, Check Application Number once again.'), 'error');
    }
  }elseif($select_button_status == 2){
    $get_hrms_no = isset($form_state['values']['application_or_hrms_no']) && !empty($form_state['values']['application_or_hrms_no']) && is_numeric($form_state['values']['application_or_hrms_no']) ? $form_state['values']['application_or_hrms_no'] : '';
    if ($get_hrms_no) {
      $query = db_select('housing_applicant_official_detail', 'haod');
      $query->innerJoin('housing_online_application', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
      $query->fields('hoa', ['online_application_id', 'status']);
      $query->condition('haod.hrms_id', $get_hrms_no);
      $result = $query->execute();
      $result = $result->fetchObject();
      $app_id = $result->online_application_id;
      $app_status = $result->status;
      drupal_goto('common-application-view/'.encrypt_url($app_id).'/'.encrypt_url($app_status));
    } else {
      drupal_set_message(t('Invalid HRMS ID, Check HRMS ID once again.'), 'error');
    }
  }
}