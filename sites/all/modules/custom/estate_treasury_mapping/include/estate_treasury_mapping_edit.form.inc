<?php
function estate_treasury_mapping_edit_form($form, &$form_state, $en_id = 0){
  
  $en_id = decrypt_url($en_id);
  
  $form = array();

  $query1 = db_select('housing_treasury_estate_mapping', 'he')->fields('he', array())->condition('housing_treasury_estate_mapping_id',$en_id )->execute();
  $result = $query1->fetchAssoc();
  if(!empty($result)){

    $form['estate_edit_dropdown'] = array(
      '#type' => 'select',
      '#title' => 'Select housing estate',
      '#options' => getEstateList(),
      '#default_value' => getEstateList($result['estate_id']),
      '#prefix' => '<div class="row"><div class="col-md-6"><div class="form-floating">',
      '#suffix' => '</div></div>',
      '#attributes' => array('class' => array('form-control')),
      '#required' => TRUE,
    );
  
    $form['treasury_edit_dropdown'] = array(
      '#type' => 'select',
      '#title' => 'Select respective treasury',
      '#prefix' => '<div class="col-md-6"><div class="form-floating">',
      '#suffix' => '</div></div></div>',
      '#options' => getTresaryList(),
      '#default_value' => getTresaryList($result['treasury_id']),
      '#attributes' => array('class' => array('form-control')),
      '#required' => TRUE,
    );
  
    $form['edit_is_active_button'] = array(
      '#type' => 'radios',
      '#title' => t('Select Activation Status'),
      '#options' => array(1 => t('Active'),0 => t('Inactive')),
      '#prefix' => '<div class="col-md-6"><div class="form-floating">',
      '#suffix' => '</div></div>',
      '#default_value' => $result['is_active']
    );
  
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#prefix' => '<div class="col-md-6"><div class="form-floating"><br><br>',
      '#suffix' => '</div></div>',
      '#attributes' => array('class'=>array('btn bg-primary btn-sm px-5 rounded-pill text-white fw-bolder')),
      '#submit' => array('estate_treasury_edit_submit')
    );
  }
  

  return $form;
}

function estate_treasury_edit_submit($form, &$form_state) {
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