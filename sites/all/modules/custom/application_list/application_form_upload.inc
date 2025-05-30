<?php

	function application_form_upload($form, &$form_state, $online_application_id) {
		$online_application_id = decrypt_url($online_application_id);
		
		$returns = check_application_entity(0,$online_application_id);
		$entityList = $returns[0];
		$application_type = 'Application for '.$entityList['type'];
		
		$result = fetch_application_detail($online_application_id);
		$data = $result->fetchObject();
		
		if($data->uploaded_app_form == '') {
			$form['online_application_id'] = array(
				'#type' => 'hidden',
				'#default_value' => $online_application_id,
			);
			$form['app_type'] = array(
				'#type' => 'hidden',
				'#default_value' => $entityList['type'],
			);
			
			$form['application_type'] = array(
				'#title' => t('Application Type'),
				'#type' => 'textfield',
				'#prefix' => '<div class="two">',
				'#suffix' => '</div>',
				'#attributes' => array('disabled' => "disabled"),
				'#value' => $application_type,
			);
			$form['application_no'] = array(
				'#title' => t('Application No.'),
				'#type' => 'textfield',
				//'#attributes' => array('readonly' => 'readonly'),
				//or
				'#attributes' => array('disabled' => 'disabled'),
				'#prefix' => '<div class="two"">',
				'#suffix' => '</div>',
				'#value' => $data->application_no,
			);
			$form['application_form_file'] = array(
				'#title' => t('Upload Signed Application Form'),
				'#type' => 'managed_file',
				'#description' => t('<b>Allowed Extension: pdf<br>Maximum File Size: 1 MB</b>'),
				'#progress_message' => t('Please wait...'),
				'#progress_indicator' => 'bar',
				'#default_value' => variable_get('Upload File', ''),
				'#upload_validators' => array(
											 'file_validate_extensions' => array("pdf"),
											 //'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
				
										),
				'#upload_location' => 'public://signed_doc/',
				'#required' => TRUE,
				'#process' => array('application_form_upload_element_process'),
			);
			
			$form['submit'] = array(
				'#type' => 'submit',
				'#value' => t('Upload Application Form'),
			);
			
			return $form;
			
			
			if(isset($form) > 0 && $form['application_form_file']["#type"] == "managed_file") {
				$form['application_form_file']["#upload_validators"]["file_upload_validation"] = array($form['application_form_file']["#upload_validators"]["file_validate_extensions"][0]);
			}
		} else {
			drupal_goto('application-list');	
		}
	}
	
	function application_form_upload_element_process($element, &$form_state, $form) {
		$element = file_managed_file_process($element, $form_state, $form);
		$element['upload_button']['#access'] = FALSE;
		//$element['remove_button']['#access'] = FALSE;
		return $element;
	}
	
	function application_form_upload_validate($form, &$form_state) {
		//$fid = $form_state['values']['application_form_file'];
		
		//digital sign checking
		/*$chk = isStringInFile($fid, 'adbe.pkcs7.detached');
		if($chk != 1)
		{
			form_set_error('', 'PDF selected for Upload is not digitally signed!!! Please remove and upload again!!!');
		}*/	
		
		$file_app_form = file_load($form['application_form_file']['#value']['fid']);
		
		if($file_app_form->filesize > 1048576) {
			form_set_error('app_form_size', 'The file '.$file_app_form->filename.' could not be uploaded, because it exceeds 1 MB, the maximum allowed size for uploads.');	
		}	
	}
	
	function application_form_upload_submit($form, &$form_state) {
		global $user;
		$application_form_arr = array();
		
		$online_application_id = $form_state['values']['online_application_id'];
		$app_type = $form_state['values']['app_type'];
		
		if($form['application_form_file']['#value']['fid'] != 0 ) {
			$file_app_form = file_load($form['application_form_file']['#value']['fid']);
			if($file_app_form->status==0) {
				
			//code for old uploaded file delete
				$query = db_select('file_managed', 'fm');
				$query->addField('fm', 'fid');
				$db_and = db_and();
				$db_and->condition('uid', $user->uid, '=');
				$db_and->condition('status', 0, '=');
				$db_and->condition('fid', $file_app_form->fid, '!=');
				$query->condition($db_and);
				$result = $query->execute();
				if($result->rowCount() > 0) {
					while($data = $result->fetchObject()) {
						$file_app_form1 = file_load($data->fid);
						file_delete($file_app_form1);
					}
				}
			//code end
				
				$file_app_form->status = FILE_STATUS_PERMANENT;
				file_save($file_app_form);
				file_usage_add($file_app_form, 'application_list', $app_type.' Application Form Upload', $user->uid);
				
				$application_form_arr['uploaded_app_form'] = $file_app_form->fid;
			}
		}
		
		if($online_application_id != 0) {
			db_update('housing_online_application')
			->fields($application_form_arr)
			->condition('online_application_id', $online_application_id, '=')
			->execute();
		}
		
		drupal_set_message($app_type.' Application Form uploaded successfully.');
		drupal_goto('application-list');
	}