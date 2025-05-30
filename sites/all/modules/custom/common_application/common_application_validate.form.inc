<?php

	
	
	function element_validate_numeric_positive($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[1-9][0-9]*$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be positive numeric.', array('%name' => $element['#title'])));
		}
	}
	
	function element_validate_alphabatic_text($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[a-zA-Z0-9][\.\-\/\,\w\s]+[a-zA-Z0-9]*$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphabatic.', array('%name' => $element['#title'])));
		}
	}
	
	function element_validate_alphabatic_fullstop($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[A-Z]+[a-zA-Z\s\.]*$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphabatic.', array('%name' => $element['#title'])));
		}
	}
	
	function element_validate_hyphenfullstop($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[a-z A-Z 0-9]+[\.\-\w\s]*[a-z A-Z 0-9]$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphabetic. Only special characters . - allowed.', array('%name' => $element['#title'])));
		}
	}
	
	function element_validate_hyphenFullStopAmpersand($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[a-z A-Z]+[\.\-\&\,\w\s]*[a-z A-Z 0-9 \.]$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphabetic. Only special characters . - & allowed.', array('%name' => $element['#title'])));
		}
	}
	
	function element_validate_streetaddress($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[a-zA-Z0-9][\.\-\/\,\w\s]+[a-zA-Z0-9]*$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphanumeric. Only special characters . , - / allowed.', array('%name' => $element['#title'])));
		}
	}
	
	function element_validate_allotmentno($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[a-zA-Z0-9][\-\w]+[0-9]*$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphnumeric. Only special characters - allowed.', array('%name' => $element['#title'])));
		}
	}
	
	function element_validate_email($element, &$form_state) {
		$value = strtolower(trim($element['#value']));
		if ($value !== '' && !filter_var($value, FILTER_VALIDATE_EMAIL)) {
			form_set_error($element['#name'], t('" %name " must be valid.', array('%name' => $element['#title'])));
		}
	}
	
	function element_validate_mobile($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/[6789][0-9]{9}/",$value)) {
			form_error($element, t('" %name " must be a valid 10 digits no.', array('%name' => $element['#title'])));
			$form_state['rebuild'] = TRUE;
		}
	}
	
	function element_validate_telephoneno($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/[0-9]+$/",$value)) {
			form_error($element, t('" %name " must be a valid telephone no.', array('%name' => $element['#title'])));
			$form_state['rebuild'] = TRUE;
		}
	}
	
	function element_validate_hrms_id($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/[1-9][0-9]{9}/",$value)) {
			form_error($element, t('" %name " must be a valid 10 digits no.', array('%name' => $element['#title'])));
			$form_state['rebuild'] = TRUE;
		}
	}
	
	function element_validate_date($element, &$form_state) {
		$value = trim($element['#value']);
		
		if($value !== ''){
			$date = DateTime::createFromFormat('d/m/Y', $value);
			$date_errors = DateTime::getLastErrors();
			if($date_errors['warning_count'] + $date_errors['error_count'] > 0) {
				form_set_error($element['#name'], t('" %name " must be DD/MM/YYYY format.', array('%name' => $element['#title'])));
			}
		}
		
		/*if ($value !== '' && !preg_match("/(^(((0[1-9]|1[0-9]|2[0-8])[\/](0[1-9]|1[012]))|((29|30|31)[\/](0[13578]|1[02]))|((29|30)[\/](0[4,6,9]|11)))[\/](19|20)\d\d$)|(^29[\/]02[\/](19|20)(00|04|08|12|16|20|24|28|32|36|40|44|48|52|56|60|64|68|72|76|80|84|88|92|96)$)/",$value)) {
			form_set_error($element['#name'], t('" %name " must be must be DD/MM/YYYY format.', array('%name' => $element['#title'])));
		}*/
	}
	
	function element_validate_age($element, &$form_state) {
		if(!empty($form_state['values']['dob'])) {
		   
			 $dob = trim($form_state['values']['dob']);
			 if(!empty($dob)) {
			 	$date = DateTime::createFromFormat('d/m/Y', $dob);
				$dob= $date->format('Y-m-d');
				if(!validateAge($dob)){
					form_set_error('dob', 'Check Date of Birth. Minimum age should be 18 Years.');
				}
			 }else{
			 	form_set_error('dob', 'Date of Birth Can\'t be empty.');
			 }
		}
	}
	
	function element_validate_joining_age($element, &$form_state) {
		if(!empty($form_state['values']['doj'])) {
			$dob = trim($form_state['values']['dob']);
			$doj = trim($form_state['values']['doj']);
			if(!empty($doj)) {
				$date1 = DateTime::createFromFormat('d/m/Y', $dob);
				$dob = $date1->format('Y-m-d');
				$date2 = DateTime::createFromFormat('d/m/Y', $doj);
				$doj = $date2->format('Y-m-d');
				
				$d1 = new DateTime($dob);
				$d2 = new DateTime($doj);
				
				$diff = $d2->diff($d1);
				
				if($diff->y < 18) {
					//echo $diff1->y;
					form_set_error('doj', t('Check Date of Joining. Minimum age should be 18 Years for Joining.'));
				}
			}
		}
	}
	
	function element_validate_flat_type($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[a-z A-Z]*[\+]*$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphabatic . Only special character + allowed.', array('%name' => $element['#title'])));
		}
	}
	
	function mobile_no_validate($element, &$form_state) {
		global $user;
		$value = trim($element['#value']);
		
		if($value !== '' && is_numeric($value)) {
		
			$query = db_select('housing_applicant', 'ha');
			$query->fields('ha', array('mobile_no'));
		
			$query->condition('ha.uid', $user->uid, '=');
		
			$result = $query->execute();
			while($data = $result->fetchObject()) {
				if($data->mobile_no != $value) {
			
					$query1 = db_select('housing_applicant','applicant');
					$query1->addExpression('mobile_no','mobile');
					$query1->condition('mobile_no', $value);
					$result1 = $query1->execute();
					
					
					if($result1->rowCount() > 0)
						form_set_error($element['#name'], t('Mobile no "%name" already exist.', array('%name' => $element['#value'])));
				}
			
			}
		}
	}
	
	function hrms_id_validate($element, &$form_state) {
		global $user;
		$value = trim($element['#value']);
		
		if($value !== '' && is_numeric($value)) {
		
			$query = db_select('housing_applicant_official_detail', 'haod');
			$query->fields('haod', array('hrms_id'));
			$query->condition('haod.uid', $user->uid, '=');
		
			$result = $query->execute();
			while($data = $result->fetchObject()) {
				if($data->hrms_id != '') {
					if($data->hrms_id != $value) {
				
						$query1 = db_select('housing_applicant_official_detail', 'haod');
						$query1->fields('haod', array('hrms_id'));
						$query1->condition('hrms_id', $value);
						$result1 = $query1->execute();
						
						
						if($result1->rowCount() > 0)
							form_set_error($element['#name'], t('Employee HRMS ID "%name" already exist.', array('%name' => $element['#value'])));
					}
				}
			}
		}
	}
	
	function email_id_validate($element, &$form_state) {
		global $user;
		$value = strtolower(trim($element['#value']));
		
		$query1 = db_select('users', 'u');
		$query1->fields('u', array('mail'));
	
		$query1->condition('u.uid', $user->uid, '=');
	
		$result1 = $query1->execute();
		while($data = $result1->fetchObject()) {
			if($data->mail != $value) {
				$query = db_select('users','u');
				$query->addExpression('mail','email');
				$query->condition('mail', $value);
				$result = $query->execute();
				
				
				if($result->rowCount() > 0)
					form_set_error($element['#name'], t('Email id "%name" already exist.', array('%name' => $element['#value'])));
			}
		}
		
	}
	
	function gpf_no_validate($element, &$form_state) {
		global $user;
		$value = strtoupper(trim($element['#value']));
		
		if ($value !== '' && !preg_match("/^[A-Z a-z]+[\/][A-Z a-z]+[\/][\d]+$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be ADM/WB/00000 format.', array('%name' => $element['#title'])));
		}
		else {
		
			$query1 = db_select('housing_applicant_official_detail', 'haod');
			$query1->fields('haod', array('gpf_no'));
		
			$query1->condition('haod.uid', $user->uid, '=');
			$query1->orderBy('haod.applicant_official_detail_id', 'ASC');
		
			$result1 = $query1->execute();
			if($result1->rowCount() > 0) {
				while($data = $result1->fetchObject()) {
					if($data->gpf_no != '') {
						if($data->gpf_no != $value) {
							$query = db_select('housing_applicant_official_detail','haod');
							$query->addField('haod', 'gpf_no');
							$query->condition('gpf_no', $value);
							$result =$query->execute();
							
							
							if($result->rowCount() > 0)
								form_set_error($element['#name'], t('GPF no "%name" already exist. Please input your unique GPF No.', array('%name' => $element['#value'])));
						}
					}
				}
			}
			else {
				$query = db_select('housing_applicant_official_detail','haod');
				$query->addField('haod', 'gpf_no');
				$query->condition('gpf_no', $value);
				$result =$query->execute();
				
				
				if($result->rowCount() > 0)
					form_set_error($element['#name'], t('GPF no "%name" already exist. Please input your unique GPF No.', array('%name' => $element['#value'])));	
			}
		}
	}


/*  if ($value !== '') {
	  $arr = explode(' ',$value);
	  $flag = TRUE;
	  foreach($arr as $val){
		  $val = trim($val);
		   if ($val !== '' && !ctype_alpha($val)) {
			   $flag = FALSE;
			   break;
		   }
	  }
	  if(!$flag){
		  form_error($element, t('" %name " must be a alphabatic letter.', array('%name' => $element['#title'])));
	  }
    
  }*/
  
  	function file_upload_validation($file, $res) {
		$errors = array();
		$res_array = explode(" ", $res);
		
		$finfo = finfo_open(FILEINFO_MIME_TYPE);
		$mime = finfo_file($finfo, $file->uri);
		$mime_array = explode("/", $mime);
		// If the detected file extension is not allowed, raise an error.
		if (!in_array($mime_array[1], $res_array)) {
			$errors[] = t("There was a problem with this file's extension.");
		}
		finfo_close($finfo);
		return $errors;
	}
	
	
	function element_validate_textarea($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[\w][-\/()\[\]\{\}\.\,\&\’\'\"\w\s]+$/",$value)) {
			form_error($element, t('%name must be alphabetic. Use proper special characters.', array('%name' => $element['#title'])));
			$form_state['rebuild'] = TRUE;
		}
	}
	function element_validate_alphanumeric($element, &$form_state) {
		$value = trim($element['#value']);
		if ($value !== '' && !preg_match("/^[\w]+$/",$value)) {
			form_error($element, t('%name must be alphnumeric.', array('%name' => $element['#title'])));
			$form_state['rebuild'] = TRUE;
		}
	}
	