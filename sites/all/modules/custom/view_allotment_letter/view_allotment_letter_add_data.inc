<?php
    function update_allotment_submit($online_application_id = NULL) {

	$query = db_select('housing_allotment_letter', 'hal');
	$query->addField('hal', 'allotment_letter_id');
	$query->addField('hal', 'flat_id');
	$query->condition('hal.online_application_id',$online_application_id,'=');
	$result = $query->execute();  
	$data = $result->fetchObject();
	
	
	 $flat_occupant_arr = array();
	 $flat_occupant_arr['online_application_id'] 		= $online_application_id;
	 $flat_occupant_arr['flat_id'] 						= $data->flat_id;
	 $flat_occupant_arr['allotment_no'] 				= $data->allotment_letter_id;	
	  
	  db_insert('housing_flat_occupant')
  	  ->fields($flat_occupant_arr)
  	  ->execute();
	 drupal_set_message(t('Successfully Allotted!!!'));
	  
  }
  
  function cancel_allotment($online_application_id = NULL) {
	 db_delete('housing_allotment_letter')
->condition('online_application_id', $online_application_id)
->execute(); 
	 
	 $housing_online_application = array();
	 $housing_online_application['status'] =  'cancel';	 
	  db_update('housing_online_application')
  	  ->fields($housing_online_application)
	   ->condition('online_application_id', $online_application_id, '=')
  	  ->execute();	 
	
	    drupal_set_message(t('Successfully Updated!!!'));
	  
  }
?>