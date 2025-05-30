<?php
	function update_password_form($form, &$form_state) {
		
		$form['submit'] = array(
			'#value' => t('Update Password'),
			'#type' => 'submit',
		);
		
		return $form;
	}
  
	function update_password_form_validate($form, &$form_state) {
		
	}
    
	function update_password_form_submit($form, &$form_state) { 
	
		//$i = 1;
		/*echo "<pre>";
		print_r($i.'	'.$data->uid.'	'.$data->name);
		$i++;*/
		//die(); 
	  
		/*$result = db_query("select * from users where uid between 176 and 1184 order by uid");
		
		if($result->rowCount() >0) {
			
			while($data = $result->fetchObject()) {
				
				$hashthepass = $data->name;
				
				require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
    			$hashthepass = user_hash_password(trim($hashthepass));
				
				if(!$hashthepass) {
				  return FALSE;
				}
				else {
				  db_update('users')
					->fields(array('pass' => $hashthepass))
					->condition('uid', $data->uid)       
					->execute();
				}
				
			}
			drupal_set_message($result->rowCount().' No of rows Updated successfully.');
		}*/
		
	}