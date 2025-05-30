<?php
		
	function flat_type_waiting_list_form($form, &$form_state) {
		$flat_type =  !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : 0;
		
		$form['flat_type'] = array(
			'#title' => t('RHE Flat Type'),
			'#type' => 'select',
			'#options' => rhe_flat_type(),
			'#required' => TRUE,
			// '#attributes' => array('class' => array('dropdown3')),//turned off sd 21-06-2024
			//'#prefix' => '<div >',//turned off sd 21-06-2024
			//'#suffix' => '</div>',//turned off sd 21-06-2024
			'#attributes' => array('class' => array('form-select')),
			'#prefix' => '<div class="col-md-12"><div class="form-floating">',//sd 20-06-2024
			'#suffix' => '</div></div>',//sd 21-06-2024
			'#ajax' => array(
				'event' => 'change',
				//'wrapper' => 'no_of_vacancy',
				'callback' => '_reload_flat_type_waiting_list',
				'method' => 'replace',
			),
	  	);
		
		$form['flat_type_waiting_list'] = array(
		'#prefix' => '<div  id="flat_type_waiting_list">',
		'#suffix' => '</div>',
		);
		
		if($flat_type != 0) {
			
			$form['flat_type_waiting_list'] = array(
				'#type' => 'markup',
				'#markup' => flat_type_waiting_list_page($flat_type),
				'#prefix' => '<div id="flat_type_waiting_list">',
				'#suffix' => '</div>',
			);
		 
	  	}
		
		return $form;
	}
	
	function flat_type_waiting_list_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function flat_type_waiting_list_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_flat_type_waiting_list($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_type_waiting_list", drupal_render($form['flat_type_waiting_list']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function flat_type_waiting_list_page($flat_type = '') {
		global $base_path;
		
		$output = '';
		
		$rows =array();
		$rows = flat_type_wise_waiting_detail($flat_type);
		
		
		$header = array();
		$header[] = array('data' => 'Flat Type Wise Waiting No');
		$header[] = array('data' => 'Applicant Name');
		$header[] = array('data' => 'Application No.');
		//$header[] = array('data' => 'Allotment Category');
		$header[] = array('data' => 'Flat Type');
		if($flat_type == 5) {
			$header[] = array('data' => 'Grade Pay');
			$header[] = array('data' => 'Computer Serial No.');
		} else {
			$header[] = array('data' => 'Computer Serial No.');	
		}
		//$header[] = array('data' => 'Status');

		

		
		
		if(count($rows) > 0) {
			// Render using Drupal's render API.
			$build['datatable'] = array(
			'#theme' => 'datatable',
			'#header' => $header,
			'#rows' => $rows,
			'#attributes' => array('class'=>array('table table-list')),
			);
	
			// Or, render using a theme function.
			$variables = array(
			'attributes' => array('class'=>array('table table-list')),
			'header' => $header,
			'rows' => $rows,
			);
			
			$output = theme('datatable', $variables);
		}
		else {
			$output = '<div>
						<table class="table table-list">
							<tr class="tr_no_data_found">
								<th class="th_no_data_found"></th>
							</tr>
							<tr class="tr_no_data_found">
								<td class="td_no_data_found">No data found!</td>
							</tr>
						</table>
					</div>';	
		}
	
	
		if(count($rows) > 0) {
			//return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'waiting_list').'/images/pdf_icon.png" title="Download Flat Type Wise Waiting List" alt="PDF Icon">Download Flat Type Wise Waiting List', 'flat_type_waiting_list_pdf/'.encrypt_url($flat_type).'/flat_type_waiting_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).$output;
			$url = l('Download Flat Type Wise Waiting List','flat_type_waiting_list_pdf/'.encrypt_url($flat_type).'/flat_type_waiting_list_'.time(),array('html' => true, 'attributes' => array('target' => '_blank','class' => array('btn bg-primary  px-5 rounded-pill text-white fw-bolder mb-2'))));

			return $url.$output;//sd 21-06-2024
		}
		else {//sd 21-06-2024 turned off
			return $output;
		}
	}