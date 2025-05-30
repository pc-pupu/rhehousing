<?php

   
  function add_existing_occupant($form, &$form_state){
		
		/*insert into housing_existing_flat_occupant*/
	    
		$occupant_arr = array();
		$occupant_arr['mail']  =  trim($form_state['values']['email']);
		$occupant_arr['applicant_name']  =  trim($form_state['values']['applicant_name']);
		$occupant_arr['guardian_name']  =  trim($form_state['values']['applicant_father_name']);
		$occupant_arr['gender']  =  trim($form_state['values']['gender']);
		$occupant_arr['date_of_birth']  =  trim($form_state['values']['dob']);
		$occupant_arr['mobile_no']  =  trim($form_state['values']['mobile']);
		$occupant_arr['ddo_id']  =   trim($form_state['values']['designation']);
		$occupant_arr['applicant_designation']  =  trim($form_state['values']['app_designation']);
		$occupant_arr['applicant_headquarter']  =  trim($form_state['values']['app_headquarter']);
		$occupant_arr['applicant_posting_place']  =  trim($form_state['values']['app_posting_place']);
		$occupant_arr['pay_band_id']  =  trim($form_state['values']['pay_band']);
		$occupant_arr['pay_in_the_pay_band']  =  trim($form_state['values']['pay_in']);
		$occupant_arr['grade_pay']  =  trim($form_state['values']['grade_pay']);
		$occupant_arr['date_of_joining']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['doj']))));
		$occupant_arr['date_of_retirement']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['dor']))));
		$occupant_arr['office_name']  =  trim($form_state['values']['office_name']);
		$occupant_arr['office_street']  =  trim($form_state['values']['office_street']);
		$occupant_arr['office_city_town_village']  =  trim($form_state['values']['office_city']);
		$occupant_arr['office_post_office']  =  trim($form_state['values']['office_post_office']);
		$occupant_arr['office_pin_code']  =  trim($form_state['values']['office_pincode']);
		
		if($form['document_upload']['file']['#value']['fid'] != 0 ){
		// file exists
      		$file = file_load($form['document_upload']['file']['#value']['fid']);
	  		if ($file->status==0)
      		{
        		$file->status = FILE_STATUS_PERMANENT;
        		file_save($file);
				file_usage_add($file, 'common_application', 'upload_documents', 1);
				$occupant_arr['document']  =  $file->fid;
			}
		}
			
		db_insert('housing_existing_flat_occupant')
		->fields($occupant_arr)
		->execute();
	  
	//insert into housing_flat_occupant
	  
	  $query = db_select('housing_existing_flat_occupant','hefo');
	  $query->addExpression('MAX(existing_flat_occupant_id)','id');
	  $result =$query->execute();
	  $data = $result->fetchObject();
		
	  $housing_flat_occupant = array();
	  $housing_flat_occupant['flat_id']  =  trim($form_state['values']['flat_name']);//
	  $housing_flat_occupant['allotment_no']  =  trim($form_state['values']['allotment_no']);//
	  $housing_flat_occupant['allotment_date']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['allotment_date']))));
	  $housing_flat_occupant['housing_existing_flat_occupant_id']  =  $data->id;
		
	  db_insert('housing_flat_occupant')
  	  ->fields($housing_flat_occupant)
  	  ->execute();
	  
	  //insert into housing_occupant_license
	  $query = db_select('housing_flat_occupant','hfo');
	  $query->addExpression('MAX(flat_occupant_id)','id');
	  $result =$query->execute();
	  $data = $result->fetchObject();
	  
	  $housing_occupant_license = array();
	  $housing_occupant_license['flat_occupant_id']  =  $data->id;
	  $housing_occupant_license['license_no']  =  trim($form_state['values']['license_no']);
		$housing_occupant_license['license_issue_date']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['license_issue_date']))));
		$housing_occupant_license['license_expiry_date']  =  trim( implode('-', array_reverse(explode('/', $form_state['values']['license_expiry_date']))));
		db_insert('housing_occupant_license')
  	  ->fields($housing_occupant_license)
  	  ->execute();
		
		
		$query = db_select('housing_flat_status', 'hfs');
		$query->addField('hfs','flat_status_id');
		$query->condition('hfs.is_occupied', TRUE, '=');
		$result =$query->execute();
		$data = $result->fetchObject();
		$id = $data->flat_status_id;
	 
		$flat_arr = array();
		$flat_arr['flat_status_id'] = $id;
		db_update('housing_flat')
		->fields($flat_arr)
		->condition('flat_id', trim($form_state['values']['flat_name']), '=')
		->execute();
	  
	  drupal_set_message(t('Successfully Added!!!'));

   }