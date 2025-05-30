<?php
	function allotment_list_form($form, &$form_state) {
	
		$allotment_process_date =  isset($form_state['values']['allotment_process_date']) && !empty($form_state['values']['allotment_process_date']) ? $form_state['values']['allotment_process_date'] : '';
		
		$allotment_process_no =  isset($form_state['values']['allotment_process_no']) && !empty($form_state['values']['allotment_process_no']) ? $form_state['values']['allotment_process_no'] : '';
		
		$allotment_process_type =  isset($form_state['values']['allotment_process_type']) && !empty($form_state['values']['allotment_process_type']) ? $form_state['values']['allotment_process_type'] : '';
		
		
		$form['allotment_process_date'] = array(
			'#title' => t('Allotment Process Date'),
			'#type' => 'select',
			'#options' => allotment_process_date(),
			'#required' => TRUE,
			'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
			'#prefix' => '<div class ="row"><div class="col-md-4"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div>',//sd 24-06-2024
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_process_no',
					   'method' => 'replace',
			),
			'#default_value' => $allotment_process_date
	  	);
		
		
		$form['allotment_process_no'] = array(
			/*'#title' => t('Allotment Process No.'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_process_type',
					   'method' => 'replace',
			),*/
			//'#prefix' => '<div class="three" id="allotment_process_no_replace">',// sd 24-06-2024 turned off
			//'#suffix' => '</div>',// sd 24-06-2024 turned off
			'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
			'#prefix' => '<div class="col-md-4" id="allotment_process_no_replace"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div>',//sd 24-06-2024
			//'#default_value' => $allotment_process_no,
		);		

		
		if($allotment_process_date != '') {
			$form['allotment_process_no'] = array(
				'#title' => t('Allotment Process No.'),
				'#type' => 'select',
				'#options' => allotment_process_no($allotment_process_date),
				'#required' => TRUE,
				//'#attributes' => array('class' => array('dropdown3')),//sd 24-06-2024 turned off
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_allotment_process_type',
						   'method' => 'replace',
				),
				//'#prefix' => '<div class="three" id="allotment_process_no_replace">',//sd 24-06-2024 turned off
				//'#suffix' => '</div>',//sd 24-06-2024 turned off
				'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
				'#prefix' => '<div class="col-md-4" id="allotment_process_no_replace"><div class="form-floating">',//sd 24-06-2024
				'#suffix' => '</div></div>',//sd 24-06-2024
				'#default_value' => $allotment_process_no,
			);
		}
		
		$form['allotment_process_type'] = array(
			/*'#title' => t('Allotment Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#ajax' => array(
					   'event' => 'change',
					   'callback' => '_reload_allotment_list',
					   'method' => 'replace',
			),*/
			//'#prefix' => '<div class="three" id="allotment_process_type_replace">', //sd 24-06-2024 turned off
			//'#suffix' => '</div>', //sd 24-06-2024 turned off
			'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
			'#prefix' => '<div class="col-md-4" id="allotment_process_type_replace"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div></div>',//sd 24-06-2024
			//'#default_value' => $allotment_process_type,
		);		

		
		if($allotment_process_date != '' && $allotment_process_no != '') {
			$form['allotment_process_type'] = array(
				'#title' => t('Allotment Process Type'),
				'#type' => 'select',
				'#options' => array('' => 'Select Allotment Process Type', 'NAL' => 'New Allotment', 'VSAL' => 'Floor Shifting', 'CSAL' => 'Category Shifting'),
				'#required' => TRUE,
				//'#attributes' => array('class' => array('dropdown3')),//sd 24-06-2024 turned off
				'#ajax' => array(
						   'event' => 'change',
						   'callback' => '_reload_allotment_list',
						   'method' => 'replace',
				),
				//'#prefix' => '<div class="three" id="allotment_process_type_replace">', //sd 24-06-2024 turned off
				//'#suffix' => '</div>', //sd 24-06-2024 turned off
				'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
				'#prefix' => '<div class="col-md-4"  id="allotment_process_type_replace"><div class="form-floating">',//sd 24-06-2024
				'#suffix' => '</div></div></div>',//sd 24-06-2024
				'#default_value' => $allotment_process_type,
			);
		}

		$form['allotment_list_details'] = array(
			'#prefix' => '<div id="allotment_list_replace">',
			'#suffix' => '</div>',
		);
		
		
		if($allotment_process_date != '' && $allotment_process_no != '' && $allotment_process_type != '') {
		 
			$form['allotment_list_details'] = array(
				'#type' => 'markup',
				'#markup' => allotment_list_page($allotment_process_date, $allotment_process_no, $allotment_process_type),
				'#prefix' => '<div id="allotment_list_replace">',
				'#suffix' => '</div>',
			);
	  	}
		
		return $form;
	}
	
	function allotment_list_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function allotment_list_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_allotment_process_no($form, &$form_state) {
		// echo "ppp";die;
		$commands[] = ajax_command_replace('#allotment_process_no_replace', drupal_render($form['allotment_process_no']));
		$commands[] = ajax_command_replace('#allotment_process_type_replace', drupal_render($form['allotment_process_type']));
		$commands[] = ajax_command_replace("#allotment_list_replace", drupal_render($form['allotment_list_details']));
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}
	
	function _reload_allotment_process_type($form, &$form_state) {
		$commands[] = ajax_command_replace('#allotment_process_type_replace', drupal_render($form['allotment_process_type']));
		$commands[] = ajax_command_replace("#allotment_list_replace", drupal_render($form['allotment_list_details']));
		return array('#type' => 'ajax', '#commands' => $commands);
 
	}
	
	function _reload_allotment_list($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#allotment_list_replace", drupal_render($form['allotment_list_details']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	
	// function allotment_list_page($allotment_process_date = '', $allotment_process_no = '', $allotment_process_type = '') {
		
	// 	$output = '';
		
	// 	$result1 = fetch_allotment_process_detail($allotment_process_no);
	// 	if($result1->rowCount() > 0) {
	// 		$data1 = $result1->fetchObject();
	// 	}
		
	// 	//$header = array(); //sd 24-06-2024 turned off
	// 	//$rows = array(); //sd 24-06-2024 turned off
		
	// 	$header[] = array('data' => 'Sl. No.');
	// 	if($allotment_process_type == 'NAL') {
	// 		$header[] = array('data' => 'Name and Designation');
	// 		$header[] = array('data' => '1. Application No.<br>2. Place of Posting<br>3. Date of Application');
	// 		$header[] = array('data' => 'Flat Allotted');
	// 		$header[] = array('data' => 'Floor');
	// 		$header[] = array('data' => 'Name of R.H.E.');
	// 		$header[] = array('data' => 'Date of Retirement');
	// 	} else if($allotment_process_type == 'VSAL' || $allotment_process_type == 'CSAL') {
	// 		$header[] = array('data' => 'Name');
	// 		$header[] = array('data' => '1. Date of Possession<br>2. Date of Application<br>3. Date of Retirement');
	// 		$header[] = array('data' => 'Allotted Flat No.');
	// 		$header[] = array('data' => 'Type of Flat');
	// 		$header[] = array('data' => 'Floor');
	// 		$header[] = array('data' => 'From Flat No.');
	// 		$header[] = array('data' => 'To Flat No.');		
	// 	}
	// 	$header[] = array('data' => 'Remarks');
		
	// 	if($allotment_process_type == 'NAL') {
			
	// 		$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type);

			
	// 		$result_roaster = db_query("(SELECT flat_occupant_id, allotment_process_no, roaster_vacancy_position, allotment_reason FROM {housing_allotment_roaster_details} hard 	
	// 		where hard.allotment_process_no = :allotment_process_no_hard)
	// 		UNION ALL 
	// 		(SELECT flat_occupant_id, allotment_process_no, roaster_vacancy_position, allotment_reason FROM {housing_flat_occupant} hfo
	// 		where hfo.allotment_date = :allotment_date AND hfo.allotment_process_no = :allotment_process_no AND substring(hfo.allotment_no, '\w+') = :allotment_no_type AND 
	// 		hfo.roaster_vacancy_position IS :roaster_vacancy_position)", array(':allotment_date' => $allotment_process_date, ':allotment_process_no' => $allotment_process_no, 
	// 		':allotment_no_type' => 'NAL', ':roaster_vacancy_position' => NULL, ':allotment_process_no_hard' => $allotment_process_no));
				
	// 		$i = 1;
	// 		while($data_roaster = $result_roaster->fetchObject()) {
	// 			$fields = array();
	// 			// echo $data_roaster->flat_occupant_id.'----p';
	// 			if($data_roaster->flat_occupant_id != '') {
				
	// 				if($data = $result->fetchObject()) {
						
	// 					if(trim($data->floor) == 'F') {
	// 						$floor = '1st';	
	// 					} else if(trim($data->floor) == 'S') {
	// 						$floor = '2nd';	
	// 					} else {
	// 						$floor = $data->floor;	
	// 					}
						
	// 					if($data->allowed_for_floor_shifting != '' && $data->allowed_for_floor_shifting == 'N') {
	// 						$allowed_for_fs = 'No Floor Shifting Henceforth';		
	// 					} else {
	// 						$allowed_for_fs = '';	
	// 					}
						
	// 					if($data->roaster_vacancy_position != '') {
	// 						if($data->roaster_vacancy_position == 1 || $data->roaster_vacancy_position == 21) {
	// 							$remarks = $data->roaster_vacancy_position.'st Vacancy<br><br>'.$data->allotment_reason.'<br>'.$allowed_for_fs;	
	// 						} else if($data->roaster_vacancy_position == 2 || $data->roaster_vacancy_position == 22) {
	// 							$remarks = $data->roaster_vacancy_position.'nd Vacancy<br><br>'.$data->allotment_reason.'<br>'.$allowed_for_fs;	
	// 						} else if($data->roaster_vacancy_position == 3 || $data->roaster_vacancy_position == 23) {
	// 							$remarks = $data->roaster_vacancy_position.'rd Vacancy<br><br>'.$data->allotment_reason.'<br>'.$allowed_for_fs;	
	// 						} else {
	// 							$remarks = $data->roaster_vacancy_position.'th Vacancy<br><br>'.$data->allotment_reason.'<br>'.$allowed_for_fs;
	// 						}
	// 					} else {
	// 						$remarks = $allowed_for_fs;		
	// 					}
						
	// 					$fields[] = $i;
	// 					$fields[] = $data->applicant_name.'<br>'.$data->applicant_designation;
	// 					$fields[] = '1. '.$data->application_no.'<br>'.'2. '.$data->applicant_posting_place.'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_application)));
	// 					$fields[] = $data->flat_no;
	// 					$fields[] = $floor;
	// 					$fields[] = $data->estate_name;
	// 					$fields[] = implode('/', array_reverse(explode('-', $data->date_of_retirement)));
	// 					$fields[] = $remarks;
						
	// 					$i++;
	// 				}
							
	// 			} else {
	// 					if($data_roaster->roaster_vacancy_position == 1 || $data_roaster->roaster_vacancy_position == 21) {
	// 						$remarks = $data_roaster->roaster_vacancy_position.'st Vacancy<br><br>'.$data_roaster->allotment_reason;	
	// 					} else if($data_roaster->roaster_vacancy_position == 2 || $data_roaster->roaster_vacancy_position == 22) {
	// 						$remarks = $data_roaster->roaster_vacancy_position.'nd Vacancy<br><br>'.$data_roaster->allotment_reason;	
	// 					} else if($data_roaster->roaster_vacancy_position == 3 || $data_roaster->roaster_vacancy_position == 23) {
	// 						$remarks = $data_roaster->roaster_vacancy_position.'rd Vacancy<br><br>'.$data_roaster->allotment_reason;	
	// 					} else {
	// 						$remarks = $data_roaster->roaster_vacancy_position.'th Vacancy<br><br>'.$data_roaster->allotment_reason;
	// 					}
					
	// 				$fields[] = $i;
	// 				$fields[] = '<b>Not Available<b>';
	// 				$fields[] = '';
	// 				$fields[] = '';
	// 				$fields[] = '';
	// 				$fields[] = '';
	// 				$fields[] = '';
	// 				$fields[] = $remarks;
					
	// 				$i++;	
	// 			}
	// 			$rows[] = $fields;
	// 		}
				
	// 	} else if($allotment_process_type == 'VSAL') {
	// 		$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type);
			
	// 		$i = 1;
	// 		while($data = $result->fetchObject()) {
	// 			$fields = array();
				
	// 			if(trim($data->floor) == 'F') {
	// 				$floor = '1st';	
	// 			} else if(trim($data->floor) == 'S') {
	// 				$floor = '2nd';	
	// 			} else {
	// 				$floor = $data->floor;	
	// 			}
				
	// 			$fields[] = $i;
	// 			$fields[] = $data->applicant_name;
	// 			$fields[] = '1. '.implode('/', array_reverse(explode('-', $data->possession_date))).'<br>'.'2. '.implode('/', array_reverse(explode('-', $data->date_of_application))).'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_retirement)));
	// 			$fields[] = $data->flat_no;
	// 			$fields[] = $data->flat_type;
	// 			$fields[] = $floor;
	// 			$fields[] = $data->occupied_flat_vs;
	// 			$fields[] = $data->flat_no;
	// 			$fields[] = 'Floor Shifting';
				
	// 			$i++;
	// 			$rows[] = $fields;
	// 		}
	// 	} else if($allotment_process_type == 'CSAL') {
	// 		$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type);
			
	// 		$i = 1;
	// 		while($data = $result->fetchObject()) {
	// 			$fields = array();
				
	// 			if(trim($data->floor) == 'F') {
	// 				$floor = '1st';	
	// 			} else if(trim($data->floor) == 'S') {
	// 				$floor = '2nd';	
	// 			} else {
	// 				$floor = $data->floor;	
	// 			}
				
	// 			$fields[] = $i;
	// 			$fields[] = $data->applicant_name;
	// 			$fields[] = '1. '.implode('/', array_reverse(explode('-', $data->possession_date))).'<br>'.'2. '.implode('/', array_reverse(explode('-', $data->date_of_application))).'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_retirement)));
	// 			$fields[] = $data->flat_no;
	// 			$fields[] = $data->flat_type;
	// 			$fields[] = $floor;
	// 			$fields[] = $data->occupied_flat_cs;
	// 			$fields[] = $data->flat_no;
	// 			$fields[] = 'Category Shifting';
				
	// 			$i++;
	// 			$rows[] = $fields;
	// 		}
	// 	}
			
			
	// 		/*global $base_path;
	// 	 	$src=$base_path.drupal_get_path('module', 'allotment_list').'/images/view1.png';
	// 		$fields[] =  l(
	// 	 				'<img src="'.$src.'" alt="View Icon">',
	// 	 				'allotment_details/'.encrypt_url($data->online_application_id), 
	// 					array(
	// 							'html'=>TRUE,
	// 	  						'attributes'=> array('target' => '_blank'),
	// 	 				)
	// 				);*/
			
	// 	 	/*$src1=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
	// 		$fields[] = l(
	// 	 				'<img src="'.$src1.'" alt="View Icon">',
	// 	 				'application_detail/'.encrypt_url($data->online_application_id), 
	// 					array(
	// 							'html'=>TRUE,
	// 	  						'attributes'=> array('target' => '_blank'),
	// 	 				)
	// 				);*/
			
			
		
	// 	/*$output = theme_table(
	// 		array(
	// 		'header' => $header,
	// 		'rows' => $rows,
	// 		'attributes' => array(),
	// 		'sticky' => true,
	// 		'caption' => '',
	// 		'colgroups' => array(),
	// 		'empty' => t("No data found!") // The message to be displayed if table is empty
	// 		)
	// 	).theme('pager');*/
		
	// 	if($allotment_process_type == 'NAL') {		
	// 		if($result->rowCount() > 0) {
	// 			// Render using Drupal's render API.
	// 			$build['datatable'] = array(
	// 			  '#theme' => 'datatable',
	// 			  '#header' => $header,
	// 			  '#rows' => $rows,
	// 			  '#attributes' => array(),
	// 			);
			
	// 			// Or, render using a theme function.
	// 			$variables = array(
	// 			  //'attributes' => array(), //sd 24-06-2024 turned off
	// 			  'header' => $header,
	// 			  'rows' => $rows,
	// 			  'attributes' => array('class'=>array('table table-list')),//sd 24-06-2024
	// 			);
				
	// 			$output = '<br>'.theme('datatable', $variables);
	// 		}
	// 		else {
	// 			$output = '<br><div>
	// 							<table class="datatable_no_data_found table table-list">
	// 								<tr class="tr_no_data_found">
	// 									<th class="th_no_data_found"></th>
	// 								</tr>
	// 								<tr class="tr_no_data_found">
	// 									<td class="td_no_data_found">No data found!</td>
	// 								</tr>
	// 							</table>
	// 						</div>';
	// 		}
			
			
	// 		$html = '';
	// 		$html = '<br><div style="padding-right:20px;">'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'allotment_list').'/images/pdf_icon.png" title="Download Allottee List" alt="PDF Icon">Download Allottees List', 'allottee_list_pdf/'.encrypt_url($allotment_process_date).'/'.encrypt_url($allotment_process_no).'/'.encrypt_url($allotment_process_type).'/'.$allotment_process_type.'_allottees_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div><br>';
			
	// 		$html .= '<font style=" font-size: 20px; color: #0090C7;"><b><u>List of Allottees at Different R.H.E. of Flat Type - '.$data1->flat_type.' (New Allotment)</u></b></font><br>';		
	
	// 		if($result->rowCount() > 0) {
	// 			return $html.$output;
	// 		}
	// 		else {
	// 			return $output;
	// 		}
	// 	}  else if($allotment_process_type == 'VSAL') {
	// 		if($result->rowCount() > 0) {
	// 			// Render using Drupal's render API.
	// 			$build['datatable'] = array(
	// 			  '#theme' => 'datatable',
	// 			  '#header' => $header,
	// 			  '#rows' => $rows,
	// 			  '#attributes' => array(),
	// 			);
			
	// 			// Or, render using a theme function.
	// 			$variables = array(
	// 			   //'attributes' => array(), sd 24-06-2024 turned off
	// 			  'header' => $header,
	// 			  'rows' => $rows,
	// 			  'attributes' => array('class'=>array('table table-list')),//sd 24-06-2024
	// 			);
				
	// 			$output = '<br>'.theme('datatable', $variables);
	// 		}
	// 		else {
	// 			$output = '<br><div>
	// 							<table class="datatable_no_data_found table table-list">
	// 								<tr class="tr_no_data_found">
	// 									<th class="th_no_data_found"></th>
	// 								</tr>
	// 								<tr class="tr_no_data_found">
	// 									<td class="td_no_data_found">No data found!</td>
	// 								</tr>
	// 							</table>
	// 						</div>';
	// 		}
			
			
	// 		$html = '';
	// 		$html = '<br><div style="padding-right:20px;">'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'allotment_list').'/images/pdf_icon.png" title="Download Allottee List" alt="PDF Icon">Download Allottees List', 'allottee_list_pdf/'.encrypt_url($allotment_process_date).'/'.encrypt_url($allotment_process_no).'/'.encrypt_url($allotment_process_type).'/'.$allotment_process_type.'_allottees_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div><br>';
			
			
	// 		$html .= '<font style=" font-size: 20px; color: #0090C7;"><b><u>List of Allottees at Different R.H.E. of Flat Type - '.$data1->flat_type.' (Floor Shifting)</u></b></font><br>';
	
	// 		if($result->rowCount() > 0) {
	// 			return $html.$output;
	// 		}
	// 		else {
	// 			return $output;
	// 		}
	// 	} else if($allotment_process_type == 'CSAL') {
	// 		if($result->rowCount() > 0) {
	// 			// Render using Drupal's render API.
	// 			$build['datatable'] = array(
	// 			  '#theme' => 'datatable',
	// 			  '#header' => $header,
	// 			  '#rows' => $rows,
	// 			  '#attributes' => array(),
	// 			);
			
	// 			// Or, render using a theme function.
	// 			$variables = array(
	// 			  //'attributes' => array(),// sd 24-06-2024 turned off
	// 			  'header' => $header,
	// 			  'rows' => $rows,
	// 			  'attributes' => array('class'=>array('table table-list')),//sd 24-06-2024
	// 			);
				
	// 			$output = '<br>'.theme('datatable', $variables);
	// 		}
	// 		else {
	// 			$output = '<br><div>
	// 							<table class="datatable_no_data_found table table-list">
	// 								<tr class="tr_no_data_found">
	// 									<th class="th_no_data_found"></th>
	// 								</tr>
	// 								<tr class="tr_no_data_found">
	// 									<td class="td_no_data_found">No data found!</td>
	// 								</tr>
	// 							</table>
	// 						</div>';
	// 		}
			
			
	// 		$html = '';
	// 		$html = '<br><div style="padding-right:20px;">'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'allotment_list').'/images/pdf_icon.png" title="Download Allottee List" alt="PDF Icon">Download Allottees List', 'allottee_list_pdf/'.encrypt_url($allotment_process_date).'/'.encrypt_url($allotment_process_no).'/'.encrypt_url($allotment_process_type).'/'.$allotment_process_type.'_allottees_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div><br>';
			
	// 		$html .= '<font style=" font-size: 20px; color: #0090C7;"><b><u>List of Allottees at Different R.H.E. of Flat Type - '.$data1->flat_type.' (Category Shifting)</u></b></font><br>';
	
	// 		if($result->rowCount() > 0) {
	// 			return $html.$output;
	// 		}
	// 		else {
	// 			return $output;
	// 		}	
	// 	}
	// }



	function allotment_list_page($allotment_process_date = '', $allotment_process_no = '', $allotment_process_type = '') {
		// echo 'hiii';die;
		
		$output = '';
		
		$result1 = fetch_allotment_process_detail($allotment_process_no);
		// print_r($result1);die;
		if($result1->rowCount() > 0) {
			$data1 = $result1->fetchObject();
			// print_r($data1);die;
		}
		
		//$header = array(); //sd 24-06-2024 turned off
		//$rows = array(); //sd 24-06-2024 turned off
		
		$header[] = array('data' => 'Sl. No.');
		if($allotment_process_type == 'NAL') {
			$header[] = array('data' => 'Name and Designation');
			$header[] = array('data' => '1. Application No.<br>2. Place of Posting<br>3. Date of Application');
			$header[] = array('data' => 'Flat Allotted');
			$header[] = array('data' => 'Floor');
			$header[] = array('data' => 'Name of R.H.E.');
			$header[] = array('data' => 'Date of Retirement');
		} else if($allotment_process_type == 'VSAL' || $allotment_process_type == 'CSAL') {
			$header[] = array('data' => 'Name');
			$header[] = array('data' => '1. Date of Possession<br>2. Date of Application<br>3. Date of Retirement');
			$header[] = array('data' => 'Allotted Flat No.');
			$header[] = array('data' => 'Type of Flat');
			$header[] = array('data' => 'Floor');
			$header[] = array('data' => 'From Flat No.');
			$header[] = array('data' => 'To Flat No.');		
		}
		$header[] = array('data' => 'Remarks');
		$header[] = array('data' => 'Allotment Approval Status');// sd 11-09-2024
		$header[] = array('data' => 'Application Status');// dg 06-12-2024
		
		if($allotment_process_type == 'NAL') {
			
			$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type);
			// print_r($result);die;

			
			/*$result_roaster = db_query("(SELECT flat_occupant_id, allotment_process_no, roaster_vacancy_position, allotment_reason FROM {housing_allotment_roaster_details} hard 	
			where hard.allotment_process_no = :allotment_process_no_hard)
			UNION ALL 
			(SELECT flat_occupant_id, allotment_process_no, roaster_vacancy_position, allotment_reason FROM {housing_flat_occupant} hfo
			where hfo.allotment_date = :allotment_date AND hfo.allotment_process_no = :allotment_process_no AND substring(hfo.allotment_no, '\w+') = :allotment_no_type AND 
			hfo.roaster_vacancy_position IS :roaster_vacancy_position)", array(':allotment_date' => $allotment_process_date, ':allotment_process_no' => $allotment_process_no, 
			':allotment_no_type' => 'NAL', ':roaster_vacancy_position' => NULL, ':allotment_process_no_hard' => $allotment_process_no));*/

			//////start 05-07-2024///
			$result_roaster = db_query("select hard.flat_occupant_id, hard.allotment_process_no, hard.roaster_vacancy_position, hard.allotment_reason from {housing_allotment_roaster_details} hard INNER JOIN {housing_flat_occupant} hfo ON hard.flat_occupant_id = hfo.flat_occupant_id
			where hfo.allotment_date = :allotment_date AND hfo.allotment_process_no = :allotment_process_no AND substring(hfo.allotment_no, '\w+') = :allotment_no_type AND hard.allotment_process_no = :allotment_process_no_hard AND
			hfo.roaster_vacancy_position IS :roaster_vacancy_position",array(':allotment_date' => $allotment_process_date, ':allotment_process_no' => $allotment_process_no, 
			':allotment_no_type' => 'NAL', ':roaster_vacancy_position' => NULL, ':allotment_process_no_hard' => $allotment_process_no));
			////end/////

			
				
			$i = 1;
			while($data_roaster = $result_roaster->fetchObject()) {
				$fields = array();
				// echo $data_roaster->flat_occupant_id.'----p';
				if($data_roaster->flat_occupant_id != '') {
				
					if($data = $result->fetchObject()) {
						// print_r($data->status);die;
						// 11-09-2024 sd
						$allotment_status=fetchAllotmentStatus($data->online_application_id);
						
						
						/*if(trim($data->floor) == 'F') {
							$floor = '1st';	
						} else if(trim($data->floor) == 'S') {
							$floor = '2nd';	
						} else {
							$floor = $data->floor;	
						}*/
						$floor = $data->floor;
						
						if($data->allowed_for_floor_shifting != '' && $data->allowed_for_floor_shifting == 'N') {
							$allowed_for_fs = 'No Floor Shifting Henceforth';		
						} else {
							$allowed_for_fs = '';	
						}
						
						//if($data->roaster_vacancy_position != '') {   ==========off  and change $data_roaster instead of $data at 05-07-2024======
							if($data_roaster->roaster_vacancy_position == 1 || $data_roaster->roaster_vacancy_position == 21) {
								$remarks = $data_roaster->roaster_vacancy_position.'st Vacancy<br><br>'.$data_roaster->allotment_reason.'<br>'.$allowed_for_fs;	
							} else if($data_roaster->roaster_vacancy_position == 2 || $data_roaster->roaster_vacancy_position == 22) {
								$remarks = $data_roaster->roaster_vacancy_position.'nd Vacancy<br><br>'.$data_roaster->allotment_reason.'<br>'.$allowed_for_fs;	
							} else if($data_roaster->roaster_vacancy_position == 3 || $data_roaster->roaster_vacancy_position == 23) {
								$remarks = $data_roaster->roaster_vacancy_position.'rd Vacancy<br><br>'.$data_roaster->allotment_reason.'<br>'.$allowed_for_fs;	
							} else {
								$remarks = $data_roaster->roaster_vacancy_position.'th Vacancy<br><br>'.$data_roaster->allotment_reason.'<br>'.$allowed_for_fs;
							}
						//} else {
						//	$remarks = $allowed_for_fs;		==========off at 05-07-2024===========
						//}

						////////////added by dg 06-12-2024//////
						if($data->status == 'offer_letter_cancel'){
							$application_status = 'Offer Letter Cancel';
						}else if($data->status == 'license_cancel'){
							$application_status = 'License Cancel';
						}else{
							$application_status = 'N/A';
						}

						/////end///////
						
						$fields[] = $i;
						$fields[] = $data->applicant_name.'<br>'.$data->applicant_designation;
						$fields[] = '1. '.$data->application_no.'<br>'.'2. '.$data->applicant_posting_place.'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_application)));
						$fields[] = $data->flat_no;
						$fields[] = $floor;
						$fields[] = $data->estate_name;
						$fields[] = implode('/', array_reverse(explode('-', $data->date_of_retirement)));
						$fields[] = $remarks;
						$fields[] = $allotment_status; //sd 11-09-2024
						//$fields[] = $application_status; //sd 11-09-2024
						$fields[] = $data->status_description; // Done by Subham 16-12-2024
						
						$i++;
					}
							
				}/* else {
						if($data_roaster->roaster_vacancy_position == 1 || $data_roaster->roaster_vacancy_position == 21) {
							$remarks = $data_roaster->roaster_vacancy_position.'st Vacancy<br><br>'.$data_roaster->allotment_reason;	
						} else if($data_roaster->roaster_vacancy_position == 2 || $data_roaster->roaster_vacancy_position == 22) {
							$remarks = $data_roaster->roaster_vacancy_position.'nd Vacancy<br><br>'.$data_roaster->allotment_reason;	
						} else if($data_roaster->roaster_vacancy_position == 3 || $data_roaster->roaster_vacancy_position == 23) {
							$remarks = $data_roaster->roaster_vacancy_position.'rd Vacancy<br><br>'.$data_roaster->allotment_reason;	
						} else {
							$remarks = $data_roaster->roaster_vacancy_position.'th Vacancy<br><br>'.$data_roaster->allotment_reason;
						}
					
					$fields[] = $i;
					$fields[] = '<b>Not Available<b>';
					$fields[] = '';
					$fields[] = '';
					$fields[] = '';
					$fields[] = '';
					$fields[] = '';
					$fields[] = $remarks;
					
					$i++;	
				}*/ /// off at 05-07-2024///
				$rows[] = $fields;
			}
				
		} else if($allotment_process_type == 'VSAL') {
			$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type);
			
			$i = 1;
			while($data = $result->fetchObject()) {
				//print_r($data);die;
				$fields = array();
				$allotment_status=fetchAllotmentStatus($data->online_application_id);// 11-09-2024 sd
				
				/*if(trim($data->floor) == 'F') {
					$floor = '1st';	
				} else if(trim($data->floor) == 'S') {
					$floor = '2nd';	
				} else {
					$floor = $data->floor;	
				}*/
				$floor = $data->floor;



				////////////added by dg 06-12-2024//////
				if($data->status == 'offer_letter_cancel'){
					$application_status = 'Offer Letter Cancel';
				}else if($data->status == 'license_cancel'){
					$application_status = 'License Cancel';
				}else{
					$application_status = 'N/A';
				}
				///////end////////////

				$fields[] = $i;
				$fields[] = $data->applicant_name;
				$fields[] = '1. '.implode('/', array_reverse(explode('-', $data->possession_date))).'<br>'.'2. '.implode('/', array_reverse(explode('-', $data->date_of_application))).'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_retirement)));
				$fields[] = $data->flat_no;
				$fields[] = $data->flat_type;
				$fields[] = $floor;
				$fields[] = $data->occupied_flat_vs;
				$fields[] = $data->flat_no;
				$fields[] = 'Floor Shifting';
				$fields[] = $allotment_status; //sd 11-09-2024
				$fields[] = $application_status; //dg 06-12-2024
				
				$i++;
				$rows[] = $fields;
			}
		} else if($allotment_process_type == 'CSAL') {
			$result = fetch_all_allottee_details($allotment_process_date, $allotment_process_no, $allotment_process_type);
			
			$i = 1;
			while($data = $result->fetchObject()) {
				$fields = array();
				$allotment_status=fetchAllotmentStatus($data->online_application_id);// 11-09-2024 sd
				
				/*if(trim($data->floor) == 'F') {
					$floor = '1st';	
				} else if(trim($data->floor) == 'S') {
					$floor = '2nd';	
				} else {
					$floor = $data->floor;	
				}*/

				$floor = $data->floor;

				////////////added by dg 06-12-2024//////
				if($data->status == 'offer_letter_cancel'){
					$application_status = 'Offer Letter Cancel';
				}else if($data->status == 'license_cancel'){
					$application_status = 'License Cancel';
				}else{
					$application_status = 'N/A';
				}
				///////end////////////
				
				
				$fields[] = $i;
				$fields[] = $data->applicant_name;
				$fields[] = '1. '.implode('/', array_reverse(explode('-', $data->possession_date))).'<br>'.'2. '.implode('/', array_reverse(explode('-', $data->date_of_application))).'<br>'.'3. '.implode('/', array_reverse(explode('-', $data->date_of_retirement)));
				$fields[] = $data->flat_no;
				$fields[] = $data->flat_type;
				$fields[] = $floor;
				$fields[] = $data->occupied_flat_cs;
				$fields[] = $data->flat_no;
				$fields[] = 'Category Shifting';
				$fields[] = $allotment_status; //sd 11-09-2024
				$fields[] = $application_status; //dg 06-12-2024
				
				$i++;
				$rows[] = $fields;
			}
		}

		// print_r($header);
			
			
			/*global $base_path;
		 	$src=$base_path.drupal_get_path('module', 'allotment_list').'/images/view1.png';
			$fields[] =  l(
		 				'<img src="'.$src.'" alt="View Icon">',
		 				'allotment_details/'.encrypt_url($data->online_application_id), 
						array(
								'html'=>TRUE,
		  						'attributes'=> array('target' => '_blank'),
		 				)
					);*/
			
		 	/*$src1=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
			$fields[] = l(
		 				'<img src="'.$src1.'" alt="View Icon">',
		 				'application_detail/'.encrypt_url($data->online_application_id), 
						array(
								'html'=>TRUE,
		  						'attributes'=> array('target' => '_blank'),
		 				)
					);*/
			
			
		
		/*$output = theme_table(
			array(
			'header' => $header,
			'rows' => $rows,
			'attributes' => array(),
			'sticky' => true,
			'caption' => '',
			'colgroups' => array(),
			'empty' => t("No data found!") // The message to be displayed if table is empty
			)
		).theme('pager');*/
		
		if($allotment_process_type == 'NAL') {		
			if($result->rowCount() > 0) {
				// Render using Drupal's render API.
				$build['datatable'] = array(
				  '#theme' => 'datatable',
				  '#header' => $header,
				  '#rows' => $rows,
				  '#attributes' => array(),
				);
			
				// Or, render using a theme function.
				$variables = array(
				  //'attributes' => array(), //sd 24-06-2024 turned off
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('class'=>array('table table-list')),//sd 24-06-2024
				);
				
				$output = '<br>'.theme('datatable', $variables);
			}
			else {
				$output = '<br><div>
								<table class="datatable_no_data_found table table-list">
									<tr class="tr_no_data_found">
										<th class="th_no_data_found"></th>
									</tr>
									<tr class="tr_no_data_found">
										<td class="td_no_data_found">No data found!</td>
									</tr>
								</table>
							</div>';
			}
			
			
			$html = '';
			$html = '<br><div style="padding-right:20px;">'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'allotment_list').'/images/pdf_icon.png" title="Download Allottee List" alt="PDF Icon">Download Allottees List', 'allottee_list_pdf/'.encrypt_url($allotment_process_date).'/'.encrypt_url($allotment_process_no).'/'.encrypt_url($allotment_process_type).'/'.$allotment_process_type.'_allottees_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div><br>';
			
			$html .= '<font style=" font-size: 20px; color: #0090C7;"><b><u>List of Allottees at Different R.H.E. of Flat Type - '.$data1->flat_type.' (New Allotment)</u></b></font><br>';		
	
			if($result->rowCount() > 0) {
				return $html.$output;
			}
			else {
				return $output;
			}
		}  else if($allotment_process_type == 'VSAL') {
			if($result->rowCount() > 0) {
				// Render using Drupal's render API.
				$build['datatable'] = array(
				  '#theme' => 'datatable',
				  '#header' => $header,
				  '#rows' => $rows,
				  '#attributes' => array(),
				);
			
				// Or, render using a theme function.
				$variables = array(
				   //'attributes' => array(), sd 24-06-2024 turned off
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('class'=>array('table table-list')),//sd 24-06-2024
				);
				
				$output = '<br>'.theme('datatable', $variables);
			}
			else {
				$output = '<br><div>
								<table class="datatable_no_data_found table table-list">
									<tr class="tr_no_data_found">
										<th class="th_no_data_found"></th>
									</tr>
									<tr class="tr_no_data_found">
										<td class="td_no_data_found">No data found!</td>
									</tr>
								</table>
							</div>';
			}
			
			
			$html = '';
			$html = '<br><div style="padding-right:20px;">'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'allotment_list').'/images/pdf_icon.png" title="Download Allottee List" alt="PDF Icon">Download Allottees List', 'allottee_list_pdf/'.encrypt_url($allotment_process_date).'/'.encrypt_url($allotment_process_no).'/'.encrypt_url($allotment_process_type).'/'.$allotment_process_type.'_allottees_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div><br>';
			
			
			$html .= '<font style=" font-size: 20px; color: #0090C7;"><b><u>List of Allottees at Different R.H.E. of Flat Type - '.$data1->flat_type.' (Floor Shifting)</u></b></font><br>';
	
			if($result->rowCount() > 0) {
				return $html.$output;
			}
			else {
				return $output;
			}
		} else if($allotment_process_type == 'CSAL') {
			if($result->rowCount() > 0) {
				// Render using Drupal's render API.
				$build['datatable'] = array(
				  '#theme' => 'datatable',
				  '#header' => $header,
				  '#rows' => $rows,
				  '#attributes' => array(),
				);
			
				// Or, render using a theme function.
				$variables = array(
				  //'attributes' => array(),// sd 24-06-2024 turned off
				  'header' => $header,
				  'rows' => $rows,
				  'attributes' => array('class'=>array('table table-list')),//sd 24-06-2024
				);
				
				$output = '<br>'.theme('datatable', $variables);
			}
			else {
				$output = '<br><div>
								<table class="datatable_no_data_found table table-list">
									<tr class="tr_no_data_found">
										<th class="th_no_data_found"></th>
									</tr>
									<tr class="tr_no_data_found">
										<td class="td_no_data_found">No data found!</td>
									</tr>
								</table>
							</div>';
			}
			
			
			$html = '';
			$html = '<br><div style="padding-right:20px;">'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'allotment_list').'/images/pdf_icon.png" title="Download Allottee List" alt="PDF Icon">Download Allottees List', 'allottee_list_pdf/'.encrypt_url($allotment_process_date).'/'.encrypt_url($allotment_process_no).'/'.encrypt_url($allotment_process_type).'/'.$allotment_process_type.'_allottees_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div><br>';
			
			$html .= '<font style=" font-size: 20px; color: #0090C7;"><b><u>List of Allottees at Different R.H.E. of Flat Type - '.$data1->flat_type.' (Category Shifting)</u></b></font><br>';
	
			if($result->rowCount() > 0) {
				return $html.$output;
			}
			else {
				return $output;
			}	
		}
	}

	

