<?php

	function applicant_regform_upload($form, &$form_state) {
		$uid =  isset($form_state['values']['registration_id']) ? $form_state['values']['registration_id'] : 0;
		
		$query = db_select('users', 'u');
		$query->innerJoin('housing_applicant', 'ha', 'ha.uid = u.uid');
		$query->addField('u', 'mail');
		$query->addField('ha', 'applicant_name');
		$query->addField('ha', 'mobile_no');
		$query->condition('u.uid', $uid, '=');
		$result = $query->execute();
		
		$form['registration_id'] = array(
			'#title' => t('Enter Registration Id'),
			'#type' => 'textfield',
			'#required' => TRUE,
			'#element_validate' => array('element_validate_numeric_positive'),
			'#attributes' => array('class' => array('numeric_positive')),
			'#prefix' => '<div class="two" id="registration_id">',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_load_applicant_details',
				'method' => 'replace',
			),
			'#description' => '',
		);
		
		$form['div_adjust'] = array(
			'#type' => 'hidden',
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
		);
		
		if($uid != 0) {
			if($result->rowCount() > 0) {
				$data = $result->fetchObject();
				$form['applicant_name'] = array(
					'#title' => t('Applicant\'s Name'),
					'#type' => 'textfield',
					'#prefix' => '<div class="two" id="applicant_name">',
					'#suffix' => '</div>',
					//'#required' => TRUE,
					'#attributes' => array('readonly' => "readonly"),
					'#value' => $data->applicant_name,
				);
				$form['applicant_mobileno'] = array(
					'#title' => t('Applicant\'s Mobile No.'),
					'#type' => 'textfield',
					'#prefix' => '<div class="two" id="applicant_mobileno">',
					'#suffix' => '</div>',
					//'#required' => TRUE,
					'#attributes' => array('readonly' => "readonly"),
					'#value' => $data->mobile_no,
				);
			} else {
				$form['registration_id']['#description'] = t('<span style="color:#FF0000"><b>Registration Id not exists. Please insert your Registration Id mentioned in the Applicant Registration Copy.</b></span>');
				
				$form['applicant_name'] = array(
					'#prefix' => '<div class="two" id="applicant_name">',
					'#suffix' => '</div>',
				);	
				$form['applicant_mobileno'] = array(
					'#prefix' => '<div class="two" id="applicant_mobileno">',
					'#suffix' => '</div>',
				);
			}
		} else {
			$form['applicant_name'] = array(
				'#prefix' => '<div class="two" id="applicant_name">',
				'#suffix' => '</div>',
			);	
			$form['applicant_mobileno'] = array(
				'#prefix' => '<div class="two" id="applicant_mobileno">',
				'#suffix' => '</div>',
			);
		}
		
		$form['applicant_regform_file'] = array(
			'#title' => t('Upload Applicant Registration Form'),
			'#type' => 'managed_file',
			'#description' => t('Allowed extensions: pdf'),
			'#progress_message' => t('Please wait...'),
			'#progress_indicator' => 'bar',
			'#default_value' => variable_get('Upload File', ''),
			'#upload_validators' => array(
										 'file_validate_extensions' => array("pdf"),
										// 'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
			
										 ),
			'#upload_location' => 'public://signed_doc/app_regform/',
			'#required' => TRUE,
			'#process' => array('applicant_regform_upload_element_process'),
		);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_applicant_regform_upload()');
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Upload Registration Form'),
		);
		
		return $form;
		
		
		if(isset($form) > 0 && $form['applicant_regform_file']["#type"] == "managed_file") {
			$form['applicant_regform_file']["#upload_validators"]["file_upload_validation"] = array($form['applicant_regform_file']["#upload_validators"]["file_validate_extensions"][0]);
		}
		
	}
	
	function applicant_regform_upload_element_process($element, &$form_state, $form) {
		$element = file_managed_file_process($element, $form_state, $form);
		$element['upload_button']['#access'] = FALSE;
		//$element['remove_button']['#access'] = FALSE;
		return $element;
	}
	
	function applicant_regform_upload_validate($form, &$form_state) {
		$uid =  $form_state['values']['registration_id'];
		$fid = $form_state['values']['applicant_regform_file'];
		
		//registration id checking
		$query = db_select('users', 'u');
		$query->innerJoin('housing_applicant', 'ha', 'ha.uid = u.uid');
		$query->addField('u', 'uid');
		$query->condition('u.uid', $uid, '=');
		$result = $query->execute();
		if($result->rowCount() > 0) {
		//file upload respect to registration id checking
			$query = db_select('users', 'u');
			$query->innerJoin('housing_applicant', 'ha', 'ha.uid = u.uid');
			$query->innerJoin('file_managed', 'fm', 'u.uid = fm.uid');
			$query->innerJoin('file_usage', 'fu', 'fm.fid = fu.fid');
			$query->fields('fm');
			$query->fields('fu');
			$db_and = db_and();
			$db_and->condition('fm.uid', $uid, '=');
			$db_and->condition('module', 'user_registration', '=');
			$db_and->condition('type', 'Applicant User Reg Form', '=');
			$query->condition($db_and);
			$result = $query->execute();
			if($result->rowCount() > 0) {
				form_set_error('', 'Applicant Registration Form of this Registration Id already uploaded. Please check Registration Id you have entered!!!');
			}
		}
		else {
			form_set_error('', 'Registration Id not exists. Please enter your Registration Id mentioned in the Applicant Registration Copy!!!');
		}
		
		
		//digital sign checking
		$chk = isStringInFile($fid, 'adbe.pkcs7.detached');
		if($chk != 1)
		{
			form_set_error('', 'PDF selected for Upload is not digitally signed!!! Please remove and upload again!!!');
		}		
	}
	
	function applicant_regform_upload_submit($form, &$form_state) {
		$uid = $form_state['values']['registration_id'];
		
		if($form['applicant_regform_file']['#value']['fid'] != 0 ) {
			$file_regform = file_load($form['applicant_regform_file']['#value']['fid']);
			if($file_regform->status==0) {
				
			//code for old uploaded file delete
				$query = db_select('file_managed', 'fm');
				$query->addField('fm', 'fid');
				$db_and = db_and();
				$query->condition('uid', 0, '=');
				$query->condition('status', 0, '=');
				$db_and->condition('fid', $file_regform->fid, '!=');
				$query->condition($db_and);
				$result = $query->execute();
				if($result->rowCount() > 0) {
					while($data = $result->fetchObject()) {
						$file_regform1 = file_load($data->fid);
						file_delete($file_regform1);
					}
				}
			//code end
				
				$file_regform->uid = $uid;
				$file_regform->status = FILE_STATUS_PERMANENT;
				file_save($file_regform);
				file_usage_add($file_regform, 'user_registration', 'Applicant User Reg Form', $uid);
			}
		}
		
		drupal_set_message('Applicant Registration Form uploaded successfully.');
	}
	
	
	function _load_applicant_details($form, &$form_state) {
		 $commands = array();
		 
		 $commands[] = ajax_command_replace('#registration_id', drupal_render($form['registration_id']));
		 $commands[] = ajax_command_replace('#applicant_name', drupal_render($form['applicant_name']));
		 $commands[] = ajax_command_replace('#applicant_mobileno', drupal_render($form['applicant_mobileno']));
		 
		 return array('#type' => 'ajax', '#commands' => $commands);
	 
	}