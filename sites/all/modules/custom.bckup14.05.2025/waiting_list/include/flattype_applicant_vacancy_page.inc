<?php
		
	function flattype_applicant_vacancy_form($form, &$form_state) {
		$district_val = !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
		$flat_type_val =  !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : '';
	   	
		$form['district'] = array(
			'#title' => t('District'),
			'#type' => 'select',
			'#options' => district_list(),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#prefix' => '<div class="two">',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				//'wrapper' => 'no_of_vacancy',
				'callback' => '_reload_flattype',
				'method' => 'replace',
			),
			'#select2' => array(
				'width' => '500',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)
	 	);
	 
		$form['flat_type'] = array(
			'#prefix' => '<div class="two" id="flat_type">',
			'#suffix' => '</div>',
		);
		
		if($district_val != '') {
			$form['flat_type'] = array(
				'#title' => t('RHE Flat Type'),
				'#type' => 'select',
				'#options' => rhe_flat_type(),
				'#required' => TRUE,
				'#attributes' => array('class' => array('dropdown3')),
				'#prefix' => '<div class="two" id="flat_type">',
				'#suffix' => '</div>',
				'#ajax' => array(
					'event' => 'change',
					//'wrapper' => 'no_of_vacancy',
					'callback' => '_reload_applicant_and_vacancy',
					'method' => 'replace',
				),
				'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				)
			);
		}
		
		$form['flattype_applicant_vacancy'] = array(
		'#prefix' => '<div  id="flattype_applicant_vacancy">',
		'#suffix' => '</div>',
		);
		
		if($district_val != '' && $flat_type_val != '') {
			
			$form['flattype_applicant_vacancy'] = array(
				'#type' => 'markup',
				'#markup' => flattype_applicant_vacancy_page(trim($district_val), trim($flat_type_val)),
				'#prefix' => '<div id="flattype_applicant_vacancy">',
				'#suffix' => '</div>',
			);
		 
	  	}
		
		return $form;
	}
	
	function flattype_applicant_vacancy_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function flattype_applicant_vacancy_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_flattype($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_type", drupal_render($form['flat_type']));
		$commands[] = ajax_command_replace("#flattype_applicant_vacancy", drupal_render($form['flattype_applicant_vacancy']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function _reload_applicant_and_vacancy($form, &$form_state) {
		$commands = array();
		
		$commands[] = ajax_command_replace("#flattype_applicant_vacancy", drupal_render($form['flattype_applicant_vacancy']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function flattype_applicant_vacancy_page($district_id = '', $flat_type_id = '') {
		global $base_path;
		
		$output = '';
		
		$result_waiting_app = flat_type_wise_waiting_detail($flat_type_id);
		
		$flat_status_id = fetch_flat_status_id('vacant');
		$result_flat_vacancy = rhe_total_flat_vacancy($district_id, $flat_type_id, $flat_status_id);
		
		if(count($result_waiting_app) > 0 || $result_flat_vacancy->rowCount() > 0) {
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'waiting_list').'/images/pdf_icon.png" title="Download Flat Type Wise Waiting Applicant and Flat Vacancy" alt="PDF Icon">Download Flat Type Wise Waiting Applicant and Flat Vacancy', 'flattype_applicant_vacancy_pdf/'.encrypt_url($district_id).'/'.encrypt_url($flat_type_id).'/flattype_waiting_applicant_vacancy_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px')));
		}
		else {
			$output = '<div>
						<table class="datatable_no_data_found">
							<tr class="tr_no_data_found">
								<th class="th_no_data_found"></th>
							</tr>
							<tr class="tr_no_data_found">
								<td class="td_no_data_found">No data found!</td>
							</tr>
						</table>
					</div>';	
		}
		
	}