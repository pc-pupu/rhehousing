<?php

function application_status_form($form,&$form_state) {
		
		
		$application_no = isset($form_state['values']['application_no']) && !empty($form_state['values']['application_no']) ? $form_state['values']['application_no'] : '';
		
		
		$form['application_no']=array(
			'#title' => t('Enter Application No.'),
			'#type' => 'textfield',
			'#default_value' => '',
			/*'#attributes' => array('placeholder' => 'Enter application no.'),
			'#required' => TRUE,
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',*/
			'#attributes' => array('placeholder' => 'Enter application no.','class'=>array('form-control form-control-sm')),//sd 20-06-2024
			'#required' => TRUE,
			'#prefix' => '<div class="row"><div class="col-md-8"><div class="form-floating">',//sd 20-06-2024
			'#suffix' => '</div></div>',//sd 20-06-2024
			'#weight' =>2,
			'#element_validate' => array('validate_application_number') // Done by Subham 31-01-2025
		);
		$form['search'] = array(
			'#value' => t('Search'),
			'#type' => 'submit',
			/*'#prefix' => '<div class="two" style="margin-top:43px;height: 30px;">',
			'#suffix' => '</div>',*/
			'#prefix' => '<div class="col-md-4"><div class="form-floating">',//sd 20-06-2024
			'#suffix' => '</div></div></div>',//sd-20-06-2024
			'#attributes'=>array('class'=>array('text-centre btn bg-primary btn-sm px-5 mt-5 rounded-pill text-white fw-bolder')),//sd-20-06-2024
			'#weight' =>3
	  	);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_application_status_form()');
	  
	    if(!empty($application_no)) {
	  		$output = application_stat_page($application_no);
			$form['breadcrumb'] = array(
				'#type' => 'markup',
				'#markup' => $output,
				'#weight' => 5
			);
		}
	  return $form;	
	}
	
	function application_status_form_submit($form, &$form_state) {
		
		$form_state['rebuild'] = TRUE;
		
	}

	function application_stat_page($application_no = '') {
		global $base_path;
		//drupal_add_css('.text-align-r {text-align:right}', 'inline');
		
		$output = '';
		$online_application_id = 0;
		// $result = application_detail_fetch($online_application_id, trim($application_no)); // turned off by debaleena

		//debaleena start 11-06-2024
		$result = fetch_full_application_status(trim($application_no));

		//end
		$rows =array();
		$header = array();
		$fields = array();
		//$header[] = array('data' => 'Application Type');
		//$header[] = array('data' => 'Application No.', 'class' => array('text-align-c'));
		//$header[] = array('data' => 'Date of Application', 'class' => array('text-align-c'));
		$header[] = array('data' => 'Status', 'class' => array('text-align-c'));
		$header[] = array('data' => 'Verification Date', 'class' => array('text-align-c'), 'width'=>'40%');
		//$header[] = array('data' => 'Computer Serial No', 'class' => array('text-align-r'));
		//$header[] = array('data' => 'Combined Waiting No', 'class' => array('text-align-r'));
		//$header[] = array('data' => 'View Details');
	
		//$flat_type_id = 0;
		
		 while($data = $result->fetchObject()) {
			//print_r($data->status_description);die;
			$fields[] = array('data' => $data->status_description, 'class' => array('text-align-c'));
			$fields[] = array('data' => $data->created_at, 'class' => array('text-align-c'));
			 /*if($flat_type_id != $data->flat_type_id){
				$flat_type_id = $data->flat_type_id;
				$data_arr = fetch_waiting_list($data->flat_type_id);
			 }
			 $data_val = isset($data_arr[$data->online_application_id])?$data_arr[$data->online_application_id]:NULL;*/
			 
			 //turned off by debaleena 11-06-2024 start
			 
			 /*if($data->status == 'allotted') {
				 $status = 'Allotted Offer';
			 }
			 else {
				 $status = $data->status;
			 }
			 
			 $fields = array();
			 $returns = check_application_entity(0,$data->online_application_id);
			 $entityList = $returns[0];
			 $fields[] = array('data' => 'Application for '.$entityList['type']);
			 $fields[] = array('data' => $data->application_no, 'class' => array('text-align-c'));
			 $fields[] = array('data' => implode('/', array_reverse(explode('-', $data->date_of_application))), 'class' => array('text-align-c'));


			 ///////////////////////////////02.05.2024///////////////////
			 $fields[] = array('data' => $status != 0 ? $status : 'Verification Pending', 'class' => array('text-align-c'));
			
			 //$fields[] = array('data' => $status, 'class' => array('text-align-c'));
			///////////////////////////////////////////////////////////////


			 $fields[] = array('data' => implode('/', array_reverse(explode('-', $data->date_of_verified))) != 0 ? implode('/', array_reverse(explode('-', $data->date_of_verified))) : 'Verification Pending' , 'class' => array('text-align-r'));
			 
			 /*if($data->status == 'verified' && substr($data->application_no,0,2) == 'NA') {
				$fields[] = array('data' => $data->computer_serial_no, 'class' => array('text-align-r'));					 
			 }
			 else {
				 $fields[] = '';
			 }*/
			 
			 /*if($data->status == 'verified') {
			 	//$fields[] = $data_val != NULL ?$data_val['waiting_no'] : '';
				$wait_no = get_individual_waiting_no($data->application_no);
		 		$fields[] = array('data' => $wait_no != 0 ? $wait_no : '', 'class' => array('text-align-r'));
			 }
			 else {
				$fields[] = ''; 
			 }*/
			 
			 
			 /*$fields[] = l('<img src="'.$base_path.drupal_get_path('module', 'application_status').'/images/view.png" alt="View Icon">', 				'view-application/'.encrypt_url($data->online_application_id), array(	  'html'=>TRUE,
			  'attributes'=> array('target' => '_blank'),
			 ));*/
			 //end
			$rows[] = $fields;
			// Remove data from array 
			unset($fields); 
		}
		 
		
		$output = theme_table(
		array(
		  'header' => $header,
		  'rows' => $rows,
		  'attributes' => array('class'=>array('table table-list table-striped')),
		  'sticky' => true,
		  'caption' => '',
		  'colgroups' => array(),
		  'empty' => t("No data found!") // The message to be displayed if table is empty
		)
	  ).theme('pager');
	  
	  return $output;
	}
	
	/* Done by Subham 31-01-2025 */
	function validate_application_number($element, &$form_state) {
		$input = $form_state['values'][$element['#name']];
	
		if (!preg_match('/^[A-Za-z-]+-\d{8}-\d{4}$/', $input)) {
			form_set_error($element['#name'], t('Invalid Application Number. Enter Proper Application Number'));
		}
	}