<?php

   
  function add_renew_license_application($form, &$form_state,$online_application_id){
   		global $user;
		/* add new license application*/  
		$renew_license_app_arr = array();
		$renew_license_app_arr['online_application_id']  =  $online_application_id;
		$renew_license_app_arr['type_of_application']  =  'new';
		$renew_license_app_arr['allotment_no']  =   trim($form['allotment_info']['allotment_no']['#value']);
		$renew_license_app_arr['allotment_date']  =   trim( implode('-', array_reverse(explode('/', $form['allotment_info']['allotment_date']['#value']))));
		$renew_license_app_arr['allotment_district']  =   trim($form['allotment_info']['allotment_district']['#value']);
		$renew_license_app_arr['allotment_estate']  =   trim($form['allotment_info']['allotment_estate']['#value']);
		$renew_license_app_arr['allotment_address']  =   trim($form['allotment_info']['allotment_address']['#value']);
		//$renew_license_app_arr['allotment_flat']  =   trim($form['allotment_info']['allotment_flat']['#value']);
		
		$renew_license_app_arr['allotment_flat_id']  =   trim($form['allotment_info']['allotment_flat_id']['#value']);		
		
		if($form_state['values']['file'] != 0){
			// file exists
			$file = file_load($form_state['values']['file']);
			
			if ($file->status==0)
			{ 
				$file->status = FILE_STATUS_PERMANENT;
				file_save($file);
				file_usage_add($file, 'renew_license', 'upload_document', 1);
				$renew_license_app_arr['document']  =  $file->fid;
				
			}
			
		}
		else {
			$renew_license_app_arr['document']  =  NULL;
		}
		
		db_insert('housing_license_application')
  	  	->fields($renew_license_app_arr)
  	  	->execute();

   }
   
   function update_renew_license_application($form, &$form_state,$online_application_id){
		$renew_license_app_arr = array();

        // deleted	
		if($form_state['values']['file'] == 0 ){	
			$file =  file_load($form_state['values']['file']) ;
			if ($file) {
				// When a module is managing a file, it must manage the usage count.
				// Here we decrement the usage count with file_usage_delete().
				file_usage_delete($file, 'renew_license', 'upload_document', 1);
	
				// The file_delete() function takes a file object and checks to see if
				// the file is being used by any other modules. If it is the delete
				// operation is cancelled, otherwise the file is deleted.
				file_delete($file);
			}		
		}
		
		if($form_state['values']['file'] != 0) {
			// file exists
			$file = file_load($form_state['values']['file']);
			
			if ($file->status==0)
			{
				$file->status = FILE_STATUS_PERMANENT;
				file_save($file);
				file_usage_add($file, 'renew_license', 'upload_document', 1);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file->fid));
				$renew_license_app_arr['document']  =  $file->fid;
				
				db_update('housing_license_application')
  	  			->fields($renew_license_app_arr)
	   			->condition('online_application_id', $online_application_id, '=')
  	  			->execute();	
			}
		}
		else {
			$renew_license_app_arr['document']  =  NULL;
			
			db_update('housing_license_application')
  	  		->fields($renew_license_app_arr)
	   		->condition('online_application_id', $online_application_id, '=')
  	  		->execute();
		}
		
		/*db_update('housing_license_application')
  	  	->fields($renew_license_app_arr)
	   	->condition('online_application_id', $online_application_id, '=')
  	  	->execute();*/
		
   }