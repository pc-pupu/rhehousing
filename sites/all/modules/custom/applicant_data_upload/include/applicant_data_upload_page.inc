<?php

	function applicant_data_upload_form($form, &$form_state) {
		
		$form['applicant_data_excel_file'] = array(
			'#title' => t('Upload Applicant Excel Data'),
			'#type' => 'managed_file',
			'#description' => t('Allowed extensions: xls xlsx'),
			'#progress_message' => t('Please wait...'),
			'#progress_indicator' => 'bar',
			'#default_value' => variable_get('Upload File', ''),
			'#upload_validators' => array(
										 'file_validate_extensions' => array("xls xlsx"),
										// 'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
			
										 ),
			'#upload_location' => 'public://excel_data_file/',
			'#required' => TRUE,
			'#process' => array('applicant_data_upload_element_process'),
		);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_applicant_data_upload_form()');
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Upload Excel File'),
		);
		
		return $form;
		
		
		if(isset($form) > 0 && $form['applicant_data_excel_file']["#type"] == "managed_file") {
			$form['applicant_data_excel_file']["#upload_validators"]["file_upload_validation"] = array($form['applicant_data_excel_file']["#upload_validators"]["file_validate_extensions"][0]);
		}
		
	}
	
	function applicant_data_upload_element_process($element, &$form_state, $form) {
		$element = file_managed_file_process($element, $form_state, $form);
		$element['upload_button']['#access'] = FALSE;
		return $element;
	}
	
	function applicant_data_upload_form_validate($form, &$form_state) {
			
	}
	
	function applicant_data_upload_form_submit($form, &$form_state) {
		
		if($form_state['values']['applicant_data_excel_file'] != 0){
			// file exists
			
			$excel_file = file_load($form_state['values']['applicant_data_excel_file']);			
			
			if($excel_file->status == 0){
				$excel_file->status = FILE_STATUS_PERMANENT;
				file_save($excel_file);
				file_usage_add($excel_file, 'applicant_data_upload', 'upload_document', 1);
				//unset($form_state['values']['applicant_data_excel_file']);
			}
			
			$fileuri = substr($excel_file -> uri, 9);
			$fileuri_arr = explode('/', $fileuri);
			$filename = $fileuri_arr[1];
			$fileroot = DRUPAL_ROOT . '/sites/default/files/excel_data_file/' . $filename;	
			
			$all_applicant = read_excel($filename, $fileroot);
			file_delete($excel_file, TRUE);			
			
			$i = 0;
			
			foreach($all_applicant as $key => $applicant) {
				$applicant = array_filter($applicant);
				if(count($applicant) > 0) {
					
					/*$UNIX_DATE = ($applicant[2] - 25569) * 86400;
					$applicant[2] = gmdate("Y-m-d", $UNIX_DATE);
					$dob = gmdate("Y-m-d", $UNIX_DATE);*/
					$applicant[2] = date_format(date_create(trim($applicant[2])), 'Y-m-d');
					$applicant[8] = date_format(date_create(trim($applicant[8])), 'Y-m-d');
					$applicant[14] = date_format(date_create(trim($applicant[14])), 'Y-m-d');
					
					
					$applicant_name = trim($applicant[0]);
					$applicant_father_name = trim($applicant[1]);
					$dob = date_format(date_create(trim($applicant[2])), 'Y-m-d');
					$gender = trim($applicant[3]);
					
					$app_designation = trim($applicant[4]);
					$pay_band = trim($applicant[5]);
					$pay_in = trim($applicant[6]);
					$app_posting_place = trim($applicant[7]);
					$dor = date_format(date_create(trim($applicant[8])), 'Y-m-d');
					
					$office_name = trim($applicant[9]);
					$office_street = trim($applicant[10]);
					$office_city = trim($applicant[11]);
					$office_pincode = trim($applicant[12]);
					
					$ddo_id = trim($applicant[13]);
					
					
					$doa = date_format(date_create(trim($applicant[14])), 'Y-m-d');
					$computer_serial_no = trim($applicant[15]);
					$remarks = trim($applicant[16]);
					$rhe_flat_type = trim($applicant[17]);
					$reason = trim($applicant[18]);			
					
					/*echo '<pre>';
					print_r($applicant);
					echo '<br>';*/
					
					//applicant data insert code
					
					$word_c = str_word_count($applicant_name);
					$splitter = " ";
					$pieces = explode($splitter, $applicant_name);
					
					if($word_c < 2) {
						$name = strtolower(substr($pieces[0], 0, 3));
					}
					else if($word_c == 2) {
						if($pieces[0] == 'Dr.' || $pieces[0] == 'Dr' || $pieces[0] == 'dr.' || $pieces[0] == 'dr' || $pieces[0] == 'DR.' || $pieces[0] == 'DR') {
							$name = strtolower(substr($pieces[1], 0, 3));
						}
						else {
							$name = strtolower(substr($pieces[0], 0, 3)).strtolower(substr($pieces[1], 0, 3));
						}
					}
					else {
						if($pieces[0] == 'Dr.' || $pieces[0] == 'Dr' || $pieces[0] == 'dr.' || $pieces[0] == 'dr' || $pieces[0] == 'DR.' || $pieces[0] == 'DR') {
							$name = strtolower(substr($pieces[1], 0, 3)).strtolower(substr($pieces[2], 0, 3));
						}
						else {
							$name = strtolower(substr($pieces[0], 0, 3)).strtolower(substr($pieces[1], 0, 3));
						}
					}
					
					$username = str_replace(".","",$name).rand(1, 100000);
					
					/*insert into user table*/
					$newUser	   	   = array();
					$newUser['name']   = $username;
					$newUser['pass']   = $username;
					/*$str[0].$str[1].trim($form_state['values']['username']).'@'.$dob_t.strrev($str1[0].$str1[1]);*/																																																						
					//$newUser['mail']   = '';
					$newUser['status'] = 1;
					
					user_save(null, $newUser);
					
					/*get last inserted uid*/
					
					$query = db_select('users','u');
					$query->addExpression('MAX(uid)','max_uid');
					$result = $query->execute();
					$data = $result->fetchObject();
					
					/*insert into housing_applicant table*/
					
					$user_reg_arr = array();
					$user_reg_arr['uid'] 				=  $data->max_uid;
					$user_reg_arr['applicant_name'] 	=  $applicant_name;
					$user_reg_arr['guardian_name'] 		=  $applicant_father_name;
					$user_reg_arr['date_of_birth'] 		=  $dob;
					$user_reg_arr['gender'] 			=  $gender;
					
					//$user_reg_arr['mobile_no'] 			=  '';
					
					
					db_insert('housing_applicant')
					->fields($user_reg_arr)
					->execute();
					
					/*assign user roles*/
					
					$arr_user_roles = array();
					$arr_user_roles['uid'] = $user_reg_arr['uid'];
					$arr_user_roles['rid'] = 4;
					
					db_insert('users_roles')
					->fields($arr_user_roles)
					->execute();
					
					
					/*add applicant_official_detail  data*/
					$app_off_detail_arr = array();
					$app_off_detail_arr['uid']  =  $data->max_uid;
					$app_off_detail_arr['applicant_designation']  =  $app_designation;
					$app_off_detail_arr['pay_band_id']  =  $pay_band;
					$app_off_detail_arr['pay_in_the_pay_band']  =  $pay_in;
					
					//$app_off_detail_arr['grade_pay']  =  '';
					//$app_off_detail_arr['gpf_no']  =  '';
					
					$app_off_detail_arr['applicant_posting_place']  =  $app_posting_place;

					//$app_off_detail_arr['applicant_headquarter']  =  '';
					//$app_off_detail_arr['date_of_joining']  =  '';
						
					$app_off_detail_arr['date_of_retirement']  =  $dor;
					$app_off_detail_arr['office_name']  =  $office_name;
					$app_off_detail_arr['office_street']  =  $office_street;
					$app_off_detail_arr['office_city_town_village']  =  $office_city;
					
					//$app_off_detail_arr['office_post_office']  =  '';
						
					$app_off_detail_arr['office_pin_code']  =  $office_pincode;
					$app_off_detail_arr['ddo_id']  =  $ddo_id;
					
					db_insert('housing_applicant_official_detail')
					->fields($app_off_detail_arr)
					->execute();
					
					/*fetching applicant_official_detail_id*/
					$query1 = db_select('housing_applicant_official_detail', 'haod');
					$query1->addExpression('MAX(applicant_official_detail_id)','id');
					$query1->condition('haod.uid', $data->max_uid, '=');
					$result1 =$query1->execute();
					$data1 = $result1->fetchObject();
					
					/*add online application*/
		
					$online_app_arr = array();
					$online_app_arr['applicant_official_detail_id']  =  $data1->id;
					$online_app_arr['status']  =  'verified';
					$online_app_arr['date_of_application']  =  $doa;
					$online_app_arr['is_backlog_applicant']  =  1;
					$online_app_arr['computer_serial_no']  =  $computer_serial_no;
					
					if($remarks != '')
						$online_app_arr['remarks'] = $remarks;
							
							
					db_insert('housing_online_application')
					->fields($online_app_arr)
					->execute();
					
					/*fetching online_application_id*/
					$query2 = db_select('housing_online_application', 'hoa');
					$query2->addExpression('MAX(online_application_id)','oid');
					$query2->condition('hoa.applicant_official_detail_id', $data1->id, '=');
					$result2 =$query2->execute();
					$data2 = $result2->fetchObject();
					
					$online_app_arr_upd = array();
					$online_app_arr_upd['application_no']  = 'NA-'.implode(array_reverse(explode('-', $doa))).'-'.$data2->oid;
					// echo 	$online_app_arr_upd['application_no'];die;
					db_update('housing_online_application')
					->fields($online_app_arr_upd)
					->condition('online_application_id', $data2->oid)
					->execute();
					
					/* add new alltment application*/  
					$new_allotment_app_arr = array();
					$new_allotment_app_arr['online_application_id']  =  $data2->oid;
					
					$new_allotment_app_arr['flat_type_id'] = fetch_rhe_flat_id($rhe_flat_type);
					$new_allotment_app_arr['allotment_category']  =  $reason;
					
					db_insert('housing_new_allotment_application')
					->fields($new_allotment_app_arr)
					->execute();
					
					$i++;
		
				}
			}
			
			drupal_set_message($i.' no of Data inserted successfully.');
		}
	}