<?php
   
  function add_new_license_application($form, &$form_state, $online_application_id){
   		global $user;
		/* add new license application*/  
		$new_license_app_arr = array();
		$new_license_app_arr['online_application_id']  =  $online_application_id;
		$new_license_app_arr['type_of_application']  =  'new';
		$new_license_app_arr['allotment_no']  =   trim($form['allotment_info']['allotment_no']['#value']);
		$new_license_app_arr['allotment_date']  =   trim( implode('-', array_reverse(explode('/', $form['allotment_info']['allotment_date']['#value']))));
		$new_license_app_arr['allotment_district']  =   trim($form['allotment_info']['allotment_district']['#value']);
		$new_license_app_arr['allotment_estate']  =   trim($form['allotment_info']['allotment_estate']['#value']);
		$new_license_app_arr['allotment_address']  =   trim($form['allotment_info']['allotment_address']['#value']);
		//$new_license_app_arr['allotment_flat']  =   trim($form['allotment_info']['allotment_flat']['#value']);
		
		$new_license_app_arr['allotment_flat_id']  =   trim($form['allotment_info']['allotment_flat_id']['#value']);		
		
		if($form_state['values']['file'] != 0){
			// file exists
			$file = file_load($form_state['values']['file']);
			
			if ($file->status==0)
			{ 
				$file->status = FILE_STATUS_PERMANENT;
				file_save($file);
				file_usage_add($file, 'new_license', 'Payslip Document', $user->uid);
				$new_license_app_arr['document']  =  $file->fid;
				
			}
			
		}
		else {
			$new_license_app_arr['document']  =  NULL;
		}
		
	//for scan sign upload into new application table
		$result = fetch_online_app_id_new_application_uid();
		if($result->rowCount() > 0) {
			$new_allotment_app_arr = array();
			$data = $result->fetchObject();
			
			if($form_state['values']['scaned_sign'] != 0){
				// file exists
				$file_scaned_sign = file_load($form_state['values']['scaned_sign']);
				
				if($file_scaned_sign->status == 0)
				{ 
					$file_scaned_sign->status = FILE_STATUS_PERMANENT;
					file_save($file_scaned_sign);
					file_usage_add($file_scaned_sign, 'new_application', 'Scaned Signature', $user->uid);
					
					$new_allotment_app_arr['scaned_sign']  =  $file_scaned_sign->fid;
				}
			}
			
			db_update('housing_new_allotment_application')
			->fields($new_allotment_app_arr)
			->condition('online_application_id', $data->online_application_id, '=')
			->execute();
			
		}
		//end
		
		if($online_application_id != 0) {
			db_insert('housing_license_application')
			->fields($new_license_app_arr)
			->execute();
		}

   }
   
   function update_new_license_application($form, &$form_state,$online_application_id){
		global $user;
		
		$new_license_app_arr = array();

        // deleted	
		if($form_state['values']['file'] == 0 ){	
			$file =  file_load($form_state['values']['file']) ;
			if ($file) {
				// When a module is managing a file, it must manage the usage count.
				// Here we decrement the usage count with file_usage_delete().
				file_usage_delete($file, 'new_license', 'Payslip Document', $user->uid);
	
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
			//code for old uploaded file delete
				$query = db_select('file_managed', 'fm');
				$query->innerJoin('file_usage', 'fu', 'fm.fid = fu.fid');
				$query->fields('fm');
				$query->fields('fu');
				$query->addField('fm', 'fid', 'file_id');
				$db_and = db_and();
				$db_and->condition('uid', $user->uid, '=');
				$db_and->condition('module', 'new_license', '=');
				$query->condition($db_and);
				$query->orderBy('fm.fid', 'ASC');
				$result = $query->execute();
				while($data = $result->fetchObject()) {
					//$filename = substr($data->uri, 13);
					/*echo '<pre>';
					print_r($filename);*/
					
					$file1 = file_load($data->file_id);
					file_usage_delete($file1, 'new_license', 'Payslip Document', $user->uid);
    				file_delete($file1);
				}
				//exit;
			//code end
			
			//code for filename change
				/*$path_parts = pathinfo($file->filename);
				$file->filename = 'payslip_doc_'.$user->uid.'_'.time().'.'.$path_parts['extension'];*/
			//code end
				
				$file->status = FILE_STATUS_PERMANENT;
				
				file_save($file);
				file_usage_add($file, 'new_license', 'Payslip Document', $user->uid);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file->fid));
				$new_license_app_arr['document']  =  $file->fid;
				
				db_update('housing_license_application')
  	  			->fields($new_license_app_arr)
	   			->condition('online_application_id', $online_application_id, '=')
  	  			->execute();	
			}
		}
		else {
			$new_license_app_arr['document']  =  NULL;
			
			if($online_application_id != 0) {
				db_update('housing_license_application')
				->fields($new_license_app_arr)
				->condition('online_application_id', $online_application_id, '=')
				->execute();
			}
		}
		
		
	//for scan sign upload into new application table
		$result_scanned_sign = fetch_online_app_id_new_application_uid();
		if($result_scanned_sign->rowCount() > 0) {
			$new_allotment_app_arr = array();
			$data_scanned_sign = $result_scanned_sign->fetchObject();
			
			if($form_state['values']['scaned_sign'] == 0){	
				$file_scaned_sign = file_load($form_state['values']['scaned_sign']) ;
				if($file_scaned_sign) {
					// When a module is managing a file, it must manage the usage count.
					// Here we decrement the usage count with file_usage_delete().
					file_usage_delete($file_scaned_sign, 'new_application', 'Scaned Signature', $user->uid);
		
					// The file_delete() function takes a file object and checks to see if
					// the file is being used by any other modules. If it is the delete
					// operation is cancelled, otherwise the file is deleted.
					file_delete($file_scaned_sign);
				}		
			}
			
			//Scaned Signature document
			if($form_state['values']['scaned_sign'] != 0){
				// file exists
				$file_scaned_sign = file_load($form_state['values']['scaned_sign']);
				
				if($file_scaned_sign->status == 0)
				{
				//code for old uploaded file delete
					$query = db_select('file_managed', 'fm');
					$query->innerJoin('file_usage', 'fu', 'fm.fid = fu.fid');
					$query->fields('fm');
					$query->fields('fu');
					$query->addField('fm', 'fid', 'file_id');
					$db_and = db_and();
					$db_and->condition('uid', $user->uid, '=');
					$db_and->condition('module', 'new_application', '=');
					$db_and->condition('type', 'Scaned Signature', '=');
					$query->condition($db_and);
					$query->orderBy('fm.fid', 'ASC');
					$result = $query->execute();
					while($data = $result->fetchObject()) {
						//$filename = substr($data->uri, 13);
						/*echo '<pre>';
						print_r($filename);*/
						
						$file_scaned_sign1 = file_load($data->file_id);
						file_usage_delete($file_scaned_sign1, 'new_application', 'Scaned Signature', $user->uid);
						file_delete($file_scaned_sign1);
					}
					//exit;
				//code end
				
				//code for filename change
					/*$path_parts = pathinfo($file_scaned_sign->filename);
					$file_scaned_sign->filename = 'scaned_sign_doc_'.$user->uid.'_'.time().'.'.$path_parts['extension'];*/
				//code end
				
					$file_scaned_sign->status = FILE_STATUS_PERMANENT;
					file_save($file_scaned_sign);
					file_usage_add($file_scaned_sign, 'new_application', 'Scaned Signature', $user->uid);
					//$upd_fields = array_merge($upd_fields, array('fid'=>$file_scaned_sign->fid));
					$new_allotment_app_arr['scaned_sign']  =  $file_scaned_sign->fid;
					
					db_update('housing_new_allotment_application')
					->fields($new_allotment_app_arr)
					->condition('online_application_id', $data_scanned_sign->online_application_id, '=')
					->execute();
				}
			}
		//end
		
		}
		
		/*db_update('housing_license_application')
  	  	->fields($new_license_app_arr)
	   	->condition('online_application_id', $online_application_id, '=')
  	  	->execute();*/
		
   }