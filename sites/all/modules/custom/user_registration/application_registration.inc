<?php

	function application_registration($usrid = '') {
		$output = '';
		$uid = decrypt_url($usrid);
		
		if(is_numeric($uid)) {
		
			$query1 = db_select('users', 'u');
			$query1->addField('u', 'uid');
			$query1->condition('u.uid', $uid, '=');
			$result1 = $query1->execute();
			
			if($result1->rowcount() > 0){
				
				$query = db_select('users', 'u');
				$query->innerJoin('housing_applicant', 'ha', 'ha.uid = u.uid');
				$query->addField('u', 'mail');
				$query->addField('ha', 'applicant_name');
				$query->addField('ha', 'gender');
				$query->addField('ha', 'mobile_no');
				$query->addField('ha', 'date_of_birth');
				$query->condition('u.uid', $uid, '=');
				$result = $query->execute();
				
				if($result->rowcount() > 0){
					$data = $result->fetchObject();
					/*$output = trim($data->applicant_name).'<br>'.trim( implode('/', array_reverse(explode('-', $data->date_of_birth)))).'<br>'.trim($data->gender).'<br>'.trim($data->mobile_no).'<br>'.trim($data->mail).'<br><br>'.
					l('<img height="18" width="18" src="'.file_create_url(drupal_get_path('module', 'user_registration') .  
					'/images/pdf_icon.png').'" title="Download Application of Registration" alt="PDF Icon">Download Application of 
					Registration', 'application_of_registration_pdf/'.$usrid.'/application_of_registration_'.time(), array(
					'html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 
					400;text-decoration: none; font-size:14px')));*/
					if(trim($data->gender) == 'M')
						$gender = 'Male';
					elseif(trim($data->gender) == 'F')
						$gender = 'Female';
					
					$output = 'REGISTRATION ID - '.trim($uid).
					'<br>NAME - '.trim($data->applicant_name).
					'<br> DATE OF BIRTH - '.trim( implode('/', array_reverse(explode('-', $data->date_of_birth)))).
					'<br> GENDER - '.$gender.
					'<br> MOBILE NO. - '.trim($data->mobile_no).
					'<br> EMAIL ID - '.trim($data->mail).'<br><br>';
					
					$filename = str_replace(' ', '', $data->applicant_name).'_'.decrypt_url(trim($usrid));
					
					return $output.l('<img height="18" width="18" src="'.file_create_url(drupal_get_path('module', 'user_registration') .  
					'/images/pdf_icon.png').'" title="Download Application of Registration" alt="PDF Icon">Download Application of 
					Registration', 'application_of_registration_pdf/'.$usrid.'/'.$filename, array(
					'html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 
					400;text-decoration: none; font-size:14px')));
				}
				else {
					return $output;
				}
			}
			else {
				return $output;
			}
		}
		else {
			return $output;	
		}
	}