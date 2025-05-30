<?php

	function rhewise_occupantlist_form($form, &$form_state) {
		$rhe_name =  !empty($form_state['values']['rhe_name']) ? $form_state['values']['rhe_name'] : 0;
		$flat_type =  !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : 0;
		$block_name =  !empty($form_state['values']['block_name']) ? $form_state['values']['block_name'] : 0;
		$floor =  !empty($form_state['values']['floor']) ? $form_state['values']['floor'] : '';
		
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
				'callback' => '_reload_rhewise_flat_type',
				'method' => 'replace',
			),
			'#select2' => array(
				'width' => '150',
				//'placeholder' => '- Select -',
				'allowClear' => TRUE
        	)
		);
		
		$form['flat_type'] = array(
			'#title' => t('Flat Type'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			//'#weight' => -10,
			'#prefix' => '<div class="three" id="flat_type_replace">',
			'#suffix' => '</div>',
			'#attributes' => array('class'	=> array('dropdown3')),
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_blocklist',
				'method' => 'replace',
			),
		);
			
		if($rhe_name != 0) {
			$form['flat_type'] = array(
				'#title' => t('Flat Type'),
				'#type' => 'select',
				'#options' => flat_type_under_rhe($rhe_name),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="flat_type_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_blocklist',
					'method' => 'replace',
				),
			);
		}
		
		$form['block_name'] = array(
			'#title' => t('Name of the Block'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			//'#weight' => -10,
			'#prefix' => '<div class="three" id="block_name_replace">',
			'#suffix' => '</div>',
			'#attributes' => array('class'	=> array('dropdown3')),
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_floorlist',
				'method' => 'replace',
			),
		);
			
		if($rhe_name != 0 && $flat_type != 0) {
			$form['block_name'] = array(
				'#title' => t('Name of the Block'),
				'#type' => 'select',
				'#options' => block_name_under_rhe($rhe_name, $flat_type),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="block_name_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_floorlist',
					'method' => 'replace',
				),
			);
		}
		
		$form['floor'] = array(
			'#title' => t('Floor'),
			'#type' => 'select',
			'#options' => array('' => '-- Select --'),
			'#required' => TRUE,
			//'#weight' => -10,
			'#prefix' => '<div class="three" id="floor_replace">',
			'#suffix' => '</div>',
			'#attributes' => array('class'	=> array('dropdown3')),
			'#ajax' => array(
				'event' => 'change',
				'callback' => '_reload_rhewise_occupantlist',
				'method' => 'replace',
			),
		);
			
		if($rhe_name != 0 && $flat_type != 0 && $block_name != 0) {
			$form['floor'] = array(
				'#title' => t('Floor'),
				'#type' => 'select',
				'#options' => floor_under_rhe($rhe_name, $flat_type, $block_name),
				'#required' => TRUE,
				//'#weight' => -10,
				'#prefix' => '<div class="three" id="floor_replace">',
				'#suffix' => '</div>',
				'#attributes' => array('class'	=> array('dropdown3')),
				'#ajax' => array(
					'event' => 'change',
					'callback' => '_reload_rhewise_occupantlist',
					'method' => 'replace',
				),
			);
		}
		
		$form['rhewise_occupantlist'] = array(
			'#prefix' => '<div  id="rhewise_occupantlist">',
			'#suffix' => '</div>',
		);
		
		if($rhe_name != 0 && $flat_type != 0 && $block_name != 0 && $floor != '') {
			
			$form['rhewise_occupantlist'] = array(
				'#type' => 'markup',
				'#markup' => rhewise_occupantlist_page($rhe_name, $flat_type, $block_name, $floor),
				'#prefix' => '<div id="rhewise_occupantlist">',
				'#suffix' => '</div>',
			);
		 
	  	}
		
		return $form;	
	}
	
	function rhewise_occupantlist_form_validate($form, &$form_state) {
		#krumo($form_state['values']['table']);
	}
	
	function rhewise_occupantlist_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_rhewise_flat_type($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#flat_type_replace", drupal_render($form['flat_type']));
		$commands[] = ajax_command_replace("#block_name_replace", drupal_render($form['block_name']));
		$commands[] = ajax_command_replace("#floor_replace", drupal_render($form['floor']));
		$commands[] = ajax_command_replace("#rhewise_occupantlist", drupal_render($form['rhewise_occupantlist']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_blocklist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#block_name_replace", drupal_render($form['block_name']));
		$commands[] = ajax_command_replace("#floor_replace", drupal_render($form['floor']));
		$commands[] = ajax_command_replace("#rhewise_occupantlist", drupal_render($form['rhewise_occupantlist']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_floorlist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#floor_replace", drupal_render($form['floor']));
		$commands[] = ajax_command_replace("#rhewise_occupantlist", drupal_render($form['rhewise_occupantlist']));
		return array('#type' => 'ajax', '#commands' => $commands);
	}
	
	function _reload_rhewise_occupantlist($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#rhewise_occupantlist", drupal_render($form['rhewise_occupantlist']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function rhewise_occupantlist_page($rhe_name = '', $flat_type = '', $block_name = '', $floor = '') {
		global $base_path;
		
		$output = '';
		
		$result = rhe_flattype_block_floor_wise_flat_list($rhe_name, $flat_type, $block_name, $floor);
		
		$result1 = rhe_flattype_block_floor_wise_flat_list($rhe_name, $flat_type, $block_name, $floor);
		$data1 = $result1->fetchObject();
		
		$header = array();
		$rows =array();
		
		$heade1r = array();
		$rows1 = array();
		$fields1 = array();
		
		$header1[] = array('data' => 'District');
		$header1[] = array('data' => 'Name of the RHE');
		$header1[] = array('data' => 'Estate Address');
		$header1[] = array('data' => 'Flat Type');
		$header1[] = array('data' => 'Block');
		$header1[] = array('data' => 'Floor');
		
		$fields1[] = $data1->district_name;
		$fields1[] = $data1->estate_name;
		$fields1[] = $data1->estate_address;
		$fields1[] = $data1->flat_type;
		$fields1[] = $data1->block_name.' Block';
		if($data1->floor == 'G')
			$fields1[] = 'Ground';
		else if($data1->floor == 'F')
			$fields1[] = 'First';
		else if($data1->floor == 'S')
			$fields1[] = 'Second';
		else if($data1->floor == 'T')
			$fields1[] = 'Third';
		else if($data1->floor == '')
			$fields1[] = '';
		$rows1[]  = $fields1;
		
		
		$header[] = array('data' => 'Sl. No.');
		//$header[] = array('data' => 'District of RHE');
		//$header[] = array('data' => 'Flat Type');
		//$header[] = array('data' => 'Name of the RHE');
		//$header[] = array('data' => 'Estate Address');
		//$header[] = array('data' => 'Block');
		//$header[] = array('data' => 'Floor');
		$header[] = array('data' => 'Flat No');
		$header[] = array('data' => 'Flat Category');
		$header[] = array('data' => 'Flat Status');
		$header[] = array('data' => 'Occupant Name');
		$header[] = array('data' => 'Designation');
		$header[] = array('data' => 'View Details');
		$header[] = array('data' => 'Action');
		
		$i = 1;
		while($data = $result->fetchObject()) {
			 $result2 = flatwise_occupantlist($data->flat_id);
			 $data2 = $result2->fetchObject();
			 
			 $fields = array();
			 $fields[] = $i;
			 //$fields[] = $data->district_name;
			 //$fields[] = $data->flat_type;
			 //$fields[] = $data->estate_name;
			 //$fields[] = $data->estate_address;
			 //$fields[] = $data->block_name.' Block';
			 /*if($data->floor == 'G')
			 	$fields[] = 'Ground';
			 else if($data->floor == 'F')
			 	$fields[] = 'First';
			 else if($data->floor == 'S')
			 	$fields[] = 'Second';
			 else if($data->floor == 'T')
			 	$fields[] = 'Third';
			 else if($data->floor == '')
			 	$fields[] = '';*/
			 $fields[] = $data->flat_no;
			 $fields[] = $data->flat_category;
			 $fields[] = $data->flat_status_code;


		/*  turned off by debaleena 26-07-2024
			 if($data->flat_status == 'vacant')
			 	$fields[] = 'Ready to Allot';
			 else if($data->flat_status == 'occupied')
			 	$fields[] = 'Occupied';
			 else if($data->flat_status == 'abandoned')
			 	$fields[] = 'Abandoned';
			 else if($data->flat_status == 'under major repair')
			 	$fields[] = 'Under Major Repair';
			 else if($data->flat_status == 'under minor repair')
			 	$fields[] = 'Under Minor Repair';

		*/
			 
			 if($result2->rowCount() > 0) {
			 	$fields[] = $data2->applicant_name;
				$fields[] = $data2->applicant_designation;
				
				$src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
					$fields[] =  l(
							'<img src="'.$src.'" alt="View Icon">',
							'application_detail/'.encrypt_url($data2->online_application_id), 
							array(
									'html'=>TRUE,
									'attributes'=> array('target' => '_blank'),
							)
						);
						
				if($data2->user_status == 0) {
					$onclick="return confirm('Are you sure you want to Approve?')";
					$onclick1="return confirm('Are you sure you want to Reject?')";
					$fields[] = l('<img height="16" width="16" src="'.$base_path.drupal_get_path('module', 	
					'existing_occupant').'/images/accept_icon.png" title="Approve" alt="Approve Icon">Approve' , 
					'update_occupant_status/'.encrypt_url($data2->uid).'/'.encrypt_url('approve'), array('html'=>TRUE, 
					'attributes' => array('onclick' => $onclick, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: 
					underline; font-size:12px'))).' &nbsp;&nbsp;&nbsp;| <br>'.l('<img height="16" width="16" src="'.$base_path.
					drupal_get_path('module', 'existing_occupant').'/images/reject_icon.png" title="Reject" alt="Reject Icon">
					Reject' , 'update_occupant_status/'.encrypt_url($data2->uid).'/'.encrypt_url('reject'), array('html'=>
					TRUE, 'attributes' => array('onclick' => $onclick1, 'style' => 'color: #0090C7;font-weight: 
					400;text-decoration: underline; font-size:12px')));	
				} else {
					$fields[] =  'Done';		
				}
			 } else {
			 	$fields[] = 'Not Available';
				$fields[] = 'Not Available';
				$fields[] = 'Not Available';
				$fields[] = 'Not Available';		 
			 }
			 
			 $rows[]  = $fields;
			 
			 $i++;
		 }
		
		$output1 = theme_table(
			array(
			  'header' => $header1,
			  'rows' => $rows1,
			  'attributes' => array(),
			  'sticky' => true,
			  'caption' => '',
			  'colgroups' => array(),
			  'empty' => t("No data found!") // The message to be displayed if table is empty
			)
		).theme('pager');
		
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
		
		
		return $output1.'<br><br>'.$output;
		
	}
		