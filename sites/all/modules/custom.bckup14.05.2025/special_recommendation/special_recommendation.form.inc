<?php
function special_recommendation_form($form, &$form_state){
  
    $form = array();

    $form['online_application_ids'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
        '#suffix' => '</div></div>',
        '#attributes' => array('class' => array('form-control'),'id' => array('online_application_ids')),
        //'#required' => TRUE,
    );
  
  
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#prefix' => '<div class="col-md-6"><div class="form-floating"><br><br>',
      '#suffix' => '</div></div>',
      '#attributes' => array('class'=>array('btn bg-primary btn-sm px-5 rounded-pill text-white fw-bolder')),
      '#submit' => array('special_recommendation_form_submit')
    );
  
  

  return $form;
}

function special_recommendation_form_submit($form, &$form_state) {
    die();
  $estate_id = $form_state['values']['estate_edit_dropdown'];
  $treasury_id = $form_state['values']['treasury_edit_dropdown'];
  $is_active_status = $form_state['values']['edit_is_active_button'];

  db_insert('housing_treasury_estate_mapping')
    ->fields(array(
      'estate_id' => $estate_id,
      'treasury_id' => $treasury_id,
      'is_active' => $is_active_status,
    ))
    ->execute();

  drupal_set_message('Data edited successfully.');
  drupal_goto('estate-treasury-selection');
}