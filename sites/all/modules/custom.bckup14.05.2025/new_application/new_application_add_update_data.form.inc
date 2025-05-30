<?php

   
  function add_new_allotment_application($form, &$form_state, $online_application_id){
	  
   		global $user;
		
		/* add new alltment application*/  
		$new_allotment_app_arr = array();
		$new_allotment_app_arr['online_application_id']  =  $online_application_id;
		$new_allotment_app_arr['allotment_category']  =  trim($form['allotment_reason']['reason']['#value']);
		$new_allotment_app_arr['flat_type_id'] = fetch_rhe_flat_id(trim($form['allotment_reason']['rhe_flat_type']['#value']));
		
		//  echo "<pre>";print_r($form_state);
		// exit();
		//if($form_state['input']['estate_preference'] != 0)
		//print_r($form_state);die;

		// debolina start
		if($form_state['values']['first_preference'] != 0 && $form_state['values']['second_preference'] && $form_state['values']['third_preference']!=0) {

			$estate_preference_arr=array();
			$estate_preference_arr[1]=array(
				'estate_id'=>$form_state['values']['first_preference'],
			);
			$estate_preference_arr[2]=array(
				'estate_id'=>$form_state['values']['second_preference'],
			);
			$estate_preference_arr[3]=array(
				'estate_id'=>$form_state['values']['third_preference'],
			);
			//print_r($estate_preference_arr);die;

			$transaction = db_transaction();
			try{
				$haveData= false;
				$estateDetailsInsertQuery = db_insert('housing_new_application_estate_preferences')->fields(array(
		        'estate_id',
		        'preference_order',
		        'online_application_id',
		        'created'
		    ));


				$counter=1;
				foreach ($estate_preference_arr as $value) {
					$estateDetailsData = array(
											'estate_id' => $value['estate_id'],
											'preference_order' => $counter,
											'online_application_id' => $online_application_id,
											'created' => date('d-m-y h:i:s')
										);
					$counter++;
					// print_r($estateDetailsData);die;
					$estateDetailsInsertQuery->values($estateDetailsData)->execute();
				}
			}catch (Exception $e){
				// One of the INSERTs failed, rollback the whole batch.
		    $transaction->rollback();
		    // Rethrow the exception for the calling code.
		    //throw $e;
		    watchdog_exception('new_allotment', $e);
		   // drupal_set_message(t($e), 'error');
			}

		}

		//debolina end

		//old code with 10 preferences
		/*if($form_state['input']['housing_preference'] != 0)  
		{
			print_r($form_state['input']['housing_preference'] );die;
		
		$transaction = db_transaction();
		try {
			    $haveData= false;
			    $estateDetailsInsertQuery = db_insert('housing_new_application_estate_preferences')->fields(array(
			        'estate_id',
			        'preference_order',
			        'online_application_id',
			        'created'
			    ));
			   
			    foreach ($form_state['input']['estate_preference'] as $key => $value) {
			        $haveData= true;
			        $estateDetailsData = array(
			            'estate_id' => $key,
			            'preference_order' => $value,
			            'online_application_id' => $online_application_id,
			            'created' => date('d-m-y h:i:s')
			        );
			       
			        $estateDetailsInsertQuery->values($estateDetailsData);
			     }
			   
			    /*Insert The estate Details*/
			  /*if ($haveData) {
			    $estateDetailsInsertQuery->execute();
		    }
		    
		}
		catch (Exception $e) {
		    // One of the INSERTs failed, rollback the whole batch.
		    $transaction->rollback();
		    // Rethrow the exception for the calling code.
		    //throw $e;
		    watchdog_exception('new_allotment', $e);
		   // drupal_set_message(t($e), 'error');
			}


		}*/

		
		
		
		
		if($form_state['values']['file'] != 0){
			// file exists
			$file_payslip = file_load($form_state['values']['file']);
			
			if($file_payslip->status == 0)
			{ 
				$file_payslip->status = FILE_STATUS_PERMANENT;
				file_save($file_payslip);
				file_usage_add($file_payslip, 'new_application', 'Payslip Document', $user->uid);
				
				$new_allotment_app_arr['document']  =  $file_payslip->fid;
			}
		}
		
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
		
		if(trim($form['allotment_reason']['reason']['#value']) == 'Transfer' || trim($form['allotment_reason']['reason']['#value']) == 'Physically Handicaped Or Serious Illness' || trim($form['allotment_reason']['reason']['#value']) == 'Recommended' || trim($form['allotment_reason']['reason']['#value']) == 'Single Earning Lady' || trim($form['allotment_reason']['reason']['#value']) == 'Legal Heir') {
			
			if($form_state['values']['extra_doc'] != 0){
				// file exists
				$file_extra_doc = file_load($form_state['values']['extra_doc']);
				
				if($file_extra_doc->status == 0)
				{ 
					$file_extra_doc->status = FILE_STATUS_PERMANENT;
					file_save($file_extra_doc);
					file_usage_add($file_extra_doc, 'new_application', 'Allotment Reason Supporting Document', $user->uid);
					
					$new_allotment_app_arr['extra_doc']  =  $file_extra_doc->fid;
				}
			}
		} else {
			if($form_state['values']['extra_doc'] == 0) {
				$new_allotment_app_arr['extra_doc'] = NULL;
			}
		}
		
		
		if($online_application_id != 0) {
			db_insert('housing_new_allotment_application')
			->fields($new_allotment_app_arr)
			->execute();
		}
		

   }
   function update_new_allotment_application($form, &$form_state, $online_application_id){
   		global $user;
		/* update new alltment application*/  
		$new_allotment_app_arr = array();
		$new_allotment_app_arr['allotment_category']  =  trim($form['allotment_reason']['reason']['#value']);
		$new_allotment_app_arr['flat_type_id'] = fetch_rhe_flat_id(trim($form['allotment_reason']['rhe_flat_type']['#value']));
		
		/*$new_allotment_app_arr['estate_id_choice1']  =  isset($form_state['values']['choice_1']) && !empty($form_state['values']['choice_1']) ? trim($form_state['values']['choice_1']) : NULL;
		$new_allotment_app_arr['estate_id_choice2']  =  isset($form_state['values']['choice_2']) && !empty($form_state['values']['choice_2']) ? trim($form_state['values']['choice_2']) : NULL;
		$new_allotment_app_arr['estate_id_choice3']  =  isset($form_state['values']['choice_3']) && !empty($form_state['values']['choice_3']) ? trim($form_state['values']['choice_3']) : NULL;
		$new_allotment_app_arr['estate_id_choice4']  =  isset($form_state['values']['choice_4']) && !empty($form_state['values']['choice_4']) ? trim($form_state['values']['choice_4']) : NULL;*/
		
		//$new_allotment_app_arr['is_pp_sww_ph'] = trim($form_state['values']['chk_extra_doc'][1]);
		
		/*if($form_state['values']['file'] != 0 || $form_state['values']['extra_doc'] != 0){
			// file exists
			$file = file_load($form_state['values']['file']);
			$file2 = file_load($form_state['values']['extra_doc']);
			
			if ($file->status==0)
			{
				$file->status = FILE_STATUS_PERMANENT;
				file_save($file);
				file_usage_add($file, 'new_application', 'upload_document', 1);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file->fid));
				$new_allotment_app_arr['document']  =  $file->fid;
			}
			if($form_state['values']['extra_doc'] != 0 && $file2->status==0) {
				$file2->status = FILE_STATUS_PERMANENT;
				file_save($file2);
				file_usage_add($file2, 'new_application', 'upload_document', 1);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file->fid));
				$new_allotment_app_arr['extra_doc']  =  $file2->fid;
			}
			else if($form_state['values']['extra_doc'] == 0) {
				$new_allotment_app_arr['extra_doc']  =  NULL;
			}
		}*/

        // deleted	
		if($form_state['values']['file'] == 0){	
			$file_payslip = file_load($form_state['values']['file']) ;
			if($file_payslip) {
				// When a module is managing a file, it must manage the usage count.
				// Here we decrement the usage count with file_usage_delete().
				file_usage_delete($file_payslip, 'new_application', 'Payslip Document', $user->uid);
	
				// The file_delete() function takes a file object and checks to see if
				// the file is being used by any other modules. If it is the delete
				// operation is cancelled, otherwise the file is deleted.
				file_delete($file_payslip);
			}		
		}
		
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
		
		if($form_state['values']['extra_doc'] == 0){
			$file_extra_doc = file_load($form_state['values']['extra_doc']) ;
			if($file_extra_doc) {
				// When a module is managing a file, it must manage the usage count.
				// Here we decrement the usage count with file_usage_delete().
				file_usage_delete($file_extra_doc, 'new_application', 'Allotment Reason Supporting Document', $user->uid);
	
				// The file_delete() function takes a file object and checks to see if
				// the file is being used by any other modules. If it is the delete
				// operation is cancelled, otherwise the file is deleted.
				file_delete($file_extra_doc);
			}		
		}
		//end
		
	//Payslip document
		if($form_state['values']['file'] != 0){
			// file exists
			$file_payslip = file_load($form_state['values']['file']);
			
			if($file_payslip->status == 0)
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
				$db_and->condition('type', 'Payslip Document', '=');
				$query->condition($db_and);
				$query->orderBy('fm.fid', 'ASC');
				$result = $query->execute();
				while($data = $result->fetchObject()) {
					//$filename = substr($data->uri, 13);
					/*echo '<pre>';
					print_r($filename);*/
					
					$file_payslip1 = file_load($data->file_id);
					file_usage_delete($file_payslip1, 'new_application', 'Payslip Document', $user->uid);
    				file_delete($file_payslip1);
				}
				//exit;
			//code end
			
			//code for filename change
				/*$path_parts = pathinfo($file_payslip->filename);
				$file_payslip->filename = 'payslip_doc_'.$user->uid.'_'.time().'.'.$path_parts['extension'];*/
			//code end
			
				$file_payslip->status = FILE_STATUS_PERMANENT;
				file_save($file_payslip);
				file_usage_add($file_payslip, 'new_application', 'Payslip Document', $user->uid);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file_payslip->fid));
				$new_allotment_app_arr['document']  =  $file_payslip->fid;
			}
		}
	//end
	
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
			}
		}
	//end
	
	//Allotment Reason Supporting document
	if(trim($form['allotment_reason']['reason']['#value']) == 'Transfer' || trim($form['allotment_reason']['reason']['#value']) == 'Physically Handicaped Or Serious Illness' || trim($form['allotment_reason']['reason']['#value']) == 'Officer on Transfer having earmarked Bungalow or Quater in their immediate previous posting') {
		if($form_state['values']['extra_doc'] != 0){
			// file exists
			$file_extra_doc = file_load($form_state['values']['extra_doc']);
				
			if($file_extra_doc->status == 0)
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
				$db_and->condition('type', 'Allotment Reason Supporting Document', '=');
				$query->condition($db_and);
				$query->orderBy('fm.fid', 'ASC');
				$result = $query->execute();
				while($data = $result->fetchObject()) {
					//$filename = substr($data->uri, 13);
					/*echo '<pre>';
					print_r($filename);*/
					
					$file_extra_doc1 = file_load($data->file_id);
					file_usage_delete($file_extra_doc1, 'new_application', 'Allotment Reason Supporting Document', $user->uid);
    				file_delete($file_extra_doc1);
				}
				//exit;
			//code end
			
			//code for filename change
				/*$path_parts = pathinfo($file_extra_doc->filename);
				$file_extra_doc->filename = 'reason_supporting_doc_'.$user->uid.'_'.time().'.'.$path_parts['extension'];*/
			//code end
			
				$file_extra_doc->status = FILE_STATUS_PERMANENT;
				file_save($file_extra_doc);
				file_usage_add($file_extra_doc, 'new_application', 'Allotment Reason Supporting Document', $user->uid);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file_extra_doc->fid));
				$new_allotment_app_arr['extra_doc']  =  $file_extra_doc->fid;
			}
		}
	} else {
		if($form_state['values']['extra_doc'] == 0) {
			$new_allotment_app_arr['extra_doc'] = NULL;
		}
	}
		
		
		if($online_application_id != 0) {
			db_update('housing_new_allotment_application')
			->fields($new_allotment_app_arr)
			->condition('online_application_id', $online_application_id, '=')
			->execute();
		}
		
   }