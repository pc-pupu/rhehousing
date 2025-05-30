<?php
		
	function view_waiting_list_page() {
		global $base_path;
		
		$output = '';
		$rows =array();
		$rows = application_waiting_detail();
		
		
		$header = array();
		$header[] = array('data' => 'Applicant Name');
		$header[] = array('data' => 'Application No.');
		$header[] = array('data' => 'Flat Type');
		$header[] = array('data' => 'Computer Serial No');
		//$header[] = array('data' => 'Flat Type Wise Waiting No');
		//$header[] = array('data' => 'Combined Waiting No');
		
		
		
		//$per_page = 10;
		// Initialize the pager
		//$current_page = pager_default_initialize(count($rows), $per_page);
		// Split your list into page sized chunks
		//$chunks = array_chunk($rows, $per_page, TRUE);
		// Show the appropriate items from the list
		//$output = theme('table', array('header' => $header, 'rows' => $chunks[$current_page]));
		// Show the pager
		//$output .= theme('pager', array('quantity',count($rows)));
		
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
			
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'waiting_list').'/images/pdf_icon.png" 
						title="Download Combined Waiting List" alt="PDF Icon">Download Combined Waiting List', 
						'view_waiting_list_pdf/waiting_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => 	
						'_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: 	none; font-size:14px'))).$output;
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
						
			return $output;
		}
		
		
		/*if(count($rows) > 0) {
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'waiting_list').'/images/pdf_icon.png" 
						title="Download Combined Waiting List" alt="PDF Icon">Download Combined Waiting List', 
						'view_waiting_list_pdf/waiting_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => 	
						'_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: 	none; font-size:14px'))).$output;
		}
		else {
			return $output;
		}*/
	
	}