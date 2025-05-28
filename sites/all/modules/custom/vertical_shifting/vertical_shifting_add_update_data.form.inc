<?php

	function add_vertical_shifting_application($form, &$form_state, $online_application_id) {
		global $user;
		
		$query = db_select('housing_pay_band', 'hpb');
		$query->fields('hpb', array('flat_type_id'));
		$query->condition('hpb.pay_band_id', $form_state['values']['pay_band'], '=');
		$result = $query->execute();
		$data = $result->fetchObject();
		
		/*add data in housing_vs_application*/
		$vertical_shifting_app_arr = array();
		$vertical_shifting_app_arr['online_application_id']  =  $online_application_id;
		$vertical_shifting_app_arr['flat_type_id']  =  $data->flat_type_id;
		$vertical_shifting_app_arr['occupation_estate']  =   trim($form_state['values']['occupation_estate']);
		$vertical_shifting_app_arr['occupation_block']  =   trim($form_state['values']['occupation_block']);
		$vertical_shifting_app_arr['occupation_flat']  =   trim($form_state['values']['occupation_flat']);
		$vertical_shifting_app_arr['possession_date']  =   trim( implode('-', array_reverse(explode('/', $form_state['values']['possession_date']))));
		
		if($form_state['values']['file_licence'] != 0) {
			$file_licence = file_load($form_state['values']['file_licence']);
			if($file_licence->status==0) {
				$file_licence->status = FILE_STATUS_PERMANENT;
				file_save($file_licence);
				file_usage_add($file_licence, 'vertical_shifting', 'Current Licence', $user->uid);
				$vertical_shifting_app_arr['file_licence']  =  $file_licence->fid;	
			}
		}

		if($form_state['values']['vs_scanned_sign'] != 0) {
			$scanned_sign = file_load($form_state['values']['vs_scanned_sign']);
			if($scanned_sign->status==0) {
				$file_licence->status = FILE_STATUS_PERMANENT;
				file_save($scanned_sign);
				file_usage_add($scanned_sign, 'vertical_shifting', 'VS Scanned Sign', $user->uid);
				$vertical_shifting_app_arr['scanned_sign']  =  $scanned_sign->fid;	
			}
		}
		
		if($online_application_id != 0) {
			db_insert('housing_vs_application')
			->fields($vertical_shifting_app_arr)
			->execute();
		}
		
	}
	
	function update_vertical_shifting_application($form, &$form_state, $online_application_id) {
		global $user;
		
		$query1 = db_select('housing_pay_band', 'hpb');
		$query1->fields('hpb', array('flat_type_id'));
		$query1->condition('hpb.pay_band_id', $form_state['values']['pay_band'], '=');
		$result1 = $query1->execute();
		$data1 = $result1->fetchObject();
		
		/*add data in housing_vs_application*/
		$vertical_shifting_app_arr = array();
		//$vertical_shifting_app_arr['']  =   trim($form['allotment_info']['allotment_no']['#value']);
		//$vertical_shifting_app_arr['possession_date']  =   trim( implode('-', array_reverse(explode('/', $form['current_occupation']['possession_date']['#value']))));
		$vertical_shifting_app_arr['flat_type_id']  =  $data1->flat_type_id;
		$vertical_shifting_app_arr['occupation_estate']  =   trim($form_state['values']['occupation_estate']);
		$vertical_shifting_app_arr['occupation_block']  =   trim($form_state['values']['occupation_block']);
		$vertical_shifting_app_arr['occupation_flat']  =   trim($form_state['values']['occupation_flat']);
		$vertical_shifting_app_arr['possession_date']  =   trim( implode('-', array_reverse(explode('/', $form_state['values']['possession_date']))));
		if($form_state['values']['file_licence'] == 0 ){
				
			$file_licence = file_load($form_state['values']['file_licence']) ;
        	if($file_licence) {
				// When a module is managing a file, it must manage the usage count.
				// Here we decrement the usage count with file_usage_delete().
				file_usage_delete($file_licence, 'vertical_shifting', 'Current Licence', $user->uid);
	
				// The file_delete() function takes a file object and checks to see if
				// the file is being used by any other modules. If it is the delete
				// operation is cancelled, otherwise the file is deleted.
				file_delete($file_licence);
        	}
				
		}
		if($form['current_occupation']['file_licence']['#value']['fid'] != 0 ) {
			$file_licence = file_load($form['current_occupation']['file_licence']['#value']['fid']);
			if($file_licence->status==0) {
			//code for old uploaded file delete
				$query = db_select('file_managed', 'fm');
				$query->innerJoin('file_usage', 'fu', 'fm.fid = fu.fid');
				$query->fields('fm');
				$query->fields('fu');
				$query->addField('fm', 'fid', 'file_id');
				$db_and = db_and();
				$db_and->condition('uid', $user->uid, '=');
				$db_and->condition('module', 'vertical_shifting', '=');
				$query->condition($db_and);
				$query->orderBy('fm.fid', 'ASC');
				$result = $query->execute();
				while($data = $result->fetchObject()) {
					//$filename = substr($data->uri, 13);
					/*echo '<pre>';
					print_r($filename);*/
					
					$file1 = file_load($data->file_id);
					file_usage_delete($file1, 'vertical_shifting', 'Current Licence', $user->uid);
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
				file_usage_add($file_licence, 'vertical_shifting', 'Current Licence', $user->uid);
				//$upd_fields = array_merge($upd_fields, array('fid'=>$file->fid));
				$vertical_shifting_app_arr['file_licence']  =  $file_licence->fid;
			}
		}
		// echo $online_application_id.'<br>'.print_r($vertical_shifting_app_arr);die;
		if($online_application_id != 0) {
			db_update('housing_vs_application')
			->fields($vertical_shifting_app_arr)
			->condition('online_application_id', $online_application_id, '=')
			->execute();
		}
	}