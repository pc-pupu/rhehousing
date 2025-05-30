<?php

	function licensee_list_form($form, &$form_state) {
		
		$licensee_type =  !empty($form_state['values']['licensee_type']) ? $form_state['values']['licensee_type'] : 0;
		
		$form['licensee_type'] = array(
			'#title' => t('Licensee Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --', '1' => 'New Licensee', '2' => 'Floor Shifting Licensee', '3' => 'Category Shifting Licensee'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown3')),
			'#prefix' => '<div >',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				//'wrapper' => 'no_of_vacancy',
				'callback' => '_reload_licensee_list',
				'method' => 'replace',
			),
	  	);
		
		$form['licensee_list'] = array(
		'#prefix' => '<div  id="licensee_list">',
		'#suffix' => '</div>',
		);
		
		if($licensee_type != 0) {
			
			$form['licensee_list'] = array(
				'#type' => 'markup',
				'#markup' => licensee_list_page($licensee_type),
				'#prefix' => '<div id="licensee_list">',
				'#suffix' => '</div>',
			);
		 
	  	}
		
		return $form;
		
	}
	
	function licensee_list_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function licensee_list_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_licensee_list($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#licensee_list", drupal_render($form['licensee_list']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function licensee_list_page($licensee_type = '') {
		
		global $base_path;
		
		$output = '';
		
		$result = fetch_licence_list($licensee_type);
		$result1 = fetch_licence_list($licensee_type);
		$data1 = $result1->fetchObject();
		
		$rows =array();
		$header = array();
		
		$header[] = array('data' => 'Licensee Name');
		$header[] = array('data' => 'Licence No.');
		$header[] = array('data' => 'Date of Issue');
		$header[] = array('data' => 'Date of Expiry');
		$header[] = array('data' => 'View Details');
		
		while($data = $result->fetchObject()) {
					
			$fields = array();
			$fields[] = $data->applicant_name;
			$fields[] = $data->license_no;
			$fields[] = implode('/', array_reverse(explode('-', $data->license_issue_date)));
			$fields[] = implode('/', array_reverse(explode('-', $data->license_expiry_date)));
			
			$src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
			$fields[] = l(
					'<img src="'.$src.'" alt="View Icon">',
					'application_detail/'.encrypt_url($data->online_application_id), 
					array(
							'html'=>TRUE,
							'attributes'=> array('target' => '_blank'),
					)
				);
				
			$rows[] = $fields;
			
		}
		
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
		
		if(count($rows) > 0) {
		// Render using Drupal's render API.
			$build['datatable'] = array(
			  '#theme' => 'datatable',
			  '#header' => $header,
			  '#rows' => $rows,
			  '#attributes' => array(),
			);
	 
			// Or, render using a theme function.
			$variables = array(
			  'attributes' => array(),
			  'header' => $header,
			  'rows' => $rows,
			);
			
			$output = theme('datatable', $variables);
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
  
  		if($result->rowCount() > 0) {
			if($data1->type_of_application == 'new') {
				$type_of_licence = 'New Allotment';	
				$type_of_licence_for_file = 'new_alot';
			} else if($data1->type_of_application == 'vs') {
				$type_of_licence = 'Floor Shifting';
				$type_of_licence_for_file = 'fllor_shifting';	
			} else if($data1->type_of_application == 'cs') {
				$type_of_licence = 'Category Shifting';
				$type_of_licence_for_file = 'category_shifting';	
			}
			
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'licence_list').'/images/pdf_icon.png" 
			title="Download Licensee List" alt="PDF Icon">Download '.$type_of_licence.' Licensee List','licence_list_pdf/'.encrypt_url( 
			$licensee_type).'/'.$type_of_licence_for_file.'_licensee_list_'.time(),
			array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7; font-weight: 400; text-decoration: none; 
			font-size:14px'))).$output;
		}
		else {
			return $output;
		}
	}