<?php

	function view_unauthorized_occupants_page() {
		date_default_timezone_set("Asia/Kolkata");
		$date1 = date('Y-m-d');
		
		$output = '';
		$result = fetch_unauthorized_occupants();
		
		$rows =array();
		$header = array();
		
		$header[] = array('data' => 'Application No.');
		$header[] = array('data' => 'Licence No.');
		$header[] = array('data' => 'Date of Retirement');
		$header[] = array('data' => 'View Details');
		$header[] = array('data' => 'View Flat Details');
		
		while($data = $result->fetchObject()) {
			
			
			$date2 = $data->date_of_retirement;
			
			if($date2 < $date1) {
				
				$fields = array();
				$fields[] = $data->application_no;
				$fields[] = $data->license_no;
		 		$fields[] = implode('/', array_reverse(explode('-', $data->date_of_retirement)));
				
				global $base_path;
				$src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
		 		$fields[] = l(
		 				'<img src="'.$src.'" alt="View Icon">',
		 				'application_detail/'.encrypt_url($data->online_application_id), 
						array(
								'html'=>TRUE,
		  						'attributes'=> array('target' => '_blank'),
		 				)
					);
					
				$src1=$base_path.drupal_get_path('module', 'unauthorized_occupants').'/images/view1.png';
		 		$fields[] = l(
		 				'<img src="'.$src1.'" alt="View Icon">',
		 				'flat_detail/'.encrypt_url($data->flat_id), 
						array(
								'html'=>TRUE,
		  						'attributes'=> array('target' => '_blank'),
		 				)
					);
					
				$rows[] = $fields;
			}
			
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
  
  		if($result->rowCount() > 0) {
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'unauthorized_occupants').
					'/images/pdf_icon.png" title="Download Unauthorized Occupants List" alt="PDF Icon">Download Unauthorized Occupants List',			
					'unauthorized_occupants_list_pdf/unauthorized_occupants_list_'	
						.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: 
						#0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).$output;
		}
		else {
			return $output;
		}
	}