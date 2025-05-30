<?php

	function validate_rhe_block($element, &$form_state) {
		$block_name = trim($element['#value']);
		
		$value = trim($element['#value']);
	
		if ($value !== '' && !preg_match("/^\w*[\w\/\-]*\w$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphabetic or alphanumeric. Only special characters / and - allowed.', 
										array('%name' => $element['#title'])));
		}
		else {
			if($block_name != '') {
				$query = db_select('housing_block', 'hb');
				$query->addField('hb', 'block_name','block_name');
				$query->condition('hb.block_name', trim($block_name), '=');
				$result = $query->execute();
				if($result->rowcount() > 0){
					form_error($element, t('This " %name " is already exists.', array('%name' => $element['#title'])));
				}
			}
		}
	}
	
	function validate_rhe_block1($element, &$form_state) {
		$block_name = trim($element['#value']);
		
		$value = trim($element['#value']);
	
		if ($value !== '' && !preg_match("/^\w*[\w\/\-]*\w$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphabetic or alphanumeric. Only special characters / and - allowed.', 
										array('%name' => $element['#title'])));
		}
	}
	
	function validate_rhe_flattype($element, &$form_state) {
		$flattype = trim($element['#value']);
		
		$value = trim($element['#value']);
	
		if ($value !== '' && !preg_match("/[A-Z]+[\+]*$/",$value)) {
			form_set_error($element['#name'], t('" %name " must be alphabetic. Only + allowed.', 
										array('%name' => $element['#title'])));
		}
	}
	
function validate_flat_no($element, &$form_state) {
	// echo "<pre>";print_r($form_state['values']);die;
  	$flat_no = trim($element['#value']);
	//$estate_id = trim($form_state['values']['rhe_name']);//10-06-2024
	
	$value = trim($element['#value']);
	if($value !== '' && !preg_match("/^[\w\/\-]+$/",$value)) {
		form_set_error($element['#name'], t('" %name " must be alphnumeric. Only special characters - and / allowed.', array('%name' => $element['#title'])));
	}
	else {
		// if($estate_id != '' && $flat_no != '') {
		if($flat_no != '') {
			$query = db_select('housing_flat', 'hf');
			$query->addField('hf', 'flat_no','flat_no');
			$db_and = db_and();
			$db_and->condition('hf.flat_no', trim($flat_no), '=');
			//$db_and->condition('hf.estate_id', $estate_id, '='); //10-06-2024
			$query->condition($db_and);
			$result = $query->execute();
			if($result->rowcount() > 0){
				form_error($element, t('this " %name " is already exists.', array('%name' => $element['#title'])));
			}
		}
	}
}

function edit_validate_flat_no($element, &$form_state) {
  	$flat_no = trim($element['#value']);
	$flat_id = trim($form_state['values']['flat_id']);
	$estate_id = trim($form_state['values']['rhe_name']);
	
	$value = trim($element['#value']);
	
	if ($value !== '' && !preg_match("/^[\w\/\-]+$/",$value)) {
		form_set_error($element['#name'], t('" %name " must be alphnumeric. Only special characters - and / allowed.', 
									array('%name' => $element['#title'])));
	}
	else {
		if($estate_id != '' && $flat_id != '' && $flat_no != '') {
			$query = db_select('housing_flat', 'hf');
			$query->addField('hf', 'flat_no','flat_no');
			$db_and = db_and();
			$db_and->condition('hf.flat_no', trim($flat_no), '=');
			$db_and->condition('hf.estate_id', $estate_id, '=');
			$db_and->condition('hf.flat_id', $flat_id, '!=');
			$query->condition($db_and);
			$result = $query->execute();
			if($result->rowcount() > 0){
				form_error($element, t('this " %name " is already exists.', array('%name' => $element['#title'])));
			}
		}
	}
}