<?php

	function rhewise_licensee_list_form($form, &$form_state) {
		
		global $user_role;
		
		$rhe_name =  !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : '';
		
		if($user_role == 7 || $user_role == 8) {
			$form['rhe_name'] = array(
				'#title' => t('Name of the RHE'),
				'#type' => 'select',
				'#options' => rhe_list_specific(),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div>',
				'#suffix' => '</div>',
				'#ajax' => array(
					'event' => 'change',
					//'wrapper' => 'no_of_vacancy',
					'callback' => '_reload_rhe_wise_licensee_list',
					'method' => 'replace',
				),
				'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				),
				//'#attributes' => array('class' => array('update_rhe_selectize')),
			);
		} else {
			$form['rhe_name'] = array(
				'#title' => t('Name of the RHE'),
				'#type' => 'select',
				'#options' => rhe_list(),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div>',
				'#suffix' => '</div>',
				'#ajax' => array(
					'event' => 'change',
					//'wrapper' => 'no_of_vacancy',
					'callback' => '_reload_rhe_wise_licensee_list',
					'method' => 'replace',
				),
				'#select2' => array(
					'width' => '500',
					//'placeholder' => '- Select -',
					'allowClear' => TRUE
				),
				//'#attributes' => array('class' => array('update_rhe_selectize')),
			);
		}
		
		$form['licensee_list'] = array(
		'#prefix' => '<div  id="licensee_list">',
		'#suffix' => '</div>',
		);
		
		if($rhe_name != '') {
			
			$form['licensee_list'] = array(
				'#type' => 'markup',
				'#markup' => rhewise_licensee_list_page($rhe_name),
				'#prefix' => '<div id="licensee_list">',
				'#suffix' => '</div>',
			);
		 
	  	}
		
		return $form;
		
	}
	
	function rhewise_licensee_list_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function rhewise_licensee_list_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_rhe_wise_licensee_list($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#licensee_list", drupal_render($form['licensee_list']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function rhewise_licensee_list_page($rhe_name = '') {
		
		global $base_path;
		global $user_role;
		
		$output = '';
		
		$result = fetch_rhewise_licensee_list($rhe_name);
		$result1 = fetch_rhewise_licensee_list($rhe_name);
		$data1 = $result1->fetchObject();
		
		$rows = array();
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
			
			if($user_role == 7 || $user_role == 8) {
				if($data->uploaded_licence != '') {
					$download_path = "sites/default/files/";
					$custom_filename = $data->license_no;
					if($data->uri_signed_licence != '') {
						$path = substr($data1->uri_signed_licence, 9);
						$custom_file_name = $custom_filename.'_Licence_Copy';
					}
					$fields[] = l('<img width="40" height="40" src="'.$base_path.drupal_get_path('module', 'licence_list').'/images/download.png" alt="Download Icon">', $download_path.$path, array('html'=>TRUE, 'attributes'=> array('download' => $custom_file_name)));	
				} else {
					$fields[] = '';	
				}
			} else {
				$src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
				$fields[] = l(
						'<img src="'.$src.'" alt="View Icon">',
						'application_detail/'.encrypt_url($data->online_application_id), 
						array(
								'html'=>TRUE,
								'attributes'=> array('target' => '_blank'),
						)
					);
			}
				
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
			$replace_item = array(',', '/', ' ', '.', '(', ')');
			$rhe_esate_name = str_replace($replace_item, '_', trim($data1->estate_name));
			$file_name = $rhe_esate_name.'_Licensee_List';
			
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'licence_list').'/images/pdf_icon.png" 
			title="Download RHE Wise Licensee List" alt="PDF Icon">Download '.$data1->estate_name.' Licensee List','rhewise_licensee_list_pdf/'.encrypt_url(
			$rhe_name).'/'.$file_name, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7; font-weight: 400; 
			text-decoration: none; font-size:14px'))).$output;
		}
		else {
			return $output;
		}
	}