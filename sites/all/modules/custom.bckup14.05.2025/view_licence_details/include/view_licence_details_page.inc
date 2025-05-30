<?php

	function view_licence_details_form($form, &$form_state) {
		
		$licence_type =  !empty($form_state['values']['licence_type']) ? $form_state['values']['licence_type'] : '';
		
		$form['licence_type'] = array(
			'#title' => t('Select Licence Type'),
			'#type' => 'select',
			'#options' => array('new' => 'New Licence', 'vs' => 'Vertical Shifting Licence', 'cs' => 'Category Shifting Licence'),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown2')),
			'#prefix' => '<div >',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				//'wrapper' => 'no_of_vacancy',
				'callback' => '_reload_licence_details',
				'method' => 'replace',
			),
		);
		  
		  
		$form['licence_details'] = array(
		'#prefix' => '<div  id="licence_details">',
		'#suffix' => '</div>',
		);
		
		
		if($licence_type != '')	 {
		  
			$form['licence_details'] = array(
				'#type' => 'markup',
				'#markup' => viewLicenceDetails($licence_type),
				'#prefix' => '<div id="licence_details">',
				'#suffix' => '</div>',
			);
		}
		
		return $form;
		
	}
	
	function view_licence_details_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_licence_details($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#licence_details", drupal_render($form['licence_details']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function viewLicenceDetails($licence_type = '') {
		global $base_path;
		
		$fetch_id = fetch_online_application_id($licence_type);
		
		$data_id = $fetch_id->fetchObject();
		
		$online_application_id = $data_id->online_application_id;
		$flat_occupant_id = $data_id->flat_occupant_id; 
		$license_application_id = $data_id->license_application_id;
		
		$result = individual_licence_details($licence_type, $online_application_id, $flat_occupant_id, $license_application_id);
		
		$header = array();
		$rows =array();
		
		if($licence_type == 'new') {
			$header[] = array('data' => 'New Licence Online Application No.');
		}
		else if($licence_type == 'vs') {
			$header[] = array('data' => 'VS Licence Online Application No.');
		}
		else if($licence_type == 'cs') {
			$header[] = array('data' => 'CS Licence Online Application No.');
		}
		$header[] = array('data' => 'Licence Issue Date');
		$header[] = array('data' => 'Licence Expiry Date');
		$header[] = array('data' => 'Licence No.');
		$header[] = array('data' => 'Action');
		
		while($data = $result->fetchObject()) {
			
			$fields = array();
			$fields[] = $data->application_no;
			$fields[] = implode('/', array_reverse(explode('-', $data->license_issue_date)));
			$fields[] = implode('/', array_reverse(explode('-', $data->license_expiry_date)));
			$fields[] = $data->license_no;
			$fields[] = l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'view_licence_details').'/images/pdf_icon.png" title="Download Licence" alt="PDF Icon">Download Licence' , 'download_licence_pdf/'.encrypt_url($licence_type).'/'.encrypt_url($online_application_id).'/'.encrypt_url($flat_occupant_id).'/'.encrypt_url($license_application_id).'/'.$licence_type.'_'.'licence_'.$online_application_id.'_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'onclick' => $onclick1, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:12px')));
			
			$rows[] = $fields;
		}
			
		$output = theme_table(
			array(
			'header' => $header,
			'rows' => $rows,
			'attributes' => array(),
			'sticky' => true,
			'caption' => '',
			'colgroups' => array(),
			'empty' => t("No data found!") // The message to be displayed if table is empty
			)
		).theme('pager');
		
		
		
		
		return $output;
	}
	
	