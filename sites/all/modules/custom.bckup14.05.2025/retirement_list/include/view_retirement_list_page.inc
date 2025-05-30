<?php

	function view_retirement_list_page() {
		
		$output = '';
		$result = fetch_retirement_list();
		
		$rows =array();
		$header = array();
		
		$header[] = array('data' => 'Application No.');
		$header[] = array('data' => 'Date of Retirement');
		$header[] = array('data' => 'View Details');
		
		while($data = $result->fetchObject()) {
			
			date_default_timezone_set("Asia/Kolkata");
			$date1 = date('Y-m-d');
			$date2 = $data->date_of_retirement;

			$diff = abs(strtotime($date2) - strtotime($date1));

			$years = floor($diff / (365*60*60*24));
			$months = floor(($diff - $years * 365*60*60*24) / (30*60*60*24));
			$days = floor(($diff - $years * 365*60*60*24 - $months*30*60*60*24)/ (60*60*24));
			if($date2 >= $date1) {
				if($years < 1 && $months < 6) {
					
					$fields = array();
					$fields[] = $data->application_no;
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
						
					$rows[] = $fields;
				}
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
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'retirement_list').'/images/pdf_icon.png" 
						title="Download Upcoming Retirement List" alt="PDF Icon">Download Upcoming Retirement List',	
						'retirement_list_pdf/retirement_list_'.time(),
						array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: 	
						#0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).$output;
		}
		else {
			return $output;
		}
		
	}