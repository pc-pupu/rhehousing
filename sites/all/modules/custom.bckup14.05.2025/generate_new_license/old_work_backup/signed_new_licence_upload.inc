<?php

	function signed_new_licence_upload($form, &$form_state, $occupant_license_id, $license_no) {
		$occupant_license_id = decrypt_url($occupant_license_id);
		$license_no = decrypt_url($license_no);
		
		$result = licence_type($occupant_license_id);
		$data = $result->fetchObject();
		
		if($data->type_of_application == 'new') {
			$licence_type = 'New Licence';			
		}
		
		if($data->uploaded_licence == '') {
			$form['occupant_license_id'] = array(
				'#type' => 'hidden',
				'#default_value' => $occupant_license_id,
			);
			
			$form['licence_no'] = array(
				'#title' => t('Licence No.'),
				'#type' => 'textfield',
				//'#attributes' => array('readonly' => 'readonly'),
				//or
				'#attributes' => array('disabled' => 'disabled'),
				'#prefix' => '<div class="two"">',
				'#suffix' => '</div>',
				'#value' => $license_no,
			);
			
			$form['licence_type'] = array(
				'#title' => t('Licence Type'),
				'#type' => 'textfield',
				'#prefix' => '<div class="two">',
				'#suffix' => '</div>',
				'#attributes' => array('disabled' => "disabled"),
				'#value' => $licence_type,
			);
			
			$form['signed_licence_file'] = array(
				'#title' => t('Upload Signed Licence'),
				'#type' => 'managed_file',
				'#description' => t('<b>Allowed Extension: pdf<br>Maximum File Size: 1 MB</b>'),
				'#progress_message' => t('Please wait...'),
				'#progress_indicator' => 'bar',
				'#default_value' => variable_get('Upload File', ''),
				'#upload_validators' => array(
											 'file_validate_extensions' => array("pdf"),
											 //'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
				
										),
				'#upload_location' => 'public://signed_licence/',
				'#required' => TRUE,
				'#process' => array('signed_new_licence_upload_element_process'),
			);
			
			$form['submit'] = array(
				'#type' => 'submit',
				'#value' => t('Upload Signed Licence'),
			);
			
			return $form;
			
			
			if(isset($form) > 0 && $form['signed_licence_file']["#type"] == "managed_file") {
				$form['signed_licence_file']["#upload_validators"]["file_upload_validation"] = array($form['signed_licence_file']["#upload_validators"]["file_validate_extensions"][0]);
			}
		} else {
			drupal_goto('generate_new_license');	
		}
	
	}
	
	function signed_new_licence_upload_element_process($element, &$form_state, $form) {
		$element = file_managed_file_process($element, $form_state, $form);
		$element['upload_button']['#access'] = FALSE;
		//$element['remove_button']['#access'] = FALSE;
		return $element;
	}
	
	function signed_new_licence_upload_validate($form, &$form_state) {
		//$fid = $form_state['values']['application_form_file'];
		
		//digital sign checking
		/*$chk = isStringInFile($fid, 'adbe.pkcs7.detached');
		if($chk != 1)
		{
			form_set_error('', 'PDF selected for Upload is not digitally signed!!! Please remove and upload again!!!');
		}*/	
		
		$file_licence = file_load($form['signed_licence_file']['#value']['fid']);
		
		if($file_licence->filesize > 1048576) {
			form_set_error('file_licence_size', 'The file '.$file_licence->filename.' could not be uploaded, because it exceeds 1 MB, the maximum allowed size for uploads.');	
		}	
	}
	
	function signed_new_licence_upload_submit($form, &$form_state) {
		$signed_licence_arr = array();
		
		$occupant_license_id = $form_state['values']['occupant_license_id'];
		$result1 = licence_type($occupant_license_id);
		$data1 = $result1->fetchObject();
		
		if($form['signed_licence_file']['#value']['fid'] != 0 ) {
			$file_licence = file_load($form['signed_licence_file']['#value']['fid']);
			if($file_licence->status==0) {
				
			//code for old uploaded file delete
				$query = db_select('file_managed', 'fm');
				$query->addField('fm', 'fid');
				$db_and = db_and();
				$db_and->condition('uid', $data1->uid, '=');
				$db_and->condition('status', 0, '=');
				$db_and->condition('fid', $file_licence->fid, '!=');
				$query->condition($db_and);
				$result = $query->execute();
				if($result->rowCount() > 0) {
					while($data = $result->fetchObject()) {
						$file_licence1 = file_load($data->fid);
						file_delete($file_licence1);
					}
				}
			//code end
				
				$file_licence->status = FILE_STATUS_PERMANENT;
				file_save($file_licence);
				file_usage_add($file_licence, 'generate_new_license', 'Signed New Licence Upload', $data1->uid);
				
				$signed_licence_arr['uploaded_licence'] = $file_licence->fid;
			}
		}
		
		if($occupant_license_id != 0) {
			db_update('housing_occupant_license')
			->fields($signed_licence_arr)
			->condition('occupant_license_id', $occupant_license_id, '=')
			->execute();
		}
		
		drupal_set_message('Signed New Licence Uploaded Successfully.');
		drupal_goto('generate_new_license');
	}