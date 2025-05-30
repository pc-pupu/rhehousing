<?php

	function add_flat_block_submit($form, &$form_state) {
		$block_arr = array();
		$block_arr['block_name'] 	=  trim($form_state['values']['block_name']);
		
		db_insert('housing_block')
		->fields($block_arr)
  	  	->execute();
	  
	
	    drupal_set_message(t('Successfully Added Block '.$block_arr['block_name'].' !!!'));
		
	}
    
	function update_flat_submit($form, &$form_state) {
	
	  
		$flat_arr = array();
		$flat_arr['flat_type_id'] 	=  trim($form_state['values']['flat_type']);
		$flat_arr['estate_id'] 				=  trim($form_state['values']['rhe_name']);
		$flat_arr['block_id'] 	=   trim($form_state['values']['rhe_block']);
		$flat_arr['floor'] 	=   trim($form_state['values']['flat_floor']);
		$flat_arr['flat_no'] 			=  trim($form_state['values']['flat_no']);
		$flat_arr['flat_status_id'] 	=   trim($form_state['values']['flat_status']);
		$flat_arr['remarks'] 	=   trim($form_state['values']['remarks_textbox']); //Subham 24-10-2024
		
		
		
		// echo '<<pre>'; print_r($flat_arr); die;


		db_insert('housing_flat')
		->fields($flat_arr)
		->execute();
		
		  
		
		drupal_set_message(t('Successfully Added Flat No. '.$flat_arr['flat_no'].' !!!'));
	  
	  
	}

	function edit_flat_submit($form, &$form_state) {
	
	
		$flat_arr = array();
		$flat_arr['flat_type_id'] 	=  trim($form_state['values']['flat_type']);
		$flat_arr['estate_id'] 				=  trim($form_state['values']['rhe_name']);
		$flat_arr['block_id'] 	=   trim($form_state['values']['rhe_block']);
		$flat_arr['floor'] 	=   trim($form_state['values']['flat_floor']);
		$flat_arr['flat_no'] 			=  trim($form_state['values']['flat_no']);
		$flat_arr['flat_status_id'] 	=   trim($form_state['values']['flat_status']);
		
		db_update('housing_flat')
		->fields($flat_arr)
		->condition('flat_id', trim($form_state['values']['flat_id']), '=')
		->execute();
		// $form['#redirect'] = "update_flat/view";
		
		drupal_set_message(t('Successfully Updated!!!'));
		
		drupal_goto('update_flat');
	
	
	}
