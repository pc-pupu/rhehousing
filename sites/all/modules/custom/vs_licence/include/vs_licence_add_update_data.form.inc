<?php
   
  function add_vs_licence_application($form, &$form_state, $online_application_id){
   		global $user;
		/* add vs licence application*/  
		$vs_licence_app_arr = array();
		$vs_licence_app_arr['online_application_id']  =  $online_application_id;
		$vs_licence_app_arr['type_of_application']  =  'vs';
		$vs_licence_app_arr['allotment_no']  =   trim($form['allotment_info']['allotment_no']['#value']);
		$vs_licence_app_arr['allotment_date']  =   trim( implode('-', array_reverse(explode('/', $form['allotment_info']['allotment_date']['#value']))));
		$vs_licence_app_arr['allotment_district']  =   trim($form['allotment_info']['allotment_district']['#value']);
		$vs_licence_app_arr['allotment_estate']  =   trim($form['allotment_info']['allotment_estate']['#value']);
		$vs_licence_app_arr['allotment_address']  =   trim($form['allotment_info']['allotment_address']['#value']);
		//$vs_license_app_arr['allotment_flat']  =   trim($form['allotment_info']['allotment_flat']['#value']);
		
		$vs_licence_app_arr['allotment_flat_id']  =   trim($form['allotment_info']['allotment_flat_id']['#value']);		
		
		if($form_state['values']['file'] != 0){
			// file exists
			$file = file_load($form_state['values']['file']);
			
			if ($file->status==0)
			{ 
				$file->status = FILE_STATUS_PERMANENT;
				file_save($file);
				file_usage_add($file, 'vs_licence', 'Payslip Document', $user->uid);
				$vs_licence_app_arr['document']  =  $file->fid;
				
			}
			
		}
		else {
			$vs_licence_app_arr['document']  =  NULL;
		}
		
		if($online_application_id != 0) {
			db_insert('housing_license_application')
			->fields($vs_licence_app_arr)
			->execute();
		}

   }
   
   function update_vs_licence_application($form, &$form_state,$online_application_id){
		global $user;
		
		$vs_licence_app_arr = array();

        // deleted	
		if($form_state['values']['file'] == 0 ){	
			$file =  file_load($form_state['values']['file']) ;
			if ($file) {
				// When a module is managing a file, it must manage the usage count.
				// Here we decrement the usage count with file_usage_delete().
				file_usage_delete($file, 'vs_licence', 'Payslip Document', $user->uid);
	
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
				$db_and->condition('module', 'vs_licence', '=');
				$query->condition($db_and);
				$query->orderBy('fm.fid', 'ASC');
				$result = $query->execute();
				while($data = $result->fetchObject()) {
					//$filename = substr($data->uri, 13);
					/*echo '<pre>';
					print_r($filename);*/
					
					$file1 = file_load($data->file_id);
					file_usage_delete($file1, 'vs_licence', 'Payslip Document', $user->uid);
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
				file_usage_add($file, 'vs_licence', 'Payslip Document', $user->uid);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file->fid));
				$vs_licence_app_arr['document']  =  $file->fid;
				
				db_update('housing_license_application')
  	  			->fields($vs_licence_app_arr)
	   			->condition('online_application_id', $online_application_id, '=')
  	  			->execute();	
			}
		}
		else {
			$vs_licence_app_arr['document']  =  NULL;
			
			if($online_application_id != 0) {
				db_update('housing_license_application')
				->fields($vs_licence_app_arr)
				->condition('online_application_id', $online_application_id, '=')
				->execute();
			}
		}
		
		/*db_update('housing_license_application')
  	  	->fields($new_license_app_arr)
	   	->condition('online_application_id', $online_application_id, '=')
  	  	->execute();*/
		
   }