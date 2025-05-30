<?php

	function add_category_shifting_application($form, &$form_state, $online_application_id) {
		global $user;
		
		$query = db_select('housing_pay_band', 'hpb');
		$query->fields('hpb', array('flat_type_id'));
		$query->condition('hpb.pay_band_id', $form_state['values']['pay_band'], '=');
		$result = $query->execute();
		$data = $result->fetchObject();
		
		/*add data in housing_cs_application*/
		$category_shifting_app_arr = array();
		$category_shifting_app_arr['online_application_id']  =  $online_application_id;
		$category_shifting_app_arr['flat_type_id']  =  $data->flat_type_id;
		$category_shifting_app_arr['occupation_estate']  =   trim($form_state['values']['cs_occupation_estate']);
		$category_shifting_app_arr['occupation_block']  =   trim($form_state['values']['cs_occupation_block']);
		$category_shifting_app_arr['occupation_flat']  =   trim($form_state['values']['cs_occupation_flat']);
		$category_shifting_app_arr['possession_date']  =   trim( implode('-', array_reverse(explode('/', $form_state['values']['cs_possession_date']))));
		
		if($form_state['values']['cs_file_licence'] != 0) {
			$file_licence = file_load($form_state['values']['cs_file_licence']);
			if($file_licence->status==0) {
				$file_licence->status = FILE_STATUS_PERMANENT;
				file_save($file_licence);
				file_usage_add($file_licence, 'shifting_of_category', 'Current Licence', $user->uid);
				$category_shifting_app_arr['file_licence']  =  $file_licence->fid;	
			}
		}


		if($form_state['values']['cs_scanned_sign'] != 0) {
			$scanned_sign = file_load($form_state['values']['cs_scanned_sign']);
			if($scanned_sign->status==0) {
				$file_licence->status = FILE_STATUS_PERMANENT;
				file_save($scanned_sign);
				file_usage_add($scanned_sign, 'shifting_of_category', 'CS Scanned Sign', $user->uid);
				$category_shifting_app_arr['scanned_sign']  =  $scanned_sign->fid;	
			}
		}
		// print_r($category_shifting_app_arr);die;
		if($online_application_id != 0) {
			db_insert('housing_cs_application')
			->fields($category_shifting_app_arr)
			->execute();
		}
		
	}
	
	function update_category_shifting_application($form, &$form_state, $online_application_id) {
		global $user;
		
		$query1 = db_select('housing_pay_band', 'hpb');
		$query1->fields('hpb', array('flat_type_id'));
		$query1->condition('hpb.pay_band_id', $form_state['values']['pay_band'], '=');
		$result1 = $query1->execute();
		$data1 = $result1->fetchObject();
		
		/*add data in housing_cs_application*/
		$category_shifting_app_arr = array();
		//$vertical_shifting_app_arr['']  =   trim($form['allotment_info']['allotment_no']['#value']);
		//$vertical_shifting_app_arr['possession_date']  =   trim( implode('-', array_reverse(explode('/', $form['current_occupation']['possession_date']['#value']))));
		$category_shifting_app_arr['flat_type_id']  =  $data1->flat_type_id;
		$category_shifting_app_arr['occupation_estate']  =   trim($form_state['values']['cs_occupation_estate']);
		$category_shifting_app_arr['occupation_block']  =   trim($form_state['values']['cs_occupation_block']);
		$category_shifting_app_arr['occupation_flat']  =   trim($form_state['values']['cs_occupation_flat']);
		$category_shifting_app_arr['possession_date']  =   trim( implode('-', array_reverse(explode('/', $form_state['values']['cs_possession_date']))));
		if($form_state['values']['cs_file_licence'] == 0 ){
				
			$file_licence = file_load($form_state['values']['cs_file_licence']) ;
        	if($file_licence) {
				// When a module is managing a file, it must manage the usage count.
				// Here we decrement the usage count with file_usage_delete().
				file_usage_delete($file_licence, 'shifting_of_category', 'Current Licence', $user->uid);
	
				// The file_delete() function takes a file object and checks to see if
				// the file is being used by any other modules. If it is the delete
				// operation is cancelled, otherwise the file is deleted.
				file_delete($file_licence);
        	}
				
		}
		if($form['current_occupation_cs']['cs_file_licence']['#value']['fid'] != 0 ) {
			$file_licence = file_load($form['current_occupation_cs']['cs_file_licence']['#value']['fid']);
			if($file_licence->status==0) {
			//code for old uploaded file delete
				$query = db_select('file_managed', 'fm');
				$query->innerJoin('file_usage', 'fu', 'fm.fid = fu.fid');
				$query->fields('fm');
				$query->fields('fu');
				$query->addField('fm', 'fid', 'file_id');
				$db_and = db_and();
				$db_and->condition('uid', $user->uid, '=');
				$db_and->condition('module', 'shifting_of_category', '=');
				$query->condition($db_and);
				$query->orderBy('fm.fid', 'ASC');
				$result = $query->execute();
				while($data = $result->fetchObject()) {
					//$filename = substr($data->uri, 13);
					/*echo '<pre>';
					print_r($filename);*/
					
					$file1 = file_load($data->file_id);
					file_usage_delete($file1, 'shifting_of_category', 'Current Licence', $user->uid);
    				file_delete($file1);
				}
				//exit;
			//code end
			
			//code for filename change
				/*$path_parts = pathinfo($file_licence->filename);
				$file_licence->filename = 'current_licence_doc_'.$user->uid.'_'.time().'.'.$path_parts['extension'];*/
			//code end
				$file_licence->status = FILE_STATUS_PERMANENT;
				file_save($file_licence);
				file_usage_add($file_licence, 'shifting_of_category', 'Current Licence', $user->uid);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file->fid));
				$category_shifting_app_arr['file_licence']  =  $file_licence->fid;
			}
		}
		
		if($online_application_id != 0) {
			db_update('housing_cs_application')
			->fields($category_shifting_app_arr)
			->condition('online_application_id', $online_application_id, '=')
			->execute();
		}
	}